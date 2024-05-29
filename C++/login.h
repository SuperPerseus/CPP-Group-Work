#pragma once
#include "user.h"
#include"include.h"

using namespace std;

class Login {
private:
    User user;
    bool administratorToken = false;
public:
    Login(User u) :user(u) {};
    ~Login() {};
    User returnU() {
        return user;
    }
};