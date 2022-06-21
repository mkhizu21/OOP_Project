#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <exception>
#include <windows.h>
#include "vaccine_system.h"
using namespace std;




string banner = R"(
                     __     __             _               ____            _        _ 
                     \ \   / /_ _  ___ ___(_)_ __   ___   |  _ \ ___  _ __| |_ __ _| |
                      \ \ / / _` |/ __/ __| | '_ \ / _ \  | |_) / _ \| '__| __/ _` | |
                       \ V / (_| | (_| (__| | | | |  __/  |  __/ (_) | |  | || (_| | |
                        \_/ \__,_|\___\___|_|_| |_|\___|  |_|   \___/|_|   \__\__,_|_|
                                                                 

)";



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
	SA->create_admin();
	SA->delete_admin();
	SA->update_admin();
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
					//admin_page(username);
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
	system("Color F0");
	string a, b;

	login_page(a, b);

	login_process(a, b);

	



	

	system("pause");
	return 0;
}