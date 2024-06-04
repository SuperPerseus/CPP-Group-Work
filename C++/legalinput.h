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
            std::getline(std::cin, input);  // ʹ��getline��ȡ��������

            std::istringstream stream(input);
            std::string temp;
            if (!(stream >> number)) {  // ���Դ��������ж�ȡһ������
                throw std::invalid_argument("Invalid input, please enter a number.");
            }

            if (stream >> temp) {  // ����Ƿ��и�������
                throw std::invalid_argument("Invalid input, only a single positive number is allowed.");
            }

            if (number < 0) {
                throw std::out_of_range("Number must be positive, please enter a positive number.");
            }

            return number;  // �ɹ���ȡ����Ч������������

        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
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

                // ������ں�ʱ��ĺϷ���
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
            std::getline(std::cin, input); // ʹ��getline��ȡ��������

            std::istringstream stream(input);
            std::string temp;
            if (!(stream >> number)) {  // ���Դ��������ж�ȡһ��������
                throw std::invalid_argument("Invalid input, please enter a float number.");
            }

            if (stream >> temp) {  // ����Ƿ��и�������
                throw std::invalid_argument("Invalid input, only a single float number is allowed.");
            }

            if (number < 0) {
                throw std::out_of_range("Number must be greater than or equal to 0, please enter a valid float number.");
            }

            return number;  // �ɹ���ȡ����Ч��������������

        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
        }
        catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

string getCompleteLine() {
    std::string input;
    std::cout << "Please enter a line of text: ";
    std::getline(std::cin, input);  // ʹ�� getline ����ȡ���У������ո���κ������ַ�
    return input;
}