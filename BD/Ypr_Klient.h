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
	/// ������ ��� Ypr_Klient
	/// </summary>
	public ref class Ypr_Klient : public System::Windows::Forms::Form
	{
	public:
		Ypr_Klient(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Ypr_Klient()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ���;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ �������;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ �����_�����������_�����;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ �����_����������;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ����������_�������;
	private: System::Windows::Forms::TextBox^ textBox1;

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->��� = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->������� = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->�����_�����������_����� = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->�����_���������� = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->����������_������� = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(269, 117);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(506, 32);
			this->label1->TabIndex = 0;
			this->label1->Text = L"������ �������� �������� ��������";
			this->label1->Click += gcnew System::EventHandler(this, &Ypr_Klient::label1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->���, this->�������,
					this->�����_�����������_�����, this->�����_����������, this->����������_�������
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 162);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(999, 230);
			this->dataGridView1->TabIndex = 1;
			// 
			// ���
			// 
			this->���->HeaderText = L"���";
			this->���->MinimumWidth = 6;
			this->���->Name = L"���";
			this->���->Width = 67;
			// 
			// �������
			// 
			this->�������->HeaderText = L"�������";
			this->�������->MinimumWidth = 6;
			this->�������->Name = L"�������";
			this->�������->Width = 96;
			// 
			// �����_�����������_�����
			// 
			this->�����_�����������_�����->HeaderText = L"�����_�����������_�����";
			this->�����_�����������_�����->MinimumWidth = 6;
			this->�����_�����������_�����->Name = L"�����_�����������_�����";
			this->�����_�����������_�����->Width = 216;
			// 
			// �����_����������
			// 
			this->�����_����������->HeaderText = L"�����_����������";
			this->�����_����������->MinimumWidth = 6;
			this->�����_����������->Name = L"�����_����������";
			this->�����_����������->Width = 163;
			// 
			// ����������_�������
			// 
			this->����������_�������->HeaderText = L"����������_�������";
			this->����������_�������->MinimumWidth = 6;
			this->����������_�������->Name = L"����������_�������";
			this->����������_�������->Width = 176;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(33, 51);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(419, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"������� ��� �������. �������� ���������� �������� � ��:";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Ypr_Klient::textBox1_TextChanged);
			// 
			// Ypr_Klient
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1172, 404);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->label1);
			this->Name = L"Ypr_Klient";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ypr_Klient";
			this->Load += gcnew System::EventHandler(this, &Ypr_Klient::Ypr_Klient_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Ypr_Klient_Load(System::Object^ sender, System::EventArgs^ e) {
		PGconn* conn = PQconnectdb("host=localhost dbname=My_DB user=postgres password=pg123 client_encoding=UTF8");
		PQsetClientEncoding(conn, "WIN1251");
		if (PQstatus(conn) != CONNECTION_OK) {
			MessageBox::Show("Connection to database failed: " + gcnew String(PQerrorMessage(conn)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			PQfinish(conn);
			return;
		}
		String^ query = "SELECT k.\"���\",k.\"�������\",k.\"����� ����������� �����\",k.\"����� ����������\",COUNT(*) AS \"���-�� �������\"FROM \"klient\" k JOIN \"zakaz\" z ON k.\"���\" = z.\"������\" GROUP BY k.\"���\", k.\"�������\", k.\"����� ����������� �����\", k.\"����� ����������\" ORDER BY COUNT(*) DESC; ";
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
		//	bool found = false;  // ���� ��� ������������, ������� �� ����������

		//	for (int j = 0; j < cols; j++) {
		//		String^ cellValue = gcnew String(PQgetvalue(res, i, j));
		//		if (cellValue == value) {
		//			found = true;
		//			break;  // ������� �� ����������� �����, ���� ������� ����������
		//		}
		//	}

			// ��������� ������ � DataGridView ������ ���� ���� ������� ����������
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
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
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
	String^ query = "delete from klient where ��� =" + value + "; ";
	std::string sQuery = msclr::interop::marshal_as<std::string>(query);
	const char* cQuery = sQuery.c_str();
	PGresult* res = PQexec(conn, cQuery);
	/*if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		MessageBox::Show("Query failed: " + gcnew String(PQresultErrorMessage(res)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		PQclear(res);
		PQfinish(conn);
		return;
	}*/

	int rows = PQntuples(res);
	int cols = PQnfields(res);
	dataGridView1->ColumnCount = cols;
	for (int i = 0; i < cols; i++) {
		dataGridView1->Columns[i]->HeaderText = gcnew String(PQfname(res, i));
		dataGridView1->Columns[i]->Width = 50;
	}
	dataGridView1->Rows->Clear();


	for (int i = 0; i < rows; i++) {
		bool found = false;  // ���� ��� ������������, ������� �� ����������

		for (int j = 0; j < cols; j++) {
			String^ cellValue = gcnew String(PQgetvalue(res, i, j));
			if (cellValue == value) {
				found = true;
				break;  // ������� �� ����������� �����, ���� ������� ����������
			}
		}

		// ��������� ������ � DataGridView ������ ���� ���� ������� ����������
		if (found) {
			array<String^>^ row = gcnew array<String^>(cols);
			for (int j = 0; j < cols; j++) {
				row[j] = gcnew String(PQgetvalue(res, i, j));
			}
			dataGridView1->Rows->Add(row);
		}
	}


	PQclear(res);
	PQfinish(conn);
	Ypr_Klient_Load(sender, e);
}
};
}
