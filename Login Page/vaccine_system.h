#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <regex> 
using namespace std;


regex valid_email("[a-zA-Z_0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z]+");
regex valid_contact_num("(03)[0-9][0-9]-[0-9]{7}");
regex valid_user_num("[0-9][0-9][0-9][0-9][0-9]");
regex valid_cnic("[0-9]{5}-[0-9]{7}-[0-9]");
regex valid_name ("[A-Za-z]+");

regex upper_case ("[A-Z]+"); 
regex lower_case ("[a-z]+"); 
regex number{ "[0-9]+" }; 
regex special_char("[@!?#$\\,.<>{}%^&]+");


HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
string FILE_PATH = "";


//---------EXCEPTIONS---------------
bool is_valid_username(string username)
{
    string modes[5] = { "SA", "AD", "DC", "FD", "GO" };
    string mode = username.substr(0, 2);
    string num = username.substr(2);

    bool un_mode = false, un_num = false;

    for (int i = 0; i < 5; i++)
    {
        if (mode == modes[i])
        {
            un_mode = true;
        }
    }

    if (regex_match(num, valid_user_num))
    {
        un_num = true;
    }

    if (un_num && un_mode)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_valid_password(string pass)
{
    int conditions = 0;

    if (pass.size() >= 8)
    {
        conditions += 1;
    }

    conditions += regex_search(pass, upper_case) + regex_search(pass, lower_case) + regex_search(pass, number) + regex_search(pass, special_char);

    if (conditions == 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_valid_name(string name)
{
    return regex_match(name, valid_name);
}

bool is_valid_email(string email)
{
    return regex_match(email, valid_email);
}

bool is_valid_contact(string num)
{
    return regex_match(num, valid_contact_num);
}

bool is_valid_cnic(string cnic)
{
    return regex_match(cnic, valid_cnic);
}

class username_exists : public exception
{

public:
    const char* what() const
    {
        return ("The entered username already exists.");
    }
};
class invalid_username : public exception
{

public:
    const char* what() const
    {
        return ("The entered username is not valid.");
    }
};
class invalid_password : public exception
{

public:
    const char* what() const
    {
        return ("The entered password is not valid.");
    }
};
class wrong_password;
class unregistered_username;
//-------------------------------------------------------------


template<typename T>
void expand(T*& ptr, int& size)
{
    if (size != 0)
    {
        T* temp = new T[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = ptr[i];
        }

        size++;

        delete[] ptr;
        ptr = new T[size];

        for (int i = 0; i < size - 1; i++)
        {
            ptr[i] = temp[i];
        }
    }
    else
    {
        size++;
        ptr = new T[size];
    }
    
}

template <typename T>
void del(T*& ptr, int size, int index)
{
    T* temp = new T[size - 1];
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (i != index)
        {
            temp[count++] = ptr[i];
        }
    }

    delete[] ptr;

    ptr = new T[size - 1];

    for (int i = 0; i < size - 1; i++)
    {
        ptr[i] = temp[i];
    }
}

string encrypt(string username, string pass)
{
    int key = 0;

    // calculates the key used for encryption
    for (int i = 2; i < 7; i++)
    {
        key += username[i] - 48; // converting char number into integar
    }

    cout << "key " << key << endl;

    // coverts the entered password into encrypted one to compare with the original
    for (int i = 0; i < pass.size(); i++)
    {

        pass[i] += key;
        cout << int(pass[i]) << endl;

        if (int(pass[i]) < 0) // makes sure ASCII doesn't go in negative value
        {
            pass[i] *= -1;
        }

        if (int(pass[i]) == 127) // 127 is the delete character; causes problems in comparing the passwords
        {
            pass[i] -= 1;
        }
        cout << int(pass[i]) << endl;
    }

    return pass;
}

void print_spaces(int space = 38)
{
    cout << "\n" << setfill(' ') << setw(space) << "";
}

void print_error(string output)
{
    SetConsoleTextAttribute(h, 252);
    cout << output;
    SetConsoleTextAttribute(h, 240);
}


class Filing;

class person
{
protected:
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
        do
        {
            cin >> firstname;
            if (!is_valid_name(firstname))
            {
                print_error("\n[!] ERROR: The name should only have alphabets.\n\n");
                cout << "Enter again: ";
            }
        } while (!is_valid_name(firstname));
        
        cout << "Enter last Name: ";
        do
        {
            cin >> lastname;
            if (!is_valid_name(lastname))
            {
                print_error("\n[!] ERROR: The name should only have alphabets.\n\n");
                cout << "Enter again: ";
            }
        } while (!is_valid_name(lastname));

        cout << "Enter Email Address: ";
        do
        {
            cin >> email;
            if (!is_valid_email(email))
            {
                print_error("\n[!] ERROR: The email entered in not valid.\n\n");
                cout << "Enter again: ";
            }
        } while (!is_valid_email(email));
        
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

        cout << "Enter Contact Number: ";
        do
        {
            cin >> contactNumber;
            if (!is_valid_contact(contactNumber))
            {
                print_error("\n[!] ERROR: The phone number entered in not valid.\n\n");
                cout << "Enter again: ";
            }
        } while (!is_valid_contact(contactNumber));


        
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

    string file_details()
    {
        return  username + "," + firstname + "," + lastname + "," + email + "," + CNIC + "," + contactNumber + ",\n";
    }

    string file_logindetails()
    {
        return username + " " + pass + "\n";
    }

    void load_data(string un, string fn, string ln, string em, string cn, string No)
    {
        username = un;
        firstname = fn;
        lastname = ln;
        email = em;
        CNIC = cn;
        contactNumber = No;
    }
    

    virtual void input_login_details() = 0; // inout username and password
};

class admin : public person
{
public:
    admin(): person(){}
    admin(string un, string fn, string ln, string em, string cn, string No);
    
    void input_login_details();
    
};

class fdo :public person 
{
public:
    void input_login_details() {}
};
class doctor :public person 
{
public:
    void input_login_details() {}
};
class gov_off :public person 
{
public:
    void input_login_details() {}
};

class super_admin : public person
{
private:
    static super_admin* self_instance;

    int admin_count, fdo_count, doctor_count, gov_off_count;

    admin* admin_list;
    fdo* fdo_list;
    doctor* doctor_list;
    gov_off* gov_off_list;

    super_admin(string un, string fn, string ln, string em, string cn, string No);

    int find_admin_index(string un);

    int find_fdo_index(string un);

    int find_doctor_index(string un);

    int find_gov_off_index(string un);



public:

    static super_admin* getInstance(string un, string fn, string ln, string em, string cn, string No);

    void create_admin();
    void delete_admin();
    void update_admin();

    void create_doctor();
    void delete_doctor();
    void update_doctor();

    void create_fdo();
    void delete_fdo();
    void update_fdo();

    void create_gov_off();
    void delete_gov_off();
    void update_gov_off();



    void input_login_details();




};



 class Filing
 {
 public:
     static bool find_super_admin(string username)
     {
         ifstream login_file(FILE_PATH + "super_admin_login_details.txt");
         string o_username;

         login_file >> o_username; // reads original username from the file


         if (username == o_username)
         {
             return true;
         }
         else
         {
             return false;
         }
     }
     static bool is_valid_login_super_admin(string username, string pass)
     {
         ifstream login_file(FILE_PATH + "super_admin_login_details.txt");
         string o_username, o_pass;
         int key = 0;

         login_file >> o_username >> o_pass; // reads original username and password from the file

         pass = encrypt(username, pass);

         if (username == o_username && pass == o_pass)
         {
             return true;
         }
         else
         {
             return false;
         }

     }
     static super_admin* login_super_admin(string username)
     {
         ifstream details_file(FILE_PATH + "super_admin_details.csv");
         int count = 0;
         string line, word;
         string details[6];
         //string o_username, fn, ln, em, cn, No;

         getline(details_file, line);
         stringstream str(line);

         while (getline(str, word, ','))
         {
             details[count++] = word;
         }

         if (details[0] == username)
         {
             return super_admin::getInstance(details[0], details[1], details[2], details[3], details[4], details[5]);
         }
     }

     static bool find_admin(string username)
     {
         ifstream login_file(FILE_PATH + "admin_login_details.txt");

         bool found = false;
         string o_username, o_pass;

         // reads original username from the file
         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass;
             if (username == o_username)
             {
                 found = true;
                 break;
             }

         }
         login_file.close();

         return found;
     }
     static bool is_valid_login_admin(string username, string pass)
     {
         ifstream login_file(FILE_PATH + "admin_login_details.txt");

         bool logined = false;
         string o_username, o_pass;

         // reads original username from the file
         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass;
             if (username == o_username)
             {
                 pass = encrypt(username, pass);

                 if (pass == o_pass)
                 {
                     logined = true;
                     break;
                 }
             }

         }
         login_file.close();

         return logined;
     }

     static void initiate_all_admin(admin*& admin_list, int& admin_count)
     {
         ifstream details_file(FILE_PATH + "admin_details.csv");
         int count = 0;
         string line, word;
         string details[6];
         //string o_username, fn, ln, em, cn, No;
         getline(details_file, line);
         while (!details_file.eof())
         {
             count = 0;
             stringstream str(line);

             while (getline(str, word, ','))
             {
                 details[count++] = word;
             }

             expand<admin>(admin_list, admin_count);

             admin_list[admin_count-1].load_data(details[0], details[1], details[2], details[3], details[4], details[5]);
             getline(details_file, line);
         }
         
     }

     static void add_new_admin(admin* obj)
     {
         ofstream details_file(FILE_PATH + "admin_details.csv", ios::app);
         ofstream login_file(FILE_PATH + "admin_login_details.txt", ios::app);

         if (!details_file || !login_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             details_file << obj->file_details();
             login_file << obj->file_logindetails();

             details_file.close();
             login_file.close();
         }
     }
     static void store_deleted_admins(string username, admin* arr, int size)
     {
         ofstream details_file(FILE_PATH + "admin_details.csv");


         if (!details_file)
         {
             print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }

             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "admin_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "admin_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username != o_username[i])
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }
     static void store_updated_admins(string username, admin* arr, int size)
     {
         ofstream details_file(FILE_PATH + "admin_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }

             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "admin_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "admin_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username == o_username[i])
             {
                 login_output_file << arr[i].file_logindetails();
             }
             else
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }

     static bool find_doctor(string username)
     {
         ifstream login_file(FILE_PATH + "doctor_login_details.txt");

         bool found = false;
         string o_username, o_pass;


         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass;  // reads original username from the file
             if (username == o_username)
             {
                 found = true;
                 break;
             }
             login_file >> o_username >> o_pass;
         }
         login_file.close();

         return found;
     }
     static bool is_valid_login_doctor(string username, string pass)
     {
         ifstream login_file(FILE_PATH + "doctor_login_details.txt");

         bool logined = false;
         string o_username, o_pass;


         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass; // reads original username from the file
             if (username == o_username)
             {
                 pass = encrypt(username, pass);

                 if (pass == o_pass)
                 {
                     logined = true;
                     break;
                 }
             }

         }
         login_file.close();

         return logined;
     }
     static void add_new_doctor(doctor* obj)
     {
         ofstream details_file(FILE_PATH + "doctor_details.csv", ios::app);
         ofstream login_file(FILE_PATH + "doctor_login_details.txt", ios::app);

         if (!details_file || !login_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             details_file << obj->file_details();
             login_file << obj->file_logindetails();

             details_file.close();
             login_file.close();
         }
     }
     static void store_deleted_doctors(string username, doctor* arr, int size)
     {
         ofstream details_file(FILE_PATH + "doctor_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }

             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "doctor_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "doctor_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username != o_username[i])
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }
     static void store_updated_doctors(string username, doctor* arr, int size)
     {
         ofstream details_file(FILE_PATH + "doctor_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: doctor_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }
             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "doctor_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "doctor_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username == o_username[i])
             {
                 login_output_file << arr[i].file_logindetails();
             }
             else
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }

     static bool find_fdo(string username)
     {
         ifstream login_file(FILE_PATH + "fdo_login_details.txt");

         bool found = false;
         string o_username, o_pass;


         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass;  // reads original username from the file
             if (username == o_username)
             {
                 found = true;
                 break;
             }
             login_file >> o_username >> o_pass;
         }
         login_file.close();

         return found;
     }
     static bool is_valid_login_fdo(string username, string pass)
     {
         ifstream login_file(FILE_PATH + "fdo_login_details.txt");

         bool logined = false;
         string o_username, o_pass;


         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass; // reads original username from the file
             if (username == o_username)
             {
                 pass = encrypt(username, pass);

                 if (pass == o_pass)
                 {
                     logined = true;
                     break;
                 }
             }
         }
         login_file.close();

         return logined;
     }
     static void add_new_fdo(fdo* obj)
     {
         ofstream details_file(FILE_PATH + "fdo_details.csv", ios::app);
         ofstream login_file(FILE_PATH + "fdo_login_details.txt", ios::app);

         if (!details_file || !login_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             details_file << obj->file_details();
             login_file << obj->file_logindetails();

             details_file.close();
             login_file.close();
         }
     }
     static void store_deleted_fdos(string username, fdo* arr, int size)
     {
         ofstream details_file(FILE_PATH + "fdo_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }
             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "fdo_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "fdo_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username != o_username[i])
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }
     static void store_updated_fdos(string username, fdo* arr, int size)
     {
         ofstream details_file(FILE_PATH + "fdo_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: fdo_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }
             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "fdo_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "fdo_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username == o_username[i])
             {
                 login_output_file << arr[i].file_logindetails();
             }
             else
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }

     static bool find_gov_off(string username)
     {
         ifstream login_file(FILE_PATH + "gov_off_details.txt");

         bool found = false;
         string o_username, o_pass;


         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass;  // reads original username from the file
             if (username == o_username)
             {
                 found = true;
                 break;
             }
             login_file >> o_username >> o_pass;
         }
         login_file.close();

         return found;
     }
     static bool is_valid_login_gov_off(string username, string pass)
     {
         ifstream login_file(FILE_PATH + "gov_off_login_details.txt");

         bool logined = false;
         string o_username, o_pass;


         while (!login_file.eof())
         {
             login_file >> o_username >> o_pass; // reads original username from the file
             if (username == o_username)
             {
                 pass = encrypt(username, pass);

                 if (pass == o_pass)
                 {
                     logined = true;
                     break;
                 }
             }
         }
         login_file.close();

         return logined;
     }
     static void add_new_gov_off(gov_off* obj)
     {
         ofstream details_file(FILE_PATH + "gov_off_details.csv", ios::app);
         ofstream login_file(FILE_PATH + "gov_off_login_details.txt", ios::app);

         if (!details_file || !login_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             details_file << obj->file_details();
             login_file << obj->file_logindetails();

             details_file.close();
             login_file.close();
         }
     }
     static void store_deleted_gov_offs(string username, gov_off* arr, int size)
     {
         ofstream details_file(FILE_PATH + "gov_off_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }
             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "gov_off_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "gov_off_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username != o_username[i])
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }
     static void store_updated_gov_offs(string username, gov_off* arr, int size)
     {
         ofstream details_file(FILE_PATH + "gov_off_details.csv");


         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: gov_off_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             for (int i = 0; i < size; i++)
             {
                 details_file << arr[i].file_details();
             }
             details_file.close();
         }

         vector<string> o_username, o_pass;
         string un, pass;
         int count = 0;;

         ifstream login_input_file(FILE_PATH + "gov_off_login_details.txt");

         while (!login_input_file.eof())
         {
             login_input_file >> un >> pass;
             o_username.push_back(un);
             o_pass.push_back(pass);
             count++;
         }
         login_input_file.close();

         ofstream login_output_file(FILE_PATH + "gov_off_login_details.txt");

         for (int i = 0; i < count; i++)
         {
             if (username == o_username[i])
             {
                 login_output_file << arr[i].file_logindetails();
             }
             else
             {
                 login_output_file << o_username[i] << " " << o_pass[i] << endl;
             }
         }

         login_output_file.close();
     }

 };

 //-------------------------SUPER ADMIN DEFINATIONS------------------------------------------------------------------
     super_admin::super_admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, cn, No)
     {
         // read admin, fdo, doctor, government officials from file
        fdo_count = doctor_count = gov_off_count = 0;
        Filing::initiate_all_admin(admin_list, admin_count);
        fdo_list = nullptr;
        doctor_list = nullptr;
        gov_off_list = nullptr;
     }
     int super_admin::find_admin_index(string un)
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
     int super_admin::find_fdo_index(string un)
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
     int super_admin::find_doctor_index(string un)
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
     int super_admin::find_gov_off_index(string un)
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


     super_admin* super_admin::getInstance(string un, string fn, string ln, string em, string cn, string No)
     {
         if (self_instance == nullptr)
             self_instance = new super_admin(un, fn, ln, em, cn, No);

         return self_instance;
     }

     void super_admin::create_admin()
     {

         expand<admin>(admin_list, admin_count);

         admin_list[admin_count - 1].input_login_details();
         admin_list[admin_count - 1].input();

         Filing::add_new_admin(&admin_list[admin_count - 1]);
     }
     void super_admin::delete_admin()
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
                 print_error("[!] ERROR: The entered username doesn't exists.");
             }
         }
         else
         {
             print_error("\n\n[!]ERROR: There is no admin to delete.\n\n");
         }
     }
     void super_admin::update_admin()
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
     void super_admin::create_doctor()
     {

         expand<doctor>(doctor_list, doctor_count);

         doctor_list[doctor_count - 1].input_login_details();
         doctor_list[doctor_count - 1].input();

         Filing::add_new_doctor(&doctor_list[doctor_count - 1]);
     }
     void super_admin::delete_doctor()
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
     void super_admin::update_doctor()
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
     void super_admin::create_fdo()
     {

         expand<fdo>(fdo_list, fdo_count);

         fdo_list[fdo_count - 1].input_login_details();
         fdo_list[fdo_count - 1].input();

         Filing::add_new_fdo(&fdo_list[fdo_count - 1]);
     }
     void super_admin::delete_fdo()
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
     void super_admin::update_fdo()
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
     void super_admin::create_gov_off()
     {

         expand<gov_off>(gov_off_list, gov_off_count);

         gov_off_list[gov_off_count - 1].input_login_details();
         gov_off_list[gov_off_count - 1].input();

         Filing::add_new_gov_off(&gov_off_list[gov_off_count - 1]);
     }
     void super_admin::delete_gov_off()
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
     void super_admin::update_gov_off()
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
     void super_admin::input_login_details() {}

 super_admin* super_admin::self_instance = nullptr; // initialization


 //----------------------------------------------------------------------------------------------------------------

    
//------------------------ ADMIN DEFINATIONS------------------------------------------------------------------
    admin::admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, cn, No)
     {

     }

    void admin::input_login_details()
     {
         string un, un_num, p; 
         bool correct_input = false;

         while (!correct_input)
         {
             try
             {
                 un = "AD";
                 cout << "Enter the username: AD";
                 cin >> un_num;

                 if (!regex_match(un_num, valid_user_num))
                 {
                     throw invalid_username();
                 }

                 un += un_num; // concats the digits with "AD"

                 if (Filing::find_admin(un))
                 {
                     throw username_exists();
                 }

                 cout << "\nEnter the password";
                 cin >> p;

                 if (!is_valid_password(p))
                 {
                     throw invalid_password();
                 }

                 correct_input = true;
             }
             catch (const exception& e)
             {
                 SetConsoleTextAttribute(h, 252);
                 print_spaces();
                 cout << "[!] Exception: " << e.what() << endl;
                 SetConsoleTextAttribute(h, 240);
             }
         }
             
         username = un;
         pass = encrypt(un, p);


     }
//----------------------------------------------------------------------------------------------------------------

     




