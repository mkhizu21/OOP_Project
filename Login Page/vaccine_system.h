#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


string FILE_PATH = "";

template<typename T>
void expand(T*& ptr, int& size)
{
    T* temp = new T[size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = ptr[i];
    }

    size++;

    delete[] ptr;
    ptr = new T[size];

    for (int i = 0; i < size-1; i++)
    {
        ptr[i] = temp[i];
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

void print_error(string output)
{
    SetConsoleTextAttribute(h, 252);
    cout << output;
    SetConsoleTextAttribute(h, 240);
}

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
        //string o_username, fn, ln, em, No, cn;

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
    static void add_new_admin(admin& obj)
    {
        ofstream details_file(FILE_PATH + "admin_details.csv", ios::app);
        ofstream login_file(FILE_PATH + "admin_login_details.txt", ios::app);

        if (!details_file || !login_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else                                 
        {                                    
            details_file << obj.file_details();
            login_file << obj.file_logindetails();
                                             
            details_file.close();
            login_file.close();
        }
    }
    static void store_deleted_admins(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "admin_details.csv");
        

        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
                login_output_file << obj.file_logindetails();
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
    static void add_new_doctor(doctor& obj)
    {
        ofstream details_file(FILE_PATH + "doctor_details.csv", ios::app);
        ofstream login_file(FILE_PATH + "doctor_login_details.txt", ios::app);

        if (!details_file || !login_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();
            login_file << obj.file_logindetails();

            details_file.close();
            login_file.close();
        }
    }
    static void store_deleted_doctors(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "doctor_details.csv");


        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
    static void store_updated_doctors(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "doctor_details.csv");


        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: doctor_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
                login_output_file << obj.file_logindetails();
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
    static void add_new_fdo(fdo& obj)
    {
        ofstream details_file(FILE_PATH + "fdo_details.csv", ios::app);
        ofstream login_file(FILE_PATH + "fdo_login_details.txt", ios::app);

        if (!details_file || !login_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();
            login_file << obj.file_logindetails();

            details_file.close();
            login_file.close();
        }
    }
    static void store_deleted_fdos(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "fdo_details.csv");


        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
    static void store_updated_fdos(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "fdo_details.csv");


        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: fdo_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
                login_output_file << obj.file_logindetails();
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
    static void add_new_gov_off(gov_off& obj)
    {
        ofstream details_file(FILE_PATH + "gov_off_details.csv", ios::app);
        ofstream login_file(FILE_PATH + "gov_off_login_details.txt", ios::app);

        if (!details_file || !login_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();
            login_file << obj.file_logindetails();

            details_file.close();
            login_file.close();
        }
    }
    static void store_deleted_gov_offs(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "gov_off_details.csv");


        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
    static void store_updated_gov_offs(string username, admin* arr, int size)
    {
        ofstream details_file(FILE_PATH + "gov_off_details.csv");


        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: gov_off_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj.file_details();

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
                login_output_file << obj.file_logindetails();
            }
            else
            {
                login_output_file << o_username[i] << " " << o_pass[i] << endl;
            }
        }

        login_output_file.close();
    }
	
};