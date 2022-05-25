#include "Customer.h"
#include "Service.h"
#include "Car.h"
#include "Buy_Rent_Process.h"
#include "Service_Process.h"
#include "Showrooms.h"
#include "Garages.h"
#include<fstream>
#include<ctime>
#define ListOfShowrooms Showrooms::ListOfShowrooms
#define ListOfgarages Garages::ListOfgarages
#define s_process Service_Process::s_process
#define MapOfShowrooms Admin::MapOfShowrooms
#define MapOfCars Admin::MapOfCars
#define MapOfGarages Admin::MapOfGarages
#define MapOfServices Admin::MapOfServices
#define clr Customer::clr
#define ErrorChecking Customer::ErrorChecking
#define DATE Customer::DATE
#define cid Customer::cid
int cid;
Customer::Customer(int id, string userName, string password, int choise) {
    this->id = id;
    this->userName = userName;
    this->password = password;
    this->choise = choise;
}
int Day,Month,Year;
void DATE(){
   time_t now = time(0);

   tm *ltm = localtime(&now);

     Year=1900 + ltm->tm_year;
     Month=1 + ltm->tm_mon;
     Day=ltm->tm_mday;
}

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

void Customer::customer() {
    int x;
    cout << "1 : View" << endl << "2 : Search" << endl << "3 : Buy" << endl << "4 : Rent" << endl << "5 : Book"<< endl << "6 : View historical service " << endl << "7 : Exit" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
        Customer::view();
        customer();
    } else if (x == 2) {
        Customer::Search();
        customer();
    } else if (x == 3) {
        Customer::buy();
        customer();
    } else if (x == 4) {
        Customer::rent();
        customer();
    } else if (x == 5) {
        Customer::book();
        customer();
    } else if (x == 6) {
        Customer::viewhistory();
        customer();
    }
    else if(x == 7){
        return;
    }
}

void Customer::view() {
    int x;
    cout << "1 : List of showrooms" << endl << "2 : List of garages" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
        for (int i = 0; i < ListOfShowrooms.size(); i++) {
            cout << "Id of showroom : " << ListOfShowrooms[i].id << endl;
            cout << "Name of showroom : " << ListOfShowrooms[i].name << endl;
            cout << "Location of showroom : " << ListOfShowrooms[i].location << endl;
            cout << "Phone of showroom : " << ListOfShowrooms[i].phone_number << endl;
            cout << "    ----------------------------------------    " << endl;
            for (int j = 0; j < ListOfShowrooms[i].list_of_Cars.size(); j++) {
                cout << "Model of car : " << ListOfShowrooms[i].list_of_Cars[j].model << endl;
                cout << "Make of car : " << ListOfShowrooms[i].list_of_Cars[j].make << endl;
                cout << "Year of car : " << ListOfShowrooms[i].list_of_Cars[j].year << endl;
                cout << "Price of car : " << ListOfShowrooms[i].list_of_Cars[j].price << endl;
                cout << "Installment state : " << ListOfShowrooms[i].list_of_Cars[j].installment << endl;
                if(ListOfShowrooms[i].list_of_Cars[j].state){
                    cout<<"State of car : Available "<<endl;
                }
                else{
                    cout<<"State of car : NOT Available ! "<<endl;
                }
                cout << endl;
            }
        }
        cout << "    ################################################################## " << endl;
    } else if (x == 2) {
        for (int i = 0; i < ListOfgarages.size(); i++) {
            cout << "Name of garage : " << ListOfgarages[i].name << endl;
            cout << "Location of garage : " << ListOfgarages[i].location << endl;
            cout << "Phone of garage : " << ListOfgarages[i].phone_number << endl;
            cout << "    ----------------------------------------    " << endl;
            for (int j = 0; j < ListOfgarages[i].list_of_Services.size(); j++) {
                cout << "Name of service : " << ListOfgarages[i].list_of_Services[j].name << endl;
                cout << "Price of service : " << ListOfgarages[i].list_of_Services[j].price << endl;
                cout << endl;
            }
        }
        cout << "    ################################################################## " << endl;
    }
}

