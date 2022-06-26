#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <regex> 
#include <iomanip>
using namespace std;


regex valid_email("[a-zA-Z_0-9._]+@[a-zA-Z0-9]+.[a-zA-Z]+");
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
        if(bg[0] == 'A' && bg[1]=='B')
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
class wrong_password : public exception
{

public:
    const char* what() const
    {
        return ("The entered password is incorrect.");
    }
};
class unregistered_username : public exception
{

public:
    const char* what() const
    {
        return ("The entered username is not registered.");
    }
};
//-------------------------------------------------------------

void print_error(string output)
{
    SetConsoleTextAttribute(h, 252);
    cout << output;
    SetConsoleTextAttribute(h, 240);
}

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

template <typename T>
T safe_input()
{
    T temp;
    bool is_input = false;

    while (!is_input)
    {
        try
        {
            cin >> temp;

            if (!cin)
                throw 0;

            is_input = true;


        }
        catch (...)
        {

            cin.clear(); //clear bad input flag
            //cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); //discard input

            print_error("\n[!] Invalid Input !!\n");
            cout << "\nEnter again: ";
        }
    }

    return temp;
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

class Filing;

class person
{
protected:
    string username, pass;
    string firstname, lastname, email, CNIC, contactNumber;

public:
    person();
    person(string un, string fn, string ln, string em, string cn, string No);
    void input();
    void output();

    bool compare_username(string un);

    virtual string file_details();

    string file_logindetails();

    void load_person_data(string un, string fn, string ln, string em, string cn, string No);
    
    
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
    void vaccineInput();
    void vaccineOutput(bool bNO = false);

    string file_details();
    void load_data(string vID, string vName, string NoDoses, string p, string q);
    void set_batchNo(int num);

    void set_quantity(int q);

    int get_batchNo();

    string get_vacName();

    string get_vacID();

    int get_Nofdoses();
    int get_price();
    
    int get_quantity();

};

class company
{
private:
    string companyName;
    vaccines* vac;
    int lastBatchNo;

    //taken from file
public:
    company();
    void companyInput();
    void companyoutput();
    
    vaccines* get_vac();
    int get_vac_quantity();

    string file_details();

    bool compare_companyName(string n);

    void load_data(string cname, string LbNo, string vID, string vName, string NoDoses, string price, string quantity);

    int get_batchID();

    
};

class warehouse
{
private:
    vaccines* vac_ware;
    string houseID; //to specify a warehouse
    int limit, total_vac_amount;
    int vaccineCount;//count type of vaccines in this warehouse
    

public:
    bool is_enough_space(int x);
    warehouse();

    void houseInput();

    void houseOutput();

    void vaccinesOutput();

    void load_vaccine(string vID, string lbatch, string vName, string NoDoses, string price, string quantity);

    vaccines* get_vaccine(int i);

    void add_new_vaccine(vaccines* v, int lbatch);

    void remove_vaccine(string vacID, int batchID);


    string file_details();

    void load_data(string id, string l, string vac_amt, string vacC);

    bool compare_warehouseID(string n);

    int find_valid_vacID_batchID(string vID, int bID);

    
};

class doctor :public person
{
public:
    doctor();
    bool is_health_ok();

    void input_login_details(){}
};

class fdo :public person 
{
    string vacCenterName, city;
    int vacCount;
    vaccines* vac_list;
    doctor* doc;

public:
    fdo();
    
    void fdo_input();
    void fdo_output();

    string file_details();

    void load_data(string un, string fn, string ln, string em, string cn, string No, string vCenName, string City, string vCount, string un1, string fn1, string ln1, string em1, string cn1, string No1);

    void load_vaccine(string vID, string lbatch, string vName, string NoDoses, string price, string quantity);

    void add_new_vaccine(vaccines* v);
    void output_vaccines();
    void get_vaccine();
    void vacinate_citizen();

    bool compare_city(string c);

    void input_login_details();

};

class admin : public person
{
private:
    static int companies_count, warehouse_count, fdo_count;
    static int totalPrice;
    static company* companies_list;
    static warehouse* warehouses_list;
    static fdo* fdo_list;


public:

    admin();
    admin(string un, string fn, string ln, string em, string cn, string No);
    
    void adminOutput();

    void add_company();
    void delete_company();
    void display_company();

    void add_warehouse();
    static void display_warehouse();

    string file_details();

    void purchase_vaccine();
    void load_admin_data(string un, string fn, string ln, string em, string cn, string No, string tprice);
    void input_login_details();    

    static warehouse* get_warehouse(int i)
    {
        return &warehouses_list[i];
    }

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

    
};

int admin::companies_count = 0;
int admin::warehouse_count = 0;
int admin::fdo_count = 0;
int admin::totalPrice = 0;

company* admin::companies_list = nullptr;
warehouse* admin::warehouses_list = nullptr;
fdo* admin::fdo_list = nullptr;

class gov_off :public person 
{
public:
    void input_login_details();
    void load_gov_off_data(string un, string fn, string ln, string em, string cn, string No);

    void percentage_vac_population();
    void percentage_partially_vac_population();

    void display_graph();
    void display_vac_population();
    void display_partially_vac_population();
    void display_citizen_with_VacID();

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

    static admin* admin_obj(string un);
    static fdo* fdo_obj(string un);
    static gov_off* gov_off_obj(string un);

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
    void display_fdo();

    void create_gov_off();
    void delete_gov_off();
    void update_gov_off();
    void display_gov_off();

    static bool does_vac_center_exists_in(string c);

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
    string bloodType, city;
    bool is_eligible;
public:
    citizen();

    citizen(string un, string fn, string ln, string em, string cn, string No, string Age, string bT, string City);
    void citizen_input();

    void citizen_output();

    bool get_eligibity();

    string file_details();

    void load_citizen(string un, string fn, string ln, string em, string cn, string No, string Age, string bT, string City);

    void input_login_details(){}
};

 class Filing
 {
 public:
     static bool find_super_admin(string username);
     static bool is_valid_login_super_admin(string username, string pass);
     static super_admin* login_super_admin(string username);

     static bool find_admin(string username);
     static bool is_valid_login_admin(string username, string pass);

     static void initiate_all_admin(admin*& admin_list, int& admin_count);

     static void add_new_admin(admin* obj);
     static void store_deleted_admins(string username, admin* arr, int size);
     static void store_updated_admins(string username, admin* arr, int size);

     static bool find_doctor(string username);
     static bool is_valid_login_doctor(string username, string pass);
     static void add_new_doctor(doctor* obj);
     static void store_deleted_doctors(string username, doctor* arr, int size);
     static void store_updated_doctors(string username, doctor* arr, int size);

     static bool find_fdo(string username);
     static bool is_valid_login_fdo(string username, string pass);
     static void initiate_all_fdo(fdo*& fdos_list, int& fdo_count);
     static void add_new_fdo(fdo* obj);
     static void add_new_fdo_vaccine(string ID, fdo* fdoobj, vaccines* obj);
     static void store_deleted_fdos(string username, fdo* arr, int size);
     static void store_updated_fdos(string username, fdo* arr, int size);

     static bool find_gov_off(string username);
     static bool is_valid_login_gov_off(string username, string pass);
     static void initiate_all_gov_off(gov_off*& gov_off_list, int& gov_off_count);
     static void add_new_gov_off(gov_off* obj);
     static void store_deleted_gov_offs(string username, gov_off* arr, int size);
     static void store_updated_gov_offs(string username, gov_off* arr, int size);

     static void initiate_all_companies(company*& companies_list, int& companies_count);
     static void add_new_company(company* obj);
     static void store_companies(company* arr, int size);

     static void initiate_all_warehouses(warehouse*& warehouses_list, int& warehouse_count);
     static void add_new_warehouse(warehouse* obj);
     static void add_new_warehouse_vaccine(string ID, warehouse* wareobj, vaccines* obj);
     static void delete_warehouse_vaccine(string ID, warehouse* obj, string vID, string bID);


     static bool find_citizen(string CNIC);
     static bool already_vacinated(string CNIC);
     static void add_new_citizen(citizen* obj);
     static citizen load_citizen(string CNIC);
     static void store_vac_citizen(string cnic, vaccines* vac);
     static void reduce_vac_doses(string cnic);
     static int get_remaining_doses(string cnic);
     static string get_citizen_vacID(string cnic);


     static int get_num_registered_citizens();
     static int get_num_vacinated();
     static int get_num_partially_vacinated();
     static bool display_citizen_with_VacID(string ID);
     static bool display_num_vacinated();
     static bool display_num_partially_vacinated();
     

 };

 //------------------------ PERSON DEFINATIONS------------------------------------------------------------------

 person::person()
 {
     username = pass = firstname = lastname = email = contactNumber = CNIC = " ";

 }
 person::person(string un, string fn, string ln, string em, string cn, string No) :username(un), firstname(fn), lastname(ln), email(em), CNIC(cn), contactNumber(No) {}
 void person::input()
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
 void person::output()
 {
     cout << "First Name: " << firstname << endl;
     cout << "last Name: " << lastname << endl;
     cout << "Email Address: " << email << endl;
     cout << "Contact Number: " << contactNumber << endl;
     cout << "CNIC: " << CNIC << endl;
 }
 bool person::compare_username(string un)
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
 string person::file_details()
 {
     return  username + "," + firstname + "," + lastname + "," + email + "," + CNIC + "," + contactNumber + ",";
 }
 string person::file_logindetails()
 {
     return username + " " + pass + "\n";
 }
 void person::load_person_data(string un, string fn, string ln, string em, string cn, string No)
 {
     username = un;
     firstname = fn;
     lastname = ln;
     email = em;
     CNIC = cn;
     contactNumber = No;
 }
 //----------------------------------------------------------------------------------------------------------------

 //-------------------------SUPER ADMIN DEFINATIONS------------------------------------------------------------------
     super_admin::super_admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, cn, No)
     {
         // read admin, fdo, doctor, government officials from file
        admin_count = fdo_count = doctor_count = gov_off_count = 0;
        
        
        Filing::initiate_all_admin(admin_list, admin_count);
        Filing::initiate_all_fdo(fdo_list, fdo_count);
        Filing::initiate_all_gov_off(gov_off_list, gov_off_count);
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

     admin* super_admin::admin_obj(string un)
     {
         int i = find_admin_index(un);
         if (i != -1)
         {
             return &admin_list[i];
         }

     }
     fdo* super_admin::fdo_obj(string un)
     {
         int i = find_fdo_index(un);
         if (i != -1)
         {
             return &fdo_list[i];
         }

     }
     gov_off* super_admin::gov_off_obj(string un)
     {
         int i = find_gov_off_index(un);
         if (i != -1)
         {
             return &gov_off_list[i];
         }

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
         cout << "\n";
         fdo_list[fdo_count - 1].fdo_input();

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
     void super_admin::display_fdo()
     {
         for (int i = 0; i < fdo_count; i++)
         {
             fdo_list[i].fdo_output();
             cout << "\n";
         }
     }

     void super_admin::create_gov_off()
     {

         expand<gov_off>(gov_off_list, gov_off_count);

         gov_off_list[gov_off_count - 1].input_login_details();
         cout << "\n";
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
     void super_admin::display_gov_off()
     {
         for (int i = 0; i < gov_off_count; i++)
         {
             gov_off_list[i].output();
             cout << "\n";
         }
     }
     void super_admin::input_login_details() {}

     bool super_admin::does_vac_center_exists_in(string c)
     {
         for (int i = 0; i < fdo_count; i++)
         {
             if (fdo_list[i].compare_city(c))
             {
                 return true;
             }

         }

         return false;

     }

    super_admin* super_admin::self_instance = nullptr; // initialization


 //----------------------------------------------------------------------------------------------------------------

    
//------------------------ ADMIN DEFINATIONS------------------------------------------------------------------
    
    admin::admin()
    {
        if (companies_list == nullptr && warehouses_list == nullptr && fdo_list == nullptr)
        {
            cout << "ADMIN CONSTRUCTOR" << endl;
            companies_count = warehouse_count = fdo_count = 0;
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

        heading("WAREHOUSES");
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

//------------------------ FDO DEFINATIONS------------------------------------------------------------------

    fdo::fdo()
    {
        doc = new doctor;
        vacCount = 0;
    }

    void fdo::fdo_input()
    {
        cout << "\n->FDO Details\n\n";
        input();

        cout << "\n\n->Vaccine Center Details\n\n";
        cout << "Enter Name: ";
        cin >> vacCenterName;
        cout << "Enter City: ";
        do
        {
            cin >> city;
            if (super_admin::does_vac_center_exists_in(city))
            {
                print_error("\n[!] ERROR: The vaccine center already exists.\n");
                cout << "\nEnter again: ";
            }
        } while (super_admin::does_vac_center_exists_in(city));

        cout << "\n\n->Doctor Details\n\n";
        doc->input();
    }
    void fdo::fdo_output()
    {
        cout << "\n->FDO Details\n\n";
        output();

        cout << "\n\n->Vaccine Center Details\n\n";
        cout << "Enter Name: ";
        cout << "Name: " << vacCenterName << endl;
        cout << "City: " << city << endl;

        cout << "\n\n->Doctor Details\n\n";
        doc->output();
    }
    string fdo::file_details()
    {
        return person::file_details() + vacCenterName + "," + city + "," + to_string(vacCount)+ "," + doc->file_details() + "\n";
    }

    void fdo::load_data(string un, string fn, string ln, string em, string cn, string No, string vCenName, string City, string vCount, string un1, string fn1, string ln1, string em1, string cn1, string No1)
    {
        load_person_data(un, fn, ln, em, cn, No);
        vacCenterName = vCenName;
        city = City;
        vacCount = stoi(vCount);
        doc->load_person_data(un1, fn1, ln1, em1, cn1, No1);
    }

    void fdo::load_vaccine(string vID, string lbatch, string vName, string NoDoses, string price, string quantity)
    {
        expand<vaccines>(vac_list, vacCount);

        vac_list[vacCount - 1].load_data(vID, vName, NoDoses, price, quantity);
        vac_list[vacCount - 1].set_batchNo(stoi(lbatch));
    }

    void fdo::add_new_vaccine(vaccines* v)
    {
        string vID = v->get_vacID();
        string vName = v->get_vacName();
        string NoDoses = to_string(v->get_Nofdoses());
        string price = to_string(v->get_price());
        string quantity = to_string(v->get_quantity());
        int lbatch = v->get_batchNo();

        expand<vaccines>(vac_list, vacCount);

        vac_list[vacCount - 1].load_data(vID, vName, NoDoses, price, quantity);
        vac_list[vacCount - 1].set_batchNo(lbatch);
    }
    void fdo::output_vaccines()
    {
        for (int i = 0; i < vacCount; i++)
        {
            cout << i + 1 << ".\n";
            vac_list[i].vaccineOutput();
            cout << "\n";
        }
    }
    //menu option
    void fdo::get_vaccine()
    {
        string wareID;

        string vacID;
        int batchID, vacIndex;

        heading("WAREHOUSES");
        admin::display_warehouse();

        cout << "\n\nEnter the ID of warehouse: ";
        do
        {
            cin >> wareID;
            if (admin::find_warehouse_index(wareID) == -1)
            {
                print_error("\n[!] ERROR: The warehouse entered doesn't exist.\n");
                cout << "Enter again: ";
            }


        } while (admin::find_warehouse_index(wareID) == -1);

        warehouse* warePtr = admin::get_warehouse(admin::find_warehouse_index(wareID));

        heading("VACCINES");
        warePtr->vaccinesOutput();


        do
        {
            cout << "\n\nEnter the vaccine ID: ";
            cin >> vacID;
            cout << "Enter the batch ID: ";
            batchID = safe_input<int>();

            if (warePtr->find_valid_vacID_batchID(vacID, batchID) == -1)
            {
                print_error("\n[!] ERROR: The vacID/batchID entered doesn't exist.\n");
            }


        } while (warePtr->find_valid_vacID_batchID(vacID, batchID) == -1);

        vacIndex = warePtr->find_valid_vacID_batchID(vacID, batchID);

        vaccines* vacPtr = warePtr->get_vaccine(vacIndex);

        add_new_vaccine(vacPtr);

        Filing::add_new_fdo_vaccine(username, this, vacPtr);

        warePtr->remove_vaccine(vacID, batchID);

        cout << "\n\n[$]: The vaccine has been transfered successfully." << endl;
    } //

    void fdo::vacinate_citizen()
    {
        int i;
        string cnic;
        cout << "Enter your CNIC: ";
        do
        {
            cin >> cnic;
            if (!is_valid_cnic(cnic))
            {
                print_error("\n[!] ERROR: The CNIC entered in not valid.\n\n");
                cout << "Enter again: ";
            }
        } while (!is_valid_cnic(cnic));

        if (Filing::find_citizen(cnic))
        {
            citizen ctz = Filing::load_citizen(cnic);

            if (!Filing::already_vacinated(cnic))
            {

                if (ctz.get_eligibity())
                {
                    cout << "\n\n->CITIZEN INFO\n\n";
                    ctz.citizen_output();


                    cout << "\n\nYou are eligible for the vaccine.\n\n";
                    cout << "Sending to the doctor to measure  blood pressure, oxygen level, and glucose level.\n\n";

                    cout << "->DOCTOR PORTAL\n\n";
                    if (doc->is_health_ok())
                    {
                        cout << "\nYour health condition is OK for the vaccination process\n\n";

                        cout << "->SELECT VACCINE\n\n";
                        output_vaccines();

                        cout << "Enter the index of vaccine: ";
                        do
                        {
                            cin >> i;
                            if (i > vacCount || i < 0)
                            {
                                print_error("\n[!] ERROR: The index entered in not valid.\n\n");
                                cout << "Enter again: ";
                            }
                        } while (i > vacCount || i < 0);

                        Filing::store_vac_citizen(cnic, &vac_list[i-1]);

                        cout << "\n\nYOU HAVE RECEIVED YOUR DOSE !\n\n";
                    }
                    else
                    {
                        print_error("\n[!] ERROR: Your vitals are safe for vaccination.\n\n");
                    }
                }
                else
                {
                    print_error("\n[!] ERROR: You are not eligible for vaccine\n\n");
                }
            }
            else
            {
                if (Filing::get_remaining_doses(cnic) != 0)
                {
                    cout << "\n\n->CITIZEN INFO\n\n";
                    ctz.citizen_output();

                    cout << "->DOCTOR PORTAL\n\n";
                    if (doc->is_health_ok())
                    {
                        cout << "\nYour health condition is OK for the vaccination process\n\n";

                        string vacID = Filing::get_citizen_vacID(cnic);

                        cout << "\nVaccine ID: " << vacID << endl;

                        cout << "\n\nYOU HAVE RECEIVED YOUR DOSE !\n\n";
                        Filing::reduce_vac_doses(cnic);
                    }
                    else
                    {
                        print_error("\n[!] ERROR: Your vitals are safe for vaccination.\n\n");
                    }
                }
                else
                {
                    print_error("\n[!] ERROR: You are fully vaccinated\n\n");
                }

            }
        }
        else
        {
            print_error("\n[!] ERROR: You are not registered\n\n");
        }
    }

    bool fdo::compare_city(string c)
    {
        return city == c;
    }

    void fdo::input_login_details()
    {
        string un, un_num, p;
        bool correct_input = false;

        while (!correct_input)
        {
            try
            {
                un = "FD";
                cout << "Enter the username: FD";
                cin >> un_num;

                if (!regex_match(un_num, valid_user_num))
                {
                    throw invalid_username();
                }

                un += un_num; // concats the digits with "AD"

                if (Filing::find_fdo(un))
                {
                    throw username_exists();
                }

                cout << "\nEnter the password: ";
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

//------------------------ WAREHOUSE DEFINATIONS------------------------------------------------------------------

    void warehouse::remove_vaccine(string vacID, int batchID)
    {
        int i = find_valid_vacID_batchID(vacID, batchID);

        total_vac_amount -= vac_ware[i].get_quantity();

        del<vaccines>(vac_ware, vaccineCount, i);
        vaccineCount--;

        Filing::delete_warehouse_vaccine(houseID, this, vacID, to_string(batchID));

    }
    bool warehouse::is_enough_space(int x)
    {
        return (limit - total_vac_amount) >= x;
    }
    warehouse::warehouse()
    {
        total_vac_amount = vaccineCount = 0;
    }

    void warehouse::houseInput()
    {
        cout << "Enter Warehouse ID: ";
        cin >> houseID;
        cout << "Enter Storage capacity: ";
        cin >> limit;

    }

    void warehouse::houseOutput()
    {
        cout << "Warehouse ID: " << houseID << endl;
        cout << "Current Vaccine amount: " << total_vac_amount << endl;
        cout << "Storage limit: " << limit << endl;
        cout << "No of batches available: " << vaccineCount << endl;
    }

    void warehouse::vaccinesOutput()
    {
        for (int i = 0; i < vaccineCount; i++)
        {
            cout << "\n";
            vac_ware[i].vaccineOutput(true);
        }
    }

    void warehouse::load_vaccine(string vID, string lbatch, string vName, string NoDoses, string price, string quantity)
    {
        expand<vaccines>(vac_ware, vaccineCount);

        vac_ware[vaccineCount - 1].load_data(vID, vName, NoDoses, price, quantity);
        vac_ware[vaccineCount - 1].set_batchNo(stoi(lbatch));
    }

    vaccines* warehouse::get_vaccine(int i)
    {
        return &vac_ware[i];
    }

    void warehouse::add_new_vaccine(vaccines* v, int lbatch)
    {
        string vID = v->get_vacID();
        string vName = v->get_vacName();
        string NoDoses = to_string(v->get_Nofdoses());
        string price = to_string(v->get_price());
        string quantity = to_string(v->get_quantity());

        expand<vaccines>(vac_ware, vaccineCount);

        vac_ware[vaccineCount - 1].load_data(vID, vName, NoDoses, price, quantity);
        vac_ware[vaccineCount - 1].set_batchNo(lbatch);

        total_vac_amount += v->get_quantity();
    }

    string warehouse::file_details()
    {
        return houseID + "," + to_string(limit) + "," + to_string(total_vac_amount) + "," + to_string(vaccineCount) + ",\n";
    }

    void warehouse::load_data(string id, string l, string vac_amt, string vacC)
    {
        houseID = id;
        limit = stoi(l);
        total_vac_amount = stoi(vac_amt);
        vaccineCount = stoi(vacC);
    }

    bool warehouse::compare_warehouseID(string n)
    {
        return n == houseID;
    }

    int warehouse::find_valid_vacID_batchID(string vID, int bID)
    {
        for (int i = 0; i < vaccineCount; i++)
        {
            if (vID == vac_ware[i].get_vacID() && bID == vac_ware[i].get_batchNo())
            {
                return i;
            }
        }

        return -1;
    }
    //----------------------------------------------------------------------------------------------------------------

    //------------------------ DOCTOR DEFINATIONS------------------------------------------------------------------
    doctor::doctor()
    {
        username = "doctor";
    }
    bool doctor::is_health_ok()
    {
        int bloodPressure, OxyLvl, GlucoseLvl;

        cout << "Enter Blood Pressure: ";
        bloodPressure = safe_input<int>();
        cout << "Enter Oxygen Level: ";
        OxyLvl = safe_input<int>();
        cout << "Enter GlucoseLvl: ";
        GlucoseLvl = safe_input<int>();

        if (bloodPressure <= 120 && OxyLvl >= 95 && GlucoseLvl >= 70 && GlucoseLvl <= 100)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //----------------------------------------------------------------------------------------------------------------

    //------------------------ COMPANY DEFINATIONS------------------------------------------------------------------
    company::company()
    {
        vac = new vaccines;
        lastBatchNo = 0;
    }
    void company::companyInput() //admin can add companies
    {
        cout << "Enter company name: ";
        cin >> companyName;

        vac->vaccineInput();
    }
    void company::companyoutput() //review company details
    {
        cout << "Company Name: " << companyName << endl;
        vac->vaccineOutput();
    }

    vaccines* company::get_vac()
    {
        return vac;
    }
    int company::get_vac_quantity()
    {
        return vac->get_quantity();
    }

    string company::file_details()
    {
        return companyName + "," + to_string(lastBatchNo) + "," + vac->get_vacID() + "," + vac->get_vacName() + "," + to_string(vac->get_Nofdoses()) + "," + to_string(vac->get_price()) + "," + to_string(vac->get_quantity()) + ",\n";
    }

    bool company::compare_companyName(string n)
    {
        return n == companyName;
    }

    void company::load_data(string cname, string LbNo, string vID, string vName, string NoDoses, string price, string quantity)
    {
        companyName = cname;
        lastBatchNo = stoi(LbNo);
        vac->load_data(vID, vName, NoDoses, price, quantity);
    }

    int company::get_batchID()
    {
        lastBatchNo++;
        return lastBatchNo;
    }
    //----------------------------------------------------------------------------------------------------------------

    
    //------------------------ VACCINES DEFINATIONS------------------------------------------------------------------
    void vaccines::vaccineInput()
    {
        cout << "Vaccine ID: ";
        cin >> vaccineID;
        cout << "Enter Vaccine Name: ";
        getline(cin >>ws, vaccineName);
        cout << "Enter no of doses: ";
        do
        {
            Nofdoses = safe_input<int>();
            if (Nofdoses <= 0)
            {
                print_error("\n[!] ERROR: The number of doses must be greater than zero.\n\n");
                cout << "Enter again: ";
            }

        } while (Nofdoses <= 0);

        cout << "Enter the price of vaccine: ";
        do
        {
            price = safe_input<int>();
            if (price <= 0)
            {
                print_error("\n[!] ERROR: The price must be greater than zero.\n\n");
                cout << "Enter again: ";
            }

        } while (price <= 0);

        cout << "Enter the quantity of vaccine: ";
        do
        {
            quantity = safe_input<int>();
            if (quantity <= 0)
            {
                print_error("\n[!] ERROR: The quantity must be greater than zero.\n\n");
                cout << "Enter again: ";
            }

        } while (quantity <= 0);
    }
    void vaccines::vaccineOutput(bool bNO) // bNO tells wheter to print BatchNo or not
    {
        cout << "Vaccine ID: " << vaccineID << endl;
        cout << "Vaccine Name: " << vaccineName << endl;
        cout << "No. of doses: " << Nofdoses << endl;
        cout << "Price of vaccine: " << price << endl;
        cout << "Quantity of vaccine: " << quantity << endl;
        if (bNO)
            cout << "BatchID: " << batchNo << endl;
    }

    string vaccines::file_details()
    {
        return vaccineID + "," + to_string(batchNo) + "," + vaccineName + "," + to_string(Nofdoses) + "," + to_string(price) + "," + to_string(quantity) + ",\n";
    }
    void vaccines::load_data(string vID, string vName, string NoDoses, string p, string q)
    {
        vaccineID = vID;
        vaccineName = vName;
        Nofdoses = stoi(NoDoses);
        price = stoi(p);
        quantity = stoi(q);
    }
    void vaccines::set_batchNo(int num)
    {
        batchNo = num;
    }

    void vaccines::set_quantity(int q)
    {
        quantity = q;
    }

    int vaccines::get_batchNo()
    {
        return batchNo;
    }

    string vaccines::get_vacName()
    {
        return vaccineName;
    }

    string vaccines::get_vacID()
    {
        return vaccineID;
    }

    int vaccines::get_Nofdoses()
    {
        return Nofdoses;
    }
    int vaccines::get_price()
    {
        return price;
    }

    int vaccines::get_quantity()
    {
        return quantity;
    }
    //----------------------------------------------------------------------------------------------------------------


    //------------------------ GOVERNMENT OFFICIAL DEFINATIONS------------------------------------------------------------------
    void gov_off::input_login_details() {
        string un, un_num, p;
        bool correct_input = false;

        while (!correct_input)
        {
            try
            {
                un = "GO";
                cout << "Enter the username: GO";
                cin >> un_num;

                if (!regex_match(un_num, valid_user_num))
                {
                    throw invalid_username();
                }

                un += un_num; // concats the digits with "GO"

                if (Filing::find_gov_off(un))
                {
                    throw username_exists();
                }

                cout << "\nEnter the password: ";
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
    void gov_off::load_gov_off_data(string un, string fn, string ln, string em, string cn, string No)
    {
        load_person_data(un, fn, ln, em, cn, No);
    }
    void gov_off::percentage_vac_population()
    {
        double total_population = Filing::get_num_registered_citizens();
        double vac_population = Filing::get_num_vacinated();

        double vac_percentage = (vac_population / total_population) * 100.0;

        cout << "Total registered population: " << total_population << endl;
        cout << "Total vaccinated population: " << vac_population << endl;

        cout << "\nThe percentage of vaccinated population: " << vac_percentage << endl;
        cout << "\n\n";
    }
    void gov_off::percentage_partially_vac_population()
    {
        double total_population = Filing::get_num_registered_citizens();
        double partially_vac_population = Filing::get_num_partially_vacinated();

        double partially_vac_percentage = (partially_vac_population / total_population) * 100.0;

        cout << "Total registered population: " << total_population << endl;
        cout << "Total vaccinated population: " << partially_vac_population << endl;

        cout << "\nThe percentage of partially vaccinated population: " << partially_vac_percentage << endl;
        cout << "\n\n";
    }
    void gov_off::display_vac_population()
    {
        
        if (!Filing::display_num_vacinated())
        {
            print_error("\n[!] ERROR: There are no fully vacinated citizens.\n\n");
        }
    }
    void gov_off::display_partially_vac_population()
    {
        if (!Filing::display_num_partially_vacinated())
        {
            print_error("\n[!] ERROR: There are no partially vacinated citizens.\n\n");
        }
    }
    void gov_off::display_citizen_with_VacID()
    {
        string ID;
        
        cout << "\nEnter the Vaccine ID: ";
        cin >> ID;

        if (!Filing::display_citizen_with_VacID(ID))
        {
            print_error("\n[!] ERROR: There vacinated citizens with the following vaccine ID.\n\n");
        }
    }
    void gov_off::display_graph()
    {
        double total_population = Filing::get_num_registered_citizens();
        double vac_population = Filing::get_num_vacinated();
        double partially_vac_population = Filing::get_num_partially_vacinated();

        int partially_vac_percentage = (partially_vac_population / total_population) * 100.0;
        int vac_percentage = (vac_population / total_population) * 100.0;

        cout << "\nThe percentage of vaccinated population: " << vac_percentage << "%" << endl;
        cout << "\nThe percentage of partially vaccinated population: " << partially_vac_percentage << "%" << endl;

        const int chart_height = 20;
        const int max_count = 100;
        int arr[2] = { vac_percentage, partially_vac_percentage };
        int max = 100;

        cout << "\n\n";
        for (int current_height = chart_height; current_height >= 0; --current_height)
        {
            for (int i = 0; i < 2; i++)
            {
                const int bar_height = (arr[i] * chart_height) / max_count;
                int values = (max * chart_height) / max_count;

                if (values == current_height && i == 0)
                {
                    cout << setw(5) << setfill(' ') << max << "%";
                    max -= 10;
                }
                else if (i == 0)
                {
                    cout << "      ";
                }

                if (bar_height < current_height)
                    std::cout << "                         "; // we're still above the bar
                else if (bar_height == current_height)
                    std::cout << "            _            "; // reached the top of the bar
                else // bar_height > current_height
                    std::cout << "           | |           "; // now the rest of the bar ...
            }
            cout << '\n';
        }
        cout << "\n\t   Fully Vaccinated \t  Partially Vaccinated\n\n";

    }
    //----------------------------------------------------------------------------------------------------------------

    //------------------------ CITIZEN DEFINATIONS------------------------------------------------------------------
    citizen::citizen()
    {
        username = "NULL";
        is_eligible = true;
    }

    citizen::citizen(string un, string fn, string ln, string em, string cn, string No, string Age, string bT, string City)
    {

        is_eligible = true;
        load_person_data("NULL", fn, ln, em, cn, No);
        age = stoi(Age);
        bloodType = bT;
        city = City;

        if (age < 5)
        {
            is_eligible = false;
        }
    }
    void citizen::citizen_input()
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

        if (age < 5)
        {
            is_eligible = false;
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

    void citizen::citizen_output()
    {
        output();
        cout << "Age: " << age << endl;
        cout << "Blood Group: " << bloodType << endl;
        cout << "City: " << city << endl;
    }

    bool citizen::get_eligibity()
    {
        return is_eligible;
    }

    string citizen::file_details()
    {
        return person::file_details() + to_string(age) + "," + bloodType + "," + city + ",\n";
    }

    void citizen::load_citizen(string un, string fn, string ln, string em, string cn, string No, string Age, string bT, string City)
    {
        load_person_data(un, fn, ln, em, cn, No);
        age = stoi(Age);
        bloodType = bT;
        city = City;

        if (age < 5)
        {
            is_eligible = false;
        }
    }
    //----------------------------------------------------------------------------------------------------------------


    //------------------------ FILING DEFINATIONS------------------------------------------------------------------
    bool Filing::find_super_admin(string username)
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
    bool Filing::is_valid_login_super_admin(string username, string pass)
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
    super_admin* Filing::login_super_admin(string username)
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

    bool Filing::find_admin(string username)
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
    bool Filing::is_valid_login_admin(string username, string pass)
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

    void Filing::initiate_all_admin(admin*& admin_list, int& admin_count)
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
            //cout << details[0] << endl;
            //cout << admin_count << endl;
            expand<admin>(admin_list, admin_count);

            admin_list[admin_count - 1].load_admin_data(details[0], details[1], details[2], details[3], details[4], details[5], details[6]);
        }

    }

    void Filing::add_new_admin(admin* obj)
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
    void Filing::store_deleted_admins(string username, admin* arr, int size)
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
    void Filing::store_updated_admins(string username, admin* arr, int size)
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

    bool Filing::find_doctor(string username)
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
    bool Filing::is_valid_login_doctor(string username, string pass)
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
    void Filing::add_new_doctor(doctor* obj)
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
    void Filing::store_deleted_doctors(string username, doctor* arr, int size)
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
    void Filing::store_updated_doctors(string username, doctor* arr, int size)
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

    bool Filing::find_fdo(string username)
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
    bool Filing::is_valid_login_fdo(string username, string pass)
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
    void Filing::initiate_all_fdo(fdo*& fdos_list, int& fdo_count)
    {
        ifstream details_file(FILE_PATH + "fdo_details.csv");
        int count = 0;
        string line, word;
        string fdo_details[15], v_details[6];
        //string houseID limit total_vac_amount vaccineCount

        cout << "ware\n";
        while (getline(details_file, line))
        {
            cout << "fdo\n";
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                cout << word << endl;
                fdo_details[count++] = word;
            }

            expand<fdo>(fdos_list, fdo_count);

            fdos_list[fdo_count - 1].load_data(fdo_details[0], fdo_details[1], fdo_details[2], fdo_details[3], fdo_details[4], fdo_details[5], fdo_details[6], fdo_details[7], "0", fdo_details[9], fdo_details[10], fdo_details[11], fdo_details[12], fdo_details[13], fdo_details[14]);


            for (int i = 0; i < stoi(fdo_details[8]); i++)
            {
                count = 0;
                getline(details_file, line);
                stringstream str1(line);

                while (getline(str1, word, ','))
                {
                    v_details[count++] = word;
                }

                fdos_list[fdo_count - 1].load_vaccine(v_details[0], v_details[1], v_details[2], v_details[3], v_details[4], v_details[5]);
            }
        }

    }
    void Filing::add_new_fdo(fdo* obj)
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
    void Filing::add_new_fdo_vaccine(string ID, fdo* fdoobj, vaccines* obj)
    {
        ifstream details_file(FILE_PATH + "fdo_details.csv");
        ofstream temp(FILE_PATH + "temp.csv");

        string line, word;

        int count = 0;
        string details[15];
        //username firstname lastname email contactNumber CNIC vacCenterName, city vacCount doc_username firstname lastname email contactNumber CNIC

        if (!details_file)
        {
            //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {

            while (getline(details_file, line))
            {
                count = 0;
                stringstream str(line);
                while (getline(str, word, ','))
                {
                    details[count++] = word;
                }

                if (details[0] != ID)
                {
                    temp << line;

                    if (line.size() != 0)
                        if (line[line.size() - 1] != '\n')
                            temp << "\n";

                }
                else
                {
                    temp << fdoobj->file_details();
                }

                for (int i = 0; i < stoi(details[8]); i++)
                {
                    getline(details_file, line);
                    temp << line;

                    if (line.size() != 0)
                        if (line[line.size() - 1] != '\n')
                            temp << "\n";
                }

                if (details[0] == ID)
                {

                    temp << obj->file_details();
                }

            }

            details_file.close();
            temp.close();

            ofstream details_file("fdo_details.csv");
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
    void Filing::store_deleted_fdos(string username, fdo* arr, int size)
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
    void Filing::store_updated_fdos(string username, fdo* arr, int size)
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

    bool Filing::find_gov_off(string username)
    {
        ifstream login_file(FILE_PATH + "gov_off_login_details.txt");

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
    bool Filing::is_valid_login_gov_off(string username, string pass)
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
    void Filing::initiate_all_gov_off(gov_off*& gov_off_list, int& gov_off_count)
    {
        ifstream details_file(FILE_PATH + "gov_off_details.csv");
        int count = 0;
        string line, word;
        string details[6];
        //string o_username, fn, ln, em, cn, No;

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }
            //cout << details[0] << endl;
            //cout << admin_count << endl;
            expand<gov_off>(gov_off_list, gov_off_count);

            gov_off_list[gov_off_count - 1].load_gov_off_data(details[0], details[1], details[2], details[3], details[4], details[5]);
        }

    }
    void Filing::add_new_gov_off(gov_off* obj)
    {
        ofstream details_file(FILE_PATH + "gov_off_details.csv", ios::app);
        ofstream login_file(FILE_PATH + "gov_off_login_details.txt", ios::app);

        if (!details_file || !login_file)
        {
            //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
        }
        else
        {
            details_file << obj->file_details() << endl;
            login_file << obj->file_logindetails();

            details_file.close();
            login_file.close();
        }
    }
    void Filing::store_deleted_gov_offs(string username, gov_off* arr, int size)
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
                details_file << arr[i].file_details() << endl;
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
    void Filing::store_updated_gov_offs(string username, gov_off* arr, int size)
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
                details_file << arr[i].file_details() << endl;
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

    void Filing::initiate_all_companies(company*& companies_list, int& companies_count)
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
    void Filing::add_new_company(company* obj)
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
    void Filing::store_companies(company* arr, int size)
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

    void Filing::initiate_all_warehouses(warehouse*& warehouses_list, int& warehouse_count)
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
    void Filing::add_new_warehouse(warehouse* obj)
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
    void Filing::add_new_warehouse_vaccine(string ID, warehouse* wareobj, vaccines* obj)
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

                    if (line.size() != 0)
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
    void Filing::delete_warehouse_vaccine(string ID, warehouse* obj, string vID, string bID)
    {
        ifstream details_file(FILE_PATH + "warehouse_details.csv");
        ofstream temp(FILE_PATH + "temp.csv");

        string line;
        string warehouseID, limit, vacamt, vacCount;
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
                getline(str, vacamt, ',');
                getline(str, vacCount, ',');



                if (warehouseID == ID)
                {
                    temp << obj->file_details();
                    for (int i = 0; i < stoi(vacCount); i++)
                    {
                        getline(details_file, line);

                        stringstream str1(line);
                        getline(str1, vacID, ',');
                        getline(str1, batchID, ',');

                        if (vID != vacID || bID != batchID)
                        {
                            temp << line;

                            if (line.size() != 0)
                                if (line[line.size() - 1] != '\n')
                                    temp << "\n";
                        }

                    }
                }
                else
                {
                    temp << line;
                    if (line.size() != 0)
                        if (line[line.size() - 1] != '\n')
                            temp << "\n";

                    for (int i = 0; i < stoi(vacCount); i++)
                    {
                        getline(details_file, line);
                        temp << line;

                        if (line.size() != 0)
                            if (line[line.size() - 1] != '\n')
                                temp << "\n";
                    }
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
                        details_file << "\n";
            }

            details_file.close();
            temp.close();
        }
    }

    bool Filing::find_citizen(string CNIC)
    {
        ifstream details_file(FILE_PATH + "citizen_details.csv");

        int count = 0;
        string line, word;
        string details[9];
        //string un fn ln em cn No Age bT City

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (CNIC == details[4])
            {
                return true;
            }
        }

        return false;
    }
    bool Filing::already_vacinated(string CNIC)
    {
        ifstream details_file(FILE_PATH + "citizen_vac.csv");
        string line, word;
        string c, vac, vacDoses;
        while (getline(details_file, line))
        {

            stringstream str(line);
            getline(str, c, ',');
            getline(str, vac, ',');
            getline(str, vacDoses, ',');


            if (CNIC == c)
            {
                return true;
            }
        }

        return false;
    }
    void Filing::add_new_citizen(citizen* obj)
    {
        ofstream details_file(FILE_PATH + "citizen_details.csv", ios::app);

        if (!details_file)
        {
            print_error("\n\nERROR IN OPENING THE FILE: citizen_details.csv\n\n");
        }
        else
        {
            details_file << obj->file_details();

            details_file.close();
        }
    }
    citizen Filing::load_citizen(string CNIC)
    {
        ifstream details_file(FILE_PATH + "citizen_details.csv");

        int count = 0;
        string line, word;
        string details[9];
        //string un fn ln em cn No Age bT City

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (CNIC == details[4])
            {
                return citizen(details[0], details[1], details[2], details[3], details[4], details[5], details[6], details[7], details[8]);
            }
        }

    }
    void Filing::store_vac_citizen(string cnic, vaccines* vac)
    {
        ofstream details_file(FILE_PATH + "citizen_vac.csv", ios::app);

        details_file << cnic + "," + vac->get_vacID() + "," + to_string(vac->get_Nofdoses()-1) + ",\n";

        details_file.close();
    }
    void Filing::reduce_vac_doses(string cnic)
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");
        ofstream temp(FILE_PATH + "temp.csv");

        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (cnic == details[0])
            {
                temp << details[0] + "," + details[1] + "," + to_string(stoi(details[2])-1) + ",\n";
            }
            else
            {
                temp << line;

                if (line.size() != 0)
                    if (line[line.size() - 1] != '\n')
                        temp << "\n";
            }
        }

        details_file.close();
        temp.close();

        ofstream detail_file("citizen_vac.csv");
        ifstream temp1("temp.csv");

        while (getline(temp1, line))
        {
            detail_file << line;

            if (line.size() != 0)
                if (line[line.size() - 1] != '\n')
                {
                    detail_file << "\n"; //Pakistani tughe salaam :))
                }
        }

        details_file.close();
        temp.close();

    }

    int Filing::get_remaining_doses(string cnic)
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");


        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (cnic == details[0])
            {
                return stoi(details[2]);
            }
            
        }

        details_file.close();

    }
    string Filing::get_citizen_vacID(string cnic)
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");


        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (cnic == details[0])
            {
                return details[1];
            }

        }

        details_file.close();

    }

    int Filing::get_num_registered_citizens()
    {
        ifstream details_file(FILE_PATH + "citizen_details.csv");

        int count = 0;
        string line;
        //string un fn ln em cn No Age bT City

        while (getline(details_file, line))
        {
            count++;
        }
        details_file.close();
        return count;
    }
    int Filing::get_num_vacinated()
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");

        int num = 0;;
        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (stoi(details[2]) == 0)
            {
                num++;
            }

        }

        details_file.close();
        return num;
    }
    int Filing::get_num_partially_vacinated()
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");

        int num = 0;;
        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (stoi(details[2]) != 0)
            {
                num++;
            }

        }

        details_file.close();
        return num;
    }
    bool Filing::display_citizen_with_VacID(string ID)
    {
        ifstream details_file(FILE_PATH + "citizen_vac.csv");

        citizen temp_ctz;
        bool found = false;
        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (details[1] == ID)
            {
                found = true;

                temp_ctz = load_citizen(details[0]);
                temp_ctz.citizen_output();
                cout << "\n";
            }

        }

        details_file.close();
        return found;
    }
    bool Filing::display_num_vacinated()
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");

        citizen temp_ctz;
        bool found = false;

        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (stoi(details[2]) == 0)
            {
                found = true;

                temp_ctz = load_citizen(details[0]);
                temp_ctz.citizen_output();
                cout << "\n";
            }

        }

        details_file.close();
        return found;
    }
    bool Filing::display_num_partially_vacinated()
    {

        ifstream details_file(FILE_PATH + "citizen_vac.csv");

        citizen temp_ctz;
        bool found = false;

        int count = 0;
        string line, word;
        string details[3];
        //string cnic vacID VacDoses

        while (getline(details_file, line))
        {
            count = 0;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                details[count++] = word;
            }

            if (stoi(details[2]) != 0)
            {
                found = true;

                temp_ctz = load_citizen(details[0]);
                temp_ctz.citizen_output();
                cout << "\n";
            }

        }

        details_file.close();
        return found;
    }


    //----------------------------------------------------------------------------------------------------------------