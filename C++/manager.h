#pragma once
#include"include.h"

class Notify {
public:
    Notify();
    ~Notify();
};

class SeatAdd {
public:
    SeatAdd();
    ~SeatAdd();
};

class SeatDelete {
public:
    SeatDelete();
    ~SeatDelete();
};

class Update {
public:
    Update();
    ~Update();
};

class SeatManagement {
public:
    SeatManagement();
    ~SeatManagement();
};

class Backend {
private:
    Manager user;
public:
    Backend(User *input) :user(input){};
    Manager returnuser() {
        return user;
    }
};