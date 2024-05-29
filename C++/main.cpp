#include"head.h"

class User {
private:
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

class Customer : public User {
public:
    int customerId;
    string ticketProfile;

    Customer(string username, string password, string userType, int customerId)
        : User(username, password, userType), customerId(customerId) {}
    ~Customer() {};
    void book() {};
    void ticket() {};
};


class Team :User {
public:
    int teamId;
    Team(string username, string password, string userType, int teamId)
        : User(username, password, userType), teamId(teamId) {}
    ~Team() {};
    void view() {};
};

class Manager :User {
public:
    int managerId;
    Manager(string username, string password, string userType, int managerId)
        : User(username, password, userType), managerId(managerId) {}
    ~Manager() {};
    void seatManage() {};
};

int main() {
    Customer *c = new Customer("tom","123","customer",1);
}