void Customer::Search() {
    int x;
    cout << "1 : Showroom" << endl << "2 : Car" << endl << "3 : Garage" << endl << "4 : Service" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
        string showroom_name;
        int sh_id;
        cout << "Enter Showroom Name" << endl;
        cin >> showroom_name;
        system("cls");
        sh_id = MapOfShowrooms[showroom_name];
        cout << "Name of showroom : " << ListOfShowrooms[sh_id - 1].name << endl;
        cout << "Location of showroom : " << ListOfShowrooms[sh_id - 1].location << endl;
        cout << "Phone of showroom : " << ListOfShowrooms[sh_id - 1].phone_number << endl;
        cout << "    ----------------------------------------    " << endl;
        for (int j = 0; j < ListOfShowrooms[sh_id - 1].list_of_Cars.size(); j++) {
            cout << "Model of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[j].model << endl;
            cout << "Make of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[j].make << endl;
            cout << "Year of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[j].year << endl;
            cout << "Price of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[j].price << endl;
            cout << "Installment state : " << ListOfShowrooms[sh_id - 1].list_of_Cars[j].installment << endl;
            cout << endl;
        }
    } else if (x == 2) {
        string model, year, nameShowroom;
        int car_id, sh_id;
        cout << "Enter Name Of Showroom" << endl;
        cin >> nameShowroom;
        system("cls");
        sh_id = MapOfShowrooms[nameShowroom];
        cout << "Enter Model Of car" << endl;
        cin >> model;
        cout << "Enter Year Of Car" << endl;
        cin >> year;
        system("cls");
        car_id = MapOfCars[{sh_id, {model, year}}];
        cout << "Model of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].model << endl;
        cout << "Make of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].make << endl;
        cout << "Year of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].year << endl;
        cout << "Price of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].price << endl;
        cout << "Installment state : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].installment << endl;
        if(ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].state){
            cout<<"State of car : Available "<<endl;
        }
        else{
            cout<<"State of car : NOT Available ! "<<endl;
        }
        cout << endl;
    } else if (x == 3) {
        string Garage_name;
        int Garage_id;
        cout << "Enter Garage Name" << endl;
        cin >> Garage_name;
        system("cls");
        Garage_id = MapOfGarages[Garage_name];
        cout << "Name of Garage : " << ListOfgarages[Garage_id - 1].name << endl;
        cout << "Location of Garage : " << ListOfgarages[Garage_id - 1].location << endl;
        cout << "Phone of Garage : " << ListOfgarages[Garage_id - 1].phone_number << endl;
        cout << "    ----------------------------------------    " << endl;
        for (int j = 0; j < ListOfgarages[Garage_id].list_of_Services.size(); j++) {
            cout << "Name of service : " << ListOfgarages[Garage_id - 1].list_of_Services[j].name << endl;
            cout << "Price of service : " << ListOfgarages[Garage_id - 1].list_of_Services[j].price << endl;
            cout << endl;
        }
    } else if (x == 4) {
        string serviceName, nameGarage;
        int g_id, s_id;
        cout << "Enter Name Of Garage" << endl;
        cin >> nameGarage;
        system("cls");
        g_id = MapOfGarages[nameGarage];
        cout << "Enter Name Of Service" << endl;
        cin >> serviceName;
        system("cls");
        s_id = MapOfServices[{g_id,serviceName}];
        cout << "Name of service : " << ListOfgarages[g_id - 1].list_of_Services[s_id - 1].name << endl;
        cout << "Price of service : " << ListOfgarages[g_id - 1].list_of_Services[s_id - 1].price << endl;
        cout << endl;

    }
}

void Customer::buy() {
    Customer::DATE();
    bool ca=true;
    string model, year, nameShowroom;
    int car_id, sh_id;
    cout << "Enter Name Of Showroom" << endl;
    cin >> nameShowroom;
    system("cls");
    sh_id = MapOfShowrooms[nameShowroom];
    if (sh_id != 0) {
        cout << "Enter Model Of Car" << endl;
        cin >> model;
        cout << "Enter Year of Car" << endl;
        cin >> year;
        system("cls");
        car_id = MapOfCars[{sh_id, {model, year}}];
        if (car_id != 0) {
        cout<<"1 : Installment"<<endl<<"2 : Cash"<<endl;
        int h;
        ErrorChecking(h);
        system("cls");
        if(h==1){
        if(!ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].installment){
            cout<<"This car is not available for installment"<<endl<<"Do you want to buy cash ? (y / n)"<<endl;
            char y;cin>>y;
            if(y=='n' || y=='N'){
                ca=false;
                cout<<"you are welcome"<<endl;
            }
        }
        else if(ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].installment){
            cout<<"Average for installment 5 years and price will be : " <<(ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].price*5)/100<<endl;
        }
    }
            if(ca || h==2){
            Buy_Rent_Process buy_rent_process(cid,{Day,Month,Year},ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].price,
                                        ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1]);
            cout << "Congratulations" << endl << endl;
            cout << "Process id : " << buy_rent_process.process_id << endl;
            cout <<"Date : "<<buy_rent_process.Date.day<<" / "<<buy_rent_process.Date.month<<" / "<<buy_rent_process.Date.year<<endl;
            cout << "Customer id : " << buy_rent_process.customer_id << endl;
            cout << "Amount of money : " << buy_rent_process.amount_of_money << endl;
            cout << "Model of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].model << endl;
            cout << "Make of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].make << endl;
            cout << "Year of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].year << endl;
            cout<<endl;
            Erase(ListOfShowrooms[sh_id - 1].list_of_Cars, car_id - 1);
        } }else {
            cout << "Car Not Found!" << endl;
        }
    } else {
        cout << "Showroom Not Found!" << endl;
    }

}

