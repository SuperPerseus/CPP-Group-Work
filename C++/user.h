#pragma once
#include"include.h"

using namespace std;

class User {
public:
    string username;
    string password;
    string userType;
    User(string username = "defaultUsername", string password = "defaultPassword", string userType = "None")
        : username(username), password(password), userType(userType) {}

    virtual ~User() {};    // 析构函数应为虚函数

    virtual string returnname() { return username; }
    virtual string returnpassword() { return password; }
    virtual string returntype() { return userType; }
    virtual bool login() { return false; }
    virtual void logout() {}
    virtual string id() { return 0; }
};

class Customer : public User {
public:
    string customerId;
    string ticketProfile;

    Customer(string username, string password, string userType, string customerId)
        : User(username, password, userType), customerId(customerId) {}

    ~Customer() {}

    void book() {}
    void ticket() {}

    string id() override {
        return customerId;
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
};


class Team :public User {
public:
    string teamId;
    Team(string username, string password, string userType,string teamId)
        : User(username, password, userType), teamId(teamId) {}
    ~Team() {};
    void view() {};
    string id() {
        return teamId;
    }
    string returnname() {
        return username;
    }
    string returnpassword() {//在这里留待payment和退钱的重新输入密码检验
        return password;
    }
    string returntype() {
        return userType;
    }
};

class Manager :public User {
public:
    string managerId;
    Manager(string username, string password, string userType, string managerId)
        : User(username, password, userType), managerId(managerId) {}
    ~Manager() {};
    void seatManage() {};
    string id() {
        return managerId;
    }
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
};