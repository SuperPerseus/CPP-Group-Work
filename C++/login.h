#pragma once
#include "user.h"
#include "include.h"

using namespace std;

class Login {
private:
    User user;
    bool administratorToken = false;
public:
    Login(User u) {

    }
    ~Login() {};
    User returnU() {
        return user;
    }
};

string hashPassword(const string& password) {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest, (const CryptoPP::byte*)password.data(), password.size());

    CryptoPP::HexEncoder encoder;
    string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

// Saves the user's information in a file
void saveUser(const std::string& username, const std::string& hashedPassword, const std::string& email, const std::string& type) {
    std::ofstream file("users.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open users.txt for appending.\n";
        return;
    }
    if (file.tellp() > 0) {
        file << std::endl;
    }
    file << username << endl << hashedPassword << endl << email << endl << type << endl;
}

// Loads users from a file into a data structure
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
        std::string username, password, email, type;
        while (std::getline(file, username)) {
            std::getline(file, password);
            std::getline(file, email);
            std::getline(file, type);
            users[username] = make_tuple(password, email, type);
        }
        file.close();
    }
    else {
        std::cout << "The file cannot be opened or created.\n";
        return false;
    }

    return true;
}

// Checks if the password is strong
bool isPasswordStrong(const string& password) {
    if (password.length() < 8) {
        return false; // The password needs to be at least 8 characters long.
    }
    bool containsDigit = false;
    bool containsAlpha = false;
    for (char ch : password) {
        if (isdigit(ch)) {
            containsDigit = true;
        }
        else if (isalpha(ch)) {
            containsAlpha = true;
        }
        if (containsDigit && containsAlpha) {
            return true; // Found both a digit and an alphabetic character.
        }
    }
    return false; // Did not find both a digit and an alphabetic character.
}

// Registers a new user after validating password strength
void registerUser(unordered_map<string, std::tuple<std::string, std::string, std::string>>& users) {
    string username, password, email, type;
    cout << "Enter username: ";
    cin >> username;

    if (users.find(hashPassword(username)) != users.end()) {
        cout << "Username already exists.\n";
        return;
    }

    do {
        cout << "Enter password: ";
        cin >> password;

        if (!isPasswordStrong(password)) {
            cout << "Password must be at least 8 characters long and contain at least one digit.\n";
        }
        else {
            break; // Valid password, exit loop.
        }
    } while (true);

    cout << "Enter email: ";
    cin >> email;
    cout << "Enter grade (Office Junior < 10, CEO >= 10): ";
    cin >> type;
    cout << "A verification code has been sent to your email.\n";

    string hashedUsername = hashPassword(username);
    string hashedPassword = hashPassword(password);
    string hashedEmail = hashPassword(email);
    users[hashedUsername] = make_tuple(hashedPassword, hashedEmail, type);
    saveUser(hashedUsername, hashedPassword, hashedEmail, type);
    cout << "User registered successfully!\n";
}

// Handles the login process
void loginUser(const unordered_map<string, tuple<string, string, string>>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = users.find(hashPassword(username));
    if (it == users.end()) {
        cout << "Invalid login credentials.\n";
        return;
    }

    if (std::get<0>(it->second) != hashPassword(password)) {
        int time = 3;
        while (time--) {
            cout << "Wrong password, please enter again.\n";
            cout << "You have " << time + 1 << " chance(s).\n";
            cin >> password;
            if (std::get<0>(it->second) == hashPassword(password)) {
                break;
            }
        }
        if (time < 0) { // All attempts used
            cout << "No more attempts allowed.\n";
            return;
        }
    }
    cout << "Logged in successfully!\n";
    cout << "Your grade is " << std::get<2>(it->second) << ".\n";
    if (stoi(std::get<2>(it->second)) >= 10) {
        cout << "Your grade is CEO.\n";
    }
    else {
        cout << "Your grade is Office Junior.\n";
    }
    cout << endl;
}

User leading() {
    std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> users;
    if (!loadUsers(users)) {
        cout << "Failed to load user data, exiting.\n";
        exit(1);
    }
    else {
        cout << "Loaded user data successfully.\n";
    }

    bool exitProgram = false;
    while (!exitProgram) {
        int option;
        cout << "1: Register\n2: Login\n0: Exit\nEnter option: ";
        cin >> option;

        switch (option) {
        case 1:
            registerUser(users);
            break;
        case 2:
            loginUser(users);
            break;
        case 0:
            exitProgram = true;
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    }

}

