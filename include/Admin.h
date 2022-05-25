#ifndef ADMIN_H
#define ADMIN_H
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;
class Admin
{
public:
    static map<string, int> Map;
    static map<pair<int, pair<string, string>>, int> MapOfCar;
    int id;
    string userName;
    string password;
    Admin(int id, string userName, string password);
     static void add();
     static void Delete();
     static void update();
     static void administration();
};

#endif // ADMIN_H
