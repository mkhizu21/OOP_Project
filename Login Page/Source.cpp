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
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner0;
	wait();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner1;
	wait();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner2;
	wait();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner3;
	wait();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner4;
	wait();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner5;
	wait();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n" << banner;

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
	bool loop = true;
	char choice;
	super_admin* SA = Filing::login_super_admin(username);


	while (loop)
	{
		heading("SUPER ADMIN MENU");

		print_spaces();
		cout << "1. Create Admin\n";
		print_spaces();
		cout << "2. Remove Admin\n";
		print_spaces();
		cout << "3. Update Admin\n";
		print_spaces();
		cout << "4. Display Admins\n";
		print_spaces();
		cout << "5. Create FDO\n";
		print_spaces();
		cout << "6. Display FDOs\n";
		print_spaces();
		cout << "7. Create Government Official\n";
		print_spaces();
		cout << "8. Remove Government Official\n";
		print_spaces();
		cout << "9. Update Government Official\n";
		print_spaces();
		cout << "0. Display Government Official\n";
		print_spaces();
		cout << "A. Exit\n";

		print_spaces();
		cout << "ENTER ANY OPTION";
		choice = _getch();

		switch (choice)
		{
		case '1':
			heading("CREATE ADMIN");

			SA->create_admin();
			break;

		case '2':
			heading("REMOVE ADMIN");

			SA->delete_admin();
			break;


		case '3':
			heading("UPDATE ADMIN");

			SA->update_admin();
			break;

		case '4':
			heading("DISPLAY ADMINs");

			SA->display_admin();
			break;


		case '5':
			heading("CREATE FDO");

			SA->create_fdo();
			break;

		case '6':
			heading("DISPLAY FDOs");

			SA->display_fdo();
			break;

		case '7':
			heading("CREATE GOVERNMENT OFFICIAL");

			SA->create_gov_off();
			break;

		case '8':
			heading("REMOVE GOVERNMENT OFFICIAL");

			SA->delete_gov_off();
			break;


		case '9':
			heading("UPDATE GOVERNMENT OFFICIAL");

			SA->update_gov_off();
			break;

		case '0':
			heading("DISPLAY GOVERNMENT OFFICIAL");

			SA->display_gov_off();
			break;
		

		case 'a':
			print_error("\n\n[!] EXITING SUPER ADMIN MENU [!]\n");

			loop = false;
			break;

		default:
			print_error("\n\n[!] INVALID INPUT [!]\n");
			break;
		}

		cout << "\n\nPRESS ANY KEY TO CONTINUE";
		_getch();

	}
}

void admin_page(string username)
{
	bool loop = true;
	char choice;
	admin* ADMIN = nullptr;
	ADMIN = super_admin::admin_obj(username);
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

		case '8':
			print_error("\n\n[!] EXITING ADMIN MENU [!]\n");
			
			loop = false;
			break;

		default:
			print_error("\n\n[!] INVALID INPUT [!]\n");
			break;
		}

		cout << "\n\nPRESS ANY KEY TO CONTINUE";
		_getch();

	}
	

}

void fdo_page(string username)
{

	bool loop = true;
	char choice;
	fdo* FDO = nullptr;
	FDO = super_admin::fdo_obj(username);

	while (loop)
	{
		heading("FDO MENU");

		print_spaces();
		cout << "1. Get Vaccine\n";
		print_spaces();
		cout << "2. Display Vaccines\n";
		print_spaces();
		cout << "3. Vaccinate Citizen\n";
		print_spaces();
		cout << "4. Exit\n";

		print_spaces();
		cout << "ENTER ANY OPTION";
		choice = _getch();

		switch (choice)
		{
		case '1':
			heading("GET VACCINE");

			FDO->get_vaccine();
			break;

		case '2':
			heading("DISPLAY VACCINES");

			FDO->output_vaccines();
			break;

		case '3':
			heading("VACCINATE CITIZEN");

			FDO->vacinate_citizen();
			break;


		case '4':
			print_error("\n\n[!] EXITING FDO MENU [!]\n");

			loop = false;
			break;

		default:
			print_error("\n\n[!] INVALID INPUT [!]\n");
			break;
		}

		cout << "\n\nPRESS ANY KEY TO CONTINUE";
		_getch();

	}
}

