#include <algorithm>
#include "bcrypt/BCrypt.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct User
{
    std::string username;
    std::string email;
    std::string password;
};

std::string trim(std::string &s)
{
    size_t first = s.find_first_not_of(" \n\t\r");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \n\t\r");
    return s.substr(first, last - first + 1);
}

struct escapeException{};
void handlEscape() {throw escapeException();}

const std::string creds_file = "stored-creds.txt";

// Load all users from file to vector
std::vector<User> loadUsersFromFile()
{
    std::vector<User> users;
    std::ifstream file(creds_file);
    std::string line;
    while (std::getline(file, line))
    {
        size_t firstColon = line.find(':');
        size_t secondColon = line.find(':', firstColon + 1);
        if (firstColon != std::string::npos && secondColon != std::string::npos)
        {
            User user;
            user.username = line.substr(0, firstColon);
            user.email = line.substr(firstColon + 1, secondColon - firstColon - 1);
            user.password = line.substr(secondColon + 1); // Don't include the colon
            users.push_back(user);
        }
    }
    file.close();
    return users;
}

bool userExists(std::vector<User>& users, std::string& username)
{
    for (User& user : users)
    {
        if (user.username == username) return true;
    }
    return false;
}

bool emailExists(std::vector<User>& users, std::string& email)
{
    for (User& user : users)
    {
        if (user.email == email) return true;
    }
    return false;
}

bool saveUserToFile(User& user)
{
    std::ofstream file(creds_file, std::ios::app); // append to the last position with ::app
    file << user.username << ':' << user.email << ':' << user.password << std::endl;
    file.close();
    return true;
}

bool emailValidation(std::string &email)
{
    size_t pos = email.find('@');
    if (email.length() > 254) return false;
    // No @
    if (pos == std::string::npos) return false;
    // Local part > 64
    if (pos == 0 || pos > 64) {std::cerr << "Local part is too long." << std::endl; return false;}

    std::string localPart = email.substr(0, pos);
    for (unsigned char c : localPart)
        if (!isalnum(c) && c != '.' && c != '_' && c != '-' && c != '+') {std::cerr<< "Invalid charactesr in email address" << std::endl; return false;}
    if (!isalnum((unsigned char)(localPart.front())) || !isalnum((unsigned char)(localPart.back()))) return false;
    // no consecutive dots anywhere
    if (email.find("..") != std::string::npos) return false;
    if (email.empty()) return false;

    std::string domain = email.substr(pos + 1);
    // no repetition of @
    if (domain.find('@') != std::string::npos) return false;
    if (domain.empty() || domain.length() > 253) return false;
    // Contain at least 1 dot
    if (domain.find('.') == std::string::npos) return false;
    if (domain.front() == '.' || domain.back() == '.') return false;
    if (domain.front() == '-' || domain.back() == '-') return false;

    size_t lastDot = domain.find_last_of('.');
    std::string tld = domain.substr(lastDot + 1);
    if (tld.length() < 2) return false;
    for (unsigned char ch : tld)
        if (!isalpha(ch)) return false;
    return true;
}

bool userValidation(std::string &user)
{   
    std::string cleanedUser = trim(user);
    if (cleanedUser.empty() || cleanedUser.length() > 50 || cleanedUser.length() < 3) return false;
    // Ensure at least 1 letter
    bool letter = false;
    for (unsigned char ch : cleanedUser)
    {
        if (isalpha(ch)) letter = true; break;
    }
    // Character validation
    for (unsigned char c : cleanedUser)
        if (!isalnum(c) && c != '-' && c!= '_') return false;
    if (!isalnum(cleanedUser[0])) return false;
    return true;
}

bool Register(std::vector<User>& users)
{
    std::string email;
    std::string username;
    std::string password;
    try
    {
        while (true)
        {
            std::cout << "Email address (enter 'e' or 'c' to exit): ";
            if (!std::getline(std::cin, email))
            {
                if (std::cin.eof()) {std::cout << "Input cancelled." << std::endl; handlEscape();}
            }
            email = trim(email);
            if (email == "e" || email == "c") {handlEscape();}
            if (!emailValidation(email)) 
            {
                std::cerr << "Invalid email address." << std::endl;
                continue;
            }
            if (emailExists(users, email))
            {
                std::cerr << "Email already exists. Please login." << std::endl;
                return false;
            }
            break;
        }

        while (true)
        {
            std::cout << "Username (enter 'e' or 'c' to quit): ";
            if (!std::getline(std::cin, username))
            {
                if (std::cin.eof()) {std::cout << "Input cancelled" << std::endl; handlEscape();}
            }
            username = trim(username);
            if (username == "e" || username == "c") {handlEscape();}
            if (!userValidation(username))
            {
                std::cerr << "Invalid username. Must be between 3 and 50 characters, can only use hyphens, underscores, letters and numbers" << std::endl;
                continue;
            }
            if (userExists(users, username))
            {
                std::cerr << "username already taken." << std::endl;
                continue;
            }
            break;
        }

        while (true)
        {

        }
    }
    catch (const std::exception& e)
    {
        std::cout << "\nRegistration cancelled" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

bool login(std::vector<User>& users)
{

}

void menu()
{
    std::cout << "=================================Authentication Program=================================" << std::endl;
    std::cout << "\n1. Register\n2. Login\n3. Quit" << std::endl;
}

int main()
{

    return 0;
}