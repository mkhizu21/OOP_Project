#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <regex> 
using namespace std;


regex valid_email("[a-zA-Z_0-9]+@[a-zA-Z0-9]+.[a-zA-Z]+");
regex valid_contact_num("(03)[0-9]{2}-[0-9]{7}");
regex valid_user_num("[0-9]{5}");
regex valid_cnic("[0-9]{5}-[0-9]{7}-[0-9]");
regex valid_name ("[A-Za-z]+");

regex upper_case ("[A-Z]+"); 
regex lower_case ("[a-z]+"); 
regex number{ "[0-9]+" }; 

void heading(string msg);

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

    conditions += regex_search(pass, upper_case) + regex_search(pass, lower_case) + regex_search(pass, number);

    if (conditions == 4)
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

bool is_valid_blood_group(string bg)
{
    if(bg.size() == 2)
    {
         if(bg[0] == 'A' || bg[0] == 'B' || bg[0] == 'O')
         {
            if(bg[1] == '+' || bg[1] == '-')
            {
                return true;
            }
         }
    }
    else if(bg.size() == 3)
    {
        if(bg[0] == 'AB')
         {
            if(bg[2] == '+' || bg[2] == '-')
            {
                return true;
            }
         }
    }

    return false;
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

    //cout << "key " << key << endl;

    // coverts the entered password into encrypted one to compare with the original
    for (int i = 0; i < pass.size(); i++)
    {

        pass[i] += key;
        //cout << int(pass[i]) << endl;

        if (int(pass[i]) < 0) // makes sure ASCII doesn't go in negative value
        {
            pass[i] *= -1;
        }

        if (int(pass[i]) == 127) // 127 is the delete character; causes problems in comparing the passwords
        {
            pass[i] -= 1;
        }
        //cout << int(pass[i]) << endl;
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

    virtual string file_details()
    {
        return  username + "," + firstname + "," + lastname + "," + email + "," + CNIC + "," + contactNumber + ",";
    }

    string file_logindetails()
    {
        return username + " " + pass + "\n";
    }

    void load_person_data(string un, string fn, string ln, string em, string cn, string No)
    {
        username = un;
        firstname = fn;
        lastname = ln;
        email = em;
        CNIC = cn;
        contactNumber = No;
    }
    

    virtual void input_login_details() = 0; // input username and password
};

class vaccines
{
private:
    string vaccineID;
    string vaccineName;
    int quantity;
    int Nofdoses;
    int price;
    int batchNo;
public:
    vaccines() {}
    void vaccineInput()
    {
        cout << "Vaccine ID: ";
        cin >> vaccineID;
        cout << "Enter Vaccine Name: ";
        cin >> vaccineName;
        cout << "Enter no of doses: ";
        cin >> Nofdoses;
        cout << "Enter the price of vaccine: ";
        cin >> price;
        cout << "Enter the quantity of vaccine: ";
        cin >> quantity;
    }
    void vaccineOutput(bool bNO = false) // bNO tells wheter to print BatchNo or not
    {
        cout << "Vaccine ID: " << vaccineID << endl;
        cout << "Vaccine Name: " << vaccineName << endl;
        cout << "No. of doses: " << Nofdoses << endl;
        cout << "Price of vaccine: "<< price << endl;
        cout << "Quantity of vaccine: " << quantity << endl;
        if(bNO)
        cout << "BatchID: " << batchNo << endl;
    }

    string file_details()
    {
        return vaccineID + "," + to_string(batchNo) + "," + vaccineName + "," + to_string(Nofdoses) + "," + to_string(price) + "," + to_string(quantity) + ",\n";
    }
    void load_data(string vID, string vName, string NoDoses, string p, string q)
    {
        vaccineID = vID;
        vaccineName = vName;
        Nofdoses = stoi(NoDoses);
        price = stoi(p);
        quantity = stoi(q);
    }
    void set_batchNo(int num)
    {
        batchNo = num;
    }

    void set_quantity(int q)
    {
        quantity = q;
    }

    int get_batchNo()
    {
        return batchNo;
    }

    string get_vacName()
    {
        return vaccineName;
    }

    string get_vacID()
    {
        return vaccineID;
    }

    int get_Nofdoses()
    {
        return Nofdoses;
    }
    int get_price()
    {
        return price;
    }
    
    int get_quantity()
    {
        return quantity;
    }

};

class company
{
private:
    string companyName;
    vaccines* vac;
    int lastBatchNo;

    //taken from file
public:
    company()
    {
        vac = new vaccines;
        lastBatchNo = 0;
    }
    void companyInput() //admin can add companies
    {
        cout << "Enter company name: ";
        cin >> companyName;
        
        vac->vaccineInput();
    }
    void companyoutput() //review company details
    {
        cout << "Company Name: " << companyName << endl;
        vac->vaccineOutput();
    }
    
    vaccines* get_vac()
    {
        return vac;
    }
    int get_vac_quantity()
    {
        return vac->get_quantity();
    }

    string file_details()
    {
        return companyName + "," + to_string(lastBatchNo) +"," + vac->get_vacID() + "," + vac->get_vacName() + "," + to_string(vac->get_Nofdoses()) + "," + to_string(vac->get_price()) + "," + to_string(vac->get_quantity()) + ",\n" ;
    }

    bool compare_companyName(string n)
    {
        return n == companyName;
    }

    void load_data(string cname, string LbNo, string vID, string vName, string NoDoses, string price, string quantity)
    {
        companyName = cname;
        lastBatchNo = stoi(LbNo);
        vac->load_data(vID, vName, NoDoses, price, quantity);
    }

    int get_batchID()
    {
        lastBatchNo++;
        return lastBatchNo;
    }

    //friend void getvaccine(int buyvaccine, company comp, warehouse ware);
};



class warehouse
{
private:
    vaccines* vac_ware;
    string houseID; //to specify a warehouse
    int limit, total_vac_amount;
    int vaccineCount;//count type of vaccines in this warehouse
    //location class will have composition here

public:
    bool is_enough_space(int x)
    {
        return (limit - total_vac_amount) >= x;
    }
    warehouse()
    {
        total_vac_amount = vaccineCount = 0;
    }

    void houseInput()
    {
        cout << "Enter Warehouse ID: ";
        cin >> houseID;
        cout << "Enter Storage capacity: ";
        cin >> limit;

    }

    void houseOutput()
    {
        cout << "Warehouse ID: " << houseID << endl;
        cout << "Current Vaccine amount: " << total_vac_amount << endl;
        cout << "Storage limit: " << limit << endl;
        cout << "No of batches available: " << vaccineCount << endl;
    }

    void vaccinesOutput()
    {
        for (int i = 0; i < vaccineCount; i++)
        {
            cout << "\n";
            vac_ware[i].vaccineOutput(true);
        }
    }

     void load_vaccine(string vID, string lbatch, string vName, string NoDoses, string price, string quantity)
    {
       expand<vaccines>(vac_ware, vaccineCount);

       vac_ware[vaccineCount-1].load_data(vID, vName, NoDoses, price, quantity);
       vac_ware[vaccineCount-1].set_batchNo(stoi(lbatch));
    }

    void add_new_vaccine(vaccines *v, int lbatch)
    {
        string vID  = v->get_vacID();
        string vName  = v->get_vacName();
        string NoDoses  = to_string(v->get_Nofdoses());
        string price = to_string(v->get_price());
        string quantity = to_string(v->get_quantity());

       expand<vaccines>(vac_ware, vaccineCount);

       vac_ware[vaccineCount-1].load_data(vID, vName, NoDoses, price, quantity);
       vac_ware[vaccineCount-1].set_batchNo(lbatch);

       total_vac_amount += v->get_quantity();
    }

    string file_details()
    {
        return houseID + "," + to_string(limit) + "," + to_string(total_vac_amount) + "," + to_string(vaccineCount) + ",\n";
    }

    void load_data(string id, string l, string vac_amt, string vacC)
    {
        houseID = id; 
        limit = stoi(l); 
        total_vac_amount = stoi(vac_amt);
        vaccineCount = stoi(vacC);
    }

    bool compare_warehouseID(string n)
    {
        return n == houseID;
    }

    //friend void getvaccine(int buyvaccine, company comp, warehouse ware);
};
//void getvaccine(int buyvaccine, company comp, warehouse ware)
//{
//	if (buyvaccine <= comp.vac->getvacNo())
//	{
//		int VN = comp.vac->getvacNo();
//		VN -= buyvaccine;
//		comp.vac->setvacNo(VN);
//		cout << "Enter warehouse ID for storage: ";
//		cin >> ware.
//	}
//	else
//	{
//		cout << "not enough vaccines" << endl;
//	}
//}

class vaccinationCenter
{
private:

};

class admin : public person
{
private:
    static int companies_count, warehouse_count, vacCen_count;
    static int totalPrice;
    static company* companies_list;
    static warehouse* warehouses_list;
    static vaccinationCenter* vacCen_list;

    static int find_company_index(string n)
    {
        for (int i = 0; i < companies_count; i++)
        {
            if (companies_list[i].compare_companyName(n))
            {
                return i;
            }
        }

        return -1;
    }

    static int find_warehouse_index(string n)
    {
        for (int i = 0; i < warehouse_count; i++)
        {
            if (warehouses_list[i].compare_warehouseID(n))
            {
                return i;
            }
        }

        return -1;
    }

public:

    admin();
    admin(string un, string fn, string ln, string em, string cn, string No);
    
    void adminOutput();

    void add_company();
    void delete_company();
    void display_company();

    void add_warehouse();
    void display_warehouse();

    string file_details();

    void purchase_vaccine();
    void load_admin_data(string un, string fn, string ln, string em, string cn, string No, string tprice);
    void input_login_details();    
};

int admin::companies_count = 0;
int admin::warehouse_count = 0;
int admin::vacCen_count = 0;
int admin::totalPrice = 0;

company* admin::companies_list = nullptr;
warehouse* admin::warehouses_list = nullptr;
vaccinationCenter* admin::vacCen_list = nullptr;

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

    static int admin_count, fdo_count, doctor_count, gov_off_count;

    static admin* admin_list;
    static fdo* fdo_list;
    static doctor* doctor_list;
    static gov_off* gov_off_list;

    super_admin(string un, string fn, string ln, string em, string cn, string No);

    static int find_admin_index(string un);

    static int find_fdo_index(string un);

    static int find_doctor_index(string un);

    static int find_gov_off_index(string un);



public:

    static super_admin* getInstance(string un, string fn, string ln, string em, string cn, string No);

    static admin* admin_obj(string un)
    {
        int i = find_admin_index(un);
        if (i != -1)
        {
            return &admin_list[i];
        }

    }

    void create_admin();
    void delete_admin();
    void update_admin();
    void display_admin();

    static void store_admins();

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

int super_admin::admin_count = 0;
int super_admin::fdo_count = 0;
int super_admin::doctor_count = 0;
int super_admin::gov_off_count = 0;

admin* super_admin::admin_list = nullptr;
fdo* super_admin::fdo_list = nullptr;
doctor* super_admin::doctor_list = nullptr;
gov_off* super_admin::gov_off_list = nullptr;



class citizen : public person
{
private:
    int age;
    string bloodType, city, is_eligible;
public:
    citizen()
    {
        is_eligible = "true";
    }

    void citizen_input()
    {
        input();

        cout << "Enter age: ";
        do
        {
            cin >> age;
            if (age <= 0)
            {
                print_error("\n[!] ERROR: The age entered in not valid.\n\n");
                cout << "Enter again: ";
            }
        } while (age <= 0);
        cin >> age;

        if (age < 5)
        {
            is_eligible = "false";
        }

        cout << "Enter blood type: ";
        do
        {
            cin >> bloodType;
            if (!is_valid_blood_group(bloodType))
            {
                print_error("\n[!] ERROR: The blood group entered in not valid.\n\n");
                cout << "Enter again: ";
            }

        } while (!is_valid_blood_group(bloodType));

        cout << "Enter city: ";
        cin >> city;
    }

    void citizen_output()
    {
        output();
        cout << "Age: " << age << endl;
        cout << "Blood Group: " << bloodType << endl;
        cout << "City: " << city << endl;
    }

    string file_detail()
    {
        return person::file_details() + "," + to_string(age) + "," + bloodType +"," + city +"," + is_eligible + ",";
    }

    void load_citizen(string un, string fn, string ln, string em, string cn, string No, string Age, string bT, string City, string is_e)
    {
        load_person_data(un, fn, ln, em, cn, No);
        age = stoi(Age);
        bloodType = bT;
        city = City;
        is_eligible = is_e;
    }


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
         string details[7];
         //string o_username, fn, ln, em, cn, No, tprice;
         
         while (getline(details_file, line))
         {
             count = 0;
             stringstream str(line);

             while (getline(str, word, ','))
             {
                 details[count++] = word;
             }
             cout << details[0] << endl;
             cout << admin_count << endl;
             expand<admin>(admin_list, admin_count);
             
             admin_list[admin_count-1].load_admin_data(details[0], details[1], details[2], details[3], details[4], details[5], details[6]);
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

     static void initiate_all_companies(company*& companies_list, int& companies_count)
     {
         ifstream details_file(FILE_PATH + "company_details.csv");
         int count = 0;
         string line, word;
         string details[7];
         //string cname LbNo vID vName NoDoses price, quantity;

         while (getline(details_file, line))
         {
             count = 0;
             stringstream str(line);

             while (getline(str, word, ','))
             {
                 details[count++] = word;
             }

             expand<company>(companies_list, companies_count);

             companies_list[companies_count - 1].load_data(details[0], details[1], details[2], details[3], details[4], details[5], details[6]);
         }

     }
     static void add_new_company(company* obj)
     {
         ofstream details_file(FILE_PATH + "company_details.csv", ios::app);

         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             details_file << obj->file_details();

             details_file.close();
         }
     }
     static void store_companies(company* arr, int size)
     {
         ofstream details_file(FILE_PATH + "company_details.csv");


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
     }

     static void initiate_all_warehouses(warehouse*& warehouses_list, int& warehouse_count)
     {
         ifstream details_file(FILE_PATH + "warehouse_details.csv");
         int count = 0;
         string line, word;
         string w_details[4], v_details[6];
         //string houseID limit total_vac_amount vaccineCount

         cout << "ware\n";
         while (getline(details_file, line))
         {
             cout << "warehouse\n";
             count = 0;
             stringstream str(line);

             while (getline(str, word, ','))
             {
                 cout << word << endl;
                 w_details[count++] = word;
             }

             expand<warehouse>(warehouses_list, warehouse_count);

             warehouses_list[warehouse_count - 1].load_data(w_details[0], w_details[1], w_details[2], "0");
         
         
             for (int i = 0; i < stoi(w_details[3]); i++)
             {
                 count = 0;
                 getline(details_file, line);
                 stringstream str1(line);

                 while (getline(str1, word, ','))
                 {
                     v_details[count++] = word;
                 }

                 warehouses_list[warehouse_count - 1].load_vaccine(v_details[0], v_details[1], v_details[2], v_details[3], v_details[4], v_details[5]);
             }
         }

     }
     static void add_new_warehouse(warehouse* obj)
     {
         ofstream details_file(FILE_PATH + "warehouse_details.csv", ios::app);

         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             details_file << obj->file_details();

             details_file.close();
         }
     }
     static void add_new_warehouse_vaccine(string ID,warehouse* wareobj, vaccines* obj)
     {
         ifstream details_file(FILE_PATH + "warehouse_details.csv");
         ofstream temp(FILE_PATH + "temp.csv");

         string line;
         string warehouseID, limit, vacamt, vacCount;

         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {
             
             while (getline(details_file, line))
             {
                 stringstream str(line);
                 getline(str, warehouseID, ',');
                 getline(str, limit, ',');
                 getline(str, vacamt, ',');
                 getline(str, vacCount, ',');

                 if (warehouseID != ID)
                 {
                    temp << line;
                    
                    if (line.size() != 0)
                    if (line[line.size() - 1] != '\n')
                        temp << "\n";
                    
                 }
                 else
                 {
                     temp << wareobj->file_details();
                 }

                 for (int i = 0; i < stoi(vacCount); i++)
                 {
                     getline(details_file, line);
                     temp << line;
                     
                     if(line.size() != 0)
                     if (line[line.size() - 1] != '\n')
                         temp << "\n";
                 }

                 if (warehouseID == ID)
                 {

                     temp << obj->file_details();
                 }
                 
             }

             details_file.close();
             temp.close();

             ofstream details_file("warehouse_details.csv");
             ifstream temp("temp.csv");

             while (getline(temp, line))
             {
                 details_file << line;

                 if (line.size() != 0)
                 if (line[line.size() - 1] != '\n')
                 {
                     details_file << "\n"; //Pakistani tughe salaam :))
                 }
             }

             details_file.close();
             temp.close();
         }
     }

     static void delete_warehouse_vaccine(string ID, string vID, string bID)
     {
         ifstream details_file(FILE_PATH + "warhouse_details.csv");
         ofstream temp(FILE_PATH + "temp.csv");

         string line;
         string warehouseID, limit, vacCount;
         string vacID, batchID;

         if (!details_file)
         {
             //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
         }
         else
         {

             while (getline(details_file, line))
             {
                 stringstream str(line);
                 getline(str, warehouseID, ',');
                 getline(str, limit, ',');
                 getline(str, vacCount, ',');

                 temp << line;

                 if (warehouseID == ID)
                 {
                     for (int i = 0; i < stoi(vacCount); i++)
                     {
                         getline(details_file, line);

                         stringstream str1(line);
                         getline(str, vacID, ',');
                         getline(str, batchID, ',');

                         if (vID != vacID && bID != batchID)
                         {
                             temp << line;
                         }

                     }
                 }
                 else
                 {
                     for (int i = 0; i < stoi(vacCount); i++)
                     {
                         getline(details_file, line);
                         temp << line;
                     }
                 }

             }

             details_file.close();
             temp.close();

             ofstream details_file("warhouse_details.csv");
             ifstream temp("temp.csv");

             while (getline(temp, line))
             {
                 details_file << line;
                 if (line[line.size() - 1] != '\n')
                 {
                     details_file << "\n"; //Pakistani tughe salaam :))
                 }
             }

             details_file.close();
             temp.close();
         }
     }

     

 };

 //-------------------------SUPER ADMIN DEFINATIONS------------------------------------------------------------------
     super_admin::super_admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, cn, No)
     {
         // read admin, fdo, doctor, government officials from file
        admin_count = fdo_count = doctor_count = gov_off_count = 0;
        
        
        Filing::initiate_all_admin(admin_list, admin_count);
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
     void super_admin::display_admin()
     {
         cout << "\n\n------------------------ADMINS------------------------\n\n";
         for (int i = 0; i < admin_count; i++)
         {
             admin_list[i].adminOutput();
             cout << "\n";
         }
     }
     
     void super_admin::store_admins()
     {
         Filing::store_updated_admins("", admin_list, admin_count);
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
    
    admin::admin()
    {
        if (companies_list == nullptr && warehouses_list == nullptr && vacCen_list == nullptr)
        {
            cout << "ADMIN CONSTRUCTOR" << endl;
            companies_count = warehouse_count = vacCen_count = 0;
            Filing::initiate_all_companies(companies_list, companies_count);
            Filing::initiate_all_warehouses(warehouses_list, warehouse_count);
        }

    }

    void admin::adminOutput()
    {
        output();
        cout << "Total amount spent: $" << totalPrice << endl;
    }
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

    void admin::add_company()
    {
        expand<company>(companies_list, companies_count);

        companies_list[companies_count - 1].companyInput();

        Filing::add_new_company(&companies_list[companies_count - 1]);
    }

    void admin::delete_company()
    {
        if (companies_count > 0)
        {
            int i;
            string n;
            cout << "Enter the name of company: ";
            cin >> n;

            i = find_company_index(n);

            if (i != -1)
            {
                del<company>(companies_list, companies_count, i);
                companies_count--;
                Filing::store_companies(companies_list, companies_count);
            }
            else
            {
                print_error("[!] ERROR: The entered name doesn't exists.");
            }
        }
        else
        {
            print_error("\n\n[!]ERROR: There is no company to delete.\n\n");
        }
    }

    void admin::display_company()
    {

        for (int i = 0; i < companies_count; i++)
        {
            cout << "\n";
            companies_list[i].companyoutput();
        }
    }

    void admin::add_warehouse()
    {
        expand<warehouse>(warehouses_list, warehouse_count);

        warehouses_list[warehouse_count - 1].houseInput();

        Filing::add_new_warehouse(&warehouses_list[warehouse_count - 1]);
    }

    void admin::display_warehouse()
    {
        
        for (int i = 0; i < warehouse_count; i++)
        {
            
            cout << "\n";
            warehouses_list[i].houseOutput();
            
        }
    }

    void admin::purchase_vaccine()
    {
        vaccines* vac;
        string company_name, wareID;
        int index, vaccineamt, bID;
        bool warehouse_available = false, correct_input = false;

        heading("COMPANIES");
        display_company();

        cout << "\n\nEnter the name of company you want to buy from: ";
        do
        {
            cin >> company_name;
            if (find_company_index(company_name) == -1)
            {
                print_error("\n[!] ERROR: The company name entered doesn't exist.\n");
                cout << "Enter again: ";
            }
        } while (find_company_index(company_name) == -1);

        index = find_company_index(company_name);
        vaccineamt = companies_list[index].get_vac_quantity();

        cout << "\n--------------------WAREHOUSES--------------------\n\n";
        for (int i = 0; i < warehouse_count; i++)
        {
            if (warehouses_list[i].is_enough_space(vaccineamt))
            {
                warehouse_available = true;
                warehouses_list[i].houseOutput();
                cout << "\n";
            }
        }
        if (warehouse_available)
        {
            cout << "\n\nEnter the ID of warehouse: ";
            do
            {
                cin >> wareID;
                if (find_warehouse_index(wareID) == -1)
                {
                    print_error("\n[!] ERROR: The warehouse entered doesn't exist.\n");
                    cout << "Enter again: ";
                }
                else
                {
                    vaccineamt = companies_list[find_warehouse_index(wareID)].get_vac_quantity();
                    if (!warehouses_list[find_warehouse_index(wareID)].is_enough_space(vaccineamt))
                    {
                        print_error("\n[!] ERROR: The warehouse entered doesn't exist.\n");
                        cout << "Enter again: ";
                    }
                    else
                    {
                        correct_input = true;
                    }
                }
                
            } while (!correct_input);

            int wareI = find_warehouse_index(wareID);
            cout << wareI << endl;

            vac = companies_list[index].get_vac();
            bID = companies_list[index].get_batchID();

            Filing::store_companies(companies_list, companies_count);

            vac->set_batchNo(bID);

            warehouses_list[wareI].add_new_vaccine(vac, bID);

            totalPrice += vac->get_price();

            Filing::add_new_warehouse_vaccine(wareID, &warehouses_list[wareI], vac);

            super_admin::store_admins();
        }
        else
        {
            print_error("\n[!] ERROR: No warehouse has enough space.\n");
        }

    }

    string admin::file_details()
    {
        return person::file_details() + to_string(totalPrice) + ",\n";
    }

    void admin::load_admin_data(string un, string fn, string ln, string em, string cn, string No, string tprice)
    {
        load_person_data(un, fn, ln, em, cn, No);
        totalPrice = stoi(tprice);
    }
//----------------------------------------------------------------------------------------------------------------

     




