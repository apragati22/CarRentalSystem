#include<bits/stdc++.h>
#include "../include/cars.hpp"
#include "../include/users.hpp"
#include "../include/macros.hpp"
#include<fstream>
using namespace std;

//functions defined in "functions.cpp"
Cars* CarsDb::dummy_car=new Cars();
Customer* UsersDb::dummy_customer=new Customer();
Employee* UsersDb::dummy_employee=new Employee();
Manager* UsersDb::dummy_manager=new Manager();

void WaitEnter();                                //to take enter as input
string curr_date_time();                         //calculates current date
bool yes_no_input(char ch);                      //takes an input yes/no
string check_user_id(UsersDb &UsersDataBase);    //checks user id being entered
string create_password();                        //creates and checks password

int main(){
    UsersDb UsersDataBase;
    CarsDb CarsDataBase;
    string curr_date=curr_date_time();
    cout<<endl<<"Welcome to Car Rental System, IIT Kanpur!"<<endl;
    cout<<endl;
    cout<<"Loading Data..."<<endl;
    cout<<"Data loading successful!"<<endl<<endl;
    ifstream carDB("../DataBase/carsdatabase.txt");
    ifstream customerDB("../DataBase/customersdata.txt");
    ifstream EmployeeDB("../DataBase/employeedata.txt");
    ifstream ManagerDB("../DataBase/managerdata.txt");

    //errors to be printed if files could not be opened//
    if (!carDB.is_open()) {
        cerr << "Could not open this file:"<< "'Database/carsdatabase.txt'"<< endl;
        return 0;
    }
    if (!customerDB.is_open()) {
        cerr << "Could not open the file:"<< "'Database/customersdata.txt'"<< endl;
        return 0;
    }
    if (!EmployeeDB.is_open()) {
        cerr << "Could not open the file:"<< "'Database/employeesdata.txt'"<< endl;
        return 0;
    }
    if (!ManagerDB.is_open()) {
        cerr << "Could not open the file:"<< "'Database/managerdata.txt'"<< endl;
        return 0;
    }

    //functions to take in database from the .txt files into the program
    CarsDataBase.populate_database();
    UsersDataBase.populate_cust_database();
    UsersDataBase.populate_emp_database();
    UsersDataBase.populate_manager_database();

    bool running=true;                  //until program is running
    while(running){
        string Name;
        string User_ID;
        string Password;
        Users *newUser=new Users;   
        Customer* newCustomer;
        Employee* newEmployee;
        Manager* newManager;
        int role=-1;                     //to decide which person is using the software
        bool logged_in=false;
        cout<<"Do you want to "<<endl;
        cout<<"[1] Register as a new user"<<endl;
        cout<<"[2] Login as an existing user"<<endl;
        cout<<"[0] Exit"<<endl;
        int command;
        cin>>command;
        while(command!=1 && command!=2 && command!=0){    //error if invalid input
            cerr<<"Invalid input"<<endl;
            cin>>command;
        }
        if(command==0){
            running=false;
            continue;
        }
        if(command==1){                  //registration process for a new user
            while(role!=1 && role!=2 && role!=3 && role!=4){
                cout<<"With which role do you want to register?"<<endl<<"[1] Customer"<<endl<<"[2] Employee"<<endl<<"[3] Manager"<<endl<<"[4] Exit"<<endl;
                cin>>role;
                if(role==4){                      //exit pressed
                    cout<<"Have a good day! Thanks :)"<<endl;
                    running=false;
                    break;
                }
                if (role!=1 && role!=2 && role!=3 && role!=4){
                    cerr<<"Invalid Input"<<endl;
                }
            }
            if(role==4) continue;
            string Name, User_ID, Password;
            string firstname, lastname;
            cout<<"Kindly enter the first Name"<<endl;
            cin>>firstname;
            cout<<"Kindly enter the last Name"<<endl;
            cin>>lastname;
            Name=firstname+' '+lastname;
            
            User_ID=check_user_id(UsersDataBase);        //checks if user_id is already taken, so that it is always unique
            cout<<"Great!"<<endl;
            Password=create_password();               //creates and checks user password

            //add user to the database suitably according to role
            if(role==1){                        
                UsersDataBase.Add_customer(Name,User_ID,Password);
                WaitEnter();
            }
            if(role==2){
                UsersDataBase.Add_employee(Name,User_ID,Password);
                WaitEnter();
            }
            if(role==3){
                UsersDataBase.Add_manager(Name,User_ID,Password);
                WaitEnter();
            }
        }

        else if(command==2){                    //login process
            while(role!=1 && role!=2 && role!=3 && role!=4){
                cout<<"With which role do you want to LogIn?"<<endl<<"[1] Customer"<<endl<<"[2] Employee"<<endl<<"[3] Manager"<<endl<<"[4] Exit"<<endl;
                cin>>role;
                if(role==4){             //exit pressed
                    cout<<"Have a good day! Thanks :)"<<endl;
                    running=false;
                    break;
                }
                if (role!=1 && role!=2 && role!=3 && role!=4){
                    cerr<<"Invalid Input"<<endl;
                }
            }

            if(role==4) continue;
            cout<<"Kindly enter your user_id:"<<endl;
            cin>>User_ID;
            
            //code to check if user_id is already taken or not, so that it is unique
            while(newUser->User_ID=="###"){
                if(role==1) {
                    newCustomer=UsersDataBase.Find_Customer(User_ID);
                    newUser=newCustomer;
                }
                else if (role==2){
                    newEmployee=UsersDataBase.Find_Employee(User_ID);
                    newUser=newEmployee;
                }
                else if(role==3) {
                    newManager=UsersDataBase.Find_Manager(User_ID);
                    newUser=newManager;
                }
                if(newUser->User_ID=="###") {
                    cerr<<"Invalid user_id"<<endl;
                    cout<<"Please enter valid user_id"<<endl;
                cin>>User_ID;
                }
            }

            //code to check password and authenticate user
            cout<<"Kindly enter your password for "<<User_ID<<endl;
            cin>>Password;
            if(role==1){
                while(Password!=newCustomer->Password){
                    cout<<"Incorrect Password!"<<endl;
                    cout<<"Kindly enter your password for "<<User_ID<<endl;
                    cin>>Password;
                }
                cout<<"Welcome "<<newCustomer->Name<<"!"<<endl;
            }
            if(role==2){
                while(Password!=newEmployee->Password){
                    cout<<"Incorrect Password!"<<endl;
                    cout<<"Kindly enter your password for "<<User_ID<<endl;
                    cin>>Password;
                }
                
                //to check if authentication key is re-entered correct
                string authentication_key;
                while(authentication_key!=newEmployee->authentication_key){
                    cout<<"Kindly enter your employee authentication key:";
                    cin>>authentication_key;
                    cout<<endl;
                    if(authentication_key!=newEmployee->authentication_key){
                        cout<<"Incorrect Authentication Key"<<endl;
                    }
                }
                cout<<"Welcome "<<newEmployee->Name<<"!"<<endl;
            }
            if(role==3){
                while(Password!=newManager->Password){
                    cout<<"Incorrect Password!"<<endl;
                    cout<<"Kindly enter your password for "<<User_ID<<endl;
                    cin>>Password;
                }

                //to check if authentication key is re-entered correct
                string authentication_key;
                while(authentication_key!=newManager->authentication_key){
                    cout<<"Kindly enter your manager authentication key:";
                    cin>>authentication_key;
                    cout<<endl;
                    if(authentication_key!=newManager->authentication_key){
                        cout<<"Incorrect Authentication Key"<<endl;
                    }
                }
                cout<<"Welcome "<<newManager->Name<<"!"<<endl;
            }
            logged_in=true;
        }   
        while(logged_in && running){

            //functionalities visible to everyone
            cout<<"Please select one of the following options:"<<endl;
            cout<<"[1] View all available cars for rent"<<endl;
            cout<<"[2] Rent a new car"<<endl;
            cout<<"[3] View list of your rented cars"<<endl;
            cout<<"[4] View your total rent as of today"<<endl;
            cout<<"[5] Extend due date for an already rented car"<<endl;
            cout<<"[6] Change Password"<<endl;

            //functionalities visible to employee and manager only
            if(role==2 || role==3){
                cout<<"[7] Change your authentication key"<<endl;  
                cout<<"[8] View all cars list"<<endl;
                cout<<"[9] Find customer to whom any car is rented"<<endl;       
                cout<<"[10] Return a currenty rented car of any customer"<<endl;
                cout<<"[11] Return your rented cars"<<endl;
            }

            //functionalities only manager can access
            if(role==3){
                cout<<"[12] Add a new car"<<endl;
                cout<<"[13] Delete an existing car"<<endl;
                cout<<"[14] Modify record of an existing car"<<endl;
                cout<<"[15] Add a new customer"<<endl;
                cout<<"[16] Delete an existing customer"<<endl;
                cout<<"[17] Modify record of an existing customer"<<endl;
                cout<<"[18] Add a new employee"<<endl;
                cout<<"[19] Delete an existing employee"<<endl;
                cout<<"[20] Modify record of an existing employee"<<endl;
                cout<<"[21] Modify your own records"<<endl;
            }
            cout<<"[0] Logout"<<endl;

            int modes=-1;          //to decide which mode is operating
            cin>>modes;
            while(modes<0 || modes>21){     //error if invalid input
                cerr<<"invalid input"<<endl;
                cin>>modes;
            }
            if(modes==0){               //logout
                cout<<"Have a good day! Thanks :)"<<endl;
                logged_in=false;
            }
            if(modes==1){               //view available cars
                cout<<endl;
                CarsDataBase.available_cars();
                cout<<endl;
                WaitEnter();
            }
            if(modes==2){                //rent a new car
                cout<<endl;
                newUser->rent_car(CarsDataBase, role);
                cout<<endl;
                WaitEnter();
            }
            if(modes==3){               //view all your rented cars
                cout<<endl;
                newUser->view_rented_cars(CarsDataBase);
                cout<<endl;
                WaitEnter();
            }
            if(modes==4){               //view your total dues 
                cout<<endl;
                cout<<"Your total outstanding dues are $";
                cout<<newUser->total_dues(CarsDataBase)<<endl;  
                cout<<"(The total fine you need to pay)"<<endl;            
                WaitEnter();
            }
            if(modes==5){               //extend due date of any of your rented car
                cout<<endl;
                newUser->extend_due_date(CarsDataBase);
                WaitEnter();
            }
            if(modes==6){             //change password
                cout<<endl;
                newUser->change_password();
                WaitEnter();
            }
            if(modes==7){             //change authentication key
                cout<<endl;
                if(role==2){
                    newEmployee->change_auth_key();
                }
                else if(role==3)
                newManager->change_auth_key();
                WaitEnter();
            }
            if(modes==8){              //view all cars in database
                cout<<endl;
                CarsDataBase.view_all_cars();
                cout<<endl;
                WaitEnter();
            }
            if(modes==9){              //find customer to whom that car is rented
                cout<<endl;
                string CarNumber;
                cout<<"Kindly enter the registration number of the car you want to find customer of"<<endl;
                cin>>CarNumber;
                while(CarsDataBase.Find_car(CarNumber)==CarsDataBase.dummy_car){
                    cerr<<"Please enter the correct car number"<<endl;
                    cin>>CarNumber;
                }
                Cars* newCar;
                newCar=CarsDataBase.Find_car(CarNumber);
                if(newCar->onRent=="No"){
                    cout<<"This car is NOT on rent currently. Therefore it is available for booking!"<<endl;
                    WaitEnter();
                }
                else{
                    newCar->find_customer(UsersDataBase);
                    cout<<endl;
                    WaitEnter();
                }
            }
            if(modes==10){             //return cars of any customer
                cout<<endl;
                if(role==2){
                newEmployee->return_request(CarsDataBase,UsersDataBase);
                }
                else if(role==3){
                    newManager->return_request(CarsDataBase,UsersDataBase);
                }
                cout<<endl;
                WaitEnter();
            }
            if(modes==11){              //return self rented car
                cout<<endl;
                if(role==2){
                newEmployee->return_self_car(CarsDataBase,UsersDataBase);
                }
                else if(role==3){
                    newManager->return_self_car(CarsDataBase,UsersDataBase);
                }
                cout<<endl;
                WaitEnter();
            }
            if(modes==12){                //add a new car
                cout<<endl;
                CarsDataBase.Add_car();
                cout<<endl;
                WaitEnter();
            }
            if(modes==13){               //delete an existing car
                cout<<endl;
                CarsDataBase.Delete_car();
                cout<<endl;
                WaitEnter();
                
            }
            if(modes==14){              //update record of an existing car
                cout<<endl;
                CarsDataBase.Modify_car();
                cout<<endl;
                WaitEnter();
            }
            if(modes==15){              //add a new customer to the database
                string Name, User_ID, Password;
                cout<<"Kindly enter the name of the customer you want to add"<<endl;
                string firstname, lastname;
                cout<<"Kindly enter the first Name"<<endl;
                cin>>firstname;
                cout<<"Kindly enter the last Name"<<endl;
                cin>>lastname;
                Name=firstname+' '+lastname;
                User_ID=check_user_id(UsersDataBase);
                cout<<"Great!"<<endl;
                Password=create_password();
                UsersDataBase.Add_customer(Name, User_ID,Password);
                WaitEnter();
            }
            if(modes==16){              //delete a customer from the database
                cout<<endl;
                cout<<"Kindly enter the user_id of the customer you want to delete"<<endl;
                cin>>User_ID;
                Customer* newCustomer;
                newCustomer=UsersDataBase.Find_Customer(User_ID);
                while(newCustomer==UsersDataBase.dummy_customer){
                    cerr<<"Please enter valid user_id."<<endl;
                    cin>>User_ID;
                    newCustomer=UsersDataBase.Find_Customer(User_ID);
                }
                UsersDataBase.Delete_customer(User_ID, CarsDataBase);
                cout<<endl;
                WaitEnter();
            }
            if(modes==17){             //modify the customer in the database
                cout<<endl;
                cout<<"Kindly enter the user_id of the customer you want to modify"<<endl;
                cin>>User_ID;
                Customer* newCustomer;
                newCustomer=UsersDataBase.Find_Customer(User_ID);
                while(newCustomer==UsersDataBase.dummy_customer){
                    cerr<<"Please enter valid user_id."<<endl;
                    cin>>User_ID;
                    newCustomer=UsersDataBase.Find_Customer(User_ID);
                }
                UsersDataBase.Update_customer(User_ID);
                cout<<endl;
                WaitEnter();
            }
            if(modes==18){              //add a new employee to the database
                string Name, User_ID, Password;
                cout<<"Kindly enter the name of the employee you want to add"<<endl;
                string firstname, lastname;
                cout<<"Kindly enter the first Name"<<endl;
                cin>>firstname;
                cout<<"Kindly enter the last Name"<<endl;
                cin>>lastname;
                Name=firstname+' '+lastname;
                cout<<"Great!"<<endl;
                User_ID=check_user_id(UsersDataBase);
                Password=create_password();
                UsersDataBase.Add_employee(Name, User_ID,Password);
                WaitEnter();
            }
            if(modes==19){             //delete an existing employee
                cout<<endl;
                cout<<"Kindly enter the user_id of the employee you want to delete."<<endl;
                cin>>User_ID;
                Employee* newEmployee;
                newEmployee=UsersDataBase.Find_Employee(User_ID);
                while(newEmployee==UsersDataBase.dummy_employee){
                    cerr<<"Please enter valid user_id."<<endl;
                    cin>>User_ID;
                    newEmployee=UsersDataBase.Find_Employee(User_ID);
                }
                UsersDataBase.Delete_employee(User_ID, CarsDataBase);
                cout<<endl;
                WaitEnter();
            }
            if(modes==20){             //modify records of an exisiting employee
                cout<<endl;
                cout<<"Kindly enter the user_id of the employee you want to modify"<<endl;
                cin>>User_ID;
                Employee* newEmployee;
                newEmployee=UsersDataBase.Find_Employee(User_ID);
                while(newEmployee==UsersDataBase.dummy_employee){
                    cerr<<"Please enter valid user_id."<<endl;
                    cin>>User_ID;
                    newEmployee=UsersDataBase.Find_Employee(User_ID);
                }
                UsersDataBase.Update_employee(User_ID);
                cout<<endl;
                WaitEnter();
            }
            if(modes==21){               //modify own records
                cout<<endl;
                newManager->Update_manager();
                cout<<endl;
                WaitEnter();
            }
        }

        //code to populate and reflect changes back in the database .txt files suitably after termination of the loop
        CarsDataBase.update_DB();
        UsersDataBase.customer_update_DB();
        UsersDataBase.employee_update_DB();
        UsersDataBase.manager_update_DB();
    }
    return 0;
}