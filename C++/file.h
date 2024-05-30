#pragma once
#include"include.h"
/*
    ticketfile format: <match_time> id seatgrade location paytime paycost 
    seatfile format: <match_time> seatgrade[dia,pt,au,ag,cu,fe] gradetotalseat[1:] value[] 
    teamfile format: <match_time> team[2] 
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

class tickets {
public:
    priority_queue<string, vector<string>,timecompare> matchtime;//用比赛时间排序
    unordered_map<string, vector<ticketinfomation>> id;//用比赛时间搜索关联下的所有票务信息
};

class seats {
public:
    priority_queue<string, vector<string>, timecompare> matchtime;
    unordered_map<string, vector<seatinfomation>> setseat;
};

class teams {
public:
    priority_queue<string, vector<string>, timecompare> matchtime;
    unordered_map<string, vector<teaminfomation>> team;
};

class File {
private:
    tickets tic;
    seats sea;
    fstream filecache;//给notify用

public:
    File() {
        //加上查验token，如果没token，就不读取内置了
        if (loadseat()) {
            loadticket();
            print();
        }
        else {
            cout << "The file cannot be opened or created.\n";
            cout << "exit with code 101" << endl;
            exit(101);
        }
    };
    ~File() {};
    void print() {
        cout << tic.matchtime.top() << endl;
    }
    virtual bool loadticket() = 0;
    virtual bool loadseat() = 0;

};
bool File::loadticket() {
    fstream file;
    file.open("tickets.txt", fstream::in | fstream::out);
    if (!file.is_open()) {
        cout << "tikect File does not exist, creating it.\n";
        file.open("tickets.txt", fstream::out);
    }
    else {
        cout << "tikect File already exists, loading ......\n";
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

bool File::loadseat() {
    fstream file;
    file.open("seats.txt", fstream::in | fstream::out);
    if (!file.is_open()) {
        cout << "seat File does not exist, creating it.\n";
        file.open("seats.txt", fstream::out);
    }
    else {
        cout << "seat File already exists, loading ......\n";
    }

    string matchtime,seatgrade, gradetotalseat,value;
    seatinfomation s;
    if (file.is_open()) {

        while (getline(file, matchtime)) {
            getline(file, seatgrade);
            getline(file, gradetotalseat);
            getline(file, value);
            sea.matchtime.push(matchtime);
            s.matchtime = matchtime;
            s.seatgrade = seatgrade;
            s.gradetotalseat = stoi(gradetotalseat);
            s.values[seatgrade]=value;
            sea.setseat[matchtime].push_back(s);
        }
        file.close();
    }
    else {
        return false;
    }

    return true;

}


void saveUser(const std::string& username, const std::string& hashedPassword, const std::string& id, const std::string& type) {
    std::ofstream file("users.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open users.txt for appending.\n";
        return;
    }
    if (file.tellp() > 0) {
        file << std::endl;
    }
    file << username << endl << hashedPassword << endl << id << endl << type << endl;
}

// Loads users from a file into a data //structure
bool loadUsers(std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>>& users) {
    std::fstream file;
    file.open("users.txt", std::fstream::in | std::fstream::out);
    if (!file.is_open()) {
        std::cout << "File does not exist, creating it.\n";
        file.open("users.txt", std::fstream::out);
    }
    else {
        std::cout << "File already exists, opening and moving the read pointer to the first position.\n";
    }

    if (file.is_open()) {
        std::string username, password, id, type;
        while (std::getline(file, username)) {
            std::getline(file, password);
            std::getline(file, id);
            std::getline(file, type);
            users[username] = make_tuple(password, id, type);
        }
        file.close();
    }
    else {
        std::cout << "The file cannot be opened or created.\n";
        return false;
    }

    return true;
}