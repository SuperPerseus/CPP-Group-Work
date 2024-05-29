#include "login.h"

Login::Login(User u) : user(u) {}

Login::~Login() {}

User Login::returnU() {
    return user;
}
