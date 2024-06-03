#pragma once
#include "include.h"
#include "file.h"
#include "legalinput.h"
#include "timestamp.h"

using namespace CryptoPP;

class Wallet {
private:
    Customer c;
    std::fstream file;
    std::string id;
    float balance;
    std::string fileName;

public:
    // Constructor opens the file associated with the customer's ID and initializes the balance
    Wallet(Customer input) : c(input) {
        try {
            id = c.returnid();
            fileName = id + ".txt";

            // Open the file in read mode to check if it exists and read data
            file.open(fileName, std::ios::in);
            if (file.is_open()) {
                file >> id >> balance;
                file.close();
            }
            else {
                // If file does not exist, create one with initial balance of 100000
                balance = 100000;
                bool update_success = false;
                update_success = updateFile();
                if (update_success) {
                    throw std::ios_base::failure("File open failed");
                }
                
            }
            
        }
        catch (const std::ios_base::failure& e) {
            std::cerr << "cant control the wallet file  " << e.what() << std::endl;
            cout << "end with error code 101 " << endl;
            exit(101);         
        }
    }

    // Destructor writes back data and closes the file
    ~Wallet() {
        updateFile();
    }

    // Writes the current id and balance back to the file
    bool updateFile() {
        file.open(fileName, std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file << id << "\n" << balance << "\n";
            file.close();
        }
        return true;
    }

    // Reduce the balance by a specified amount if possible
    bool reduce(float amount) {
        if (amount > balance) {
            std::cout << "Insufficient balance. " << std::endl;
            return false;
        }
        else {
            balance -= amount;
            updateFile();
            return true;
        }
    }

    // View current balance
    void view() const {
        std::cout << "your balance: " << balance << std::endl;
    }

    // Recharge the balance by asking the user for an amount
    void recharge() {
        float amount;
        std::cout << "Enter amount to recharge: ";
        std::cin >> amount;
        if (amount < 0) {
            std::cout << "Invalid amount." << std::endl;
        }
        else {
            balance += amount;
            updateFile();
        }
    }
    void refund(float amount) {       
        if (amount < 0) {
            std::cout << "Invalid amount. End with error code 102" << std::endl;
            exit(102);
        }
        else {
            balance += amount;
            updateFile();
        }
    }
};


class Payment {
private:
    int password;
    float paynumber = 0;
    bool successpay = false;
    Customer c;
public:
    Payment(float shouldpay, Customer user) :paynumber(shouldpay), c(user) {
    }
    bool pay(float price) {
        cout << endl;
        cout << "loading your wallet " << endl;
        Wallet wallet(c);
        successpay=wallet.reduce(price);
        if (successpay == true) {
            return true;
        }
        else {
            return false;
        }
        
    }
};

