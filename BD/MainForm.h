#pragma once
#include <iostream>
#include <libpq-fe.h>
#include <msclr/marshal_cppstd.h>
#include "Zakazchik.h"
#include"Sotrudnik.h"
#include <string>
#include <cliext/vector >
#include "Yprav_Main.h"
namespace BD {
	using namespace msclr;
	using namespace cliext;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm()
		{
			InitializeComponent();

		}


	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label3;




	private: System::Windows::Forms::Button^ btn_1;
	private: System::Windows::Forms::Button^ btn_2;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Button^ button3;





































	protected:

	private:

		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->btn_1 = (gcnew System::Windows::Forms::Button());
			this->btn_2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(195, 82);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(325, 32);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Подключение успешно!";
			// 
			// btn_1
			// 
			this->btn_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_1->Location = System::Drawing::Point(21, 194);
			this->btn_1->Name = L"btn_1";
			this->btn_1->Size = System::Drawing::Size(166, 32);
			this->btn_1->TabIndex = 2;
			this->btn_1->Text = L"Заказчик";
			this->btn_1->UseVisualStyleBackColor = true;
			this->btn_1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// btn_2
			// 
			this->btn_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_2->Location = System::Drawing::Point(526, 194);
			this->btn_2->Name = L"btn_2";
			this->btn_2->Size = System::Drawing::Size(195, 32);
			this->btn_2->TabIndex = 3;
			this->btn_2->Text = L"Сотрудник магазина";
			this->btn_2->UseVisualStyleBackColor = true;
			this->btn_2->Click += gcnew System::EventHandler(this, &MainForm::btn_2_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 38);
			this->button1->TabIndex = 4;
			this->button1->Text = L"X";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_1);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(251, 194);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(246, 32);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Управляющий бизнес-процессами";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(733, 367);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btn_2);
			this->Controls->Add(this->btn_1);
			this->Controls->Add(this->label3);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion

		Void ExecuteQuery(String^ query, DataGridView^ dataGridView) {
			
			
		}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	
		
		
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	Zakazchik^ f2 = gcnew Zakazchik();
	f2->Owner = this;
	f2->Show();
	MainForm::Hide();
	/*ExecuteQuery("SELECT * FROM public.status_zakaza", dataGridView1);*/
}
private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	this->Close();

}
private: System::Void btn_2_Click(System::Object^ sender, System::EventArgs^ e) {
	Sotrudnik^ f3 = gcnew Sotrudnik();
	f3->Owner = this;
	f3->Show();
	MainForm::Hide();
}
//private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
//	PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
//	PQsetClientEncoding(conn, "WIN1251");
//	if (PQstatus(conn) != CONNECTION_OK) {
//		MessageBox::Show("Connection to database failed yeban: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		PQfinish(conn);
//		return;
//	}
//	
//	for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
//	{
//		
//	}
//
//
//	int* ids = new int[dataGridView1->Rows->Count];
//	/*std::vector<System::String^> statuses(dataGridView1->Rows->Count);*/
//	
//	std::vector<std::string> statuses(dataGridView1->Rows->Count);
//	
//	/*std::string statuses = new [dataGridView1->Rows->Count];*/
//	/*System::String^ statuses = gcnew System::String ^ [dataGridView1->Rows->Count];
//	System::String^ [] statuses = gcnew System::String ^ [dataGridView1->Rows->Count];*/
//	std::string* dates = new std::string[dataGridView1->Rows->Count];
//	for (int i = 0; i < dataGridView1->Rows->Count-1; i++)
//	{
//		// Получение ячеек для каждой строки
//		DataGridViewRow^ row = dataGridView1->Rows[i];
//
//		// Получение значений ячеек
//		ids[i] = Convert::ToInt32(row->Cells["Number"]->Value);                          //statuses[i] = msclr::interop::marshal_as<std::string>(row->Cells["Статус заказа"]->Value);
//		statuses[i] = msclr::interop::marshal_as<std::string>(row->Cells["Status"]->Value->ToString());                                                            /*dates[i] = msclr::interop::marshal_as<std::string>(row->Cells["Date"]->Value);*/
//		
//	}
//	conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
//	PQsetClientEncoding(conn, "WIN1251");
//	if (PQstatus(conn) != CONNECTION_OK)
//	{
//
//		MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		/*std::cerr << "Ошибка подключения к базе данных: " << PQerrorMessage(conn) << std::endl;*/
//		PQfinish(conn);
//		return;
//	}
//	int n = 7;
//	for (int i = 0; i < dataGridView1->Rows->Count-1; i++)
//	{
//		/*String^ query = "INSERT INTO status_zakaza(\"Номер\", \"Статус\", \"Дата\") VALUES(" + Convert::ToString(ids[i])+"," + gcnew String(statuses[i]) + ", '2024-04-09')";*/
//		/*String^ query = "INSERT INTO status_zakaza(\"Номер\", \"Статус\", \"Дата\") VALUES(" + Convert::ToString(ids[i]) + "," + statuses[i]->ToString() + ", '2024-04-09')";*/
//		String^ query = "INSERT INTO status_zakaza(\"Номер\", \"Статус\", \"Дата\") VALUES(" +
//			Convert::ToString(ids[i]) + ", '" + gcnew String(statuses[i].c_str()) + "', '2024-04-09')";
//	
//		std::string sQuery = msclr::interop::marshal_as<std::string>(query);
//		const char* cQuery = sQuery.c_str();
//		PGresult* res = PQexec(conn, cQuery);
//		/*if (PQresultStatus(res) != PGRES_TUPLES_OK) {
//			MessageBox::Show("Query failed: " + gcnew String(PQresultErrorMessage(res)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//			PQclear(res);
//			PQfinish(conn);
//			return;
//		}*/
//		// Подготовка запроса
//		//String^ query = "SELECT * FROM public.status_zakaza";
//		//std::string sQuery = msclr::interop::marshal_as<std::string>(query);
//		//const char* cQuery = sQuery.c_str();
//		//// Выполнение запроса
//		//PGresult* res = PQexec(conn, cQuery.c_str());
//
//		//if (PQresultStatus(res) != PGRES_COMMAND_OK)
//		//{
//		//	MessageBox::Show("Connection to database failed yebanishe : " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		//	/*std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;*/
//		//	PQclear(res);
//		//	PQfinish(conn);
//		//	return;
//		//}
//
//		PQclear(res);
//	}
//
//	PQfinish(conn);
//
//}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Yprav_Main^ f4 = gcnew Yprav_Main();
	f4->Owner = this;
	f4->Show();
	MainForm::Hide();
}
};
};
