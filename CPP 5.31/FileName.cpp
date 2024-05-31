#include <iostream>
#include <math.h>
#include <string>

#define pi 3.1516

using namespace std;
//{
//	//
//	//void power_factor(float a) {
//	//	if (a > 1 || a < -1) {
//	//		throw(a);
//	//	}
//	//	else {
//	//		cout << "voltage(v) is lagging from current(I) by" << acos(a) * 180 / pi << " degree\n";
//	//
//	//	}
//	//}
//	//int main() {
//	//	float a;
//	//	try {
//	//		cout << "enter power factor ";
//	//		cin >> a;
//	//		power_factor(a);
//	//	}
//	//	catch (float b) {
//	//		cout << "caught an exception \n"<<b;
//	//	}
//	//	return 0;
//	//}
//}


#include <iostream>
#include <string>
#include <stdexcept>

// 自定义异常类
class InvalidUsernameException : public std::invalid_argument {
public:
    InvalidUsernameException(const std::string& msg) : std::invalid_argument(msg) {}
};

class InvalidPasswordException : public std::invalid_argument {
public:
    InvalidPasswordException(const std::string& msg) : std::invalid_argument(msg) {}
};

class UserExistsException : public std::invalid_argument {
public:
    UserExistsException(const std::string& msg) : std::invalid_argument(msg) {}
};

class UserNotFoundException : public std::runtime_error {
public:
    UserNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidLoginException : public std::runtime_error {
public:
    InvalidLoginException(const std::string& msg) : std::runtime_error(msg) {}
};

// 用户管理类
class UserManager {
public:
    std::map<std::string, std::string> users;

    void registerUser(const std::string& username, const std::string& password) {
        if (username.length() < 3) {
            throw InvalidUsernameException("Username must be at least 3 characters long.");
        }
        if (password.length() < 5) {
            throw InvalidPasswordException("Password must be at least 5 characters long.");
        }
        if (users.find(username) != users.end()) {
            throw UserExistsException(f"The username '{username}' already exists.");
        }
        users[username] = password;
    }

    std::string loginUser(const std::string& username, const std::string& password) {
        auto it = users.find(username);
        if (it == users.end()) {
            throw UserNotFoundException(f"The username '{username}' does not exist.");
        }
        if (it->second != password) {
            throw InvalidLoginException("Invalid username or password.");
        }
        return f"Welcome, {username}!";
    }
};

int main() {
    UserManager userManager;
    std::string username, password;

    // 注册
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    try {
        userManager.registerUser(username, password);
        std::cout << "Registration successful." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Registration failed: " << e.what() << std::endl;
    }

    // 登录
    std::cout << "Enter username for login: ";
    std::cin >> username;
    std::cout << "Enter password for login: ";
    std::cin >> password;
    try {
        std::cout << userManager.loginUser(username, password) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Login failed: " << e.what() << std::endl;
    }

    return 0;
}
