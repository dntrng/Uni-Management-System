#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "admin.h"
#include "student.h"
#include "teacher.h"

void split(std::string &s, char c, std::vector<std::string> &v)
{
    int i = 0;
    int j = s.find(c);

    // TH chỉ có 1 data column trong file csv
    if (j == std::string::npos)
        v.push_back(s.substr(i, s.length() - i));

    while (j != std::string::npos)
    {
        // TH Data ở column quê quán đặc biệt "..., ..."
        if ((s[i] == '\"') && (s[j + 1] == ' '))
        {
            j = s.find("\"", j + 1);
            v.push_back(s.substr(i, j - i + 1));
        }
        else
            v.push_back(s.substr(i, j - i));

        i = ++j;
        j = s.find(c, j);

        // Check overload input
        while (i == j)
        {
            ++i;
            j = s.find(c, i);
        }

        if (j == std::string::npos)
            if (s.length() != i)
                v.push_back(s.substr(i, s.length() - i));
    }
}

int main()
{
    std::string usr, pwd, person;

    std::string state;
    do
    {
        system("cls");
        state.clear();
        std::vector<std::string> info;
        usr.clear();
        pwd.clear();

        std::cout << "Username: ";
        getline(std::cin, usr);
        std::cout << "Password: ";
        getline(std::cin, pwd);

        std::fstream user(".\\data\\user.csv", std::fstream::in);

        while(!user.eof())
        {
            getline(user, person);
            info.clear();
            split(person, ',', info);

            if ((usr == info[0]) && (pwd == info[1]))
                state = info[2];
        }

        user.close();
    } while (state == "");
    
    system("cls");
    
    if (state == "admin")
    {
        Admin ad;
        while (true)
        {
            ad.display();
            std::string command;
            getline(std::cin, command);
            ad.action(command);
        }
    }
    else if (state == "teacher")
    {
        while (true)
        {
            Teacher teacher(usr, pwd);
            teacher.display();
            std::string command;
            getline(std::cin, command);
            teacher.action(command);
        }
    }
    else
    {
        while(true)
        {
            Student student(usr, pwd);
            student.display();
            std::string command;
            getline(std::cin, command);
            student.action(command);
        }
    }
}