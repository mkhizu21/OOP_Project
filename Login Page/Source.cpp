#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <exception>
#include <windows.h>
#include <chrono>
#include <thread>
#include "vaccine_system.h"
using namespace std;




string banner = R"(
                     __     __             _               ____            _        _ 
                     \ \   / /_ _  ___ ___(_)_ __   ___   |  _ \ ___  _ __| |_ __ _| |
                      \ \ / / _` |/ __/ __| | '_ \ / _ \  | |_) / _ \| '__| __/ _` | |
                       \ V / (_| | (_| (__| | | | |  __/  |  __/ (_) | |  | || (_| | |
                        \_/ \__,_|\___\___|_|_| |_|\___|  |_|   \___/|_|   \__\__,_|_|
                                                                 

)";

string banner0 = R"(

                     __     __ 
                     \ \   / /_
                      \ \ / / _
                       \ V / (_
                        \_/ \__
                                                                 

)";
string banner1 = R"(

                     __     __             
                     \ \   / /_ _  ___ ___(
                      \ \ / / _` |/ __/ __|
                       \ V / (_| | (_| (__|
                        \_/ \__,_|\___\___|
                                                                 

)";
string banner2 = R"(

                     __     __             _    
                     \ \   / /_ _  ___ ___(_)_ _
                      \ \ / / _` |/ __/ __| | '_
                       \ V / (_| | (_| (__| | | 
                        \_/ \__,_|\___\___|_|_| 
                                                                 

)";
string banner3 = R"(

                     __     __             _           
                     \ \   / /_ _  ___ ___(_)_ __   ___
                      \ \ / / _` |/ __/ __| | '_ \ / _ 
                       \ V / (_| | (_| (__| | | | |  __
                        \_/ \__,_|\___\___|_|_| |_|\___
                                                                 

)";
string banner4 = R"(

                     __     __             _               ____     
                     \ \   / /_ _  ___ ___(_)_ __   ___   |  _ \ ___
                      \ \ / / _` |/ __/ __| | '_ \ / _ \  | |_) / _ 
                       \ V / (_| | (_| (__| | | | |  __/  |  __/ (_)
                        \_/ \__,_|\___\___|_|_| |_|\___|  |_|   \___
                                                                 

)";
string banner5 = R"(

                     __     __             _               ____           
                     \ \   / /_ _  ___ ___(_)_ __   ___   |  _ \ ___  _ __
                      \ \ / / _` |/ __/ __| | '_ \ / _ \  | |_) / _ \| '__
                       \ V / (_| | (_| (__| | | | |  __/  |  __/ (_) | |  
                        \_/ \__,_|\___\___|_|_| |_|\___|  |_|   \___/|_|  
                                                                 

)";

void wait(int x = 200)
{
	this_thread::sleep_for(chrono::milliseconds(x));
}

void loading_animation()
{
	wait(1000);
	system("clear");
	cout << "\n\n" << banner0;
	wait();
	system("clear");
	cout << "\n\n" << banner1;
	wait();
	system("clear");
	cout << "\n\n" << banner2;
	wait();
	system("clear");
	cout << "\n\n" << banner3;
	wait();
	system("clear");
	cout << "\n\n" << banner4;
	wait();
	system("clear");
	cout << "\n\n" << banner5;
	wait();
	system("clear");
	cout << "\n\n" << banner;

	for (int i = 0; i < 5; i++)
	{
		system("Color F0");
		wait();
		system("Color 0F");
		wait();
	}

}


void heading(string msg)
{
	system("cls");
	cout << banner;
	print_spaces();
	cout << setfill('-') << setw(10) << "";
	cout << msg;
	cout << setfill('-') << setw(10) << "\n\n";
}

void print_login(string username, string pass, int count)
{
	system("cls");
	cout << banner;

	print_spaces();
	cout << setfill('-') << setw(10) << "";
	cout << "LOGIN PAGE";
	cout << setfill('-') << setw(10) << "\n\n";


	print_spaces();
	cout << "Username: ";
	SetConsoleTextAttribute(h, 241);
	cout << username;
	SetConsoleTextAttribute(h, 240);

	cout << "\n";
	print_spaces();
	cout << "Password: ";
	for (int i = 0; i < count; i++)
	{
		SetConsoleTextAttribute(h, 241);
		cout << "*";
		SetConsoleTextAttribute(h, 240);
	}
}

void login_page(string& username, string& pass)
{
	char pass_char;
	int count = 0;
	cout << banner;

	print_spaces();
	cout <<  setfill('-') << setw(10) << "";
	cout << "LOGIN PAGE";
	cout << setfill('-') << setw(10) << "\n\n" ;


	print_spaces();
	try
	{
		cout << "Username: ";
		SetConsoleTextAttribute(h, 241);
		cin >> username;
		SetConsoleTextAttribute(h, 240);

		if (!is_valid_username(username))
		{
			throw invalid_username();
		}

		print_spaces();
		cout << "Password: ";
		pass_char = _getch();
		while (pass_char != '\r')
		{
			cout << pass_char;
			pass.push_back(pass_char);
			count++;
			print_login(username, pass, count);
			pass_char = _getch();
		}

		if (!is_valid_password(pass))
		{
			throw invalid_password();
		}
	}
	catch (const exception& e)
	{
		SetConsoleTextAttribute(h, 252);
		print_spaces();
		cout << "[!] Exception: " << e.what() << endl;
		SetConsoleTextAttribute(h, 240);
	}
	

	cout << "\n" << pass << endl;

}

void super_admin_page(string username)
{
	super_admin* SA = Filing::login_super_admin(username);
	SA->output();
	SA->display_admin();
	SA->create_admin();
}

void admin_page(string username)
{
	bool loop = true;
	char choice;
	admin* ADMIN = super_admin::admin_obj(username);
	while (loop)
	{
		heading("ADMIN MENU");
		
		print_spaces();
		cout << "1. Add Company\n";
		print_spaces();
		cout << "2. Remove Company\n";
		print_spaces();
		cout << "3. Display Companies\n";
		print_spaces();
		cout << "4. Add Warehouse\n";
		print_spaces();
		cout << "5. Display Warehouses\n";
		print_spaces();
		cout << "6. Purchase Vaccine\n";
		print_spaces();
		cout << "7. Admin Details\n";
		print_spaces();
		cout << "8. Exit\n";
		
		print_spaces();
		cout << "ENTER ANY OPTION";
		choice = _getch();

		switch (choice)
		{
		case '1':
			heading("ADD COMPANY");

			ADMIN->add_company();
			break;

		case '2':
			heading("REMOVE COMPANY");
			
			ADMIN->delete_company();
			break;


		case '3':
			heading("COMPANIES");

			ADMIN->display_company();
			break;

		case '4':
			heading("ADD WAREHOUSE");

			ADMIN->add_warehouse();
			break;

			
		case '5':
			heading("WAREHOUSES");

			ADMIN->display_warehouse();
			break;

		case '6':
			heading("PURCHASE VACCINE");

			ADMIN->purchase_vaccine();
			break;

		case '7':
			heading("ADMIN DETAILS");

			ADMIN->adminOutput();

			break;

		default:
			print_error("\n\n[!] EXITING ADMIN MENU [!]\n");
			
			loop = false;
			break;
		}

		cout << "\n\nPRESS ANY KEY TO CONTINUE";
		_getch();

	}
	

}

void login_process(string username, string pass)
{
	string modes[5] = { "SA", "AD", "DC", "FD", "GO" };
	string mode = username.substr(0, 2);
	try
	{
		if (mode == modes[0]) // Super Admin
		{
			if (Filing::find_super_admin(username))
			{
				if (Filing::is_valid_login_super_admin(username, pass))
				{
					super_admin_page(username);
				}
				else
				{
					//throw wrong_password();
				}
			}
			else
			{
				//throw unregistered_username();
			}
		}
		else if (mode == modes[1]) // Admin
		{
			if (Filing::find_admin(username))
			{
				if (Filing::is_valid_login_admin(username, pass))
				{
					admin_page(username);
				}
				else
				{
					//throw wrong_password();
				}
			}
			else
			{
				//throw unregistered_username();
			}
		}
		else if (mode == modes[2]) // Doctor
		{
			if (Filing::find_doctor(username))
			{
				if (Filing::is_valid_login_doctor(username, pass))
				{
					//doctor_page(username);
				}
				else
				{
					//throw wrong_password();
				}
			}
			else
			{
				//throw unregistered_username();
			}
		}
		else if (mode == modes[3]) // Front Desk Officer
		{
			if (Filing::find_fdo(username))
			{
				if (Filing::is_valid_login_fdo(username, pass))
				{
					//fdo_page(username);
				}
				else
				{
					//throw wrong_password();
				}
			}
			else
			{
				//throw unregistered_username();
			}
		}
		else if (mode == modes[4]) // Government Offcial
		{
			if (Filing::find_gov_off(username))
			{
				if (Filing::is_valid_login_gov_off(username, pass))
				{
					//gov_off_page(username);
				}
				else
				{
					//throw wrong_password();
				}
			}
			else
			{
				//throw unregistered_username();
			}
		}

	}
	catch (const exception& e)
	{
		SetConsoleTextAttribute(h, 252);
		print_spaces();
		cout << "[!] Exception: " << e.what() << endl;
		SetConsoleTextAttribute(h, 240);
	}
		
}

int main()
{
	
	string a, b;

	Filing::login_super_admin("SA90530");

	system("cls");
	loading_animation();
	system("cls");
	system("Color F0");
	login_page(a, b);

	login_process(a, b);

	



	

	system("pause");
	return 0;
}