class Reserve {//预订票
private:
    bool paysuccess = false;
public:
    Reserve(){}
    ~Reserve(){}
    bool book(Customer c) {
        timestamp();
        string wanttime, wantgrade;
        bool timeExists = false;
        bool gradeExists = false;
        int availseats = 0;
        float price = -1;
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
                            price = stof(seat.values.at(seat.seatgrade));
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
            float totalPrice = wantbookseats * price;
            cout << "Total price: " << totalPrice << endl;
            Payment pay(totalPrice,c);
            paysuccess = pay.pay(totalPrice);
            if (paysuccess == true) {
                int lockedseats = 0;
                ticketinfomation newt;
                vector<int> seatsvector;
                newt.matchtime = wanttime;
                newt.id = c.returnid();
                newt.seatgrade = wantgrade;

                for (auto& time : file.sea.setseat) {
                    string matchtime = time.first;
                    vector<seatinfomation>& seatinfomation = time.second;
                    if (matchtime == wanttime) {
                        timeExists = true;
                        for (auto& seat : seatinfomation) {
                            if (seat.seatgrade == wantgrade) {
                                for (auto& it : seat.seated) {
                                    if (it.second) {  
                                        it.second = false;  
                                        seatsvector.push_back(it.first);  
                                        lockedseats++;  
                                        if (lockedseats >= wantbookseats) {  
                                            break;  
                                        }
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                newt.paytime = returntimestamp();
                for (auto e : seatsvector) {
                    newt.location = e;
                    newt.paycost = price;
                    file.tic.matchtime.push(wanttime);
                    file.tic.id[wanttime].push_back(newt);
                }
                cout << endl;
                cout << endl;
            }
            break;
        }

        
        return true;
        
    }

};

class Viewing {
public:
    Viewing(){}
    ~Viewing(){}
    void view() {
        timestamp();
        File file;
        for (const auto& time : file.sea.setseat) {
            const string& matchtime = time.first;
            const vector<seatinfomation>& seatinfomation = time.second;

            cout << "matchtime is: " << matchtime << endl;

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
    Reservation(Customer& c) {
        File file;
        priority_queue<string, vector<string>, timecompare> matchtime;//用比赛时间排序
        unordered_map<string, vector<ticketinfomation>> id;
        file.tic.id;
        for (const auto& match : file.tic.id) {
            const vector<ticketinfomation>& ticketinfomation = match.second;
            for (auto& ticket : ticketinfomation) {
                if (ticket.id == c.returnid()) {
                    matchtime.push(match.first);
                    id[match.first].push_back(ticket);
                }
            }

        }
        ticketinfomation ticket;
        while (!matchtime.empty()) {
            string match = matchtime.top();
            matchtime.pop();
            for (auto ticket: id[match]) {
                cout << endl;
                cout << "your matchtime is : " << ticket.matchtime << "  your grade is : "<<ticket.seatgrade<< endl <<" your location is : " << ticket.location << " your pay time is ："<<ticket.paytime << endl;
                cout << endl;
            }
        }
    
    }
    ~Reservation() {}
};



class Refund {
private:
    float refundTotal = 0.0;

public:
    Refund(Customer& c) {
        File file;
        bool ticketFound = false;
        vector<ticketinfomation>::iterator it;

        string matchtime = getValidTimeString();
        string seatgrade;
        int location = -1;

        cout << "Please enter your seat grade: ";
        cin >> seatgrade;
        cout << "Please enter your seat location: ";
        cin >> location;

        for (auto iter = file.tic.id[matchtime].begin(); iter != file.tic.id[matchtime].end(); ++iter) {
            if (iter->id == c.returnid() && iter->seatgrade == seatgrade && iter->location == location) {
                ticketFound = true;
                it = iter;
                break;
            }
        }

        if (ticketFound) {
            for (auto& time : file.sea.setseat) {
                if (time.first == matchtime) {
                    for (auto& seat : time.second) {
                        if (seat.seatgrade == seatgrade) {
                            for (auto& seatinfo : seat.seated) {
                                if (seatinfo.first == location && seatinfo.second == false) {
                                    seatinfo.second = true; 
                                    refundTotal = stof(seat.values[seatgrade]);
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            file.tic.id[matchtime].erase(it);
            cout << "Refund processed for user ID: " << c.returnid() << ". Total refund amount: " << refundTotal << endl;

            // Assuming Wallet is defined and c has a method to access wallet
            Wallet wallet(c);
            wallet.refund(refundTotal);
        }
        else {
            cout << "No matching ticket found for the given details." << endl;
            cout << "Please check the input details again." << endl;
        }
    }

    ~Refund() {}
};


class Server {
    Customer c;
public:
    Server(User*input):c(input) {};
    void menu() {
        
        while (true) {
            cout << endl;
            cout << "deal customer,what can i do for you " << endl;
            cout << "enter number to choose function" << endl;
            cout << " 1. view the game and the tickets reservation situation " << endl;
            cout << " 2. book the ticket " << endl;
            cout << " 3. refund the ticket " << endl;
            cout << " 4. look your wallet " << endl;
            cout << " 5. exit the system " << endl;
            cout << endl;
            int a = getValidInt() ;
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
                bool booksuccess=r.book(c);
                break;
            }
            case 3: {
                Reservation reservation(c);
                Refund refund(c);

                break;
            }
            case 4: {
                Wallet wallet(c);
                wallet.view();
                break;
            }
            case 5: {
                return ;
            }
            default: {
                cout << "wrong input ,try again " << endl;
            }

            }
        }
    }
};