#pragma once
#include"include.h"
#include"head.h"


int getValidInput() {
    int choice;
    while (true) {
        try {
            cout << "Please enter your choice: ";
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