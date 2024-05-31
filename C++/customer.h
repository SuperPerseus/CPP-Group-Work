#pragma once
#include "include.h"
#include "head.h"



//class Reserve {//预订票
//public:
//    Reserve();
//    ~Reserve();
//    void add(File& file) {
//        std::string matchtime, id, seatgrade, location, paytime, paycost;
//        ticketinfomation t;
//        std::cout << "请输入比赛时间: ";
//        std::cin >> matchtime;
//
//        std::cout << "请输入ID: ";
//        std::cin >> id;
//
//        std::cout << "请输入座位等级: ";
//        std::cin >> seatgrade;
//
//        std::cout << "请输入地点: ";
//        std::cin >> location;
//
//        std::cout << "请输入支付时间: ";
//        std::cin >> paytime;
//
//        std::cout << "请输入支付金;";
//        std::cin >> paycost;
//
//
//        file.tic.matchtime.push(matchtime);
//        t.matchtime = matchtime;
//        t.id = id;
//        t.seatgrade = seatgrade;
//        t.location = stoi(location);
//        t.paytime = paytime;
//        t.paycost = stoi(paycost);
//        file.tic.id[matchtime].push_back(t);
//        file.savefile();
//    }
//};

class Viewing {//没有必要，可以合并到reservation
public:
};

class Reservation {
public:
};

class Payment {
public:
};

class Refund {
public:

};

class Wallet {

};

class Server {
    Customer c;
public:
    Server(User*input):c(input) {};
    void menu() {
        SellManagement m;
        while (true) {
            cout << "deat customer,what can i do for you " << endl;
            cout << "enter number to choose function" << endl;
            cout << " 1. view the game and the tickets reservation situation " << endl;
            cout << " 2. book the ticket " << endl;
            cout << " 3. refund the ticket " << endl;
            cout << " 4. look your wallet " << endl;
            cout << " 5. exit the system " << endl;
            int a =getValidInput();
            switch (a) {
            case 1:{

            }
            case 2: {

            }
            case 3: {

            }
            case 4: {

            }
            case 5: {

            }
            }
        }
    }
};