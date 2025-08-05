#pragma once
#include "Ypr_Analiz.h"
#include "Ypr_Klient.h"
#include "Ypr_Postavki.h"
#include "Ypr_Sotr.h"
namespace BD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Yprav_Main
	/// </summary>
	public ref class Yprav_Main : public System::Windows::Forms::Form
	{
	public:
		Yprav_Main(void)
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
		~Yprav_Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(76, 266);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(514, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Анализ продаж по категориям товаров (по месяцам)";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Yprav_Main::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(76, 169);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(514, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Количество заказов и их сумма всего (по годам/месяцам)";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(76, 221);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(514, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Количество заказов и их сумма за определенный год/месяц";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(76, 35);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(514, 23);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Список лояльных клиентов магазина";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Yprav_Main::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(76, 78);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(514, 23);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Список сотрудников магазина";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(76, 125);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(514, 23);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Список поставщиков магазина";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Yprav_Main::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(12, 6);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Назад";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Yprav_Main::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(76, 317);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(514, 23);
			this->button8->TabIndex = 7;
			this->button8->Text = L"Уволить сотрудника";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Yprav_Main::button8_Click);
			// 
			// Yprav_Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(659, 388);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Yprav_Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Yprav_Main";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Ypr_Analiz^ f1 = gcnew Ypr_Analiz();
		f1->Show();
		Yprav_Main::Hide();
	}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	Ypr_Klient^ f2 = gcnew Ypr_Klient();
	f2->Show();
	Yprav_Main::Hide();
}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	Ypr_Postavki^ f3 = gcnew Ypr_Postavki();
	f3->Show();
	Yprav_Main::Hide();
}
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	Owner->Show();
	this->Close();
}
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	Ypr_Sotr^ f4 = gcnew Ypr_Sotr();
	f4->Show();
	Yprav_Main::Hide();
}
};
}
