#pragma once
#include"include.h"

class Notify {
public:
    Notify();
    ~Notify();
};

class SeatAdd {
public:
    SeatAdd() {
    
    };
    ~SeatAdd();
    void xiugai() {
        std::string matchtime, id, seatgrade, location, paytime, paycost;
        ticketinfomation t;
        std::cout << "请输入比赛时间: ";
        std::cin >> matchtime;

        std::cout << "请输入ID: ";
        std::cin >> id;

        std::cout << "请输入座位等级: ";
        std::cin >> seatgrade;

        std::cout << "请输入地点: ";
        std::cin >> location;

        std::cout << "请输入支付时间: ";
        std::cin >> paytime;

        std::cout << "请输入支付金;";
        std::cin >> paycost;


        tic.matchtime.push(matchtime);
        t.matchtime = matchtime;
        t.id = id;
        t.seatgrade = seatgrade;
        t.location = stoi(location);
        t.paytime = paytime;
        t.paycost = stoi(paycost);
        tic.id[matchtime].push_back(t);

    }
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
    SeatManagement() {
        File file;
    
    };
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