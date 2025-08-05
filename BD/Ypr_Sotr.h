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
	/// Сводка для Ypr_Sotr
	/// </summary>
	public ref class Ypr_Sotr : public System::Windows::Forms::Form
	{
	public:
		Ypr_Sotr(void)
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
		~Ypr_Sotr()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Код;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ФИО;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Номер_телефона;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Должность;
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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Код = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ФИО = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Номер_телефона = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Должность = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Код, this->ФИО,
					this->Номер_телефона, this->Должность
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 156);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(673, 264);
			this->dataGridView1->TabIndex = 0;
			// 
			// Код
			// 
			this->Код->HeaderText = L"Код";
			this->Код->MinimumWidth = 6;
			this->Код->Name = L"Код";
			this->Код->Width = 60;
			// 
			// ФИО
			// 
			this->ФИО->HeaderText = L"ФИО";
			this->ФИО->MinimumWidth = 6;
			this->ФИО->Name = L"ФИО";
			this->ФИО->Width = 67;
			// 
			// Номер_телефона
			// 
			this->Номер_телефона->HeaderText = L"Номер_телефона";
			this->Номер_телефона->MinimumWidth = 6;
			this->Номер_телефона->Name = L"Номер_телефона";
			this->Номер_телефона->Width = 152;
			// 
			// Должность
			// 
			this->Должность->HeaderText = L"Должность";
			this->Должность->MinimumWidth = 6;
			this->Должность->Name = L"Должность";
			this->Должность->Width = 107;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(249, 100);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(213, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Добавить сотрудника";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Ypr_Sotr::button1_Click);
			// 
			// Ypr_Sotr
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(697, 452);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"Ypr_Sotr";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ypr_Sotr";
			this->Load += gcnew System::EventHandler(this, &Ypr_Sotr::Ypr_Sotr_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Ypr_Sotr_Load(System::Object^ sender, System::EventArgs^ e) {
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
		String^ query = "select * from sotrudnik_magazina ";
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
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
	PQsetClientEncoding(conn, "WIN1251");
	if (PQstatus(conn) != CONNECTION_OK) {
		MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		PQfinish(conn);
		return;
	}

	for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
	{

	}


	int* ids = new int[dataGridView1->Rows->Count];
	/*std::vector<System::String^> statuses(dataGridView1->Rows->Count);*/

	std::vector<std::string> fio(dataGridView1->Rows->Count);
	std::vector<std::string> number(dataGridView1->Rows->Count);
	std::vector<std::string> doljnost(dataGridView1->Rows->Count);
	/*std::string statuses = new [dataGridView1->Rows->Count];*/
	/*System::String^ statuses = gcnew System::String ^ [dataGridView1->Rows->Count];
	System::String^ [] statuses = gcnew System::String ^ [dataGridView1->Rows->Count];*/
	std::string* dates = new std::string[dataGridView1->Rows->Count];
	for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
	{
		// Получение ячеек для каждой строки
		DataGridViewRow^ row = dataGridView1->Rows[i];

		// Получение значений ячеек
		ids[i] = Convert::ToInt32(row->Cells["Код"]->Value);                          //statuses[i] = msclr::interop::marshal_as<std::string>(row->Cells["Статус заказа"]->Value);
		fio[i] = msclr::interop::marshal_as<std::string>(row->Cells["ФИО"]->Value->ToString());
		number[i] = msclr::interop::marshal_as<std::string>(row->Cells["Номер_телефона"]->Value->ToString());
		doljnost[i] = msclr::interop::marshal_as<std::string>(row->Cells["Должность"]->Value->ToString());/*dates[i] = msclr::interop::marshal_as<std::string>(row->Cells["Date"]->Value);*/

	}
	conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
	PQsetClientEncoding(conn, "WIN1251");
	if (PQstatus(conn) != CONNECTION_OK)
	{

		MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		/*std::cerr << "Ошибка подключения к базе данных: " << PQerrorMessage(conn) << std::endl;*/
		PQfinish(conn);
		return;
	}
	int n = 7;
	for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
	{
		/*String^ query = "INSERT INTO status_zakaza(\"Номер\", \"Статус\", \"Дата\") VALUES(" + Convert::ToString(ids[i])+"," + gcnew String(statuses[i]) + ", '2024-04-09')";*/
		/*String^ query = "INSERT INTO status_zakaza(\"Номер\", \"Статус\", \"Дата\") VALUES(" + Convert::ToString(ids[i]) + "," + statuses[i]->ToString() + ", '2024-04-09')";*/
		String^ query = "INSERT INTO public.sotrudnik_magazina( \"Код\", \"ФИО\", \"Номер_телефона\", \"Должность\") VALUES(" + Convert::ToString(ids[i]) + ", '" + gcnew String(fio[i].c_str())+"', '" + gcnew String(number[i].c_str()) + "', '" + gcnew String(doljnost[i].c_str()) + "')";

		std::string sQuery = msclr::interop::marshal_as<std::string>(query);
		const char* cQuery = sQuery.c_str();
		PGresult* res = PQexec(conn, cQuery);
		/*if (PQresultStatus(res) != PGRES_TUPLES_OK) {
			MessageBox::Show("Query failed: " + gcnew String(PQresultErrorMessage(res)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQclear(res);
			PQfinish(conn);
			return;
		}*/
		// Подготовка запроса
		//String^ query = "SELECT * FROM public.status_zakaza";
		//std::string sQuery = msclr::interop::marshal_as<std::string>(query);
		//const char* cQuery = sQuery.c_str();
		//// Выполнение запроса
		//PGresult* res = PQexec(conn, cQuery.c_str());

		//if (PQresultStatus(res) != PGRES_COMMAND_OK)
		//{
		//	MessageBox::Show("Connection to database failed yebanishe : " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		//	/*std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;*/
		//	PQclear(res);
		//	PQfinish(conn);
		//	return;
		//}

		PQclear(res);
	}

	PQfinish(conn);

}
};
}
