#pragma once
#include"include.h"
/*
    ticketfile format: <match_time> id seatgrade location paytime paycost 
    seatfile format: <match_time> seatgrade[dia,pt,au,ag,cu,fe] gradetotalseat[1:] value[] 
    teamfile format: <match_time> team[0] team[1] 
*/

struct timecompare {
    bool operator()(const string& a, const string& b) {
        return a > b; 
    }
};

struct ticketinfomation {
public:
    string matchtime;
    string id;
    string seatgrade;
    int location;
    string paytime;
    int paycost;
};

struct seatinfomation {
public:
    string matchtime;
    string seatgrade;
    int gradetotalseat;
    unordered_map<int, bool> seated;
    queue<int> unseat;
    unordered_map<string, string> values;
};

struct teaminfomation {
    string matchtime;
    string teamid[2];
};

class seats {
public:
    priority_queue<string, vector<string>, timecompare> matchtime;
    unordered_map<string, vector<seatinfomation>> setseat;
};

class tickets {
public:
    priority_queue<string, vector<string>,timecompare> matchtime;//用比赛时间排序
    unordered_map<string, vector<ticketinfomation>> id;//用比赛时间搜索关联下的所有票务信息
};

class teams {
public:
    priority_queue<string, vector<string>, timecompare> matchtime;
    unordered_map<string, vector<teaminfomation>> team;
};

class File {
public:
    seats sea;
    tickets tic;
    teams tea;
    fstream filecache;//给notify用
    File() {
        init();
    };
    ~File() {
        bool successsave=savefile();
        if (successsave != true) {
            std::cout << "file save error,exit with error code 103" << endl;
            exit(103);
        }
        cout << "save file success" << endl;
    };
    void print() {
        std::cout << tic.matchtime.top() << endl;
    }
    bool loadticket() ;
    bool loadseat() ;
    bool loadteam();
    bool savefile();

    void init() {
        if (loadseat()) {
            loadticket();
            loadteam();
            print();
            bool yes=savefile();
        }
        else {
            std::cout << "The file cannot be opened or created.\n";
            std::cout << "exit with code 104" << endl;
            exit(104);
        }
    }

};

bool File::loadseat() {
    fstream file;
    file.open("seats.txt", fstream::in | fstream::out);
    if (!file.is_open()) {
        std::cout << "seat File does not exist, creating it.\n";
        file.open("seats.txt", fstream::out);
    }
    else {
        std::cout << "seat File already exists, loading ......\n";
    }

    string matchtime, seatgrade, gradetotalseat, value;
    seatinfomation s;
    if (file.is_open()) {

        while (getline(file, matchtime)) {
            getline(file, seatgrade);
            getline(file, gradetotalseat);
            getline(file, value);
            s.matchtime = matchtime;
            s.seatgrade = seatgrade;
            s.gradetotalseat = stoi(gradetotalseat);
            s.values[seatgrade] = value;
            sea.matchtime.push(matchtime);
            sea.setseat[matchtime].push_back(s);
        }
        file.close();
    }
    else {
        return false;
    }

    return true;

}

bool File::loadticket() {
    fstream file;
    file.open("tickets.txt", fstream::in | fstream::out);
    if (!file.is_open()) {
        std::cout << "tikect File does not exist, creating it.\n";
        file.open("tickets.txt", fstream::out);
    }
    else {
        std::cout << "tikect File already exists, loading ......\n";
    }

    string matchtime, id, seatgrade, location, paytime, paycost;
    ticketinfomation t;
    if (file.is_open()) {

        while (getline(file, matchtime)) {
            getline(file, id);
            getline(file, seatgrade);
            getline(file, location);
            getline(file, paytime);
            getline(file, paycost);
            tic.matchtime.push(matchtime);
            t.matchtime = matchtime;
            t.id = id;
            t.seatgrade = seatgrade;
            t.location = stoi(location);
            t.paytime = paytime;
            t.paycost = stoi(paycost);
            tic.id[matchtime].push_back(t);
        }
        file.close();
    }
    else {
        return false;
    }

    return true;
    
}

