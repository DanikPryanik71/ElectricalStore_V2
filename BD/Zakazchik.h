#pragma once
#include"Status.h"
#include "Artikul.h"
namespace BD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Zakazchik
	/// </summary>
	public ref class Zakazchik : public System::Windows::Forms::Form
	{
	public:
		Zakazchik(void)
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
		~Zakazchik()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn_3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	protected:

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
			this->btn_3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_3
			// 
			this->btn_3->Location = System::Drawing::Point(182, 105);
			this->btn_3->Name = L"btn_3";
			this->btn_3->Size = System::Drawing::Size(244, 23);
			this->btn_3->TabIndex = 0;
			this->btn_3->Text = L"Узнать статус заказа!";
			this->btn_3->UseVisualStyleBackColor = true;
			this->btn_3->Click += gcnew System::EventHandler(this, &Zakazchik::button1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(-1, 1);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(190, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Вернуться на главную";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Zakazchik::button1_Click_1);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::HotTrack;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(510, 1);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(135, 38);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Выход";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Zakazchik::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(182, 163);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(244, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Просмотреть каталог товаров";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Zakazchik::button3_Click);
			// 
			// Zakazchik
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(657, 329);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btn_3);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Zakazchik";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Zakazchik";
			this->ResumeLayout(false);

		}
#pragma endregion
		 private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			 Artikul^ f4 = gcnew Artikul();
			 f4->Owner = this;
			  f4->Show();
			  this->Hide();
		  }
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		
		Status^ f3 = gcnew Status();
		f3->Owner = this;
	f3->Show();
	this->Hide();
	
	}
		 
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}

private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	Owner->Show();
	this->Close();
}
};
}
