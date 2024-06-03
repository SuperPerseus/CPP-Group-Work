#pragma once
#include"include.h"

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

int getValidInt() {
    int number;
    std::string input;
    while (true) {
        try {
            std::cout << "Please enter a positive number: ";
            std::cin >> input;

            // Check if input contains only digits
            bool isAllDigits = true;
            for (char c : input) {
                if (!std::isdigit(c)) {
                    isAllDigits = false;
                    break;
                }
            }

            if (!isAllDigits) {
                throw std::invalid_argument("Invalid input, please enter a number.");
            }

            number = std::stoi(input);

            if (number < 0) {
                throw std::out_of_range("Number must be positive, please enter a positive number.");
            }

            return number;

        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
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


float getValidFloat() {
    float number;
    std::string input;
    while (true) {
        try {
            std::cout << "Please enter a float number greater than or equal to 0: ";
            std::cin >> input;

            // Check if input is a valid float
            bool validFloat = true;
            bool decimalPointSeen = false;
            for (size_t i = 0; i < input.length(); i++) {
                if (!isdigit(input[i]) && input[i] != '.' && !(i == 0 && input[i] == '-')) {
                    validFloat = false;
                    break;
                }
                if (input[i] == '.') {
                    if (decimalPointSeen) {
                        validFloat = false; // Multiple decimal points are not allowed
                        break;
                    }
                    decimalPointSeen = true;
                }
            }

            if (!validFloat) {
                throw std::invalid_argument("Invalid input, please enter a float number.");
            }

            number = std::stof(input);

            if (number < 0) {
                throw std::out_of_range("Number must be greater than or equal to 0, please enter a valid float number.");
            }

            return number;

        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}