#include<bits/stdc++.h>
#include "../include/cars.hpp"
#include "../include/users.hpp"
#include "../include/macros.hpp"

using namespace std;

//functions defined in "functions.cpp"
string curr_date_time();
bool yes_no_input(char ch);
void WaitEnter();
int no_of_days_between(string &startdate, string &enddate);
string add_days_to_date(string startdate, int no_of_days);
string create_password();

Users::Users(){              //user constructor
    Name="###";
    User_ID="###";
    Password="###";
    user_record=5;
}

Employee::Employee(){          //employee constructor
    authentication_key="###";
} 

void UsersDb::populate_cust_database(){        //to take in customer data from text files into the program
    ifstream customerDB("../DataBase/customersdata.txt");
    vector<string> input;
    string s;
    vector<string> temp;
    while (getline(customerDB, s)){
        input.push_back(s);
    }
    for(int i=0;i<input.size();i=i+6){
        Customer newCustomer;
        newCustomer.Name=input[i];
        newCustomer.User_ID=input[i+1];
        newCustomer.Password=input[i+2];
        newCustomer.user_record=stoi(input[i+3]);
        temp=newCustomer.create_user_car_list(input[i+4]);
        newCustomer.user_car_list=temp;
        Customers_list.push_back(newCustomer);
    }
}

void UsersDb::populate_emp_database(){        //to take in employee data from text files into the program
    ifstream EmployeeDB("../DataBase/employeedata.txt");
    vector<string> input;
    string s;
    vector<string> temp;
     while (getline(EmployeeDB, s)){
        input.push_back(s);
    }
    for(int i=0;i<input.size();i=i+7){
        Employee newEmployee;
        newEmployee.Name=input[i];
        newEmployee.User_ID=input[i+1];
        newEmployee.Password=input[i+2];
        newEmployee.user_record=stoi(input[i+3]);
        newEmployee.authentication_key=input[i+4];
        temp=newEmployee.create_user_car_list(input[i+5]);
        newEmployee.user_car_list=temp;
        Employee_list.push_back(newEmployee);
    }
}

void UsersDb::populate_manager_database(){       //to take in manager data from text files into the program
    ifstream ManagerDB("../DataBase/managerdata.txt");
    vector<string> input;
    string s;
    vector<string> temp;
    while (getline(ManagerDB, s)){
        input.push_back(s);
    }
    for(int i=0;i<input.size();i=i+7){
        Manager newManager;
        newManager.Name=input[i];
        newManager.User_ID=input[i+1];
        newManager.Password=input[i+2];
        newManager.user_record=stoi(input[i+3]);
        newManager.authentication_key=input[i+4];
        temp=newManager.create_user_car_list(input[i+5]);
        newManager.user_car_list=temp;
        Manager_list.push_back(newManager); 
    }
}

//to add a new customer in the list
void UsersDb::Add_customer(string Name, string User_ID, string Password){
    Customer newCustomer;
    newCustomer.Name=Name;
    newCustomer.User_ID=User_ID;
    newCustomer.Password=Password;
    newCustomer.user_record=5;
    newCustomer.user_car_list.clear();
    Customers_list.push_back(newCustomer);
    cout<<"Customer registration successful!"<<endl;
}

//to add a new employee in the list
void UsersDb::Add_employee(string Name, string User_ID, string Password){
    string authentication_key;
    cout<<"Kindly generate an employee authentication key for employee access"<<endl;
    cin>>authentication_key;
    cout<<endl;

    Employee newEmployee;
    newEmployee.Name=Name;
    newEmployee.User_ID=User_ID;
    newEmployee.Password=Password;
    newEmployee.user_record=5;
    newEmployee.authentication_key=authentication_key;
    newEmployee.user_car_list.clear();
    Employee_list.push_back(newEmployee);

    cout<<"Employee registration successful!"<<endl;
}