void Customer::rent() {
    Customer::DATE();
    string model, year, nameShowroom;
    int car_id, sh_id, days;
    cout << "Enter Name Of Showroom" << endl;
    cin >> nameShowroom;
    sh_id = MapOfShowrooms[nameShowroom];
    if (sh_id != 0) {
        cout << "Enter Model and Year of Car" << endl;
        cin >> model >> year;
        cout << "How Many Days?" << endl;
        cin >> days;
        system("cls");
        car_id = MapOfCars[{sh_id, {model, year}}];
        cout << "=======" << endl;
        if (car_id != 0) {
            Buy_Rent_Process buy_rent_process(cid, {Day,Month,Year},
                                              ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].price,
                                              ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1]);
            cout << "amount of money : " << ((buy_rent_process.amount_of_money * days) / 100) << endl;
            cout << "Agree or not?( yes / no )" << endl;
            char p;
            cin >> p;
            system("cls");
            int Monthh,Dayy;
            if (p == 'y' || p == 'Y') {
                int dayrent;
                dayrent= (ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.day)+days;
                if(dayrent>30){
                     Monthh=dayrent/30;
                     Dayy=dayrent%30;
                ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.day=Dayy;
                ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.month+=Monthh;
                ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.year=Year;
                }
                else{
                    Monthh=dayrent/30;
                    Dayy=dayrent%30;
                    ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.day=Dayy;
                    ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.month+=Monthh;
                    ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].Date.year=Year;
                }
                cout << "Congratulations ,The car is booked for you" << endl;
                cout << "Process id : " << buy_rent_process.process_id << endl;
                cout <<"Date : "<<buy_rent_process.Date.day<<" / "<<buy_rent_process.Date.month<<" / "<<buy_rent_process.Date.year<<endl;
                cout << "Customer id : " << buy_rent_process.customer_id << endl;
                cout << "Amount of money : " << ((buy_rent_process.amount_of_money * days) / 100) << endl;
                cout << "Model of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].model << endl;
                cout << "Make of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].make << endl;
                cout << "Year of car : " << ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].year << endl;
                 ListOfShowrooms[sh_id - 1].list_of_Cars[car_id - 1].state=false;
            } else if (p == 'n' || p == 'N') {
                cout << "Thank you for using our app" << endl;
            }
        } else {
            cout <<"Car Not Found!" << endl;
        }
    } else {
        cout << "Showroom Not Found!" << endl;
    }

}

void Customer::book() {
    Customer::DATE();
    string name, namegarage;
    int g_id, service_id;
    cout << "Enter Name of Garage" << endl;
    cin >> namegarage;
    system("cls");
    g_id = MapOfGarages[namegarage];
    if (g_id != 0) {
        cout << "Enter Name of Service" << endl;
        cin >> name;
        system("cls");
        service_id = MapOfServices[{g_id,name}];
        cout << "=======" << endl;
        if (service_id != 0) {
            Service_Process service_p(cid,{Day,Month,Year},name, ListOfgarages[g_id - 1].list_of_Services[service_id - 1].price,
                                      ListOfgarages[g_id - 1].list_of_Services[service_id - 1]);

            cout << "Price of your service is : " << ListOfgarages[g_id - 1].list_of_Services[service_id - 1].price << endl;
            cout << "Agree or not?( y / n )" << endl;
            char p;
            cin >> p;
            system("cls");
            if (p == 'y' || p == 'Y') {

                cout << "The appointment is booked, we are waiting for you " << endl;
                cout << "Process id : " << service_p.process_id << endl;
                cout << "Customer id : " << service_p.customer_id << endl;
                cout << "Name of service : " << ListOfgarages[g_id - 1].list_of_Services[service_id - 1].name << endl;
                cout << "amount of money : " << service_p.amount_of_money << endl;
                cout<< "Date of service process : "<<service_p.Date.day<<" /"<<service_p.Date.month<<" /"<<service_p.Date.year<<endl;
                s_process[cid-1].push_back(service_p);
                } else if (p == 'n' || p == 'N') {
                cout << "Thank you for using our app" << endl;
            }
        } else {
            cout << "Service Not Found!" << endl;
        }
    } else {
        cout << "Garage Not Found!" << endl;
    }
}
void Customer::viewhistory(){
    for(int i=0;i<s_process[cid-1].size();i++){
        cout<<"-----------------------------------------------------"<<endl;
        cout<< "Customer id : " << s_process[cid-1][i].customer_id << endl;
        cout<<"Process id : "<<i+1<<endl;
        cout<<"amount of money : "<<s_process[cid-1][i].amount_of_money<<endl;
        cout<<"Name of service : "<<s_process[cid-1][i].name<<endl;
        cout<< "Date of service process : "<<s_process[cid-1][i].Date.day<<" / "<<s_process[cid-1][i].Date.month<<" / "<<s_process[cid-1][i].Date.year<<endl;
        cout<<"-----------------------------------------------------"<<endl;
    }
}










