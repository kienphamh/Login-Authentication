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
    if (email.length() > 254) return false;
    // No @
    if (pos == std::string::npos) return false;
    // Local part > 64
    if (pos == 0 || pos > 64) std::cerr << "Local part is too long." << std::endl; return false;
    // no consecutive dots anywhere
    if (email.find("..") != std::string::npos) return false;
    if (email.empty()) return false;

    std::string domain = email.substr(pos + 1);

    if (domain.find('.') == std::string::npos) return false;
    // no repetition of @
    if (domain.find('@') != std::string::npos) return false;
    if (domain.empty() || domain.length() > 253) return false;
    // Contain at least 1 dot
    if (domain.find('.') == std::string::npos) return false;
    if (domain.front() == '.' || domain.back() == '.') return false;
    if (domain.front() == '-' || domain.front() == '-') return false;

    size_t lastDot = domain.find_last_not_of('.');
    std::string tld = domain.substr(lastDot + 1);
    if (tld.length() < 2) return false;
    return true;
}

bool userValidation(std::string &user)
{
    
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

        while (true)
        {

        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error with the email address" << e.what() << '\n';
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