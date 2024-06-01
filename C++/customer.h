#pragma once
#include "include.h"
#include "head.h"



class Reserve {//预订票
public:
    Reserve(){}
    ~Reserve(){}
    bool book() {
        timestamp();
        string wanttime, wantgrade;
        bool timeExists = false;
        bool gradeExists = false;
        int availseats = 0;
        int price = -1;
        File file;
        wanttime = getValidTimeString();
        while (true) {
            cout << "enter your want seatgrade:  ";
            cin >> wantgrade;
            for (const auto& time : file.sea.setseat) {
                const string& matchtime = time.first;
                const vector<seatinfomation>& seatinfomation = time.second;
                if (matchtime == wanttime) {
                    timeExists = true;
                    for (const auto& seat : seatinfomation) {
                        if (seat.seatgrade == wantgrade) {
                            gradeExists = true;
                            for (const auto& avail : seat.seated) {
                                if (avail.second) {
                                    availseats++;
                                }
                            }
                            price = stoi(seat.values.at(seat.seatgrade));
                            break;
                        }
                    }
                    break;
                }
            }

            if (!timeExists) {
                cout << "invaild matchtime ,enter again " << endl;
                cout << endl;
                wanttime = getValidTimeString();
                continue;
            }

            if (!gradeExists) {
                cout << "invaild seatgrade ,enter again " << endl;
                continue;
            }

            cout << "Enter how many seats you want to book: ";
            int wantbookseats = getValidInt();

            if (wantbookseats > availseats) {
                cout << "invaild seats enter agagin " << endl;
                continue;
            }
            int totalPrice = wantbookseats * price;
            cout << "Total price: " << totalPrice << endl;
            bool paysuccess=Payment pay(totalPrice);

            break;


        }
        
    }

};

class Viewing {//没有必要，可以合并到reservation
public:
    Viewing(){}
    ~Viewing(){}
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

                cout << "seatgrade: " << seatinfo.seatgrade << " , can booked total seats: " << available_seats << ", this grade's price: " << price << endl;
            }

            cout << endl;
            cout << endl;
        }
    }
};

class Reservation {
public:
};

class Payment {
private:
    int pay = 0;
public:
    Payment(int shouldpay):pay(shouldpay) {
    }
    bool pay()
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
        
        while (true) {
            cout << endl;
            cout << "deat customer,what can i do for you " << endl;
            cout << "enter number to choose function" << endl;
            cout << " 1. view the game and the tickets reservation situation " << endl;
            cout << " 2. book the ticket " << endl;
            cout << " 3. refund the ticket " << endl;
            cout << " 4. look your wallet " << endl;
            cout << " 5. exit the system " << endl;
            cout << endl;
            int a = getValidInt();
            switch (a) {
            case 1:{
                Viewing v;
                v.view();
                break;
            }
            case 2: {
                Viewing v;
                v.view();
                Reserve r;
                bool booksuccess=r.book();
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            }
        }
    }
};