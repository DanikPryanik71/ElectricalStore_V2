#pragma once
#include <libpq-fe.h>
#include <string>
#include <msclr/marshal_cppstd.h>
namespace BD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Ypr_Postavki
	/// </summary>
	public ref class Ypr_Postavki : public System::Windows::Forms::Form
	{
	public:
		Ypr_Postavki(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Ypr_Postavki()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Код;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Название;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Код = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Название = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(183, 50);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(502, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Введите название поставщика, которого необходимо добавить:";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(183, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(502, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"Введите название поставщика, которого необходимо удалить:";
			/*this->textBox1->TextChanged += gcnew System::EventHandler(this, &Ypr_Postavki::textBox1_TextChanged);*/
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(260, 105);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(291, 32);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Список поставщиков";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->Код, this->Название });
			this->dataGridView1->Location = System::Drawing::Point(164, 151);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(509, 255);
			this->dataGridView1->TabIndex = 4;
			// 
			// Код
			// 
			this->Код->HeaderText = L"Код";
			this->Код->MinimumWidth = 6;
			this->Код->Name = L"Код";
			this->Код->Width = 60;
			// 
			// Название
			// 
			this->Название->HeaderText = L"Название";
			this->Название->MinimumWidth = 6;
			this->Название->Name = L"Название";
			this->Название->Width = 102;
			// 
			// Ypr_Postavki
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(829, 418);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Ypr_Postavki";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ypr_Postavki";
			this->Load += gcnew System::EventHandler(this, &Ypr_Postavki::Ypr_Postavki_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Ypr_Postavki_Load(System::Object^ sender, System::EventArgs^ e) {
		PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
		PQsetClientEncoding(conn, "WIN1251");
		if (PQstatus(conn) != CONNECTION_OK) {
			MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQfinish(conn);
			return;
		}
		String^ query = "SELECT p.\"Код\", p.\"Название\",COUNT(*) AS \"Кол-во поставок\" FROM \"postavshik\" p JOIN \"Поставка\" p1 ON p.\"Код\" = p1.\"Поставщик\" GROUP BY p.\"Код\", p.\"Название\" ORDER BY COUNT(*) DESC; ";
		std::string sQuery = msclr::interop::marshal_as<std::string>(query);
		const char* cQuery = sQuery.c_str();
		PGresult* res = PQexec(conn, cQuery);
		if (PQresultStatus(res) != PGRES_TUPLES_OK) {
			MessageBox::Show("Query failed: " + gcnew String(PQresultErrorMessage(res)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQclear(res);
			PQfinish(conn);
			return;
		}

		int rows = PQntuples(res);
		int cols = PQnfields(res);
		dataGridView1->ColumnCount = cols;
		for (int i = 0; i < cols; i++) {
			dataGridView1->Columns[i]->HeaderText = gcnew String(PQfname(res, i));
			dataGridView1->Columns[i]->Width = 50;
		}
		dataGridView1->Rows->Clear();

		for (int i = 0; i < rows; i++)
		{
			array<String^>^ row = gcnew array<String^>(cols);
			for (int j = 0; j < cols; j++) {
				row[j] = gcnew String(PQgetvalue(res, i, j));
			}
			dataGridView1->Rows->Add(row);
		}

		PQclear(res);
		PQfinish(conn);
	}
//private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
//	String^ value;
//	System::String^ str = textBox1->Text;
//	int pos = str->IndexOf(':');
//	value = str->Substring(pos + 1);
//	PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
//	PQsetClientEncoding(conn, "WIN1251");
//	if (PQstatus(conn) != CONNECTION_OK) {
//		MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		PQfinish(conn);
//		return;
//	}
//	String^ query = "BEGIN TRANSACTION; DELETE FROM \"Товар в поставке/заказе\" WHERE \"Номер заказа/поставки\" = (SELECT \"Поставщик\" FROM postavka WHERE \"Поставщик\" =" + value + " LIMIT 1) and \"Тип операции(заказ/поставка)\" = 'Поставка';DELETE FROM postavka WHERE \"Поставщик\" =" + value + ";DELETE FROM postavshik WHERE \"Код\" =" + value + ";COMMIT;";
//	std::string sQuery = msclr::interop::marshal_as<std::string>(query);
//	const char* cQuery = sQuery.c_str();
//	PGresult* res = PQexec(conn, cQuery);
//	
//	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
//		MessageBox::Show("Query failed: " + gcnew String(PQresultErrorMessage(res)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		PQclear(res);
//		PQfinish(conn);
//		return;
//	}
//}
};
}
