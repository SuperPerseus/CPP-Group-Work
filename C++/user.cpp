#include "user.h"

User::User(std::string username, std::string password, std::string userType)
    : username(username), password(password), userType(userType) {}

User::~User() {}

bool User::login() {
    return true; // Placeholder return value
}

void User::logout() {}

Customer::Customer(std::string username, std::string password, int customerId)
    : User(username, password, userType), customerId(customerId) {}

Customer::~Customer() {}

void Customer::book() {}

void Customer::ticket() {}

Team::Team(std::string username, std::string password, int teamId)
    : User(username, password, userType), teamId(teamId) {}

Team::~Team() {}

void Team::view() {}

Manager::Manager(std::string username, std::string password, int managerId)
    : User(username, password, userType), managerId(managerId) {}

Manager::~Manager() {}

void Manager::seatManage() {}
