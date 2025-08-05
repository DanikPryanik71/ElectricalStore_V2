#pragma once
#include <libpq-fe.h>
#include <msclr/marshal_cppstd.h>
#include<cstdlib>
#include <vector>
#include <string>
#include"Sotrudnik_2.h"
namespace BD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class Sotrudnik : public System::Windows::Forms::Form
	{
	public:
		Sotrudnik(void)
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
		~Sotrudnik()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(181, 109);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(363, 22);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Введите свое ФИО:";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Sotrudnik::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(31, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Назад";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Sotrudnik::button1_Click);
			// 
			// Sotrudnik
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(745, 354);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Sotrudnik";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ value;
		/*if (int::TryParse(textBox1->Text, value))
		{*/
		System::String^ str = textBox1->Text;
		int pos = str->IndexOf(':');
		value = str->Substring(pos + 1);
		PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
		PQsetClientEncoding(conn, "WIN1251");
		if (PQstatus(conn) != CONNECTION_OK) {
			MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQfinish(conn);
			return;
		}
		if (PQstatus(conn) != CONNECTION_OK) {
			MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQfinish(conn);
			return;
		}
		String^ query = "select ФИО from sotrudnik_magazina";
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
		/*dataGridView2->ColumnCount = cols;
		for (int i = 0; i < cols; i++) {
			dataGridView2->Columns[i]->HeaderText = gcnew String(PQfname(res, i));
			dataGridView2->Columns[i]->Width = 50;
		}
		dataGridView2->Rows->Clear();*/


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
				MessageBox::Show("Подтверждение личности прошло успешно! " + gcnew 
					String(PQresultErrorMessage(res)), "Ok",
					MessageBoxButtons::OK);
				Sotrudnik_2^ f4 = gcnew Sotrudnik_2();
				f4->Owner = this;
				f4->Show();
				Sotrudnik::Hide();

				//f4->Show();
				//Sotrudnik::Hide();
				}
				/*dataGridView2->Rows->Add(row);*/
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
