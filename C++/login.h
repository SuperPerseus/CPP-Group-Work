#pragma once
#include "user.h"

class Login {
private:
    User user;
    bool administratorToken = false;
public:
    Login(User u);
    ~Login();
    User returnU();
};
