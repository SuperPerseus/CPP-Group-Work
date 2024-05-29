#pragma once
#include"include.h"

using namespace std;

class User {
protected:
    string username;
    string password;
    string userType;
public:   
    User(string username = "defaultUsername", string password = "defaultPassword", string userType = "None")
        : username(username), password(password), userType(userType) {}
    ~User() {};
    bool login() {}
    void logout() {}
};

class Customer :User {
public:
    int customerId;
    string ticketProfile;
    string userType = "cus";

    Customer(string username, string password, int customerId)
        : User(username, password, userType), customerId(customerId) {}
    ~Customer() {};
    void book() {};
    void ticket() {};
};


class Team :User {
public:
    int teamId;
    string userType = "tea";
    Team(string username, string password, int teamId)
        : User(username, password, userType), teamId(teamId) {}
    ~Team() {};
    void view() {};
};

class Manager :User {
public:
    int managerId;
    string userType = "man";
    Manager(string username, string password, int managerId)
        : User(username, password, userType), managerId(managerId) {}
    ~Manager() {};
    void seatManage() {};
};