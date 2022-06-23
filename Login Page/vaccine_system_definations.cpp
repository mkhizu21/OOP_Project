//#include "vaccine_system.h"
//
//
//
//
////-------------------------SUPER ADMIN DEFINATIONS------------------------------------------------------------------
//super_admin::super_admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, cn, No)
//{
//    // read admin, fdo, doctor, government officials from file
//    admin_count = fdo_count = doctor_count = gov_off_count = 0;
//
//
//    Filing::initiate_all_admin(admin_list, admin_count);
//    Filing::initiate_all_fdo(fdo_list, fdo_count);
//}
//int super_admin::find_admin_index(string un)
//{
//    for (int i = 0; i < admin_count; i++)
//    {
//        if (admin_list[i].compare_username(un))
//        {
//            return i;
//        }
//    }
//
//    return -1;
//}
//int super_admin::find_fdo_index(string un)
//{
//    for (int i = 0; i < fdo_count; i++)
//    {
//        if (fdo_list[i].compare_username(un))
//        {
//            return i;
//        }
//    }
//
//    return -1;
//}
//int super_admin::find_doctor_index(string un)
//{
//    for (int i = 0; i < doctor_count; i++)
//    {
//        if (doctor_list[i].compare_username(un))
//        {
//            return i;
//        }
//    }
//
//    return -1;
//}
//int super_admin::find_gov_off_index(string un)
//{
//    for (int i = 0; i < gov_off_count; i++)
//    {
//        if (gov_off_list[i].compare_username(un))
//        {
//            return i;
//        }
//    }
//
//    return -1;
//}
//
//
//super_admin* super_admin::getInstance(string un, string fn, string ln, string em, string cn, string No)
//{
//    if (self_instance == nullptr)
//        self_instance = new super_admin(un, fn, ln, em, cn, No);
//
//    return self_instance;
//}
//
//void super_admin::create_admin()
//{
//
//    expand<admin>(admin_list, admin_count);
//
//    admin_list[admin_count - 1].input_login_details();
//    admin_list[admin_count - 1].input();
//
//    Filing::add_new_admin(&admin_list[admin_count - 1]);
//}
//void super_admin::delete_admin()
//{
//    if (admin_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of admin: ";
//        cin >> un;
//
//        i = find_admin_index(un);
//
//        if (i != -1)
//        {
//            del<admin>(admin_list, admin_count, i);
//            admin_count--;
//            Filing::store_deleted_admins(un, admin_list, admin_count);
//        }
//        else
//        {
//            print_error("[!] ERROR: The entered username doesn't exists.");
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no admin to delete.\n\n");
//    }
//}
//void super_admin::update_admin()
//{
//    if (admin_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of admin: ";
//        cin >> un;
//
//        i = find_admin_index(un);
//
//        if (i != -1)
//        {
//            admin_list[i].input_login_details();
//            admin_list[i].input();
//
//            Filing::store_updated_admins(un, admin_list, admin_count);
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no admin to update.\n\n");
//    }
//
//}
//void super_admin::display_admin()
//{
//
//    for (int i = 0; i < admin_count; i++)
//    {
//        admin_list[i].adminOutput();
//        cout << "\n";
//    }
//}
//
//void super_admin::store_admins()
//{
//    Filing::store_updated_admins("", admin_list, admin_count);
//}
//
//void super_admin::create_doctor()
//{
//
//    expand<doctor>(doctor_list, doctor_count);
//
//    doctor_list[doctor_count - 1].input_login_details();
//    doctor_list[doctor_count - 1].input();
//
//    Filing::add_new_doctor(&doctor_list[doctor_count - 1]);
//}
//void super_admin::delete_doctor()
//{
//    if (doctor_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of doctor: ";
//        cin >> un;
//
//        i = find_doctor_index(un);
//
//        if (i != -1)
//        {
//            del<doctor>(doctor_list, doctor_count, i);
//            doctor_count--;
//            Filing::store_deleted_doctors(un, doctor_list, doctor_count);
//        }
//        else
//        {
//            //error messages display karwa
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no doctor to delete.\n\n");
//    }
//}
//void super_admin::update_doctor()
//{
//    if (doctor_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of doctor: ";
//        cin >> un;
//
//        i = find_doctor_index(un);
//
//        if (i != -1)
//        {
//            doctor_list[i].input_login_details();
//            doctor_list[i].input();
//
//            Filing::store_updated_doctors(un, doctor_list, doctor_count);
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no doctor to update.\n\n");
//    }
//
//}
//
//void super_admin::create_fdo()
//{
//
//    expand<fdo>(fdo_list, fdo_count);
//
//    fdo_list[fdo_count - 1].input_login_details();
//    fdo_list[fdo_count - 1].fdo_input();
//
//    Filing::add_new_fdo(&fdo_list[fdo_count - 1]);
//}
//void super_admin::delete_fdo()
//{
//    if (fdo_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of fdo: ";
//        cin >> un;
//
//        i = find_fdo_index(un);
//
//        if (i != -1)
//        {
//            del<fdo>(fdo_list, fdo_count, i);
//            fdo_count--;
//            Filing::store_deleted_fdos(un, fdo_list, fdo_count);
//        }
//        else
//        {
//            //error messages display karwa
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no fdo to delete.\n\n");
//    }
//}
//void super_admin::update_fdo()
//{
//    if (fdo_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of fdo: ";
//        cin >> un;
//
//        i = find_fdo_index(un);
//
//        if (i != -1)
//        {
//            fdo_list[i].input_login_details();
//            fdo_list[i].input();
//
//            Filing::store_updated_fdos(un, fdo_list, fdo_count);
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no fdo to update.\n\n");
//    }
//
//}
//void super_admin::display_fdo()
//{
//    for (int i = 0; i < fdo_count; i++)
//    {
//        fdo_list[i].fdo_output();
//        cout << "\n";
//    }
//}
//
//void super_admin::create_gov_off()
//{
//
//    expand<gov_off>(gov_off_list, gov_off_count);
//
//    gov_off_list[gov_off_count - 1].input_login_details();
//    gov_off_list[gov_off_count - 1].input();
//
//    Filing::add_new_gov_off(&gov_off_list[gov_off_count - 1]);
//}
//void super_admin::delete_gov_off()
//{
//    if (gov_off_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of gov_off: ";
//        cin >> un;
//
//        i = find_gov_off_index(un);
//
//        if (i != -1)
//        {
//            del<gov_off>(gov_off_list, gov_off_count, i);
//            gov_off_count--;
//            Filing::store_deleted_gov_offs(un, gov_off_list, gov_off_count);
//        }
//        else
//        {
//            //error messages display karwa
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no gov_off to delete.\n\n");
//    }
//}
//void super_admin::update_gov_off()
//{
//    if (gov_off_count > 0)
//    {
//        int i;
//        string un;
//        cout << "Enter the username of gov_off: ";
//        cin >> un;
//
//        i = find_gov_off_index(un);
//
//        if (i != -1)
//        {
//            gov_off_list[i].input_login_details();
//            gov_off_list[i].input();
//
//            Filing::store_updated_gov_offs(un, gov_off_list, gov_off_count);
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no gov_off to update.\n\n");
//    }
//
//}
//void super_admin::input_login_details() {}
//
//super_admin* super_admin::self_instance = nullptr; // initialization
//
//
////----------------------------------------------------------------------------------------------------------------
//
//
////------------------------ ADMIN DEFINATIONS------------------------------------------------------------------
//
//admin::admin()
//{
//    if (companies_list == nullptr && warehouses_list == nullptr && fdo_list == nullptr)
//    {
//        cout << "ADMIN CONSTRUCTOR" << endl;
//        companies_count = warehouse_count = fdo_count = 0;
//        Filing::initiate_all_companies(companies_list, companies_count);
//        Filing::initiate_all_warehouses(warehouses_list, warehouse_count);
//    }
//
//}
//
//void admin::adminOutput()
//{
//    output();
//    cout << "Total amount spent: $" << totalPrice << endl;
//}
//admin::admin(string un, string fn, string ln, string em, string cn, string No) : person(un, fn, ln, em, cn, No)
//{
//
//}
//
//void admin::input_login_details()
//{
//    string un, un_num, p;
//    bool correct_input = false;
//
//    while (!correct_input)
//    {
//        try
//        {
//            un = "AD";
//            cout << "Enter the username: AD";
//            cin >> un_num;
//
//            if (!regex_match(un_num, valid_user_num))
//            {
//                throw invalid_username();
//            }
//
//            un += un_num; // concats the digits with "AD"
//
//            if (Filing::find_admin(un))
//            {
//                throw username_exists();
//            }
//
//            cout << "\nEnter the password";
//            cin >> p;
//
//            if (!is_valid_password(p))
//            {
//                throw invalid_password();
//            }
//
//            correct_input = true;
//        }
//        catch (const exception& e)
//        {
//            SetConsoleTextAttribute(h, 252);
//            print_spaces();
//            cout << "[!] Exception: " << e.what() << endl;
//            SetConsoleTextAttribute(h, 240);
//        }
//    }
//
//    username = un;
//    pass = encrypt(un, p);
//
//
//}
//
//void admin::add_company()
//{
//    expand<company>(companies_list, companies_count);
//
//    companies_list[companies_count - 1].companyInput();
//
//    Filing::add_new_company(&companies_list[companies_count - 1]);
//}
//
//void admin::delete_company()
//{
//    if (companies_count > 0)
//    {
//        int i;
//        string n;
//        cout << "Enter the name of company: ";
//        cin >> n;
//
//        i = find_company_index(n);
//
//        if (i != -1)
//        {
//            del<company>(companies_list, companies_count, i);
//            companies_count--;
//            Filing::store_companies(companies_list, companies_count);
//        }
//        else
//        {
//            print_error("[!] ERROR: The entered name doesn't exists.");
//        }
//    }
//    else
//    {
//        print_error("\n\n[!]ERROR: There is no company to delete.\n\n");
//    }
//}
//
//void admin::display_company()
//{
//
//    for (int i = 0; i < companies_count; i++)
//    {
//        cout << "\n";
//        companies_list[i].companyoutput();
//    }
//}
//
//void admin::add_warehouse()
//{
//    expand<warehouse>(warehouses_list, warehouse_count);
//
//    warehouses_list[warehouse_count - 1].houseInput();
//
//    Filing::add_new_warehouse(&warehouses_list[warehouse_count - 1]);
//}
//
//void admin::display_warehouse()
//{
//
//    for (int i = 0; i < warehouse_count; i++)
//    {
//
//        cout << "\n";
//        warehouses_list[i].houseOutput();
//
//    }
//}
//
//void admin::purchase_vaccine()
//{
//    vaccines* vac;
//    string company_name, wareID;
//    int index, vaccineamt, bID;
//    bool warehouse_available = false, correct_input = false;
//
//    heading("COMPANIES");
//    display_company();
//
//    cout << "\n\nEnter the name of company you want to buy from: ";
//    do
//    {
//        cin >> company_name;
//        if (find_company_index(company_name) == -1)
//        {
//            print_error("\n[!] ERROR: The company name entered doesn't exist.\n");
//            cout << "Enter again: ";
//        }
//    } while (find_company_index(company_name) == -1);
//
//    index = find_company_index(company_name);
//    vaccineamt = companies_list[index].get_vac_quantity();
//
//    heading("WAREHOUSES");
//    for (int i = 0; i < warehouse_count; i++)
//    {
//        if (warehouses_list[i].is_enough_space(vaccineamt))
//        {
//            warehouse_available = true;
//            warehouses_list[i].houseOutput();
//            cout << "\n";
//        }
//    }
//    if (warehouse_available)
//    {
//        cout << "\n\nEnter the ID of warehouse: ";
//        do
//        {
//            cin >> wareID;
//            if (find_warehouse_index(wareID) == -1)
//            {
//                print_error("\n[!] ERROR: The warehouse entered doesn't exist.\n");
//                cout << "Enter again: ";
//            }
//            else
//            {
//
//                if (!warehouses_list[find_warehouse_index(wareID)].is_enough_space(vaccineamt))
//                {
//                    print_error("\n[!] ERROR: The warehouse entered doesn't exist.\n");
//                    cout << "Enter again: ";
//                }
//                else
//                {
//                    correct_input = true;
//                }
//            }
//
//        } while (!correct_input);
//
//        int wareI = find_warehouse_index(wareID);
//        cout << wareI << endl;
//
//        vac = companies_list[index].get_vac();
//        bID = companies_list[index].get_batchID();
//
//        Filing::store_companies(companies_list, companies_count);
//
//        vac->set_batchNo(bID);
//
//        warehouses_list[wareI].add_new_vaccine(vac, bID);
//
//        totalPrice += vac->get_price();
//
//        Filing::add_new_warehouse_vaccine(wareID, &warehouses_list[wareI], vac);
//
//        super_admin::store_admins();
//    }
//    else
//    {
//        print_error("\n[!] ERROR: No warehouse has enough space.\n");
//    }
//
//}
//
//string admin::file_details()
//{
//    return person::file_details() + to_string(totalPrice) + ",\n";
//}
//
//void admin::load_admin_data(string un, string fn, string ln, string em, string cn, string No, string tprice)
//{
//    load_person_data(un, fn, ln, em, cn, No);
//    totalPrice = stoi(tprice);
//}
////----------------------------------------------------------------------------------------------------------------
//
////------------------------ FDO DEFINATIONS------------------------------------------------------------------------
//
//fdo::fdo()
//{
//    doc = new doctor;
//    vacCount = 0;
//}
//
//void fdo::fdo_input()
//{
//    cout << "\n->FDO Details\n\n";
//    input();
//
//    cout << "\n\n->Vaccine Center Details\n\n";
//    cout << "Enter Name: ";
//    cin >> vacCenterName;
//    cout << "Enter City: ";
//    do
//    {
//        cin >> city;
//        if (admin::does_vac_center_exists_in(city))
//        {
//            print_error("\n[!] ERROR: The vaccine center already exists.\n");
//            cout << "Enter again: ";
//        }
//    } while (admin::does_vac_center_exists_in(city));
//
//    cout << "\n\n->Doctor Details\n\n";
//    doc->input();
//}
//void fdo::fdo_output()
//{
//    cout << "\n->FDO Details\n\n";
//    output();
//
//    cout << "\n\n->Vaccine Center Details\n\n";
//    cout << "Enter Name: ";
//    cout << "Name: " << vacCenterName << endl;
//    cout << "City: " << city << endl;
//
//    cout << "\n\n->Doctor Details\n\n";
//    doc->output();
//}
//string fdo::file_details()
//{
//    return person::file_details() + vacCenterName + "," + city + "," + to_string(vacCount) + "," + doc->file_details() + "\n";
//}
//
//void fdo::load_data(string un, string fn, string ln, string em, string cn, string No, string vCenName, string City, string vCount, string un1, string fn1, string ln1, string em1, string cn1, string No1)
//{
//    load_person_data(un, fn, ln, em, cn, No);
//    vacCenterName = vCenName;
//    city = City;
//    vacCount = stoi(vCount);
//    doc->load_person_data(un1, fn1, ln1, em1, cn1, No1);
//}
//
//void fdo::load_vaccine(string vID, string lbatch, string vName, string NoDoses, string price, string quantity)
//{
//    expand<vaccines>(vac_list, vacCount);
//
//    vac_list[vacCount - 1].load_data(vID, vName, NoDoses, price, quantity);
//    vac_list[vacCount - 1].set_batchNo(stoi(lbatch));
//}
//
//void fdo::add_new_vaccine(vaccines* v)
//{
//    string vID = v->get_vacID();
//    string vName = v->get_vacName();
//    string NoDoses = to_string(v->get_Nofdoses());
//    string price = to_string(v->get_price());
//    string quantity = to_string(v->get_quantity());
//    int lbatch = v->get_batchNo();
//
//    expand<vaccines>(vac_list, vacCount);
//
//    vac_list[vacCount - 1].load_data(vID, vName, NoDoses, price, quantity);
//    vac_list[vacCount - 1].set_batchNo(lbatch);
//}
//void fdo::output_vaccines()
//{
//    for (int i = 0; i < vacCount; i++)
//    {
//        cout << i + 1 << ".\n";
//        vac_list[i].vaccineOutput();
//        cout << "\n";
//    }
//}
////menu option
//void fdo::get_vaccine()
//{
//    string wareID;
//
//    string vacID;
//    int batchID, vacIndex;
//
//    heading("WAREHOUSES");
//    admin::display_warehouse();
//
//    cout << "\n\nEnter the ID of warehouse: ";
//    do
//    {
//        cin >> wareID;
//        if (admin::find_warehouse_index(wareID) == -1)
//        {
//            print_error("\n[!] ERROR: The warehouse entered doesn't exist.\n");
//            cout << "Enter again: ";
//        }
//
//
//    } while (admin::find_warehouse_index(wareID) == -1);
//
//    warehouse* warePtr = admin::get_warehouse(admin::find_warehouse_index(wareID));
//
//    heading("VACCINES");
//    warePtr->vaccinesOutput();
//
//
//    do
//    {
//        cout << "\n\nEnter the vaccine ID: ";
//        cin >> vacID;
//        cout << "Enter the batch ID: ";
//        batchID = safe_input<int>();
//
//        if (warePtr->find_valid_vacID_batchID(vacID, batchID) == -1)
//        {
//            print_error("\n[!] ERROR: The vacID/batchID entered doesn't exist.\n");
//        }
//
//
//    } while (warePtr->find_valid_vacID_batchID(vacID, batchID) == -1);
//
//    vacIndex = warePtr->find_valid_vacID_batchID(vacID, batchID);
//
//    vaccines* vacPtr = warePtr->get_vaccine(vacIndex);
//
//    add_new_vaccine(vacPtr);
//
//    Filing::add_new_fdo_vaccine(username, this, vacPtr);
//
//    warePtr->remove_vaccine(vacID, batchID);
//
//    cout << "\n\n[$]: The vaccine has been transfered successfully." << endl;
//} //
//
//void fdo::vacinate_citizen()
//{
//    int i;
//    string cnic;
//    cout << "Enter your CNIC: ";
//    do
//    {
//        cin >> cnic;
//        if (!is_valid_cnic(cnic))
//        {
//            print_error("\n[!] ERROR: The CNIC entered in not valid.\n\n");
//            cout << "Enter again: ";
//        }
//    } while (!is_valid_cnic(cnic));
//
//    if (Filing::find_citizen(cnic))
//    {
//        if (!Filing::already_vacinated(cnic))
//        {
//            citizen ctz = Filing::load_citizen(cnic);
//
//            if (ctz.get_eligibity())
//            {
//                cout << "\n\n->CITIZEN INFO\n\n";
//                ctz.citizen_output();
//
//
//                cout << "\n\nYou are eligible for the vaccine.\n\n";
//                cout << "Sending to the doctor to measure  blood pressure, oxygen level, and glucose level.\n\n";
//
//                cout << "->DOCTOR PORTAL\n\n";
//                if (doc->is_health_ok())
//                {
//                    cout << "\nYour health condition is OK for the vaccination process\n\n";
//
//                    cout << "->SELECT VACCINE\n\n";
//                    output_vaccines();
//
//                    cout << "Enter the index of vaccine: ";
//                    do
//                    {
//                        cin >> i;
//                        if (i > vacCount || i < 0)
//                        {
//                            print_error("\n[!] ERROR: The index entered in not valid.\n\n");
//                            cout << "Enter again: ";
//                        }
//                    } while (i > vacCount || i < 0);
//
//                    Filing::store_vac_citizen(cnic, vac_list[i - 1].get_vacID());
//
//                    cout << "\n\nYOU HAVE BEEN VACCINATED !\n\n";
//                }
//            }
//            else
//            {
//                print_error("\n[!] ERROR: You are not eligible for vaccine\n\n");
//            }
//        }
//        else
//        {
//            print_error("\n[!] ERROR: You have already vaccinated\n\n");
//        }
//    }
//}
//
//bool fdo::compare_city(string c)
//{
//    return city == c;
//}
//
//void fdo::input_login_details()
//{
//    string un, un_num, p;
//    bool correct_input = false;
//
//    while (!correct_input)
//    {
//        try
//        {
//            un = "FD";
//            cout << "Enter the username: FD";
//            cin >> un_num;
//
//            if (!regex_match(un_num, valid_user_num))
//            {
//                throw invalid_username();
//            }
//
//            un += un_num; // concats the digits with "AD"
//
//            if (Filing::find_fdo(un))
//            {
//                throw username_exists();
//            }
//
//            cout << "\nEnter the password: ";
//            cin >> p;
//
//            if (!is_valid_password(p))
//            {
//                throw invalid_password();
//            }
//
//            correct_input = true;
//        }
//        catch (const exception& e)
//        {
//            SetConsoleTextAttribute(h, 252);
//            print_spaces();
//            cout << "[!] Exception: " << e.what() << endl;
//            SetConsoleTextAttribute(h, 240);
//        }
//    }
//
//    username = un;
//    pass = encrypt(un, p);
//}
////----------------------------------------------------------------------------------------------------------------
//
////------------------------ FILING DEFINATIONS---------------------------------------------------------------------
//bool Filing::find_super_admin(string username)
//{
//    ifstream login_file(FILE_PATH + "super_admin_login_details.txt");
//    string o_username;
//
//    login_file >> o_username; // reads original username from the file
//
//
//    if (username == o_username)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//bool Filing::is_valid_login_super_admin(string username, string pass)
//{
//    ifstream login_file(FILE_PATH + "super_admin_login_details.txt");
//    string o_username, o_pass;
//    int key = 0;
//
//    login_file >> o_username >> o_pass; // reads original username and password from the file
//
//    pass = encrypt(username, pass);
//
//    if (username == o_username && pass == o_pass)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//
//}
//super_admin* Filing::login_super_admin(string username)
//{
//    ifstream details_file(FILE_PATH + "super_admin_details.csv");
//    int count = 0;
//    string line, word;
//    string details[6];
//    //string o_username, fn, ln, em, cn, No;
//
//    getline(details_file, line);
//    stringstream str(line);
//
//    while (getline(str, word, ','))
//    {
//        details[count++] = word;
//    }
//
//    if (details[0] == username)
//    {
//        return super_admin::getInstance(details[0], details[1], details[2], details[3], details[4], details[5]);
//    }
//}
//
//bool Filing::find_admin(string username)
//{
//    ifstream login_file(FILE_PATH + "admin_login_details.txt");
//
//    bool found = false;
//    string o_username, o_pass;
//
//    // reads original username from the file
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass;
//        if (username == o_username)
//        {
//            found = true;
//            break;
//        }
//
//    }
//    login_file.close();
//
//    return found;
//}
//bool Filing::is_valid_login_admin(string username, string pass)
//{
//    ifstream login_file(FILE_PATH + "admin_login_details.txt");
//
//    bool logined = false;
//    string o_username, o_pass;
//
//    // reads original username from the file
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass;
//        if (username == o_username)
//        {
//            pass = encrypt(username, pass);
//
//            if (pass == o_pass)
//            {
//                logined = true;
//                break;
//            }
//        }
//
//    }
//    login_file.close();
//
//    return logined;
//}
//    
//void Filing::initiate_all_admin(admin*& admin_list, int& admin_count)
//{
//    ifstream details_file(FILE_PATH + "admin_details.csv");
//    int count = 0;
//    string line, word;
//    string details[7];
//    //string o_username, fn, ln, em, cn, No, tprice;
//
//    while (getline(details_file, line))
//    {
//        count = 0;
//        stringstream str(line);
//
//        while (getline(str, word, ','))
//        {
//            details[count++] = word;
//        }
//        cout << details[0] << endl;
//        cout << admin_count << endl;
//        expand<admin>(admin_list, admin_count);
//
//        admin_list[admin_count - 1].load_admin_data(details[0], details[1], details[2], details[3], details[4], details[5], details[6]);
//    }
//
//}
//   
//void Filing::add_new_admin(admin* obj)
//{
//    ofstream details_file(FILE_PATH + "admin_details.csv", ios::app);
//    ofstream login_file(FILE_PATH + "admin_login_details.txt", ios::app);
//
//    if (!details_file || !login_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//        login_file << obj->file_logindetails();
//
//        details_file.close();
//        login_file.close();
//    }
//}
//void Filing::store_deleted_admins(string username, admin* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "admin_details.csv");
//
//
//    if (!details_file)
//    {
//        print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "admin_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "admin_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username != o_username[i])
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//void Filing::store_updated_admins(string username, admin* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "admin_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "admin_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "admin_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username == o_username[i])
//        {
//            login_output_file << arr[i].file_logindetails();
//        }
//        else
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//   
//bool Filing::find_doctor(string username)
//{
//    ifstream login_file(FILE_PATH + "doctor_login_details.txt");
//
//    bool found = false;
//    string o_username, o_pass;
//
//
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass;  // reads original username from the file
//        if (username == o_username)
//        {
//            found = true;
//            break;
//        }
//        login_file >> o_username >> o_pass;
//    }
//    login_file.close();
//
//    return found;
//}
//bool Filing::is_valid_login_doctor(string username, string pass)
//{
//    ifstream login_file(FILE_PATH + "doctor_login_details.txt");
//
//    bool logined = false;
//    string o_username, o_pass;
//
//
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass; // reads original username from the file
//        if (username == o_username)
//        {
//            pass = encrypt(username, pass);
//
//            if (pass == o_pass)
//            {
//                logined = true;
//                break;
//            }
//        }
//
//    }
//    login_file.close();
//
//    return logined;
//}
//void Filing::add_new_doctor(doctor* obj)
//{
//    ofstream details_file(FILE_PATH + "doctor_details.csv", ios::app);
//    ofstream login_file(FILE_PATH + "doctor_login_details.txt", ios::app);
//
//    if (!details_file || !login_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//        login_file << obj->file_logindetails();
//
//        details_file.close();
//        login_file.close();
//    }
//}
//void Filing::store_deleted_doctors(string username, doctor* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "doctor_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "doctor_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "doctor_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username != o_username[i])
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//void Filing::store_updated_doctors(string username, doctor* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "doctor_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: doctor_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "doctor_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "doctor_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username == o_username[i])
//        {
//            login_output_file << arr[i].file_logindetails();
//        }
//        else
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//  
//bool Filing::find_fdo(string username)
//{
//    ifstream login_file(FILE_PATH + "fdo_login_details.txt");
//
//    bool found = false;
//    string o_username, o_pass;
//
//
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass;  // reads original username from the file
//        if (username == o_username)
//        {
//            found = true;
//            break;
//        }
//        login_file >> o_username >> o_pass;
//    }
//    login_file.close();
//
//    return found;
//}
//bool Filing::is_valid_login_fdo(string username, string pass)
//{
//    ifstream login_file(FILE_PATH + "fdo_login_details.txt");
//
//    bool logined = false;
//    string o_username, o_pass;
//
//
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass; // reads original username from the file
//        if (username == o_username)
//        {
//            pass = encrypt(username, pass);
//
//            if (pass == o_pass)
//            {
//                logined = true;
//                break;
//            }
//        }
//    }
//    login_file.close();
//
//    return logined;
//}
//void Filing::initiate_all_fdo(fdo*& fdos_list, int& fdo_count)
//{
//    ifstream details_file(FILE_PATH + "fdo_details.csv");
//    int count = 0;
//    string line, word;
//    string fdo_details[15], v_details[6];
//    //string houseID limit total_vac_amount vaccineCount
//
//    cout << "ware\n";
//    while (getline(details_file, line))
//    {
//        cout << "fdo\n";
//        count = 0;
//        stringstream str(line);
//
//        while (getline(str, word, ','))
//        {
//            cout << word << endl;
//            fdo_details[count++] = word;
//        }
//
//        expand<fdo>(fdos_list, fdo_count);
//
//        fdos_list[fdo_count - 1].load_data(fdo_details[0], fdo_details[1], fdo_details[2], fdo_details[3], fdo_details[4], fdo_details[5], fdo_details[6], fdo_details[7], "0", fdo_details[9], fdo_details[10], fdo_details[11], fdo_details[12], fdo_details[13], fdo_details[14]);
//
//
//        for (int i = 0; i < stoi(fdo_details[8]); i++)
//        {
//            count = 0;
//            getline(details_file, line);
//            stringstream str1(line);
//
//            while (getline(str1, word, ','))
//            {
//                v_details[count++] = word;
//            }
//
//            fdos_list[fdo_count - 1].load_vaccine(v_details[0], v_details[1], v_details[2], v_details[3], v_details[4], v_details[5]);
//        }
//    }
//
//}
//void Filing::add_new_fdo(fdo* obj)
//{
//    ofstream details_file(FILE_PATH + "fdo_details.csv", ios::app);
//    ofstream login_file(FILE_PATH + "fdo_login_details.txt", ios::app);
//
//    if (!details_file || !login_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//        login_file << obj->file_logindetails();
//
//        details_file.close();
//        login_file.close();
//    }
//}
//void Filing::add_new_fdo_vaccine(string ID, fdo* fdoobj, vaccines* obj)
//{
//    ifstream details_file(FILE_PATH + "fdo_details.csv");
//    ofstream temp(FILE_PATH + "temp.csv");
//
//    string line, word;
//
//    int count = 0;
//    string details[15];
//    //username firstname lastname email contactNumber CNIC vacCenterName, city vacCount doc_username firstname lastname email contactNumber CNIC
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//
//        while (getline(details_file, line))
//        {
//            count = 0;
//            stringstream str(line);
//            while (getline(str, word, ','))
//            {
//                details[count++] = word;
//            }
//
//            if (details[0] != ID)
//            {
//                temp << line;
//
//                if (line.size() != 0)
//                    if (line[line.size() - 1] != '\n')
//                        temp << "\n";
//
//            }
//            else
//            {
//                temp << fdoobj->file_details();
//            }
//
//            for (int i = 0; i < stoi(details[8]); i++)
//            {
//                getline(details_file, line);
//                temp << line;
//
//                if (line.size() != 0)
//                    if (line[line.size() - 1] != '\n')
//                        temp << "\n";
//            }
//
//            if (details[0] == ID)
//            {
//
//                temp << obj->file_details();
//            }
//
//        }
//
//        details_file.close();
//        temp.close();
//
//        ofstream details_file("fdo_details.csv");
//        ifstream temp("temp.csv");
//
//        while (getline(temp, line))
//        {
//            details_file << line;
//
//            if (line.size() != 0)
//                if (line[line.size() - 1] != '\n')
//                {
//                    details_file << "\n"; //Pakistani tughe salaam :))
//                }
//        }
//
//        details_file.close();
//        temp.close();
//    }
//}
//void Filing::store_deleted_fdos(string username, fdo* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "fdo_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "fdo_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "fdo_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username != o_username[i])
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//void Filing::store_updated_fdos(string username, fdo* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "fdo_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: fdo_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "fdo_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "fdo_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username == o_username[i])
//        {
//            login_output_file << arr[i].file_logindetails();
//        }
//        else
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
// 
//bool Filing::find_gov_off(string username)
//{
//    ifstream login_file(FILE_PATH + "gov_off_details.txt");
//
//    bool found = false;
//    string o_username, o_pass;
//
//
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass;  // reads original username from the file
//        if (username == o_username)
//        {
//            found = true;
//            break;
//        }
//        login_file >> o_username >> o_pass;
//    }
//    login_file.close();
//
//    return found;
//}
//bool Filing::is_valid_login_gov_off(string username, string pass)
//{
//    ifstream login_file(FILE_PATH + "gov_off_login_details.txt");
//
//    bool logined = false;
//    string o_username, o_pass;
//
//
//    while (!login_file.eof())
//    {
//        login_file >> o_username >> o_pass; // reads original username from the file
//        if (username == o_username)
//        {
//            pass = encrypt(username, pass);
//
//            if (pass == o_pass)
//            {
//                logined = true;
//                break;
//            }
//        }
//    }
//    login_file.close();
//
//    return logined;
//}
//void Filing::add_new_gov_off(gov_off* obj)
//{
//    ofstream details_file(FILE_PATH + "gov_off_details.csv", ios::app);
//    ofstream login_file(FILE_PATH + "gov_off_login_details.txt", ios::app);
//
//    if (!details_file || !login_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//        login_file << obj->file_logindetails();
//
//        details_file.close();
//        login_file.close();
//    }
//}
//void Filing::store_deleted_gov_offs(string username, gov_off* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "gov_off_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "gov_off_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "gov_off_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username != o_username[i])
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//void Filing::store_updated_gov_offs(string username, gov_off* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "gov_off_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: gov_off_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//        details_file.close();
//    }
//
//    vector<string> o_username, o_pass;
//    string un, pass;
//    int count = 0;;
//
//    ifstream login_input_file(FILE_PATH + "gov_off_login_details.txt");
//
//    while (!login_input_file.eof())
//    {
//        login_input_file >> un >> pass;
//        o_username.push_back(un);
//        o_pass.push_back(pass);
//        count++;
//    }
//    login_input_file.close();
//
//    ofstream login_output_file(FILE_PATH + "gov_off_login_details.txt");
//
//    for (int i = 0; i < count; i++)
//    {
//        if (username == o_username[i])
//        {
//            login_output_file << arr[i].file_logindetails();
//        }
//        else
//        {
//            login_output_file << o_username[i] << " " << o_pass[i] << endl;
//        }
//    }
//
//    login_output_file.close();
//}
//    
//void Filing::initiate_all_companies(company*& companies_list, int& companies_count)
//{
//    ifstream details_file(FILE_PATH + "company_details.csv");
//    int count = 0;
//    string line, word;
//    string details[7];
//    //string cname LbNo vID vName NoDoses price, quantity;
//
//    while (getline(details_file, line))
//    {
//        count = 0;
//        stringstream str(line);
//
//        while (getline(str, word, ','))
//        {
//            details[count++] = word;
//        }
//
//        expand<company>(companies_list, companies_count);
//
//        companies_list[companies_count - 1].load_data(details[0], details[1], details[2], details[3], details[4], details[5], details[6]);
//    }
//
//}
//void Filing::add_new_company(company* obj)
//{
//    ofstream details_file(FILE_PATH + "company_details.csv", ios::app);
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//
//        details_file.close();
//    }
//}
//void Filing::store_companies(company* arr, int size)
//{
//    ofstream details_file(FILE_PATH + "company_details.csv");
//
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            details_file << arr[i].file_details();
//        }
//        details_file.close();
//    }
//}
//  
//void Filing::initiate_all_warehouses(warehouse*& warehouses_list, int& warehouse_count)
//{
//    ifstream details_file(FILE_PATH + "warehouse_details.csv");
//    int count = 0;
//    string line, word;
//    string w_details[4], v_details[6];
//    //string houseID limit total_vac_amount vaccineCount
//
//    cout << "ware\n";
//    while (getline(details_file, line))
//    {
//        cout << "warehouse\n";
//        count = 0;
//        stringstream str(line);
//
//        while (getline(str, word, ','))
//        {
//            cout << word << endl;
//            w_details[count++] = word;
//        }
//
//        expand<warehouse>(warehouses_list, warehouse_count);
//
//        warehouses_list[warehouse_count - 1].load_data(w_details[0], w_details[1], w_details[2], "0");
//
//
//        for (int i = 0; i < stoi(w_details[3]); i++)
//        {
//            count = 0;
//            getline(details_file, line);
//            stringstream str1(line);
//
//            while (getline(str1, word, ','))
//            {
//                v_details[count++] = word;
//            }
//
//            warehouses_list[warehouse_count - 1].load_vaccine(v_details[0], v_details[1], v_details[2], v_details[3], v_details[4], v_details[5]);
//        }
//    }
//
//}
//void Filing::add_new_warehouse(warehouse* obj)
//{
//    ofstream details_file(FILE_PATH + "warehouse_details.csv", ios::app);
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//
//        details_file.close();
//    }
//}
//void Filing::add_new_warehouse_vaccine(string ID, warehouse* wareobj, vaccines* obj)
//{
//    ifstream details_file(FILE_PATH + "warehouse_details.csv");
//    ofstream temp(FILE_PATH + "temp.csv");
//
//    string line;
//    string warehouseID, limit, vacamt, vacCount;
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//
//        while (getline(details_file, line))
//        {
//            stringstream str(line);
//            getline(str, warehouseID, ',');
//            getline(str, limit, ',');
//            getline(str, vacamt, ',');
//            getline(str, vacCount, ',');
//
//            if (warehouseID != ID)
//            {
//                temp << line;
//
//                if (line.size() != 0)
//                    if (line[line.size() - 1] != '\n')
//                        temp << "\n";
//
//            }
//            else
//            {
//                temp << wareobj->file_details();
//            }
//
//            for (int i = 0; i < stoi(vacCount); i++)
//            {
//                getline(details_file, line);
//                temp << line;
//
//                if (line.size() != 0)
//                    if (line[line.size() - 1] != '\n')
//                        temp << "\n";
//            }
//
//            if (warehouseID == ID)
//            {
//
//                temp << obj->file_details();
//            }
//
//        }
//
//        details_file.close();
//        temp.close();
//
//        ofstream details_file("warehouse_details.csv");
//        ifstream temp("temp.csv");
//
//        while (getline(temp, line))
//        {
//            details_file << line;
//
//            if (line.size() != 0)
//                if (line[line.size() - 1] != '\n')
//                {
//                    details_file << "\n"; //Pakistani tughe salaam :))
//                }
//        }
//
//        details_file.close();
//        temp.close();
//    }
//}
//void Filing::delete_warehouse_vaccine(string ID, warehouse* obj, string vID, string bID)
//{
//    ifstream details_file(FILE_PATH + "warehouse_details.csv");
//    ofstream temp(FILE_PATH + "temp.csv");
//
//    string line;
//    string warehouseID, limit, vacamt, vacCount;
//    string vacID, batchID;
//
//    if (!details_file)
//    {
//        //print_error("\n\nERROR IN OPENING THE FILE: admin_details.csv or admin_login_details.txt\n\n");
//    }
//    else
//    {
//
//        while (getline(details_file, line))
//        {
//            stringstream str(line);
//            getline(str, warehouseID, ',');
//            getline(str, limit, ',');
//            getline(str, vacamt, ',');
//            getline(str, vacCount, ',');
//
//
//
//            if (warehouseID == ID)
//            {
//                temp << obj->file_details();
//                for (int i = 0; i < stoi(vacCount); i++)
//                {
//                    getline(details_file, line);
//
//                    stringstream str1(line);
//                    getline(str1, vacID, ',');
//                    getline(str1, batchID, ',');
//
//                    if (vID != vacID || bID != batchID)
//                    {
//                        temp << line;
//
//                        if (line.size() != 0)
//                            if (line[line.size() - 1] != '\n')
//                                temp << "\n";
//                    }
//
//                }
//            }
//            else
//            {
//                temp << line;
//                if (line.size() != 0)
//                    if (line[line.size() - 1] != '\n')
//                        temp << "\n";
//
//                for (int i = 0; i < stoi(vacCount); i++)
//                {
//                    getline(details_file, line);
//                    temp << line;
//
//                    if (line.size() != 0)
//                        if (line[line.size() - 1] != '\n')
//                            temp << "\n";
//                }
//            }
//
//        }
//
//        details_file.close();
//        temp.close();
//
//        ofstream details_file("warehouse_details.csv");
//        ifstream temp("temp.csv");
//
//        while (getline(temp, line))
//        {
//            details_file << line;
//
//            if (line.size() != 0)
//                if (line[line.size() - 1] != '\n')
//                    details_file << "\n";
//        }
//
//        details_file.close();
//        temp.close();
//    }
//}
//
//bool Filing::find_citizen(string CNIC)
//{
//    ifstream details_file(FILE_PATH + "citizen_details.csv");
//
//    int count = 0;
//    string line, word;
//    string details[9];
//    //string un fn ln em cn No Age bT City
//
//    while (getline(details_file, line))
//    {
//        count = 0;
//        stringstream str(line);
//
//        while (getline(str, word, ','))
//        {
//            details[count++] = word;
//        }
//
//        if (CNIC == details[4])
//        {
//            return true;
//        }
//    }
//
//    return false;
//}
//bool Filing::already_vacinated(string CNIC)
//{
//    ifstream details_file(FILE_PATH + "citizen_vac.csv");
//    string line, word;
//    string c, vac, is_vac;
//    while (getline(details_file, line))
//    {
//
//        stringstream str(line);
//        getline(str, c, ',');
//        getline(str, vac, ',');
//        getline(str, is_vac, ',');
//
//
//        if (CNIC == c && is_vac == "yes")
//        {
//            return true;
//        }
//    }
//
//    return false;
//}
//void Filing::add_new_citizen(citizen* obj)
//{
//    ofstream details_file(FILE_PATH + "citizen_details.csv", ios::app);
//
//    if (!details_file)
//    {
//        print_error("\n\nERROR IN OPENING THE FILE: citizen_details.csv\n\n");
//    }
//    else
//    {
//        details_file << obj->file_details();
//
//        details_file.close();
//    }
//}
//citizen Filing::load_citizen(string CNIC)
//{
//    ifstream details_file(FILE_PATH + "citizen_details.csv");
//
//    int count = 0;
//    string line, word;
//    string details[9];
//    //string un fn ln em cn No Age bT City
//
//    while (getline(details_file, line))
//    {
//        count = 0;
//        stringstream str(line);
//
//        while (getline(str, word, ','))
//        {
//            details[count++] = word;
//        }
//
//        if (CNIC == details[4])
//        {
//            return citizen(details[0], details[1], details[2], details[3], details[4], details[5], details[6], details[7], details[8]);
//        }
//    }
//
//}
//void Filing::store_vac_citizen(string cnic, string vacID)
//{
//    ofstream details_file(FILE_PATH + "citizen_vac.csv", ios::app);
//
//    details_file << cnic + "," + vacID + ",yes,\n";
//
//    details_file.close();
//}
////----------------------------------------------------------------------------------------------------------------