//to add a new manager in the list
void UsersDb::Add_manager(string Name, string User_ID, string Password){    
    string authentication_key;
    cout<<"Kindly generate an employee authentication key for manager access"<<endl;
    cin>>authentication_key;
    cout<<endl;
    Manager newManager;
    newManager.Name=Name;
    newManager.User_ID=User_ID;
    newManager.Password=Password;
    newManager.user_record=8;
    newManager.authentication_key=authentication_key;
    newManager.user_car_list.clear();
    Manager_list.push_back(newManager);

    cout<<"Manager registration successful!"<<endl;
}

//to create vector lists of cars rented by each user
vector<string> Users::create_user_car_list(string temp){
    vector<string> output;
    output.clear();
    stringstream ss(temp);
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        if(substr!="*") output.push_back(substr);
    }
    return output;
}

//to search for a customer in the database using unique user_id
Customer* UsersDb::Find_Customer(string user_id){
    for(auto &it:Customers_list){
        if(it.User_ID==user_id){
            return &it;
        }
    }
    return dummy_customer;
}

//to search for a employee in the database using unique user_id
Employee* UsersDb::Find_Employee(string User_ID){
    for(auto &it:Employee_list){
        if(it.User_ID==User_ID){
            return &it;
        }
    }
    return dummy_employee;
}

//to search for a manager in the database using unique user_id
Manager* UsersDb::Find_Manager(string User_ID){
    for(auto &it:Manager_list){
        if(it.User_ID==User_ID){
            return &it;
        }
    }
    return dummy_manager;
}

