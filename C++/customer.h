#pragma once
#include "include.h"
#include "head.h"



//class Reserve {//Ԥ��Ʊ
//public:
//    Reserve();
//    ~Reserve();
//    void add(File& file) {
//        std::string matchtime, id, seatgrade, location, paytime, paycost;
//        ticketinfomation t;
//        std::cout << "���������ʱ��: ";
//        std::cin >> matchtime;
//
//        std::cout << "������ID: ";
//        std::cin >> id;
//
//        std::cout << "��������λ�ȼ�: ";
//        std::cin >> seatgrade;
//
//        std::cout << "������ص�: ";
//        std::cin >> location;
//
//        std::cout << "������֧��ʱ��: ";
//        std::cin >> paytime;
//
//        std::cout << "������֧����;";
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

class Viewing {//û�б�Ҫ�����Ժϲ���reservation
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