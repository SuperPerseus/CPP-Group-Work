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
        std::cout << "���������ʱ��: ";
        std::cin >> matchtime;

        std::cout << "������ID: ";
        std::cin >> id;

        std::cout << "��������λ�ȼ�: ";
        std::cin >> seatgrade;

        std::cout << "������ص�: ";
        std::cin >> location;

        std::cout << "������֧��ʱ��: ";
        std::cin >> paytime;

        std::cout << "������֧����;";
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