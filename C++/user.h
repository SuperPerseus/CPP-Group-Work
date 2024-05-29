#pragma once
#include <string>

class User {
protected:
    std::string password;
    std::string userType;
public:
    std::string username;
    User(std::string username = "defaultUsername", std::string password = "defaultPassword", std::string userType = "None");
    virtual ~User();
    bool login();
    void logout();
};

class Customer : public User {
public:
    int customerId;
    std::string ticketProfile;
    std::string userType = "cus";

    Customer(std::string username, std::string password, int customerId);
    ~Customer();
    void book();
    void ticket();
};

class Team : public User {
public:
    int teamId;
    std::string userType = "tea";
    Team(std::string username, std::string password, int teamId);
    ~Team();
    void view();
};

class Manager : public User {
public:
    int managerId;
    std::string userType = "man";
    Manager(std::string username, std::string password, int managerId);
    ~Manager();
    void seatManage();
};
