#include "Service.h"
#include "Car.h"
#include "Buy_Rent_Process.h"
#include "Service_Process.h"
#include "Showrooms.h"
#include "Garages.h"
#include "Customer.h"
#include<fstream>
#include<ctime>
#define ListOfShowrooms Showrooms::ListOfShowrooms
#define ListOfgarages Garages::ListOfgarages
#define MapOfShowrooms Admin::MapOfShowrooms
#define MapOfCars Admin::MapOfCars
#define MapOfGarages Admin::MapOfGarages
#define MapOfServices Admin::MapOfServices
#define clr Admin::clr
#define ErrorChecking Admin::ErrorChecking
#define ByeBye Admin::ByeBye

map<string, int> Admin::MapOfShowrooms;
map<pair<int, pair<string, string>>, int> Admin::MapOfCars;
map<string, int> Admin::MapOfGarages;
map<pair<int,string>, int> Admin::MapOfServices;

Admin::Admin(int id, string userName, string password) {
    this->id = id;
    this->userName = userName;
    this->password = password;
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

date DATE(){
    int Day,Month,Year;
   time_t now = time(0);

   tm *ltm = localtime(&now);

     Year=1900 + ltm->tm_year;
     Month=1 + ltm->tm_mon;
     Day=ltm->tm_mday;
     return {Day,Month,Year};
}
void Admin::add() {
    Customer::DATE();
    int x;
    cout << "1 : ShowRoom" << endl << "2 : Car" << endl << "3 : Garage" << endl << "4 : Service" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
here_a_sh:string name, location, phone;
        cout << "Enter Showroom Name" << endl;
        cin >> name;
        cout << "Enter Showroom Location" << endl;
        cin >> location;
        cout << "Enter Showroom Phone" << endl;
        cin >> phone;
        system("cls");
        vector<Car> cars;
        Showrooms showroom(ListOfShowrooms.size() + 1, name, location, phone, cars);
        ListOfShowrooms.push_back(showroom);
        MapOfShowrooms[showroom.name] = showroom.id;
        cout << "Added Successfully" << endl;
        cout<<"Do you want to add another showroom ! (y / n)"<<endl;
            char d;cin>>d;if(d=='y'||d=='Y'){
                goto here_a_sh;
            }
    }
    else if (x == 2) {
        string nameshowroom;
        cout << "Enter Showroom Name" << endl;
        cin >> nameshowroom;
        system("cls");
        here_a_c:int sh_id = MapOfShowrooms[nameshowroom];
        if (sh_id != 0) {
            int inst;
            bool in;
            string make, model, year;
            double price;
            int c_id;
            cout << "Enter Car Model" << endl;
            cin >> model;
            cout << "Enter Car Make" << endl;
            cin >> make;
            cout << "Enter Car Year" << endl;
            cin >> year;
            cout << "Enter Car Price" << endl;
            cin >> price;
            cout << "Available for installment or no ( 0 : false / 1 : true )?" << endl;
            ErrorChecking(inst) ;
            if(inst==0){
                in=false;
            }
            else{
                in=true;
            }
            system("cls");
            c_id = ListOfShowrooms[sh_id - 1].list_of_Cars.size() + 1;
            Car car(c_id, year, price, make, true, model, in,DATE());
            ListOfShowrooms[sh_id - 1].list_of_Cars.push_back(car);
            MapOfCars[{sh_id, {model, year}}] = car.id;
            cout << "Added Successfully" << endl;
            cout<<"Do you want to add another car ! (y / n)"<<endl;
            char d;cin>>d;if(d=='y'||d=='Y'){
                goto here_a_c;
            }
        } else {
            cout << "Showroom Not Found!" << endl;
        }
    }
 else if (x == 3) {
    here_a_g: string name, location, phone;
        cout << "Enter garage Name" << endl;
        cin >> name;
        cout << "Enter garage Location" << endl;
        cin >> location;
        cout << "Enter garage Phone" << endl;
        cin >> phone;
        system("cls");
        vector<Service> service;
        Garages garage(ListOfgarages.size() + 1, name, location, phone, service);
        ListOfgarages.push_back(garage);
        MapOfGarages[garage.name] = garage.id;
        cout << "Added Successfully" << endl;
        cout<<"Do you want to add another garage ! (y / n)"<<endl;
            char d;cin>>d;if(d=='y'||d=='Y'){
                goto here_a_g;
            }
    } else if (x == 4) {
        string gname;
        cout << "Enter garage Name " << endl;
        cin >> gname;
        system("cls");
        here_a_s:int g_id = MapOfGarages[gname];
        if (g_id != 0) {
        int s_id;
            string name;
            long long price;
            cout << "Enter service name" << endl;
            cin >> name;
            cout << "Enter service price" << endl;
            cin >> price;
            system("cls");
            s_id = ListOfgarages[g_id - 1].list_of_Services.size() + 1;
            Service service(s_id, name, price);
            ListOfgarages[g_id - 1].list_of_Services.push_back(service);
            MapOfServices[{g_id,name}] = service.id;
            cout << "Added Successfully" << endl;
            cout<<"Do you want to add another service ! (y / n)"<<endl;
            char d;cin>>d;if(d=='y'||d=='Y'){
                goto here_a_s;
            }
        }
        else {
            cout << "Garage Not Found!" << endl;
             }
        }
}
void Admin::update() {
    int x;
    cout << "1 : ShowRooms" << endl << "2 : Car" << endl << "3 : Garage" << endl << "4 : Service" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
        here_u_sh:
        string old_name;
        cout << "Enter Name Of Showroom" << endl;
        cin >> old_name;
        system("cls");
        int sh_id = MapOfShowrooms[old_name];
            if (sh_id!=0) {
                 cout << "1 : Name " << endl << "2 : Location " << endl << "3 : Phone Number " << endl;
                int choice;string new_name, location, Phone;
                cin >> choice;
                system("cls");
                if (choice == 1) {
                    cout << "Enter New Name Of Showroom" << endl;
                    cin >> new_name;
                    system("cls");
                    ListOfShowrooms[sh_id-1].name = new_name;
                    cout << "Name Modified Successfully" << endl;
                } else if (choice == 2) {
                    cout << "Enter New Location Of Showroom" << endl;
                    cin >> location;
                    system("cls");
                    ListOfShowrooms[sh_id-1].location = location;
                    cout << "Location Modified Successfully" << endl;
                } else if (choice == 3) {
                    cout << "Enter New Phone Number Of Showroom" << endl;
                    cin >> Phone;
                    system("cls");
                    ListOfShowrooms[sh_id-1].phone_number = Phone;
                    cout << "Phone Number Modified Successfully" << endl;
                }
                    cout<<"Do you want to update another showroom ! (y / n)"<<endl;
                    char up;cin>>up;if(up=='y'||up=='Y'){
                    goto here_u_sh;
                    }
                else if(sh_id==0)
                    cout << "Invalid Showroom"<<endl;
        }
    }
    if (x == 2) {
        int choice;
        string name;
        cout << "Enter Name Of Showroom " << endl;
        cin >> name;
        system("cls");
        int sh_id = MapOfShowrooms[name];
            if (sh_id!=0) {
                here_u_c:
                string model ,year;
                cout << "Enter Car Model" << endl;
                cin >> model;
                cout << "Enter Car Year" << endl;
                cin >> year;
                system("cls");
                int car_id=MapOfCars[{sh_id,{model,year}}];
                if (car_id!=0) {
                        cout<<"1 : price"<<endl<<"2 : installment"<<endl;
                        int r;long long price;
                        ErrorChecking(r);
                    if(r==1){
                        cout << "Enter New Price Of Car" << endl;
                        cin >> price;
                        system("cls");
                        ListOfShowrooms[sh_id-1].list_of_Cars[car_id-1].price = price;
                        cout << "Price Modified Successfully" << endl;
                    }
                    else if(r==2){
                            bool insta;
                        cout << "Enter new state for installment" << endl;
                        cin >> insta;
                        ListOfShowrooms[sh_id-1].list_of_Cars[car_id-1].installment = insta;
                        system("cls");
                        cout << "New state for installment Modified Successfully" << endl;
                    }
                }
                else if (car_id==0) {
                    cout << "Invalid Car" << endl;
                }
            }
            else if (sh_id==0) {
                cout << "Invalid Showroom" << endl;
            }
            cout<<"Do you want to update another showroom ! (y / n)"<<endl;
                    char up;cin>>up;if(up=='y'||up=='Y'){
                    goto here_u_c;
                    }
    }


    if (x == 3) {
        here_u_g:
        string old_name;
        cout << "Enter Name Of Garage" << endl;
        cin >> old_name;
        system("cls");
        int g_id=MapOfGarages[old_name];
            if (g_id!=0) {
                cout << "1 : Name" << endl << "2 : Location " << endl << "3 : Phone Number " << endl;
                int choice;string new_name, location, phone;
                cin >> choice;
                system("cls");
                if (choice == 1) {
                    cout << "Enter New Name Of Garage" << endl;
                    cin >> new_name;
                    system("cls");
                    ListOfgarages[g_id-1].name = new_name;
                    cout << "Name Modified Successfully" << endl;
                } else if (choice == 2) {
                    cout << "Enter New Location Of Garage" << endl;
                    cin >> location;
                    system("cls");
                    ListOfgarages[g_id-1].location = location;
                    cout << "Location Modified Successfully" << endl;
                } else if (choice == 3) {
                    cout << "Enter New Phone Number Of Garage" << endl;
                    cin >> phone;
                    system("cls");
                    ListOfgarages[g_id-1].phone_number = phone;
                    cout << " Phone Number Modified Successfully" << endl;
                }
                cout<<"Do you want to update another showroom ! (y / n)"<<endl;
                char up;cin>>up;if(up=='y'||up=='Y'){
                goto here_u_g;
                }
            else if(g_id==0)
                cout << "Invalid Garage";
        }
        else if (x == 4) {
        string name_of_garage;
        cout << "Enter Name Of Garage " << endl;
        cin >> name_of_garage;
        system("cls");
        int g_id=MapOfGarages[name_of_garage];
            if (g_id!=0) {
                here_u_s:cout << "Enter Service Name" << endl;
                string name_of_service;
                cin >> name_of_service;
                system("cls");
                int s_id=MapOfServices[{g_id,name_of_service}];
                    if (s_id!=0) {
                        long long price;
                        cout << "Enter New Price Of Service" << endl;
                        cin >> price;
                        system("cls");
                        ListOfgarages[g_id-1].list_of_Services[s_id-1].price = price;
                        cout << "Price Modified Successfully" << endl;
                        cout<<"Do you want to update another service ! (y / n)"<<endl;
                        char up;     cin>>up;
                        if(up=='y'||up=='Y'){
                        goto here_u_s;
                        }
                    }
                    else if(s_id==0) {
                        cout << "Invalid Service" << endl;
                    }
            }
            else if(g_id==0) {
                cout << "Invalid Garage" << endl;
            }
        }
    }
}
void Admin::Delete() {
    int x;
    cout << "1 : Showroom" << endl << "2 : Car" << endl << "3 : Garage" << endl << "4 : Service" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
here_sh:int sh_id;string n;
        cout << "Enter Name Of Showroom" << endl;
        cin >> n;
        sh_id=MapOfShowrooms[n];
        system("cls");
            if (sh_id!=0) {
                Erase(ListOfShowrooms, sh_id-1);
                cout << "Showroom Deleted Successfully" << endl;
                cout<<"Do you want to delete another showroom ! (y / n)"<<endl;
                char de;cin>>de;if(de=='y'||de=='Y'){
                goto here_sh;
                }
            }
            else{
                cout<<"Invalid showroom "<<endl;
                goto here_sh;
            }
            for(int i=sh_id-1;i<ListOfShowrooms.size();i++){
                ListOfShowrooms[i].id--;
                MapOfShowrooms[ListOfShowrooms[i].name]=ListOfShowrooms[i].id;
            }
        }
     else if (x == 2) {
     in:string m, y, s;
        cout << "Enter Name Of Showroom" << endl;
        cin >> s;
        system("cls");
        int sh_id;
        sh_id=MapOfShowrooms[s];
            if (sh_id!=0) {
        here_c: cout << "Enter Model of car" << endl;
                cin >> m ;
                cout << "Enter Year of car" << endl;
                cin >> y ;
                system("cls");
                int car_id=MapOfCars[{sh_id, {m, y}}];
                    if (car_id!=0) {
                        Erase(ListOfShowrooms[sh_id-1].list_of_Cars, car_id-1);
                        cout << "Car Deleted Successfully" << endl;
                        cout<<"Do you want to delete another car ! (y / n)"<<endl;
                        char de;cin>>de;if(de=='y'||de=='Y'){
                        goto here_c;
                    }
                }
                    else{
                        cout<<"Invalid car "<<endl;
                }
                for(int i=car_id-1;i<ListOfShowrooms[sh_id-1].list_of_Cars.size();i++){
                    ListOfShowrooms[sh_id-1].list_of_Cars[i].id--;
                    MapOfCars[{sh_id,{ListOfShowrooms[sh_id-1].list_of_Cars[i].model,ListOfShowrooms[sh_id-1].list_of_Cars[i].year}}]
                    =ListOfShowrooms[i].id;
                }
            }
            else{
                cout<<"Invalid showroom "<<endl;
                goto in;
            }
        }
        else if (x == 3) {
        here_g: int g_id;string ng;
        cout << "Enter Name Of Garage" << endl;
        cin >> ng;
        g_id=MapOfGarages[ng];
        system("cls");
            if (g_id!=0) {
                Erase(ListOfgarages, g_id-1);
                cout << "Garage Deleted Successfully" << endl;
                cout<<"Do you want to delete another garage ! (y / n)"<<endl;
                char de;cin>>de;if(de=='y'||de=='Y'){
                goto here_g;

            }
        }
        else{
            cout<<"Invalid garage "<<endl;
            goto here_g;
        }
        for(int i=g_id-1;i<ListOfgarages.size();i++){
                ListOfgarages[i].id--;
                MapOfGarages[ListOfgarages[i].name]=ListOfgarages[i].id;
            }
    }
    else if (x == 4) {
      garag:string g;
            cout << "Enter Name Of Garage" << endl;
            cin >> g;
            system("cls");
                int ga_id=MapOfGarages[g];
                if (ga_id!=0) {
               serv:cout << "Enter Name Of Service" << endl;
                    string ns;cin >> ns;
                    int ser_id=MapOfServices[{ga_id,ns}];
                    system("cls");
                        if (ser_id!=0) {
                            Erase(ListOfgarages[ga_id-1].list_of_Services, ser_id-1);
                            cout << "Service Deleted Successfully" << endl;
                            cout<<"Do you want to delete another service ! (y / n)"<<endl;
                            char de;cin>>de;if(de=='y'||de=='Y'){
                            goto serv;
                            }
                        }
                        else{
                           cout<<"Invalid service "<<endl;
                           goto serv;
                        }
                        for(int i=ser_id-1;i<ListOfgarages[ga_id-1].list_of_Services.size();i++){
                            ListOfgarages[ga_id-1].list_of_Services[i].id--;
                            MapOfServices[{ga_id,ListOfgarages[ga_id-1].list_of_Services[i].name}]
                            =ListOfgarages[ga_id].list_of_Services[i].id;
                        }
                    }
                    else{
                        cout<<"Invalid garage "<<endl;
                        goto garag;
                    }
            }
}
void Admin::administration() {
    int x;
    cout << "1 : Add" << endl;
    cout << "2 : Update" << endl;
    cout << "3 : Delete" << endl;
    cout << "4 : Exit" << endl;
    ErrorChecking(x);
    system("cls");
    if (x == 1) {
        add();
        administration();
    } else if (x == 2) {
        update();
        administration();
    } else if (x == 3) {
        Delete();
        administration();
    } else if (x == 4)
        return;
}
