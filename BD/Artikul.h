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
	/// Сводка для Artikul
	/// </summary>
	public ref class Artikul : public System::Windows::Forms::Form
	{
	public:
		Artikul(void)
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
		~Artikul()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	protected:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ btn_exit3;
	private: System::Windows::Forms::Button^ button1;

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
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->btn_exit3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView2
			// 
			this->dataGridView2->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Column4,
					this->Column5, this->Column6, this->Column7
			});
			this->dataGridView2->Location = System::Drawing::Point(95, 120);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->RowTemplate->Height = 24;
			this->dataGridView2->Size = System::Drawing::Size(624, 150);
			this->dataGridView2->TabIndex = 6;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Артикул";
			this->Column4->MinimumWidth = 90;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Название";
			this->Column5->MinimumWidth = 100;
			this->Column5->Name = L"Column5";
			this->Column5->Width = 125;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Тип товара";
			this->Column6->MinimumWidth = 145;
			this->Column6->Name = L"Column6";
			this->Column6->Width = 195;
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"Гарантия";
			this->Column7->MinimumWidth = 40;
			this->Column7->Name = L"Column7";
			this->Column7->Width = 125;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(95, 71);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(195, 22);
			this->textBox2->TabIndex = 7;
			this->textBox2->Text = L"Введите артикул товара:";
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Artikul::textBox2_TextChanged);
			// 
			// btn_exit3
			// 
			this->btn_exit3->Font = (gcnew System::Drawing::Font(L"Microsoft New Tai Lue", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_exit3->Location = System::Drawing::Point(646, 10);
			this->btn_exit3->Name = L"btn_exit3";
			this->btn_exit3->Size = System::Drawing::Size(148, 45);
			this->btn_exit3->TabIndex = 8;
			this->btn_exit3->Text = L"Выход";
			this->btn_exit3->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 10);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Назад";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Artikul::button1_Click);
			// 
			// Artikul
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(806, 319);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btn_exit3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->dataGridView2);
			this->Name = L"Artikul";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Artikul";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ value;
		/*if (int::TryParse(textBox1->Text, value))
		{*/
		System::String^ str = textBox2->Text;
		int pos = str->IndexOf(':');
		value = str->Substring(pos + 1);
		PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
		PQsetClientEncoding(conn, "WIN1251");
		if (PQstatus(conn) != CONNECTION_OK) {
			MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQfinish(conn);
			return;
		}
		String^ query = "SELECT * FROM public.\"tovar-katalog\"";
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
		dataGridView2->ColumnCount = cols;
		for (int i = 0; i < cols; i++) {
			dataGridView2->Columns[i]->HeaderText = gcnew String(PQfname(res, i));
			dataGridView2->Columns[i]->Width = 50;
		}
		dataGridView2->Rows->Clear();


		for (int i = 0; i < rows; i++) {
			bool found = false;  // Флаг для отслеживания, найдено ли совпадение

			for (int j = 0; j < cols; j++) {
				String^ cellValue = gcnew String(PQgetvalue(res, i, j));
				if (cellValue == value) {
					found = true;
					break;  // Выходим из внутреннего цикла, если найдено совпадение
				}
			}

			// Добавляем строку в DataGridView только если было найдено совпадение
			if (found) {
				array<String^>^ row = gcnew array<String^>(cols);
				for (int j = 0; j < cols; j++) {
					row[j] = gcnew String(PQgetvalue(res, i, j));
				}
				dataGridView2->Rows->Add(row);
			}
		}


		PQclear(res);
		PQfinish(conn);
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	Owner->Show();
	this->Close();
}
};
}
