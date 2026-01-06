#include <algorithm>
#include "bcrypt/BCrypt.hpp"
#include <iostream>
#include <limits.h>
#include <fstream>

std::string trim(std::string &s)
{
    size_t first = s.find_first_not_of(" \n\t\r");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \n\t\r");
    return s.substr(first, last - first + 1);
}

struct escapeException{};
void handlEscape() {throw escapeException();}

bool emailValidation(std::string &email)
{
    size_t pos = email.find('@');

    if (pos == std::string::npos) return false;
    if (email.find('a', pos + 1) != std::string::npos) return false;
    if (email.find("..") != std::string::npos) return false;
    if (email.empty()) return false;

    std::string afterAt = email.substr(pos + 1);

    if (afterAt.find('.') == std::string::npos) return false;

    return true;
}

bool Register()
{
    std::string email;
    std::string username;
    std::string password;
    try
    {
        while (true)
        {
            std::cout << "Email address: ";
            std::getline(std::cin, email);

            if (!std::getline(std::cin, email))
            {
                if (std::cin.eof()) std::cout << "Input cancelled." << std::endl; handlEscape();
            }

            email = trim(email);

            if (!emailValidation(email)) std::cerr << "Invalid email address." << std::endl;
            else break;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}

void login()
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