#pragma once
#include"include.h"
#include"head.h"

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

int getVaildChoice() {//加个价格设置有效检验
    int choice;
    while (true) {
        try {
            cout << "please enter : ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input, please enter a number.");
            }

            if (choice < 1 || choice > 5) {
                throw out_of_range("Choice out of range, please enter a number between 1 and 5.");
            }

            return choice;

        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cerr << e.what() << endl;
        }
    }
}

int getValidInt() {//加个价格设置有效检验
    int number;
    while (true) {
        try {
            cout << "please enter : ";
            cin >> number;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input, please enter a number.");
            }

            return number;

        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }
}

string getValidTimeString() {
    const regex pattern(
        R"((\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}))"
    );
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string input;
    while (true) {
        try {
            cout << "Enter the time must obey the printed format (format: YYYY-MM-DD HH:MM): ";
            
            getline(cin, input);

            smatch match;
            if (regex_match(input, match, pattern)) {
                int year = stoi(match[1].str());
                int month = stoi(match[2].str());
                int day = stoi(match[3].str());
                int hour = stoi(match[4].str());
                int minute = stoi(match[5].str());

                // 检查日期和时间的合法性
                if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31 &&
                    hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
                    cout << "Valid date and time format." << endl;
                    return input;
                }
                else {
                    throw invalid_argument("Invalid date and time values.");
                }
            }
            else {
                throw invalid_argument("Invalid date and time format.");
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Please try again." << endl;
        }
    }
}