#pragma once
#include "include.h"
#include "head.h"

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
            std::cout << "Insufficient balance." << std::endl;
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
        std::cout << "Current balance: ¥" << balance << std::endl;
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
};


class Payment {
private:
    int password;
    int paynumber = 0;
    Customer c;
public:
    Payment(int shouldpay, Customer user) :paynumber(shouldpay), c(user) {
    }
    bool pay(float price) {
        cout << endl;
        cout << "loading your wallet " << endl;
        Wallet wallet(c);
        wallet.reduce(price);
        return true;
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

            break;
        }

        if (paysuccess == true) {
            
            file.tic
        }
        return true;
        
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
    Reservation() {}
    ~Reservation() {}

    void viewTickets(const Customer& c) {
        std::string id = c.returnId();
        std::string fileName = "tickets.txt"; // Assuming all tickets are stored in this file
        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " + fileName << std::endl;
            return;
        }

        std::string line;
        std::vector<std::string> userTickets;

        // Read the file line by line
        while (getline(file, line)) {
            // Assuming each line represents a record and the user ID is the first part of the line
            if (line.find(id) == 0) { // Check if the line starts with the user ID
                userTickets.push_back(line);
            }
        }

        file.close();

        // Display all matching records
        std::cout << "Displaying all tickets for user ID: " << id << std::endl;
        for (const auto& ticket : userTickets) {
            std::cout << ticket << std::endl;
        }
    }
};



class Refund {
public:

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
            int a = getValidChoice();
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
                break;
            }
            case 4: {
                Wallet wallet(c);
                break;
            }
            case 5: {

                return ;
            }
            }
        }
    }
};