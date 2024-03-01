#pragma once
#include<bits/stdc++.h>
#include "macros.hpp"
using namespace std;

class Cars{
    public:
        string ModelName;       //model name of the car
        string Company;         //company of the car
        string CarNumber;       //unique registration number of the car
        int current_condition;            //on a scale 1 to 5
        string onRent;          //"Yes" if the car is currently under rent, "No" otherwise
        string IssueDate;       //the date on which that car was rented by any user, if not under rent then "##-##-####"
        string DueDate;         //the expected date on which the user will return the car, if not under rent then "##-##-####"
        int rent;              //the rent price per day of the car (in $)

        Cars();
        string Calc_DueDate(string &curr_date, int no_of_days);       //to calculate the due date of that car, if being rented on that day, for some "no_of_days" days
        int Calc_rent();         //the total rent on that car for these many days
        int Calc_fine();         //the total fine on that car, when it is being returned, according to current date and due date
        void find_customer(UsersDb &usersdatabase);       //to find the customer who has rented that car
};

class CarsDb{
    public:
        static Cars* dummy_car;        
        vector<Cars> list_of_cars;     //list of all cars 

        void populate_database();      //to fill in the vectors from databae .txt files
        Cars* Find_car(string carNumber);   //to find that car in the database using its unique registration number
        void available_cars();         //to view all cars currently available for renting
        void view_all_cars();       //to view all the cars owned by the company at present
        void Add_car();      //to add a car to the database
        void Delete_car();    //to delete a car from the database
        void Modify_car();   //to modify a car in the database

        //populate and reflect changes back into the database .txt files
        void update_DB();
};