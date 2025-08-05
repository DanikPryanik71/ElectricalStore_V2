#include "MainForm.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	BD::MainForm Mainform;
	const char* conninfo = "host=localhost dbname=My_DB user=postgres password=pg123";
	PGconn* conn = PQconnectdb(conninfo);
	if (PQstatus(conn) == CONNECTION_OK)
		Application::Run(% Mainform);
	else
		MessageBox::Show("Ошибка подключения к базе данных.", "Ошибка подключения");
		PQfinish(conn);
}

   
	