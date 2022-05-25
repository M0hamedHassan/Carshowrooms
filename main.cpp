#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "Customer.h"
#include "Showrooms.h"
#include "Garages.h"
#include<Service_Process.h>
#include<ctime>
#define ListOfShowrooms Showrooms::ListOfShowrooms
#define ListOfgarages Garages::ListOfgarages
#define s_process Service_Process::s_process
#define MapOfShowrooms Admin::MapOfShowrooms
#define MapOfCars Admin::MapOfCars
#define MapOfGarages Admin::MapOfGarages
#define MapOfServices Admin::MapOfServices
#define cid Customer::cid


using namespace std;
set<pair<string, string>> SetOfEmails;
map<pair<string, string>, int> m_id;
template<typename T>
void Erase(vector<T> &X, int Y) {
    for(int i=Y;i<X.size()-1;i++){
        swap(X[i], X[i+1]);
    }
    if (X.size() != 0)
        X.pop_back();
}

/** Error checking input **/
void clr(int &x) {
    cin.clear();
    cin.ignore(100000, '\n');
}

void ErrorChecking(int &check) {
    /**/while (true) {
        cin >> check;
        /**/    if (cin.fail()) {
            /**/        cout << "Enter a valid number" << endl;
            clr(check);
            /**/
        } else break;
        /**/
    }
}
void Registration() {
    int id = SetOfEmails.size();
    string us, ps;
    ifstream input("data.txt");
    while (input >> id >> us >> ps) {
        m_id[{us, ps}] = id;
        SetOfEmails.insert({us, ps});
    }
    int c;
    cout << "1 : REGISTER" << endl;
    cout << "2 : LOGIN " << endl;
    ErrorChecking(c);
        system("cls");
    if (c == 1) {
        int b = 0;
        int idd = SetOfEmails.size();
        idd += 1;
        string reguser, regpass;
        cout << "Enter Username : ";
        cin >> reguser;
        cout << "Enter Password : ";
        cin >> regpass;
        system("cls");
        if (SetOfEmails.count({reguser, regpass})) {
            b = 1;
        }
        if (b == 1) {
            cout << "Username Already Exist" << endl;
            Registration();
        } else {
            SetOfEmails.insert({reguser, regpass});
            ofstream output("data.txt", ios::app);
            output << idd << " " << reguser << " " << regpass << " " << endl;
            cout << "Registration Successfully" << endl;
            Registration();
        }
    } else if (c == 2) {
        int lid;
        string loguser, logpass, us, ps;
        cout << "Enter Username : ";
        cin >> loguser;
        cout << "Enter Password : ";
        cin >> logpass;
        system("cls");
        if (loguser == "admin" && logpass == "admin123") {
            cout << "                    Welcome Admin                  " << endl;
            Admin::administration();

        } else {
            if (SetOfEmails.count({loguser, logpass})) {
                cid = m_id[{loguser, logpass}];
                cout << "Welcome Customer" << endl;
                Customer::customer();
            } else {
                cout << "Account Not Found!" << endl;
                Registration();
            }
        }
    }
    input.close();
}

void Welcome() {
    ifstream input;
    input.open("Showrooms.txt");
    int sizee=0;
    input >> sizee;
    for (int i = 0; i < sizee; i++) {
        Showrooms x;
        input >> x.id >> x.name >> x.location >> x.phone_number;
        MapOfShowrooms[x.name] = x.id;
        int SizeOfCars;
        input >> SizeOfCars;
        for (int j = 0; j < SizeOfCars; j++) {
            Car car;
            input >> car.id >> car.year >> car.price >> car.make >> car.model >> car.installment
            >> car.Date.day >> car.Date.month >> car.Date.year >> car.state;
            MapOfCars[{x.id, {car.model, car.year}}] = car.id;
            x.list_of_Cars.push_back(car);
        }
        ListOfShowrooms.push_back(x);
    }
    input.close();

    input.open("Garages.txt");
    input >> sizee;
    for (int i = 0; i < sizee; i++) {
        Garages x;
        input >> x.id >> x.name >> x.location >> x.phone_number;
        MapOfGarages[x.name] = x.id;
        int SizeOfServices;
        input >> SizeOfServices;
        for (int j = 0; j < SizeOfServices; j++) {
            Service service;
            input >> service.id >> service.name >> service.price;
            MapOfServices[{x.id,service.name}] = service.id;
            x.list_of_Services.push_back(service);
        }
        ListOfgarages.push_back(x);
    }
    input.close();

    input.open("Historical_service_process.txt");
    input >> sizee;
    for(int i=0;i<sizee;i++){
        int sizeee;
        input >> sizeee;
        for(int j=0;j<sizeee;j++){
            Service_Process ser_p;
            input >> ser_p.process_id >> ser_p.customer_id >> ser_p.amount_of_money
            >> ser_p.Date.day >>ser_p.Date.month >> ser_p.Date.year >>ser_p.name;
            s_process[i].push_back(ser_p);

        }
    }
    input.close();
}

