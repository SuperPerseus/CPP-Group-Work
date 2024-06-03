#pragma once
#include "include.h"
#include "legalinput.h"
#include "file.h"


class InsertTeam {
public:
    InsertTeam() {
        File file;
        string matchtime, teamname[2], starter;
        teaminfomation t;
        cout << "enter the matchtime : " << endl;
        matchtime = getValidTimeString();

        cout << "enter the first teamname : " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, teamname[0]);

        cout << "enter the second teamname : " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, teamname[1]);

        cout << "enter your team's starter ,you must enter in one line: " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, starter);

        bool exised = false;

        auto it = file.tea.team.find(matchtime);
        if (it != file.tea.team.end()) {
            cout << endl;
            cout << "in this matchtime ,the  team message is exist" << endl;            
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
            t.matchtime = matchtime;
            t.teamname[0] = teamname[0];
            t.teamname[1] = teamname[1];
            t.starter = starter;
            file.tea.matchtime.push(matchtime);
            file.tea.team[matchtime].push_back(t);                     
            file.savefile();
        }
        else {
            t.matchtime = matchtime;
            t.teamname[0] = teamname[0];
            t.teamname[1] = teamname[1];
            t.starter = starter;
            file.tea.matchtime.push(matchtime);
            file.tea.team[matchtime].push_back(t);
            file.savefile();
        }
    }
    ~InsertTeam(){}
};

class TeamViewing {
public:
    TeamViewing() {
        File file;
        for (const auto& team : file.tea.team) {
            const string& matchteam = team.first;
            const vector<teaminfomation>& teaminfomation = team.second;


            for (const auto& teaminfo : teaminfomation) {
                cout << endl;
                cout << "the team 's infomation in this matchtime: " << teaminfo.matchtime <<
                    " , \nfirst team 's name : " << teaminfo.teamname[0] <<
                    " , \nsecond team 's  name : " << teaminfo.teamname[1] <<
                    " , \nsecond team 's  starter  : " << teaminfo.starter << endl;

                cout << endl;
            }

            cout << endl;
            cout << endl;
        }
    }
    ~TeamViewing() {}
};

class Modify{
public:
    Modify() {
        File file;
        string matchtime, teamname[2], starter;
        teaminfomation t;
        cout << "enter the matchtime : " << endl;
        matchtime = getValidTimeString();

        auto it = file.tea.team.find(matchtime);
        if (it != file.tea.team.end()) {
            cout << endl;
            cout << "team message is found " << endl;
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
            cout << "enter the new matchtime : " << endl;
            matchtime = getValidTimeString();

            cout << "enter the new first teamname : " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, teamname[0]);

            cout << "enter the new second teamname : " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, teamname[1]);

            cout << "enter the new team's starter : " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, starter);


            t.matchtime = matchtime;
            t.teamname[0] = teamname[0];
            t.teamname[1] = teamname[1];
            t.starter = starter;
            file.tea.matchtime.push(matchtime);
            file.tea.team[matchtime].push_back(t);
            file.savefile();
        }
        else {

            cout << "cant find it infomation ,please check file or retry " << endl;
        }
    }
    ~Modify() {}
};


class TeamManagement {
public:
    TeamManagement(Team t) {
        while (true) {
            cout << endl;
            cout << "Deal team coach ,this is the teambackend  " << endl;
            cout << "enter number to choose function" << endl;
            cout << " 1. insert your team and match information  " << endl;
            cout << " 2. viewing the match time and Opposite team " << endl;
            cout << " 3. rename your team name  " << endl;
            cout << " 4. exit the system " << endl;
            cout << endl;
            int a = getValidInt();
            switch (a) {
            case 1: {
                InsertTeam it;
                break;
            }
            case 2: {
                TeamViewing tv;
                break;
            }
            case 3: {
                Modify rt;
                break;
            }
            case 4: {
                return ;
            }
            default: {
                cout << "wrong input " << endl;
                break;
            }
            }
        }
    };
    ~TeamManagement() {};
};