//to view all cars currently under rent by that user
void Users::view_rented_cars(CarsDb &carsdatabase){
    cout<<endl;
    if(user_car_list.size()==0){
        cout<<"You have not rented any car"<<endl;
        return;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Model Name\t||\tCompany \t||\tCar Number\t||\t Condition \t||\tRent/day (in $)\t||\t Total rent paid"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    int rent_of_car;
    Cars* car;
    for(auto x:user_car_list){
        car=carsdatabase.Find_car(x);
        rent_of_car=car->Calc_rent();
        cout<<setfill(' ')<<setw(20)<<left<<car->ModelName<<"\t"<<setfill(' ')<<setw(15)<<left<<car->Company<<"\t\t"<<setw(10)<<left<<car->CarNumber<<"\t\t  "<<left<<car->current_condition<<"\t\t\t   "<<car->rent<<"\t\t\t  "<<rent_of_car<<endl;
    }
    cout<<endl;
}

//to rent a new car by that user
void Users::rent_car(CarsDb &carsdatabase, int role){
    if(user_car_list.size()>=user_record){
        cout<<"Sorry, you have reached your maximum limit of rented cars. Kindly rent a new car after you have returned the already rented ones."<<endl<<endl;
        return;
    }
    cout<<endl<<"Trip coming :)"<<endl<<endl;
    Cars* newCar;
    string carNumber;
    int no_of_days;
    cout<<"Kindly enter the registration number (Number Plate) of the car you want to rent"<<endl;
    cin>>carNumber;
    newCar=carsdatabase.Find_car(carNumber);

    //to check if that car is not currently on rent by someone else
    while(newCar==carsdatabase.dummy_car || newCar->onRent=="Yes"){
        if(newCar==carsdatabase.dummy_car){
            cout<<"Please enter a valid car number."<<endl;
        }
        if(newCar->onRent=="Yes"){
            cout<<"This car is not available for rent. Kindly enter a car available for rent."<<endl;
        }
        cin>>carNumber;
        newCar=carsdatabase.Find_car(carNumber);
    }
    cout<<"The rent/day of your selected car is $"<<newCar->rent<<"."<<endl;
    
    //the number of days for which they want the car
    cout<<"Kindly enter the number of days for which you want to rent the car"<<endl;
    cin>>no_of_days;
    if(role==1){
    cout<<"Your total rent would be $"<<newCar->rent*no_of_days<<"."<<endl;}
    if(role==2 || role==3){
    cout<<"Your total rent would be $"<<no_of_days*(newCar->rent-newCar->rent*EMP_DISC/100)<<"."<<endl;}
    string curr_date;
    curr_date=curr_date_time();
    string DueDate;
    DueDate=newCar->Calc_DueDate(curr_date,no_of_days);
    cout<<"Your due date would be "<<DueDate<<"."<<endl;
    cout<<"If you return after this due date, you will be charged an additional fine of $"<<FINE_PER_DAY<<"/day."<<endl;
    cout<<"Do you want to confirm [Y/N]"<<endl;
    char ch;
    cin>>ch;
    if(yes_no_input(ch)==true){
        newCar->onRent="Yes";
        newCar->IssueDate=curr_date;
        newCar->DueDate=DueDate;
        user_car_list.push_back(newCar->CarNumber);
        cout<<"Car "<<newCar->ModelName<<" with Registration Number "<<newCar->CarNumber<<" rented successfully."<<endl;
        
    }
    return;
}

//calculates the total dues(fine) of any customer if car is returned after due date
int Users::total_dues(CarsDb &carsdatabase){
    int total=0;
    Cars* newCar;
    string curr_date=curr_date_time();
    int days=0;
    for(auto x:user_car_list){
        newCar=carsdatabase.Find_car(x);
        days=no_of_days_between(newCar->DueDate,curr_date);
        if(days>0){
            total+=FINE_PER_DAY*days;
        }
    }
    return total;
}

//to extend due date of any rented car by that customer
void Users::extend_due_date(CarsDb &carsdatabase){
    cout<<"Kindly enter the registration number of the car you want to extend due date for"<<endl;
    string carNumber;
    cin>>carNumber;
    bool found=false;
    Cars* newCar;
    while(found==false){
        for(auto car:user_car_list){
            if(car==carNumber){
                found=true;
                break;
            }
        }
        if(found) break;
        if(found==false){
            cout<<"Please enter the valid number of a car you have currently rented!"<<endl;
            cin>>carNumber;
        }
    }
    newCar=carsdatabase.Find_car(carNumber);
    cout<<"The current due date for your car "<<newCar->ModelName<<" is "<<newCar->DueDate<<"."<<endl;
    
    string newDueDate;
    cout<<"Kindly enter the new due date upto which you want to rent this car in the format DD-MM-YYYY"<<endl;
    cin>>newDueDate;

    //to check if the entered date is in valid format and after the previous due date
    tm startDate={};
    istringstream startDateStream(newDueDate);
    startDateStream >> get_time(&startDate, "%d-%m-%Y");

    //invalid format
    while(startDateStream.fail()) {
        cerr << "Invalid date format. Please use DD-MM-YYYY format.\n";
        cin>>newDueDate;
        istringstream startDateStream(newDueDate);
        startDateStream>>get_time(&startDate, "%d-%m-%Y");
    }
    string curr_date=curr_date_time();

    //to check that new due date is after the previous one
    while(no_of_days_between(curr_date,newDueDate)<=0 || startDateStream.fail()){
        if(startDateStream.fail())
        cerr<<"Invalid date! "<<endl;
        else{
            cout<<"The current due date for your rented car is "<<newCar->DueDate<<endl;
            cerr<<"Kindly enter some date after this date."<<endl;
        }
        cin>>newDueDate;
        istringstream startDateStream(newDueDate);
        startDateStream>>get_time(&startDate, "%d-%m-%Y");
    }
    cout<<"Your car "<<newCar->ModelName<<" with registration number "<<newCar->CarNumber<<" is due upto "<<newDueDate<<endl;
    cout<<"Do you want to confirm [Y/N] "<<endl;
    char ch;
    cin>>ch;
    if(yes_no_input(ch)==true){
        newCar->DueDate=newDueDate;
        cout<<"Due date extended successfully upto "<<newDueDate<<endl;
        cout<<"Your total rent for this car would be $"<<newCar->Calc_rent()<<endl;
    }
    return;
}

//to change password
void Users::change_password(){
    cout<<"Kindly enter your current password"<<endl;
    string curr_pass, new_pass, check_new_pass;
    cin>>curr_pass;
    if(curr_pass!=Password){
        cout<<"incorrect password"<<endl;
        cout<<"Please try again"<<endl;
        return;
    }
    else{
        do{
            cout<<"Kindly enter your new password"<<endl;
            cin>>new_pass;
            cout<<"Re-enter your password: ";
            cin>>check_new_pass;
            if(new_pass!=check_new_pass){
                cout<<"Passwords do not match!"<<endl;
            }
        }while(new_pass!=check_new_pass);
        cout<<"Do you want to confirm [Y/N]"<<endl;
        char ch;
        cin>>ch;
        if(yes_no_input(ch)==true){
            Password=new_pass;
            cout<<"Password changed successfully!"<<endl;
        }
        return;
    }
}

//to change authentication key
void Employee::change_auth_key(){
    cout<<"Kindly enter your current authentication key"<<endl;
    string curr_auth_key, new_auth_key, check_new_auth_key;
    cin>>curr_auth_key;
    if(curr_auth_key!=authentication_key){
        cout<<"incorrect authentication key"<<endl;
        cout<<"Please try again"<<endl;
        return;
    }
    else{
        do{
            cout<<"Kindly enter your new authentication key"<<endl;
            cin>>new_auth_key;
            cout<<"Re-enter your authentication key: ";
            cin>>check_new_auth_key;
            if(new_auth_key!=check_new_auth_key){
                cout<<"Authentication keys do not match!"<<endl;
            }
        }while(new_auth_key!=check_new_auth_key);
        cout<<"Do you want to confirm [Y/N]"<<endl;
        char ch;
        cin>>ch;
        if(yes_no_input(ch)==true){
            authentication_key=new_auth_key;
            cout<<"authentication key changed successfully!"<<endl;
        }
        return;
    }
}

//to return any car for any customer and rate its condition
void Employee::return_request(CarsDb &carsdatabase, UsersDb &usersdatabase){
    string user_id;
    cout<<"Kindly enter the user_id of the customer you want to return car of"<<endl;
    cin>>user_id;
    Customer* newUser;
    newUser=usersdatabase.Find_Customer(user_id);
    while(newUser==usersdatabase.dummy_customer){
        cerr<<"Please enter valid user_id."<<endl;
        cin>>user_id;
    }
    Cars* newCar;
    string carNumber;
    
    cout<<"Kindly enter the registration number of the car the customer wants to return"<<endl;
    cin>>carNumber;
    bool found=false;

    //finds if that user can currently rented that car
    while(found==false){
        for(auto car:newUser->user_car_list){
            if(car==carNumber){
                found=true;
                break;
            }
        }
        if(found) break;
        if(found==false){
            cout<<"Please enter the valid number of a car the customer has currently rented!"<<endl;
        }
        cin>>carNumber;
    }
    newCar=carsdatabase.Find_car(carNumber);
    if(newCar->onRent=="No"){
        cout<<"This car is not on rent. "<<endl;
        return;
    }
    int condition;
    cout<<"Kindly enter the current condition of the car being returned:"<<endl;
    cout<<"[1] Poor"<<endl;
    cout<<"[2] Average"<<endl;
    cout<<"[3] Fair"<<endl;
    cout<<"[4] Good"<<endl;
    cout<<"[5] Excellent"<<endl;
    cin>>condition;
    while(condition!=1 && condition!=2 && condition!=3 && condition!=4 && condition!=5){
        cerr<<"Invalid input"<<endl;
        cin>>condition;
    }
    string authentication_key;
    cin>>authentication_key;
    if(authentication_key!=authentication_key){
        cout<<"Incorrect Authentication Key"<<endl;
        cout<<"Please retry."<<endl;
        return;
    }
    if(condition>=newCar->current_condition && newUser->user_record<10) newUser->user_record++;
    else if(condition<newCar->current_condition && newUser->user_record>0) newUser->user_record--;
    int dues_on_car;
    dues_on_car=newCar->Calc_fine();
    newCar->IssueDate="##-##-####";
    newCar->DueDate="##-##-####";
    newCar->onRent="No";
    newCar->current_condition=condition;

    //to erase that car number from the user's list of rented cars
    if(newUser->user_car_list.size()==1){
        newUser->user_car_list.clear();
    }
    else{
        auto s=newUser->user_car_list.begin();
        for(int i=0;i<newUser->user_car_list.size();i++){
            if(newUser->user_car_list[i]==carNumber){
                newUser->user_car_list.erase(s+i);
                break;
            }
        }
    }
    if(dues_on_car==0){
        cout<<"Successfully returned car."<<endl;
        return;
    }
    else{
        cout<<"Kindly ensure that the customer has made a payment of $"<<dues_on_car<<endl;
        cout<<"Successfully returned car."<<endl;
        return;
    }
    
}

//to return any car currently rented by that employee/manager
void Employee::return_self_car(CarsDb &carsdatabase, UsersDb &usersdatabase){
    Cars* newCar;
    string carNumber;
    cout<<"Kindly enter the registration number of the car you want to return"<<endl;
    cin>>carNumber;
    bool found=false;
    
    //finds if that user can currently rented that car
    while(found==false){
        for(auto car:user_car_list){
            if(car==carNumber){
                found=true;
                break;
            }
        }
        if(found) break;
        if(found==false){
            cout<<"Please enter the valid number of a car you have currently rented!"<<endl;
        }
        cin>>carNumber;
    }
    newCar=carsdatabase.Find_car(carNumber);
    int condition;
    cout<<"Kindly enter the current condition of the car being returned:"<<endl;
    cout<<"[1] Poor"<<endl;
    cout<<"[2] Average"<<endl;
    cout<<"[3] Fair"<<endl;
    cout<<"[4] Good"<<endl;
    cout<<"[5] Excellent"<<endl;
    
    cin>>condition;
    while(condition!=1 && condition!=2 && condition!=3 && condition!=4 && condition!=5){
        cerr<<"Invalid input"<<endl;
        cin>>condition;
    }
    if(condition>=newCar->current_condition && user_record<10) user_record++;
    else if(condition<newCar->current_condition && user_record>0) user_record--;
    int dues_on_car;
    dues_on_car=newCar->Calc_fine();
    newCar->IssueDate="##-##-####";
    newCar->DueDate="##-##-####";
    newCar->onRent="No";
    newCar->current_condition=condition;
    
    //to erase that car number from that user's list of rented cars
    if(user_car_list.size()==1){
        user_car_list.clear();
    }
    else{
        auto s=user_car_list.begin();
        for(int i=0;i<user_car_list.size();i++){
            if(user_car_list[i]==carNumber){
                user_car_list.erase(s+i);
                break;
            }
        }
    }
    if(dues_on_car==0){
        cout<<"Successfully returned car."<<endl;
        return;
    }
    else{
        cout<<"Kindly ensure that the you have made a payment of $"<<dues_on_car<<endl;
        WaitEnter();
        cout<<"Successfully returned car."<<endl;
        return;
    }
}

//to delete that customer from data.
//if that customer has currently rented some car, then it cannot be deleted until all rented cars are returned
void UsersDb::Delete_customer(string User_ID, CarsDb &carsdatabase){
    Customer* newCustomer;
    newCustomer=Find_Customer(User_ID);
    cout<<newCustomer->Name<<endl;
    if(newCustomer->user_car_list.size()!=0){
        Cars* newCar;
        for(auto car:newCustomer->user_car_list){
            newCar=carsdatabase.Find_car(car);
            newCar->onRent="No";
            newCar->IssueDate="##-##-####";
            newCar->DueDate="##-##-####";
        }
    }
    cout<<"This customer "<<newCustomer->Name<<" with user_id "<<newCustomer->User_ID<<" deleted successfully from the database."<<endl;
    auto idx=Customers_list.begin();
    for(int i=0;i<Customers_list.size();i++){
        if(Customers_list[i].User_ID==newCustomer->User_ID){
            Customers_list.erase(idx+i);
            break;
        }
    }
    
}

//to delete that employee from data.
//if that employee has currently rented some car, then it cannot be deleted until all rented cars are returned
void UsersDb::Delete_employee(string User_ID, CarsDb &carsdatabase){
    Employee* newEmployee;
    newEmployee=Find_Employee(User_ID);
    if(newEmployee->user_car_list.size()!=0){
        Cars* newCar;
        for(auto car:newEmployee->user_car_list){
            newCar=carsdatabase.Find_car(car);
            newCar->onRent="No";
            newCar->IssueDate="##-##-####";
            newCar->DueDate="##-##-####";
        }
    }
    cout<<"This employee "<<newEmployee->Name<<" with user_id "<<newEmployee->User_ID<<" deleted successfully from the database."<<endl;
    auto idx=Employee_list.begin();
    for(int i=0;i<Employee_list.size();i++){
        if(Employee_list[i].User_ID==newEmployee->User_ID){
            Employee_list.erase(idx+i);
            break;
        }
    }
    
}

//to update details of any customer: Name, user_id, user_record value
void UsersDb::Update_customer(string User_ID){
    Customer* newCustomer;
    newCustomer=Find_Customer(User_ID);
    string Name;
    int user_record;
    cout<<"If you want to change the Name of this customer, enter the new Name, otherwise enter a \"-\" to keep it same"<<endl;
    string firstname, lastname;
    cout<<"Kindly enter the first Name"<<endl;
    cin>>firstname;
    cout<<"Kindly enter the last Name"<<endl;
    cin>>lastname;
    Name=firstname+' '+lastname;
    if(Name!="- -"){
        newCustomer->Name=Name;
    }
    cout<<"If you want to change the user ID of this customer, enter the new user ID, otherwise enter a \"-\" to keep it same"<<endl;
    cin>>User_ID;
    while((User_ID!="-") && (Find_Customer(User_ID)!=dummy_customer || Find_Employee(User_ID)!=dummy_employee || Find_Manager(User_ID)!=dummy_manager)){
        cout<<"User_ID already taken. Kindly enter another user_ID."<<endl;
        cin>>User_ID;
    }
    if(User_ID!="-"){
        newCustomer->User_ID=User_ID;
    }
    cout<<"If you want to change the customer record of this customer, enter the updated customer record, otherwise enter -1 to keep it same"<<endl;
    cin>>user_record;
    if(user_record>0 && user_record<11){
        newCustomer->user_record=user_record;
    }
    cout<<"Customer details updated successfully."<<endl;
    return;
}

//to update details of any employee: Name, user_id, user_record value, authentication key
void UsersDb::Update_employee(string User_ID){
    Employee* newEmployee;
    newEmployee=Find_Employee(User_ID);
    string Name, auth_key;
    int user_record;
    cout<<"If you want to change the Name of this employee, enter the new Name, otherwise enter a \"-\" to keep it same"<<endl;
    string firstname, lastname;
    cout<<"Kindly enter the first Name"<<endl;
    cin>>firstname;
    cout<<"Kindly enter the last Name"<<endl;
    cin>>lastname;
    Name=firstname+' '+lastname;
    if(Name!="- -"){
        newEmployee->Name=Name;
    }
    cout<<"If you want to change the user ID of this employee, enter the new user ID, otherwise enter a \"-\" to keep it same"<<endl;
    cin>>User_ID;
    while((User_ID!="-") && (Find_Customer(User_ID)!=dummy_customer || Find_Employee(User_ID)!=dummy_employee || Find_Manager(User_ID)!=dummy_manager)){
        cout<<"User_ID already taken. Kindly enter another user_ID."<<endl;
        cin>>User_ID;
    }
    if(User_ID!="-"){
        newEmployee->User_ID=User_ID;
    }
    cout<<"If you want to change the employee record of this employee, enter the updated employee record, otherwise enter -1 to keep it same"<<endl;
    cin>>user_record;
    if(user_record>0 && user_record<11){
        newEmployee->user_record=user_record;
    }
    cout<<"If you want to change the authentication key of this employee, enter the new authentication key, otherwise enter a \"-\" to keep it same"<<endl;
    cin>>auth_key;
    if(auth_key!="-"){
        newEmployee->authentication_key=auth_key;
    }
    cout<<"Employee details updated successfully."<<endl;
    return;
}

//to update details of the manager: Name, authentication key
void Manager::Update_manager(){
    string Name, auth_key;
    cout<<"If you want to change your Name, enter the new Name, otherwise enter a \"-\" to keep it same"<<endl;
    string firstname, lastname;
    cout<<"Kindly enter the first Name"<<endl;
    cin>>firstname;
    cout<<"Kindly enter the last Name"<<endl;
    cin>>lastname;
    Name=firstname+' '+lastname;
    if(Name!="- -"){
        Name=Name;
    }
    cout<<"If you want to change your authentication key, enter the new authentication key, otherwise enter a \"-\" to keep it same"<<endl;
    cin>>auth_key;
    if(auth_key!="-"){
        authentication_key=auth_key;
    }
    cout<<"Details updated successfully."<<endl;
}

//to fill back the databases from vectors created in the program, so as to reflect all changes made
void UsersDb::customer_update_DB(){
    ofstream custDb ("../database/customersdata.txt");
    vector<string> final;
    string s;
    for(auto cust:Customers_list){
        custDb<<cust.Name<<endl;
        custDb<<cust.User_ID<<endl;
        custDb<<cust.Password<<endl;
        custDb<<cust.user_record<<endl;
        if(cust.user_car_list.size()==0){
            custDb<<"*"<<endl;
        }
        else{
            for(auto car:cust.user_car_list){
                if(car==cust.user_car_list[cust.user_car_list.size()-1]){
                    custDb<<car<<endl;
                }
                else
                custDb<<car<<",";
            }
        }
        custDb<<endl;
    }
    custDb.close();
}

//to fill back the databases from vectors created in the program, so as to reflect all changes made
void UsersDb::employee_update_DB(){
    ofstream empDb ("../database/employeedata.txt");
    vector<string> final;
    string s;
    for(auto emp:Employee_list){
        empDb<<emp.Name<<endl;
        empDb<<emp.User_ID<<endl;
        empDb<<emp.Password<<endl;
        empDb<<emp.user_record<<endl;
        empDb<<emp.authentication_key<<endl;
        if(emp.user_car_list.size()==0){
            empDb<<"*"<<endl;
        }
        else{
            for(auto car:emp.user_car_list){
                if(car==emp.user_car_list[emp.user_car_list.size()-1]){
                    empDb<<car<<endl;
                }
                else
                empDb<<car<<",";
            }
        }
        empDb<<endl;
    }
    empDb.close();
}

//to fill back the databases from vectors created in the program, so as to reflect all changes made
void UsersDb::manager_update_DB(){
    ofstream managerDb ("../database/managerdata.txt");
    vector<string> final;
    string s;
    for(auto manager:Manager_list){
        managerDb<<manager.Name<<endl;
        managerDb<<manager.User_ID<<endl;
        managerDb<<manager.Password<<endl;
        managerDb<<manager.user_record<<endl;
        managerDb<<manager.authentication_key<<endl;
        if(manager.user_car_list.size()==0){
            managerDb<<"*"<<endl;
        }
        else{
            for(auto car:manager.user_car_list){
                if(car==manager.user_car_list[manager.user_car_list.size()-1]){
                    managerDb<<car<<endl;
                }
                else
                managerDb<<car<<",";
            }
        }
        managerDb<<endl;
    }
    managerDb.close();
}