void ByeBye() {
    ofstream output;
    output.open("Showrooms.txt");
    output << ListOfShowrooms.size() << endl;
    for (int i = 0; i < ListOfShowrooms.size(); i++) {
        output << i+1 << ' ' << ListOfShowrooms[i].name << ' ' << ListOfShowrooms[i].location << ' '
               << ListOfShowrooms[i].phone_number << endl;
        output << ListOfShowrooms[i].list_of_Cars.size() << endl;
        for (int j = 0; j < ListOfShowrooms[i].list_of_Cars.size(); j++) {
            output << j+1 << ' ' << ListOfShowrooms[i].list_of_Cars[j].year << ' '
                   << ListOfShowrooms[i].list_of_Cars[j].price << ' ' << ListOfShowrooms[i].list_of_Cars[j].make << ' '
                   << ListOfShowrooms[i].list_of_Cars[j].model << ' ' << ListOfShowrooms[i].list_of_Cars[j].installment
                   <<' '<<ListOfShowrooms[i].list_of_Cars[j].Date.day<<' '<<ListOfShowrooms[i].list_of_Cars[j].Date.month<<' '
                   <<ListOfShowrooms[i].list_of_Cars[j].Date.year<<' '<<ListOfShowrooms[i].list_of_Cars[j].state
                   << endl;
        }
        output << endl << endl;
    }
    output.close();

    output.open("Garages.txt");
    output << ListOfgarages.size() << endl;
    for (int i = 0; i < ListOfgarages.size(); i++) {
        output << i+1 << ' ' << ListOfgarages[i].name << ' ' << ListOfgarages[i].location << ' '
               << ListOfgarages[i].phone_number << endl;
        output << ListOfgarages[i].list_of_Services.size() << endl;
        for (int j = 0; j < ListOfgarages[i].list_of_Services.size(); j++) {
            output << j+1 << ' ' << ListOfgarages[i].list_of_Services[j].name << ' '
                   << ListOfgarages[i].list_of_Services[j].price << endl;
        }
        output << endl << endl;
    }
    output.close();

    output.open("Historical_service_process.txt");
    output << SetOfEmails.size() << endl ;
    for(int i=0; i < SetOfEmails.size(); i++){
        output<< s_process[i].size() << endl;
        for(int j=0;j<s_process[i].size();j++){
            output << j+1 << ' ' << s_process[i][j].customer_id << ' '
            << s_process[i][j].amount_of_money << ' ' << s_process[i][j].Date.day << ' '
            << s_process[i][j].Date.month << ' ' << s_process[i][j].Date.year << ' ' << s_process[i][j].name << endl;
        }
        output << endl << endl;
    }
    output.close();
}

int Day1,Month1,Year1;
void DATE_of_day(){
   time_t now = time(0);

   tm *ltm = localtime(&now);

     Year1=1900 + ltm->tm_year;
     Month1=1 + ltm->tm_mon;
     Day1=ltm->tm_mday;
}

void return_car()
{
    DATE_of_day();
    for(int i=0;i<ListOfShowrooms.size();i++)
    {
        for(int j=0;j<ListOfShowrooms[i].list_of_Cars.size();j++)
        {
            if(ListOfShowrooms[i].list_of_Cars[j].state==0)
            {
                if(ListOfShowrooms[i].list_of_Cars[j].Date.month<Month1)
                {
                    ListOfShowrooms[i].list_of_Cars[j].state=1;
                }
                else if(ListOfShowrooms[i].list_of_Cars[j].Date.day<=Day1 && ListOfShowrooms[i].list_of_Cars[j].Date.month<=Month1)
                {
                    ListOfShowrooms[i].list_of_Cars[j].state=1;
                }
            }
        }
    }
}

int main() {
    Welcome();
    return_car();
    Registration();
    ByeBye();
    return 0;
}
