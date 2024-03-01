#pragma once
#include <bits/stdc++.h>
#include "cars.hpp"
#include "macros.hpp"
using namespace std;

class Users{
    public:
        string Name;          //Name of the user
        string User_ID;       //unique user_id of the user
        string Password;      //password set by the user, used for authentication
        int user_record;      //on a scale of 1 to 10, default value=5  

        Users();        

        vector<string> user_car_list;  //list on registration numbers of all cars owned by the user
        vector<string> create_user_car_list(string temp);     //function to create the lists

        void view_rented_cars(CarsDb &carsdatabase);   //to view cars currently rented by that user
        void rent_car(CarsDb &carsdatabase, int role);  //to rent a new car
        int total_dues(CarsDb &carsdatabase);           //to find the total due/fine on that customer till date
        void extend_due_date(CarsDb &carsdatabase);     //to extend the due date of any car being rented by any customer
        void change_password();        //to change password
};

class Customer:public Users{
    public:
};

class Employee: public Users{
    public:
        string authentication_key;             //a 4 digit number to validate the employee
        Employee();                       //constructor
        void return_request(CarsDb &carsdatabase, UsersDb &usersdatabase);     //to return a car rented by a customer
        void return_self_car(CarsDb &carsdatabase, UsersDb &usersdatabase);    //to return any car rented by that employee 
        void change_auth_key();              //to change authentication key
};

class Manager: public Employee{
    public:
        void Update_manager();         //to update details of the manager
};

class UsersDb{

    public:
        static Customer* dummy_customer;
        static Employee* dummy_employee;
        static Manager* dummy_manager;

        vector<Customer> Customers_list;         //list of all customers
        vector<Employee> Employee_list;          //list of all employees
        vector<Manager> Manager_list;            //list of all managers

        void populate_cust_database();           //to fill in the vectors from databae .txt files
        void populate_emp_database();            //to fill in the vectors from databae .txt files
        void populate_manager_database();        //to fill in the vectors from databae .txt files

        Customer* Find_Customer(string User_ID);       //to find any customer in the database
        Employee* Find_Employee(string User_ID);       //to find any employee in the database
        Manager* Find_Manager(string User_ID);         //to find any manager in the database
 
        void Add_customer(string Name, string User_ID, string Password);   //add customer to the database
        void Add_employee(string Name, string User_ID, string Password);    //add employee to the database
        void Add_manager(string Name, string User_ID, string Password);    //add manager to the database

        void Delete_customer(string user_ID, CarsDb &carsdatabase);      //delete customer from the database
        void Delete_employee(string user_ID, CarsDb &carsdatabase);      //delete employee from the database

        void Update_customer(string user_id);        //update customer details in the database
        void Update_employee(string user_id);        //update employee details in the database
        
        //populate and reflect changes back into the database .txt files
        void customer_update_DB();           
        void employee_update_DB();
        void manager_update_DB();

        
};


