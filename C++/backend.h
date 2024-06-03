#include "include.h"
#include "timestamp.h"
#include "team.h"

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
                        //cout << available_seats << endl;
                    }
                }
                string price = seatinfo.values.at(seatinfo.seatgrade);

                cout << "seatgrade: " << seatinfo.seatgrade << " , can booked total seats: " << available_seats << ", this grade's price: " << price << endl;
            }



            cout << endl;
            cout << endl;
        }

        for (const auto& ticket : file.tic.id) {
            const string& matchticket = ticket.first;
            const vector<ticketinfomation>& ticketinfomation = ticket.second;

            for (const auto& ticketinfo : ticketinfomation) {
                cout << endl;
                cout << "ticket matchtime: " << ticketinfo.matchtime <<
                    " , customers id : " << ticketinfo.id <<
                    " \n, this ticket seatgrade : " << ticketinfo.seatgrade <<
                    " , location: " << ticketinfo.location <<
                    " \n, paytime: " << ticketinfo.paytime <<
                    " , paycost: " << ticketinfo.paycost << endl;

            }

            cout << endl;
            cout << endl;
        }


        for (const auto& team : file.tea.team) {
            const string& matchteam = team.first;
            const vector<teaminfomation>& teaminfomation = team.second;

            for (const auto& teaminfo : teaminfomation) {
                cout << endl;
                cout << "the team 's infomation in this matchtime: " << teaminfo.matchtime <<
                    " ,\n first team 's name : " << teaminfo.teamname[0] <<
                    " , \nsecond team 's  name : " << teaminfo.teamname[1] <<
                    " , \nsecond team 's  starter  : " << teaminfo.starter <<endl;

                cout << endl;
            }

            cout << endl;
            cout << endl;
        }
    }
};


class Notify {
public:
    Notify() {
        cout << " if want exit ,push any keyboard " << endl;
        bkViewing v;
        while (true) {           
            v.view();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            if (_kbhit()) {
                break;
            }
        }
        
    }
    ~Notify() {};
};

class InsertNewMatch {
public:
    InsertNewMatch(){
        File file;
        string matchtime, seatgrade, value;
        int gradetotalseat;
        seatinfomation s;
        cout << "enter the matchtime : " << endl;
        matchtime = getValidTimeString();

        cout << "enter seatgrade: " << endl;
        
        getline(cin, seatgrade);


        cout << "enter gradetotalseat: " << endl;
        gradetotalseat = getValidInt();

        cout << "enter value : " << endl;
        value = to_string(getValidFloat());

        auto it = file.sea.setseat.find(matchtime);
        if (it == file.sea.setseat.end()) {
            cout << "no matchtime is existed ,you can insert new one " << endl;
            cout << "if you want stop the danger opertion ,please put 0. if you want continue,enter the 1" << endl;
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
            s.matchtime = matchtime;
            s.seatgrade = seatgrade;
            s.gradetotalseat = gradetotalseat;
            s.values[seatgrade] = value;

            file.sea.matchtime.push(matchtime);
            file.sea.setseat[matchtime].push_back(s);

            cout << endl;
            cout << "success" << endl;
            cout << endl;
            file.savefile();
        }
        else {
            cout << "the matchtime is existed ,delete game time is banned " << endl;
        }

    }

    ~InsertNewMatch() {


    }
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, seatgrade);

        cout << "enter the grade total seats : ";
        gradetotalseats=to_string(getValidInt());

        auto it = file.sea.setseat.find(matchtime);
        if (it != file.sea.setseat.end()) {

        for (auto& time : file.sea.setseat) {
            if (time.first == matchtime) {
                for (auto& seat : time.second) {
                    if (seat.seatgrade == seatgrade) {
                        if (seat.gradetotalseat > stoi(gradetotalseats)) {
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, seatgrade);

        cout << "enter want to delete seats: ";
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
                            if (seat.gradetotalseat >= stoi(gradetotalseats)) {
                                seat.gradetotalseat = stoi(gradetotalseats);
                            }
                            else {
                                seat.gradetotalseat = -1;
                            }
                            //connect with file 's loadticket()
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, seatgrade);

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
        getline(cin, seatgrade);

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
            cout << endl;
            cout << "attention , the matchtime is cannot be changed" << endl;
            cout << "To avoid irritating customers,you can only to add price or total seats "<< endl;
            cout << endl;
            cout << " 1.insert new matchtime " << endl;
            cout << " 2. add seat  " << endl;
            cout << " 3. update price  " << endl;
            cout << " 4. add new grade  " << endl;
            cout << " 5. notify mode  " << endl;
            cout << " 6. seat delete  " << endl;
            cout << " 7. viewing the now seats and match  " << endl;
            cout << " 8. exit the system " << endl;
            cout << endl;
            int a = getValidInt();
            switch (a) {
            case 1: {
                InsertNewMatch inm;
                break;
            }case 2: {
                SeatAdd sa;
                break;
            }
            case 3: {
                Update up;
                break;
            }
            case 4: {
                GradeAdd ga;
                break;
            }
            case 5: {
                Notify no;
                break;
            }
            case 6: {
                SeatDelete sd;
                break;
            }
            case 7: {
                bkViewing bk;
                bk.view();
                break;
            }
            case 8: {
                return;
            }
            default: {
                cout << "wrong input " << endl;
                break;
            }
            }
        }        
    }
    SellManagement(Team t) {
        TeamManagement tm(t);

    }

    ~SellManagement() {};

};

class Backend {//only manager and team can in this
private:
    bool token=false;
public:
    Backend(User* input,bool token) :token(token) {
        if (token == true) {
            Manager m(input);
            SellManagement sm(m);
        }
        else {
            Team t(input);
            SellManagement sm(t);
        }
    }
    ~Backend() {};
};
