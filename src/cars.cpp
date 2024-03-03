#include<bits/stdc++.h>
#include "../include/cars.hpp"
#include "../include/users.hpp"
#include "../include/macros.hpp"

using namespace std;

//functions defined in "functions.cpp"
void WaitEnter();
string curr_date_time();
string yes_no_input();
int no_of_days_between(string &startdate, string &enddate);
string add_days_to_date(string startdate, int no_of_days);

Cars::Cars(){                //car constructor
    ModelName="###";
    Company="###";
    CarNumber="###";
    current_condition=5;
    onRent="###";
    DueDate="###";
    rent=0;
}

void CarsDb::populate_database(){      //to take in car data from text files into the program
    ifstream carDB("../DataBase/carsdatabase.txt");
    vector<string> input;
    string s;
    
    while (getline(carDB, s)){
        input.push_back(s);
    }
    for(int i=0;i<input.size();i=i+9){
        Cars newCar;
        newCar.ModelName=input[i];
        newCar.Company=input[i+1];
        newCar.CarNumber=input[i+2];
        newCar.current_condition=stoi(input[i+3]);
        newCar.onRent=input[i+4];
        newCar.IssueDate=input[i+5];
        newCar.DueDate=input[i+6];
        newCar.rent=stoi(input[i+7]);
        list_of_cars.push_back(newCar);
    }

}

//to calculate the due date of any car, based on current date and number of days for which car is being rented
string Cars::Calc_DueDate(string &curr_date, int no_of_days){
    // string Due_date;
    return add_days_to_date(curr_date,no_of_days);
}

//to calculate rent on any car based on number of days it is being rented and its price of rent /day
int Cars::Calc_rent(){
    int temp;
    int days_in_between=no_of_days_between(IssueDate,DueDate);

    temp=(days_in_between)*rent;
    return temp;
}

//to calculate the fine to be taken from the user for that car if car is returned after the due date
int Cars::Calc_fine(){
    int temp=0;
    string curr_date=curr_date_time();
    int days=no_of_days_between(DueDate, curr_date);
    if(days>0){
        temp=days*FINE_PER_DAY;
    }
    return temp;
}

//to find the customer to whom that car is rented
void Cars::find_customer(UsersDb &usersdatabase){
    for(auto user:usersdatabase.Customers_list){
        for(auto car:user.user_car_list){
            if(car==this->CarNumber){
                cout<<"This car is rented to customer "<<user.Name<<" upto "<<this->DueDate<<endl;
                return;
            }
        }
    }
    for(auto user:usersdatabase.Employee_list){
        for(auto car:user.user_car_list){
            if(car==this->CarNumber){
                cout<<"This car is rented to employee "<<user.Name<<" upto "<<this->DueDate<<endl;
                return;
            }
        }
    }
    for(auto user:usersdatabase.Manager_list){
        for(auto car:user.user_car_list){
            if(car==this->CarNumber){
                cout<<"This car is rented to manager "<<user.Name<<" upto "<<this->DueDate<<endl;
                return;
            }
        }
    }
}

//to find a car in the database using its unique car registration number
Cars* CarsDb::Find_car(string CarNumber){
    for(auto &it:list_of_cars){
        if(it.CarNumber==CarNumber){
            return &it;
        }
    }
    return dummy_car;
}

//to view the list of all cars available for renting
void CarsDb::available_cars(){
    cout<<endl;
    cout<<"Cars available on rent are:"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Model Name\t||\tCompany \t||\tCar Number\t||\t Condition  \t||\tRent/day (in $)"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
    int count=0;
    for(auto car:list_of_cars){
        if(car.onRent=="No"){
            // cout<<setfill(' ')<<setw(20)<<left<<car.ModelName<<"\t"<<setfill(' ')<<setw(15)<<left<<car.Company<<"\t\t"<<setw(10)<<left<<car.CarNumber<<"\t\t   "<<left<<car.current_condition<<"\t\t\t   "<<left<<car.rent<<endl;
            cout<<setfill(' ')<<setw(20)<<left<<car.ModelName<<"\t"<<setfill(' ')<<setw(15)<<left<<car.Company<<"\t\t"<<setw(10)<<left<<car.CarNumber<<"\t\t    "<<left<<car.current_condition<<"\t\t\t   "<<left<<car.rent<<endl;
        }
        count++;
    }
    if(count==0) cout<<"No car is available for rent :("<<endl;
}

//to view the list of alll cars owned by the company at that point
void CarsDb::view_all_cars(){
    cout<<endl;
    cout<<"All cars on our platform are:"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Model Name\t||\tCompany \t||\tCar Number\t||\t Condition  \t||\tRent/day (in $)"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
    for(auto car:list_of_cars){
        cout<<setfill(' ')<<setw(20)<<left<<car.ModelName<<"\t"<<setfill(' ')<<setw(15)<<left<<car.Company<<"\t\t"<<setw(10)<<left<<car.CarNumber<<"\t\t    "<<left<<car.current_condition<<"\t\t\t   "<<left<<car.rent<<endl;
    }
    if(list_of_cars.size()==0) cout<<"No car is present on our platform :("<<endl;
}

