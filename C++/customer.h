#pragma once
#include "include.h"
#include "head.h"

using namespace CryptoPP;

class Wallet {
private:
    Customer c;
    fstream walletfile;
    string key;
    string id, ba;

    void recharge() {
        float newba = getValidFloat() + stof(ba);
        walletfile.seekp(0);
        walletfile << key << endl << id << endl << to_string(newba) << endl;
    }

public:
    Wallet(Customer input) : c(input) {
        try {
            walletfile.open(c.returnid(), fstream::in | fstream::out | fstream::app);

            if (!walletfile.is_open()) {
                throw ios_base::failure("File open failed");
            }

            walletfile.seekg(0, ios::end);
            if (walletfile.tellg() == 0) {
                // File is empty, initialize it
                cout << "File is empty, initializing it." << endl;
                walletfile.close();
                walletfile.open(c.returnid(), fstream::out);
                if (walletfile.is_open()) {
                    cout << "Initializing wallet..." << endl;
                    id = c.returnid();
                    key = getValidPassword();
                    ba = "0";
                    walletfile << key << endl << id << endl << ba << endl;
                    walletfile.close();
                    walletfile.open(c.returnid(), fstream::in | fstream::out);
                }
            }
            else {                
                walletfile.seekg(0, ios::beg);               
                cout << "File already exists, loading..." << endl;
                balance();
            }
        }
        catch (const ios_base::failure& e) {
            cerr << "Can't create or open the wallet, exiting with code 104." << endl;
            exit(104);
        }
    }

    ~Wallet() {
        walletfile.close();
    }

    void menu() {
        int choice;
        do {
            cout << "1. Check balance" << endl;
            cout << "2. Recharge" << endl;
            cout << "3. Exit" << endl;
            choice = getVaildChoice();
            switch (choice) {
            case 1:
                cout << "Your balance is: " << balance() << endl;
                break;
            case 2:
                recharge();
                break;
            case 3:
                break;
            default:
                cout << "Wrong input, please enter again." << endl;
                break;
            }
        } while (choice != 3);
    }

    float balance() {
        key = getValidPassword();
        AES_Encrypt_Decrypt_File(walletfile, key, false);
        if (walletfile.is_open()) {
            getline(walletfile, key);
            getline(walletfile, id);
            getline(walletfile, ba);
        }
        return stof(ba);
    }

    bool reduce(float reducevalue) {
        if (reducevalue > stof(ba)) {
            return false;
        }
        else {
            float tempba = stof(ba) - reducevalue;
            ba = to_string(tempba);
            walletfile.seekp(0);
            walletfile << key << endl << id << endl << ba << endl;
            return true;
        }
    }

    void AES_Encrypt_Decrypt_File(fstream& file, const string& key, bool encrypt) {
        SHA256 hash;
        SecByteBlock keyBlock(AES::DEFAULT_KEYLENGTH);
        hash.CalculateDigest(keyBlock, reinterpret_cast<const byte*>(key.data()), key.size());

        byte iv[AES::BLOCKSIZE];
        hash.CalculateDigest(iv, keyBlock, keyBlock.size());

        string fileContents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        string result;
        int exceptionCount = 0;
        while (exceptionCount < 3) {
            try {
                if (encrypt) {
                    CBC_Mode<AES>::Encryption encryption;
                    encryption.SetKeyWithIV(keyBlock, keyBlock.size(), iv);

                    StringSource ss(fileContents, true,
                        new StreamTransformationFilter(encryption,
                            new StringSink(result)
                        )
                    );
                }
                else {
                    CBC_Mode<AES>::Decryption decryption;
                    decryption.SetKeyWithIV(keyBlock, keyBlock.size(), iv);

                    StringSource ss(fileContents, true,
                        new StreamTransformationFilter(decryption,
                            new StringSink(result)
                        )
                    );
                }
                break;
            }
            catch (const Exception& e) {
                cerr << e.what() << endl;
                exceptionCount++;
            }
        }

        if (exceptionCount >= 3) {
            cerr << "Too many exceptions, exiting." << endl;
            exit(101);
        }

        file.seekp(0);
        file << result;
        file.flush();
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
            bool paysuccess = pay.pay(totalPrice);

            break;


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
                bool booksuccess=r.book(c);
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                Wallet wallet(c);
                wallet.menu();
                break;
            }
            case 5: {
                break;
            }
            }
        }
    }
};