bool File::loadteam() {
    fstream file;
    file.open("teams.txt", fstream::in | fstream::out);
    if (!file.is_open()) {
        std::cout << "team File does not exist, creating it.\n";
        file.open("teams.txt", fstream::out);
    }
    else {
        std::cout << "team File already exists, loading ......\n";
    }

    string matchtime;
    string team[2];
    teaminfomation t;
    if (file.is_open()) {

        while (getline(file, matchtime)) {
            getline(file, team[0]);
            getline(file, team[1]);
            t.matchtime = matchtime;
            t.teamid[0] = team[0];
            t.teamid[1] = team[1];
            tea.matchtime.push(matchtime);
            tea.team[matchtime].push_back(t);
        }
        file.close();
    }
    else {
        return false;
    }

    return true;

}

bool File::savefile() {
    seats outseat=sea;
    tickets outticket=tic;
    teams outteam=tea;
    bool writeseat = false, writeticket = false, writeteam=false;
    ofstream file("seats.txt", ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Failed to open seats.txt for appending.\n";
        exit(104);
    }
    string time;
    seatinfomation seatitem;
    while (!outseat.matchtime.empty()) {
        time=outseat.matchtime.top();
        outseat.matchtime.pop();
        auto it = outseat.setseat.find(time);
        if (it != outseat.setseat.end()) {
            if (it->second.size() != 0) {
                seatitem = it->second[0];
                it->second.erase(it->second.begin());

                file << seatitem.matchtime << endl << seatitem.seatgrade << endl << seatitem.gradetotalseat << endl << seatitem.gradetotalseat << endl;
            }
            else {
                std::cout << "in one matchtime,lose some seat record,error with code 106" << std::endl;
                exit(106);
            }
        }
        else {
            std::cout << "matchtime is different with seat record,error with code 105" << std::endl;
            exit(105);
        }
    }

    file.close();
    writeseat = true;


    ofstream ticketfile("tickets.txt", ios::out | ios::trunc);
    if (!ticketfile.is_open()) {
        cerr << "Failed to open tickets.txt for appending.\n";
        exit(104);
    }
    ticketinfomation ticketitem;
    while (!outticket.matchtime.empty()) {
        time = outticket.matchtime.top();
        outticket.matchtime.pop();
        auto it = outticket.id.find(time);
        if (it != outticket.id.end()) {
            if (it->second.size() != 0) {
                ticketitem = it->second[0];
                it->second.erase(it->second.begin());

                ticketfile << ticketitem.matchtime << endl << ticketitem.id << endl << ticketitem.seatgrade << endl << ticketitem.location << endl<< ticketitem.paytime<<endl<< ticketitem.paycost<<endl;
            }
            else {
                std::cout << "in one matchtime,lose some seat record,error with code 106" << std::endl;
                exit(106);
            }
        }
        else {
            std::cout << "matchtime is different with seat record,error with code 105" << std::endl;
            exit(105);
        }
    }

    ticketfile.close();
    writeticket = true;



    ofstream teamfile("teams.txt", ios::out | ios::trunc);
    if (!teamfile.is_open()) {
        cerr << "Failed to open tickets.txt for appending.\n";
        exit(104);
    }
    teaminfomation teamitem;
    while (!outteam.matchtime.empty()) {
        time = outteam.matchtime.top();
        outteam.matchtime.pop();
        auto it = outteam.team.find(time);
        if (it != outteam.team.end()) {
            if (it->second.size() != 0) {
                teamitem = it->second[0];
                it->second.erase(it->second.begin());

                teamfile << teamitem.matchtime << endl << teamitem.teamid[0] << teamitem.teamid[1] << endl;
            }
            else {
                std::cout << "in one matchtime,lose some seat record,error with code 106" << std::endl;
                exit(106);
            }
        }
        else {
            std::cout << "matchtime is different with seat record,error with code 105" << std::endl;
            exit(105);
        }
    }

    teamfile.close();
    writeteam = true;

    return (writeseat && writeteam && writeticket);
}
