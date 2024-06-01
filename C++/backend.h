#pragma once
#include "include.h"
#include "head.h"



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
public:
    SellManagement() {    
    };
    ~SellManagement() {};
    void view() {
        timestamp();
        File file;
        for (const auto& time : file.sea.setseat) {
            const string& matchtime = time.first;
            const vector<seatinfomation>& seatinfomation = time.second;

            cout << "Matchtime is: " << matchtime << endl;

            for (const auto& seatinfo : seatinfomation) {
                int available_seats = 0;
                for (const auto& seat : seatinfo.seated) {
                    if (seat.second) {
                        available_seats++;
                    }
                }
                string price = seatinfo.values.at(seatinfo.seatgrade);

                cout << "seatgrade: " << seatinfo.seatgrade <<  " , can booked total seats: " << available_seats << ", this grade's price: " << price << endl;
            }

            cout << endl;
            cout << endl;
        }
    }
    void book() {
        timestamp();

        string wanttime, wantgrade, wanthowmuch;
        view();
        bool timeExists = false;
        bool gradeExists = false;
        File file;
        wanttime=getValidTimeString();
        while(true) {
            cout << "enter your want seatgrade";
            cin >> wantgrade;
            for (const auto& time : file.sea.setseat) {
                const string& matchtime = time.first;
                const vector<seatinfomation>& seatinfomation = time.second;
                if (matchtime == wanttime) {
                    break;
                }
            }

            

        } 
        


    }
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