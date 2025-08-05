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
	/// Сводка для Ypr_Analiz
	/// </summary>
	public ref class Ypr_Analiz : public System::Windows::Forms::Form
	{
	public:
		Ypr_Analiz(void)
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
		~Ypr_Analiz()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Месяц;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Категория_товаров;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Количество_проданных_товаров;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Сумма_проданных_товаров;




	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Месяц = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Категория_товаров = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Количество_проданных_товаров = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Сумма_проданных_товаров = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(148, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(644, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"продажи по разным категориям товаров (по месяцам)";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Месяц,
					this->Категория_товаров, this->Количество_проданных_товаров, this->Сумма_проданных_товаров
			});
			this->dataGridView1->Location = System::Drawing::Point(60, 62);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(1076, 332);
			this->dataGridView1->TabIndex = 1;
			// 
			// Месяц
			// 
			this->Месяц->HeaderText = L"Месяц";
			this->Месяц->MinimumWidth = 125;
			this->Месяц->Name = L"Месяц";
			this->Месяц->Width = 125;
			// 
			// Категория_товаров
			// 
			this->Категория_товаров->HeaderText = L"Категория_товаров";
			this->Категория_товаров->MinimumWidth = 155;
			this->Категория_товаров->Name = L"Категория_товаров";
			this->Категория_товаров->Width = 166;
			// 
			// Количество_проданных_товаров
			// 
			this->Количество_проданных_товаров->HeaderText = L"Количество_проданных_товаров";
			this->Количество_проданных_товаров->MinimumWidth = 230;
			this->Количество_проданных_товаров->Name = L"Количество_проданных_товаров";
			this->Количество_проданных_товаров->Width = 254;
			// 
			// Сумма_проданных_товаров
			// 
			this->Сумма_проданных_товаров->HeaderText = L"Сумма_проданных_товаров";
			this->Сумма_проданных_товаров->MinimumWidth = 215;
			this->Сумма_проданных_товаров->Name = L"Сумма_проданных_товаров";
			this->Сумма_проданных_товаров->Width = 219;
			// 
			// Ypr_Analiz
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1209, 442);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->label1);
			this->Name = L"Ypr_Analiz";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ypr_Analiz";
			this->Load += gcnew System::EventHandler(this, &Ypr_Analiz::Ypr_Analiz_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Ypr_Analiz_Load(System::Object^ sender, System::EventArgs^ e) {
		String^ value;
		/*if (int::TryParse(textBox1->Text, value))
		{*/
		PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
		PQsetClientEncoding(conn, "WIN1251");
		if (PQstatus(conn) != CONNECTION_OK) {
			MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQfinish(conn);
			return;
		}
		String^ query = "select  DATE_TRUNC('month', \"Дата\")::date as month, \"tovar-katalog\".\"Тип товара\" as \"Категория товаров\", sum(\"Товар в поставке/заказе\".\"Количество товаров\") as \"Кол-во проданных товаров\", sum(\"Товар в поставке/заказе\".\"Количество товаров\" * \"Товар в поставке/заказе\".\"Стоимость единицы товара\") as \"Сумма проданных товаров\" from \"tovar-katalog\" left join \"Товар в поставке/заказе\"on \"tovar-katalog\".Артикул = \"Товар в поставке/заказе\".Артикул join zakaz on zakaz.Номер = \"Товар в поставке/заказе\".\"Номер заказа/поставки\"where \"Товар в поставке/заказе\".\"Тип операции(заказ/поставка)\" = 'Заказ'GROUP BY DATE_TRUNC('month', \"Дата\"), \"tovar-katalog\".\"Тип товара\" ORDER BY  month; ";
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


		//for (int i = 0; i < rows; i++) {
		//	bool found = false;  // Флаг для отслеживания, найдено ли совпадение

		//	for (int j = 0; j < cols; j++) {
		//		String^ cellValue = gcnew String(PQgetvalue(res, i, j));
		//		if (cellValue == value) {
		//			found = true;
		//			break;  // Выходим из внутреннего цикла, если найдено совпадение
		//		}
		//	}

			// Добавляем строку в DataGridView только если было найдено совпадение
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
};
}