//to add a new car to the database
void CarsDb::Add_car(){
    string CarNumber, ModelName, company;
    int curr_cond;
    int rent;
    cout<<"Kindly enter the registration number of the car you want to add to the database."<<endl;
    cin>>CarNumber;

    //code to check if the car number if correct
    while(Find_car(CarNumber)!=dummy_car){
        cerr<<"Please enter the correct car number"<<endl;
        cin>>CarNumber;
    }
    cout<<"Please enter the model name of the car"<<endl;
    cin.ignore();
    getline(cin,ModelName);

    cout<<"Please enter its company"<<endl;
    cin>>company;
    cout<<"Please enter its current condition on a scale of 1(Poor) to 5(Excellent)"<<endl;
    cin>>curr_cond;
    cout<<"Please enter the rent price/day of the car"<<endl;
    cin>>rent;
    Cars newCar;
    newCar.ModelName=ModelName;
    newCar.Company=company;
    newCar.CarNumber=CarNumber;
    newCar.current_condition=curr_cond;
    newCar.IssueDate="##-##-####";
    newCar.DueDate="##-##-####";
    newCar.onRent="No";
    newCar.rent=rent;
    list_of_cars.push_back(newCar);
}

//to delete a car from the database. If that car is currently under rent, then it cannot be deleted until it is returned back
void CarsDb::Delete_car(){
    string CarNumber, ModelName, company, curr_cond;
    int rent;
    cout<<"Kindly enter the registration number of the car you want to delete from the database."<<endl;
    cin>>CarNumber;
    while(Find_car(CarNumber)==dummy_car){
        cerr<<"Please enter the correct car number"<<endl;
        cin>>CarNumber;
    }
    Cars* newCar;
    newCar=Find_car(CarNumber);
    if(newCar->onRent=="Yes"){
        cout<<"This car is currently under rent. You can not delete this car until it is returned."<<endl;
        return;
    }
    else{
        cout<<"This car "<<newCar->ModelName<<" with registration number "<<newCar->CarNumber<<" deleted successfully from the database."<<endl;
        auto idx=list_of_cars.begin();
        for(int i=0;i<list_of_cars.size();i++){
            if(list_of_cars[i].CarNumber==newCar->CarNumber){
                list_of_cars.erase(idx+i);
                break;
            }
        }
        
    }
}

//to modify the details of any car: Model Name, Company, current condition, rent/day
void CarsDb::Modify_car(){
    string CarNumber, ModelName, company;
    int curr_cond;
    int rent;
    cout<<"Kindly enter the registration number of the car you want to modify in the database."<<endl;
    cin>>CarNumber;
    while(Find_car(CarNumber)==dummy_car){
        cerr<<"Please enter the correct car number"<<endl;
        cin>>CarNumber;
    }
    Cars* newCar;
    newCar=Find_car(CarNumber);
    cout<<"If you want to change the Model Name of this car, enter the new Model Name, otherwise enter a \"-\" to keep it same"<<endl;
    cin>>ModelName;
    if(ModelName!="-"){
        newCar->ModelName=ModelName;
    }
    cout<<"If you want to change the Company of this car, enter the new Company, otherwise enter a \"-\" to keep it same"<<endl;
    cin>>company;
    if(company!="-"){
        newCar->Company=company;
    }
    cout<<"If you want to change the current condition of this car, enter the new current condition, otherwise enter -1 to keep it same"<<endl;
    cin>>curr_cond;
    if(curr_cond>=0 && curr_cond<=5){
        newCar->current_condition=curr_cond;
    }
    cout<<"If you want to change the rent of this car, enter the new rent, otherwise enter -1 to keep it same"<<endl;
    cin>>rent;
    if(rent>0){
        newCar->rent=rent;
    }
    cout<<"Car details updated successfully."<<endl;
    return;
}

//to fill back the databases .txt files from vectors created in the program, so as to reflect all changes made
void CarsDb::update_DB(){
    ofstream carDb ("../database/carsdatabase.txt");
    vector<string> final;
    string s;
    for(auto car:list_of_cars){
        carDb<<car.ModelName<<endl;
        carDb<<car.Company<<endl;
        carDb<<car.CarNumber<<endl;
        carDb<<car.current_condition<<endl;
        carDb<<car.onRent<<endl;
        carDb<<car.IssueDate<<endl;
        carDb<<car.DueDate<<endl;
        carDb<<car.rent<<endl;
        carDb<<endl;
    }
    carDb.close();
}
