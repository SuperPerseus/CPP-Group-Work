#pragma once
#include"include.h"
/*
    ticketfile format: <match_time> id seatgrade location paytime paycost 
    seatfile format: <match_time> seatgrade[VIP,NORMAL,SUPER,dia,Pt,Au,Ag,Cu,Fe] gradetotalseat[1:] value[] 
    teamfile format: <match_time> team[0] team[1] 
*/

struct timecompare {
    bool operator()(const string& a, const string& b) {
        return a > b; 
    }
};

struct seatinfomation {
public:
    string matchtime;
    string seatgrade;
    int gradetotalseat;
    unordered_map<int, bool> seated;
    unordered_map<string, string> values;
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
    fstream seatsfile;
    fstream ticketsfile;
    fstream teamsfile;
    File() {
        const int maxRetries = 10;
        int attempt = 0;
        while (attempt < maxRetries) {
            try {
                seatsfile.open("seats.txt", std::fstream::in | std::fstream::out | std::ios::app);
                loadorcreate(seatsfile, string("seats.txt"));
                ticketsfile.open("tickets.txt", std::fstream::in | std::fstream::out | std::ios::app);
                loadorcreate(ticketsfile, string("tickets.txt"));
                teamsfile.open("teams.txt", std::fstream::in | std::fstream::out | std::ios::app);
                loadorcreate(teamsfile, string("teams.txt"));
                cout << endl;
                cout << endl;

                if (!seatsfile.is_open() || !ticketsfile.is_open() || !teamsfile.is_open()) {
                    throw std::ios_base::failure("File open failed");
                }

                init(seatsfile, ticketsfile, teamsfile);
                break;

            }
            catch (const std::ios_base::failure& e) {
                std::cerr << "Attempt " << (attempt + 1) << " failed: " << e.what() << std::endl;
                attempt++;
                if (seatsfile.is_open()) seatsfile.close();
                if (ticketsfile.is_open()) ticketsfile.close();
                if (teamsfile.is_open()) teamsfile.close();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }

        if (attempt == maxRetries) {
            std::cerr << "File exception: Unable to open files after " << maxRetries << " attempts." << std::endl;
        }
    };
    ~File() {
        bool successsave=savefile();
        if (successsave != true) {
            std::cout << "file save error,exit with error code 103" << endl;
            exit(103);
        }
        //cout << "save file success" << endl;
    };
    void print() {
        std::cout << tic.matchtime.top() << endl;
    }
    bool loadticket(fstream &file) ;
    bool loadseat(fstream &file) ;
    bool loadteam(fstream &file);
    bool savefile();
    void loadorcreate(fstream& file,string filename) {
        if (!file.is_open()) {
            std::cout << "does not exist, creating it.\n";
            file.open(filename, fstream::out);
        }
        else {
            cout << endl;
        }
    }

    void init(fstream &seatsfile, fstream &ticketsfile, fstream &teamsfile) {
        if (loadseat(seatsfile)) {
            loadticket(ticketsfile);
            loadteam(teamsfile);
            print();
            bool yes=savefile();
            cout << endl;
            cout << endl;
        }
        else {
            std::cout << "The file cannot be opened or created.\n";
            std::cout << "exit with code 104" << endl;
            exit(104);
        }
    }

};

bool File::loadseat(fstream &file) {


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


            for (int i = 1; i <= s.gradetotalseat; ++i) {
                s.seated[i] = true;
            }

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

bool File::loadticket(fstream &file) {

    string matchtime, id, seatgrade, location, paytime, paycost;
    ticketinfomation t;

    if (file.is_open()) {
        while (getline(file, matchtime)) {
            getline(file, id);
            getline(file, seatgrade);
            getline(file, location);
            getline(file, paytime);
            getline(file, paycost);

            t.matchtime = matchtime;
            t.id = id;
            t.seatgrade = seatgrade;
            t.location = stoi(location);
            t.paytime = paytime;
            t.paycost = stoi(paycost);
            for (auto& s : sea.setseat[matchtime]) {//检查比赛时间合不合法
                if (s.seatgrade == seatgrade) {
                    s.seated[t.location] = false;
                    break;
                }
            }

            tic.matchtime.push(matchtime);
            tic.id[matchtime].push_back(t);
        }
        file.close();
    }
    else {
        return false;
    }

    return true;
}

bool File::loadteam(fstream &file) {


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
                cout << "seat" << endl;
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
                cout << "ticket" << endl;
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
                cout << "team" << endl;
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
