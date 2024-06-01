#pragma once
#include "include.h"
#include "customer.h"
#include "file.h"
#include "legalinput.h"




class Notify {
public:
    Notify();
    ~Notify();
};

class SeatAdd {
public:
    SeatAdd(){
        
    }
    ~SeatAdd() {
    };
    void add() {
        File file;
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


        file.tic.matchtime.push(matchtime);
        t.matchtime = matchtime;
        t.id = id;
        t.seatgrade = seatgrade;
        t.location = stoi(location);
        t.paytime = paytime;
        t.paycost = stoi(paycost);
        file.tic.id[matchtime].push_back(t);
        file.savefile();
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

class SellManagement {
private:
    bool tokens=false;
public:
    SellManagement(){

    }
    SellManagement(bool input):tokens(input) {
    };

    ~SellManagement() {};

};

class Backend {//only manager and team can in this
private:
    User user;
    Manager m;
    Team t;
public:
    Backend(User* input) : user(*input), m(nullptr), t(nullptr) {
        if (dynamic_cast<Manager*>(input)) {
            m = new Manager(input);
        }
        else if (dynamic_cast<Team*>(input)) {
            t = new Team(input);
        }
    }
    void managercontrol() {

    }

};