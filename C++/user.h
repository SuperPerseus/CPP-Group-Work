#pragma once
#include"include.h"

using namespace std;

class User {
public:
    string username;
    string password;
    string userType;
    string id;
    User(string username = "defaultUsername", string password = "defaultPassword", string userType = "None",string id="000000000")
        : username(username), password(password), userType(userType),id(id) {}
    User(const User* user) :User(*user) {};
    virtual ~User() {};
    virtual string returnname() { return username; }
    virtual string returnpassword() { return password; }
    virtual string returntype() { return userType; }
    virtual string returnid() { return 0; }
    virtual bool login() { return false; }
    virtual void logout() {}
};

class Customer : public User {
public:
    string ticketProfile;

    Customer(string username, string password, string userType, string customerId)
        : User(username, password, userType, customerId) {}
    Customer(const User *user):User(*user){}
    ~Customer() {}
    int wallet() {
        int money;
        return money;
    }
    string returnname() override {
        return username;
    }

    string returnpassword() override {
        return password;
    }

    string returntype() override {
        return userType;
    }
    string returnid() override {
        return id;
    }
};


class Team :public User {
public:
    Team(string username, string password, string userType,string teamId)
        : User(username, password, userType, teamId) {}
    Team(const User *user) :User(*user) {}
    ~Team() {};
    void view() {};
    string returnname() {
        return username;
    }
    string returnpassword() {//在这里留待payment和退钱的重新输入密码检验
        return password;
    }
    string returntype() {
        return userType;
    }
    string returnid() {
        return id;
    }
};

class Manager :public User {
public:
    Manager(string username, string password, string userType, string managerId)
        : User(username, password, userType, managerId) {}
    Manager(const User *user) :User(*user) {}
    ~Manager() {};
    void seatManage() {};
    string returnname() {
        cout << "return name " << endl;
        return username;
    }
    string returnpassword() {//在这里留待payment和退钱的重新输入密码检验
        return password;
    }
    string returntype() {
        return userType;
    }
    string returnid() {
        return id;
    }
};