void gov_off_page(string username)
{
	bool loop = true;
	char choice;
	gov_off* GOV = nullptr;
	GOV = super_admin::gov_off_obj(username);

	while (loop)
	{
		heading("GOVERNEMNT OFFICIAL MENU");

		print_spaces();
		cout << "1. Display Government Official details\n";
		print_spaces();
		cout << "2. Show percentage of vaccinated population\n";
		print_spaces();
		cout << "3. Show percentage of partially vaccinated population\n";
		print_spaces();
		cout << "4. Show fully vaccinated citizens \n";
		print_spaces();
		cout << "5. Show partially vaccinated citizens \n";
		print_spaces();
		cout << "6. Show citizens with specific vaccine ID\n";
		print_spaces();
		cout << "7. Display graph of vaccinated & partially vaccinated citizens\n";
		print_spaces();
		cout << "8. Exit\n";

		print_spaces();
		cout << "ENTER ANY OPTION";
		choice = _getch();

		switch (choice)
		{
		case '1':
			heading("GOVERNMENT OFFICIAL DETAILS");
			cout << "\n\n";
			GOV->output();
			break;

		case '2':
			heading("PERCENTAGE OF VACCINATED POPULATION");
			cout << "\n\n";
			GOV->percentage_vac_population();
			break;

		case '3':
			heading("PERCENTAGE OF PARTIALLY VACCINATED POPULATION");
			cout << "\n\n";
			GOV->percentage_partially_vac_population();
			break;

		case '4':
			heading("FULLY VACCINATED CITIZENS");
			cout << "\n\n";
			GOV->display_vac_population();
			break;

		case '5':
			heading("PARTIALLY VACCINATED CITIZENS");
			cout << "\n\n";
			GOV->display_partially_vac_population();
			break;

		case '6':
			heading("CITIZENS WITH SPECIFIC VACCINE ID");
			cout << "\n\n";
			GOV->display_citizen_with_VacID();
			break;

		case '7':
			heading("GRAPH OF VACCINATED & PARTIALLY VACCINATED CITIZENS");
			cout << "\n\n";
			GOV->display_graph();
			break;


		case '8':
			print_error("\n\n[!] EXITING GOVERNMENT OFFICIAL MENU [!]\n");

			loop = false;
			break;

		default:
			print_error("\n\n[!] INVALID INPUT [!]\n");
			break;
		}

		cout << "\n\nPRESS ANY KEY TO CONTINUE";
		_getch();

	}
}

void login_process(string username, string pass)
{
	string modes[4] = { "SA", "AD", "FD", "GO" };
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
					throw wrong_password();
				}
			}
			else
			{
				throw unregistered_username();
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
					throw wrong_password();
				}
			}
			else
			{
				throw unregistered_username();
			}
		}
		else if (mode == modes[2]) // Front Desk Officer
		{
			if (Filing::find_fdo(username))
			{
				if (Filing::is_valid_login_fdo(username, pass))
				{
					fdo_page(username);
				}
				else
				{
					throw wrong_password();
				}
			}
			else
			{
				throw unregistered_username();
			}
		}
		else if (mode == modes[3]) // Government Offcial // ABHI BANA HI NAI ;-;
		{
			if (Filing::find_gov_off(username))
			{
				if (Filing::is_valid_login_gov_off(username, pass))
				{
					gov_off_page(username);
				}
				else
				{
					throw wrong_password();
				}
			}
			else
			{
				throw unregistered_username();
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

void register_citizen()
{
	string CNIC;
	citizen CITIZEN;
	cout << "Enter CNIC: ";

	do
	{
		cin >> CNIC;
		if (!is_valid_cnic(CNIC))
		{
			print_error("\n[!] ERROR: The CNIC entered in not valid.\n\n");
			cout << "Enter again: ";
		}
	} while (!is_valid_cnic(CNIC));

	if (Filing::find_citizen(CNIC))
	{
		cout << "\n\n ->ALREADY REGISTERED<-\n\n";

		CITIZEN = Filing::load_citizen(CNIC);

		cout << "->CITIZEN INFO\n\n";
		CITIZEN.citizen_output();

		if (Filing::already_vacinated(CNIC))
		{
			cout << "\nVaccinated Status: True\n";
		}
		else
		{
			cout << "\nVaccinated Status: False\n";
		}
	}
	else
	{
		cout << "\n\n ->NOT REGISTERED<-\n\n";

		cout << "->CITIZEN INFO\n\n";
		CITIZEN.citizen_input();

		Filing::add_new_citizen(&CITIZEN);

		cout << "\n\n ->YOU HAVE REGISTERED SUCCESSFULLY\n\n";
	}

}

int main()
{
	char x;
	string username, pass;
	bool loop = true;
	char choice;

	Filing::login_super_admin("SA90530");

	system("cls");
	loading_animation();

	system("Color F0");
	while (loop)
	{
		username = pass = "";

		system("cls");
		heading("MAIN MENU");

		print_spaces();
		cout << "1. Admin Login\n";
		print_spaces();
		cout << "2. Register Citizen\n";
		print_spaces();
		cout << "3. Exit\n";

		print_spaces();
		cout << "ENTER ANY OPTION";
		choice = _getch();

		switch (choice)
		{
		case '1':
			system("cls");
			login_page(username, pass);
			login_process(username, pass);
			break;

		case '2':
			heading("REGISTER CITIZEN");

			register_citizen();
			break;

		case '3':
			print_error("\n\n[!] EXITING PROGRAM [!]\n");

			loop = false;
			break;

		default:
			print_error("\n\n[!] INVALID INPUT [!]\n");
			break;
		}

		cout << "\n\nPRESS ANY KEY TO CONTINUE";
		_getch();

	}

	return 0;
}