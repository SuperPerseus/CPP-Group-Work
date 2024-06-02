#pragma once
#include "include.h"
#include "file.h"
#include "legalinput.h"

class bkViewing {
public:
    bkViewing() {}
    ~bkViewing() {}
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


class Notify {
public:
    Notify() {
        cout << "if want exit ,push any keyboard " << endl;
        bkViewing v;
        while (true) {           
            v.view();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (_kbhit()) {
                break;
            }
        }
        
    }
    ~Notify() {};
};

class SeatAdd {
public:
    SeatAdd() {
        File file;
        string matchtime, seatgrade, gradetotalseats;
        ticketinfomation t;
        cout << "enter the matchtime : ";
        matchtime = getValidTimeString();

        cout << "enter seatgrade: ";
        cin >> seatgrade;

        cout << "enter the grade total seats : ";
        gradetotalseats=to_string(getValidInt());

        auto it = file.sea.setseat.find(matchtime);
        if (it != file.sea.setseat.end()) {

        for (auto& time : file.sea.setseat) {
            if (time.first == matchtime) {
                for (auto& seat : time.second) {
                    if (seat.seatgrade == seatgrade) {
                        if (seat.gradetotalseat < stoi(gradetotalseats)) {
                            cout << "new seats are lower than the now ,some  locked seats will be canceled too " << endl;
                            cout << "if you want stop the opertion ,please put 0. if you want continue,enter the 1" << endl;
                            int Dangerous_operation = getValidInt();
                            switch (Dangerous_operation) {
                            case 1:
                                break;
                            case 0:
                                return;
                            default:
                                cout << "unknowen number,will stop this opertion " << endl;
                                return;
                            }
                        }
                        else {
                            seat.gradetotalseat = stoi(gradetotalseats);
                            cout << "success " << endl;
                        }
                        break;
                    }
                }
                break;
            }
        }
        cout << endl;
        cout << "success" << endl;
        cout << endl;
        file.savefile();
        }
        else {
            cout << "cant find it seat,please check file or retry " << endl;
        }

    }
        
    ~SeatAdd() {
    }
};

class SeatDelete {
public:
    SeatDelete() {
        File file;
        string matchtime, seatgrade, gradetotalseats;
        ticketinfomation t;
        cout << "enter the matchtime :";
        matchtime = getValidTimeString();

        cout << "enter seatgrade: ";
        cin >> seatgrade;

        cout << "enter total seats: ";
        gradetotalseats = to_string(getValidInt());

       
        auto it = file.sea.setseat.find(matchtime);
        if (it != file.sea.setseat.end()) {

            for (auto& time : file.sea.setseat) {
                if (time.first == matchtime) {
                    for (auto& seat : time.second) {
                        if (seat.seatgrade == seatgrade) {
                            
                            cout << "some customer `s tickets ,which locked seats will be canceled too " << endl;
                            cout << "if you want stop the opertion ,please put 0. if you want continue,enter the 1" << endl;
                            int Dangerous_operation = getValidInt();
                            switch (Dangerous_operation) {
                            case 1:
                                break;
                            case 0:
                                return;
                            default:
                                cout << "unknowen number,will stop this opertion " << endl;
                                return;
                            }
                            seat.gradetotalseat = -1;//connect with file 's loadticket()
                            break;
                        }
                    }
                    break;
                }

            }
            file.savefile();
            cout << endl;
            cout << "success" << endl;
            cout << endl;
        }
        else {
            cout << "cant find it seat,please check file or retry " << endl;
        }
    
    
    };
    ~SeatDelete() {};
};

class GradeAdd {
public:
    GradeAdd() {
        File file;
        string matchtime, seatgrade,  value;
        int gradetotalseat;
        seatinfomation s;
        cout << "enter the matchtime : " << endl;
        matchtime = getValidTimeString();

        cout << "enter seatgrade: " << endl;
        cin >> seatgrade;

        cout << "enter gradetotalseat: " << endl;
        gradetotalseat= getValidInt();

        cout << "enter value : " << endl;
         value= to_string(getValidFloat());

        bool exised=false;

        auto it = file.sea.setseat.find(matchtime);
        if (it != file.sea.setseat.end()) {

            for (auto& time : file.sea.setseat) {
                if (time.first == matchtime) {
                    for (auto& seat : time.second) {
                        if (seat.seatgrade == seatgrade) {
                            exised = true;
                            break;
                        }
                    }
                    if (exised == true) {
                        cout << "the grade is existed ,the operation will return with none" << endl;
                    }
                    else {
                        s.matchtime = matchtime;
                        s.seatgrade = seatgrade;
                        s.gradetotalseat = gradetotalseat;
                        s.values[seatgrade] = value;
                        file.sea.matchtime.push(matchtime);
                        file.sea.setseat[matchtime].push_back(s);
                        cout << endl;
                        cout<<"success"<<endl;
                        cout << endl;
                    }
                    break;
                }

            }
            file.savefile();
        }
        else {
            cout << "cant find it seat,please check file or retry " << endl;
        }
    }
    ~GradeAdd() {};
};

class Update {
public:
    Update() {
        File file;
        string matchtime, seatgrade, values;
        ticketinfomation t;
        cout << "enter the matchtime : "<<endl;
        matchtime = getValidTimeString();

        cout << "enter the new values: "<<endl;
        values = to_string(getValidInt());

        cout << "enter seatgrade: "<<endl;
        cin >> seatgrade;

        auto it = file.sea.setseat.find(matchtime);
        if (it != file.sea.setseat.end()) {

            for (auto& time : file.sea.setseat) {
                if (time.first == matchtime) {
                    for (auto& seat : time.second) {
                        if (seat.seatgrade == seatgrade) {
                            cout << "if you want stop the opertion ,please put 0. if you want continue,enter the 1" << endl;
                            int Dangerous_operation = getValidInt();
                            switch (Dangerous_operation) {
                            case 1:
                                break;
                            case 0:
                                return;
                            default:
                                cout << "unknowen number,will stop this opertion " << endl;
                                return;
                            }
                            seat.values[seatgrade] = values;
                            break;
                        }
                    }
                    break;
                }

            }
            file.savefile();
            cout << endl;
            cout << "success" << endl;
            cout << endl;
        }
        else {
            cout << "cant find it seat,please check file or retry " << endl;
        }

    }

    ~Update() {};
};

class SellManagement {
private:
public:
    SellManagement(Manager m) {
        while (true) {
            cout << endl;
            cout << "deal manager,this is the backend  " << endl;
            cout << "enter number to choose function" << endl;
            cout << " 1. add seat  " << endl;
            cout << " 2. update price  " << endl;
            cout << " 3. add new grade  " << endl;
            cout << " 4. notify mode  " << endl;
            cout << " 5. seat delete  " << endl;
            cout << " 6. exit the system " << endl;
            cout << endl;
            int a = getValidChoice();
            switch (a) {
            case 1: {
                SeatAdd sa;
                break;
            }
            case 2: {
                Update up;
                break;
            }
            case 3: {
                GradeAdd ga;
                break;
            }
            case 4: {
                Notify no;
                break;
            }
            case 5: {
                SeatDelete sd;
                break;
            }
            case 6: {
                return;
            }
            }
        }
        
        
    }
    SellManagement(Team t) {

    }

    ~SellManagement() {};

};

class Backend {//only manager and team can in this
public:
    Backend(Manager *input){
        cout << "here" << endl;
        Manager m(input);
        SellManagement sm(m);

    }
    Backend(Team *input) {
        /*SellManagement sm(input);*/
    }
    ~Backend() {};
};