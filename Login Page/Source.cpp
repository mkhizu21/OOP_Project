#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <exception>
#include <windows.h>
#include "vaccine_system.h"
using namespace std;


void print_spaces(int space = 38)
{
	cout << "\n" << setfill(' ') << setw(space) << "";
}

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

string banner = R"(
                     __     __             _               ____            _        _ 
                     \ \   / /_ _  ___ ___(_)_ __   ___   |  _ \ ___  _ __| |_ __ _| |
                      \ \ / / _` |/ __/ __| | '_ \ / _ \  | |_) / _ \| '__| __/ _` | |
                       \ V / (_| | (_| (__| | | | |  __/  |  __/ (_) | |  | || (_| | |
                        \_/ \__,_|\___\___|_|_| |_|\___|  |_|   \___/|_|   \__\__,_|_|
                                                                 

)";


//---------EXCEPTIONS---------------
class invalid_username : public exception
{
public:
	const char* what() const
	{
		return ("The entered username is not valid.");
	}
};

class invalid_password;
class wrong_password;
class unregistered_username;
//-------------------------------------------------------------

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

		if (username == "x")
		{
			throw invalid_username();
		}

		/*if (!is_valid_username(username))
		{
			throw invalid_username();
		}*/

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

		/*if (!is_valid_password(pass))
		{
			throw invalid_password();
		}*/
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


class person
{
private:
	string username, pass;
	string firstname, lastname, email, CNIC, contactNumber;

public:
	person()
	{
		username = pass = firstname = lastname = email = contactNumber = CNIC = " ";
		
	}
	person(string un, string fn, string ln, string em, string cn, string No) :username(un), firstname(fn), lastname(ln), email(em), CNIC(cn), contactNumber(No) {}

	void input()
	{
		cout << "Enter First Name: ";
		cin >> firstname;
		cout << "Enter last Name: ";
		cin >> lastname;
		cout << "Enter Email Address: ";
		cin >> email;
		cout << "Enter Contact Number: ";
		cin >> contactNumber;
		cout << "Enter CNIC: ";
		cin >> CNIC;
	}

	void output()
	{
		cout << "First Name: " << firstname << endl;
		cout << "last Name: " << lastname << endl;
		cout << "Email Address: " << email << endl;
		cout << "Contact Number: " << contactNumber << endl;
		cout << "CNIC: " << CNIC << endl;
	}

	bool compare_username(string un)
	{
		if (username == un)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual void input_login_details() = 0; // inout username and password
};


class admin : public person{};
class fdo : public person {};
class doctor : public person {};
class gov_off : public person {};

class super_admin : public person
{
private:
	static super_admin* self_instance;

	int admin_count, fdo_count, doctor_count, gov_off_count;

	admin* admin_list;
	fdo* fdo_list;
	doctor* doctor_list;
	gov_off* gov_off_list;

	super_admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, No, cn)
	{
		// read admin, fdo, doctor, government officials from file
	}

	int find_admin_index(string un)
	{
		for (int i = 0; i < admin_count; i++)
		{
			if (admin_list[i].compare_username(un))
			{
				return i;
			}
		}

		return -1;
	}

	int find_fdo_index(string un)
	{
		for (int i = 0; i < fdo_count; i++)
		{
			if (fdo_list[i].compare_username(un))
			{
				return i;
			}
		}

		return -1;
	}

	int find_doctor_index(string un)
	{
		for (int i = 0; i < doctor_count; i++)
		{
			if (doctor_list[i].compare_username(un))
			{
				return i;
			}
		}

		return -1;
	}

	int find_gov_off_index(string un)
	{
		for (int i = 0; i < gov_off_count; i++)
		{
			if (gov_off_list[i].compare_username(un))
			{
				return i;
			}
		}

		return -1;
	}

public:

	static super_admin* getInstance(string un, string fn, string ln, string em, string No, string cn)
	{
		if (self_instance == nullptr)
			self_instance = new super_admin(un, fn, ln, em, No, cn);

		return self_instance;
	}

	void create_admin()
	{
		
		expand<admin>(admin_list, admin_count);

		admin_list[admin_count - 1].input_login_details();
		admin_list[admin_count - 1].input();

		Filing::add_new_admin(admin_list[admin_count - 1]);
	}
	void delete_admin()
	{
		if (admin_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of admin: ";
			cin >> un;

			i = find_admin_index(un);

			if (i != -1)
			{
				del<admin>(admin_list, admin_count, i);
				admin_count--;
				Filing::store_deleted_admins(un, admin_list, admin_count);
			}
			else
			{
				//error messages display karwa
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no admin to delete.\n\n");
		}
	}
	void update_admin()
	{
		if (admin_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of admin: ";
			cin >> un;

			i = find_admin_index(un);

			if (i != -1)
			{
				admin_list[i].input_login_details();
				admin_list[i].input();

				Filing::store_updated_admins(un, admin_list, admin_count);
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no admin to update.\n\n");
		}
			
	}

	void create_doctor()
	{

		expand<doctor>(doctor_list, doctor_count);

		doctor_list[doctor_count - 1].input_login_details();
		doctor_list[doctor_count - 1].input();

		Filing::add_new_doctor(doctor_list[doctor_count - 1]);
	}
	void delete_doctor()
	{
		if (doctor_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of doctor: ";
			cin >> un;

			i = find_doctor_index(un);

			if (i != -1)
			{
				del<doctor>(doctor_list, doctor_count, i);
				doctor_count--;
				Filing::store_deleted_doctors(un, doctor_list, doctor_count);
			}
			else
			{
				//error messages display karwa
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no doctor to delete.\n\n");
		}
	}
	void update_doctor()
	{
		if (doctor_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of doctor: ";
			cin >> un;

			i = find_doctor_index(un)create_doctor;

			if (i != -1)
			{
				doctor_list[i].input_login_details();
				doctor_list[i].input();

				Filing::store_updated_doctors(un, doctor_list, doctor_count);
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no doctor to update.\n\n");
		}

	}

	void create_fdo()
	{

		expand<fdo>(fdo_list, fdo_count);

		fdo_list[fdo_count - 1].input_login_details();
		fdo_list[fdo_count - 1].input();

		Filing::add_new_fdo(fdo_list[fdo_count - 1]);
	}
	void delete_fdo()
	{
		if (fdo_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of fdo: ";
			cin >> un;

			i = find_fdo_index(un);

			if (i != -1)
			{
				del<fdo>(fdo_list, fdo_count, i);
				fdo_count--;
				Filing::store_deleted_fdos(un, fdo_list, fdo_count);
			}
			else
			{
				//error messages display karwa
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no fdo to delete.\n\n");
		}
	}
	void update_fdo()
	{
		if (fdo_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of fdo: ";
			cin >> un;

			i = find_fdo_index(un);

			if (i != -1)
			{
				fdo_list[i].input_login_details();
				fdo_list[i].input();

				Filing::store_updated_fdos(un, fdo_list, fdo_count);
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no fdo to update.\n\n");
		}

	}

	void create_gov_off()
	{

		expand<gov_off>(gov_off_list, gov_off_count);

		gov_off_list[gov_off_count - 1].input_login_details();
		gov_off_list[gov_off_count - 1].input();

		Filing::add_new_gov_off(gov_off_list[gov_off_count - 1]);
	}
	void delete_gov_off()
	{
		if (gov_off_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of gov_off: ";
			cin >> un;

			i = find_gov_off_index(un);

			if (i != -1)
			{
				del<gov_off>(gov_off_list, gov_off_count, i);
				gov_off_count--;
				Filing::store_deleted_gov_offs(un, gov_off_list, gov_off_count);
			}
			else
			{
				//error messages display karwa
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no gov_off to delete.\n\n");
		}
	}
	void update_gov_off()
	{
		if (gov_off_count > 0)
		{
			int i;
			string un;
			cout << "Enter the username of gov_off: ";
			cin >> un;

			i = find_gov_off_index(un);

			if (i != -1)
			{
				gov_off_list[i].input_login_details();
				gov_off_list[i].input();

				Filing::store_updated_gov_offs(un, gov_off_list, gov_off_count);
			}
		}
		else
		{
			print_error("\n\n[!]ERROR: There is no gov_off to update.\n\n");
		}

	}



	void input_login_details(){}


	

};

super_admin* super_admin::self_instance = nullptr; // initialization

void super_admin_page(string username)
{
	super_admin* SA = Filing::login_super_admin(username);
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
				throw unregistered_username();
			}
		}
		else if (mode == modes[2]) // Doctor
		{
			if (Filing::find_doctor(username))
			{
				if (Filing::is_valid_login_doctor(username, pass))
				{
					doctor_page(username);
				}
				else
				{
					throw wrong_password();
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
					fdo_page(username);
				}
				else
				{
					throw wrong_password();
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