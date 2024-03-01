//contains some frequently used functions across different files
#include<bits/stdc++.h>
using namespace std;
#include "../include/cars.hpp"
#include "../include/users.hpp"
#include "../include/macros.hpp"

void WaitEnter(){                 //waits for the user to press the enter key and continue
  cout<<"Press enter to continue..."<<endl;
  cin.ignore();
    cin.get();
}

string curr_date_time(){            //calculates the current date from the system
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currentTime);
    ostringstream formattedDate;
    formattedDate << setw(2) << setfill('0') << localTime->tm_mday << "-"
                  << setw(2) << setfill('0') << (localTime->tm_mon + 1) << "-"
                  << (localTime->tm_year + 1900);
    return formattedDate.str();
}

bool yes_no_input(char ch){           //takes a yes/no input from the user
    while(ch!='y' && ch!='Y' && ch!='N' && ch!='n'){
        cerr<<"Invalid input"<<endl;
        cin>>ch;
    }
    if(ch=='Y' || ch=='y') return 1;                //1 means yes
    else return 0;                                  //0 means no
}

//to calculate the number of days between two dates in the format DD-MM-YYYY
int no_of_days_between(string &startdate, string &enddate){        
    tm startDate = {};
    tm endDate = {};
    istringstream startDateStream(startdate);
    istringstream endDateStream(enddate);

    startDateStream >> get_time(&startDate, "%d-%m-%Y");
    endDateStream >> get_time(&endDate, "%d-%m-%Y");

    chrono::system_clock::time_point startTime = chrono::system_clock::from_time_t(mktime(&startDate));
    chrono::system_clock::time_point endTime = chrono::system_clock::from_time_t(mktime(&endDate));

    auto duration = chrono::duration_cast<chrono::duration<int, ratio<86400>>>(endTime - startTime);
    int daysBetween = duration.count();

    return daysBetween;
}

//to add a given number of days to some input date and return the final date in the format DD-MM-YYYY
string add_days_to_date(string startdate, int no_of_days){
    istringstream ss(startdate);
    int year, month, day;

    char dash;
    ss >> day >> dash >> month >> dash >> year;

    tm timeinfo = {};
    timeinfo.tm_year = year - 1900; // Years since 1900
    timeinfo.tm_mon = month - 1;    // Months are 0-based
    timeinfo.tm_mday = day;

    time_t time = mktime(&timeinfo);
    time += no_of_days * 24 * 60 * 60;
    tm* timeinfoResult = localtime(&time);

    ostringstream resultStream;
    resultStream << put_time(timeinfoResult, "%d-%m-%Y");
    
    return resultStream.str();
}

//to check if the user_id is not being used by anybody else on the system, so that it is unique for everyone
string check_user_id(UsersDb &UsersDataBase){
    string User_ID;
    cout<<"Enter User_ID :";
    cin>>User_ID;

    //code to check if this userid already exists//
    while(UsersDataBase.Find_Customer(User_ID)!=UsersDataBase.dummy_customer || UsersDataBase.Find_Employee(User_ID)!=UsersDataBase.dummy_employee || UsersDataBase.Find_Manager(User_ID)!=UsersDataBase.dummy_manager){
        cout<<"User_ID already taken. Kindly enter another user_ID."<<endl;
        cin>>User_ID;
    }
    return User_ID;
}

//to check the re-enetered password and return the final password created by the user
string create_password(){
    string check_Password, Password;
    do{
        cout<<"Generate Password : ";
        cin>>Password;
        cout<<"Re-enter your password: ";
        cin>>check_Password;
        if(Password!=check_Password){
            cout<<"Passwords do not match!"<<endl;
        }
    }while(Password!=check_Password);
    return Password;
}