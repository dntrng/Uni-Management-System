#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

class Admin
{
  private:
  /*
    TẤT CẢ CÁC HÀM PHỤ-CON viết ở private
  */
    std::vector<std::vector<std::string> > search_result;       //Temporary result after search
    std::vector<std::vector<std::string> > data_out_teacher;    //For teacher csv file.
    std::vector<std::vector<std::string> > data_out_student;    //For student csv file.
    std::vector<std::vector<std::string> > data_out_user;       //For user csv file

    void split(std::string s, std::string c, std::vector<std::string> &v);
    void readCSV(std::fstream &input, std::vector<std::vector<std::string> > &v);
    void writeCSV(std::ofstream &input, std::vector<std::vector<std::string> > &data_in);
    
    void Add(int j);
    void Remove(int, std::string del);
    void ChangePwd();

    void Find(int type, std::string &input);
    std::string checkType(std::string &input);
    bool checkName(std::string full_name, std::string query);

  public:
    //Admin();
    void display();
    void action(std::string cmd);
};

void Admin::ChangePwd()
{
    std::vector<std::vector<std::string> > data_user;
    std::fstream user_file(".\\data\\user.csv", std::fstream::in);
    readCSV(user_file, data_user);
    std::string confirm, password;
    
    system("cls");
    std::cout << "Your new password: ";
    std::cin >> password;
    std::cout << "Confirm your password: ";
    std::cin >> confirm;
    if (password == confirm)
    {
        for (int i = 0; i < data_user.size(); i++)
        {
            if (data_user[i][0] == "admin")
            {
                data_user[i][1] = password;
                std::cout << "Change password successfully";

                std::ofstream write_user(".\\data\\user.csv", std::ofstream::out);
                writeCSV(write_user, data_user);
                break;
            }
        }
    }
    else std::cout << "Error: Wrong confirm password.";
    system("pause");
}

void Admin::writeCSV(std::ofstream &input, std::vector<std::vector<std::string> > &data_in)
{
    for(int i = 0; i < data_in.size();i++)
    {
        for(int j = 0; j < data_in[i].size(); j++)
        {
            input << data_in[i][j]; // Write all value in each line before end line.
            if (j != data_in[i].size() - 1) 
                input  << ",";
        }
        if (i != data_in.size() - 1) 
            input << std::endl;
    }
    input.close();
}

void Admin::Remove(int mod, std::string del)
{
    std::vector<std::string> query;
    split(del, " ", query);

    if (mod == 1) //Teacher
    {
        for (int count = 1; count < query.size(); count++)
            if (query[count] > "S")          //Delete by ID
            {
                data_out_teacher.clear();
                std::fstream teacher_data(".\\data\\teacher.csv", std::fstream::in); 
                readCSV(teacher_data, data_out_teacher);                             
                //Use readCSV function to read and split each data in order to push back to vector and store.   
                
                for (int i = 0; i < data_out_teacher.size(); i++)
                {
                    if (data_out_teacher[i][0] == query[count])
                    {
                        data_out_teacher.erase(data_out_teacher.begin() + i);
                        break;
                    }
                }
                std::ofstream write_teacher(".\\data\\teacher.csv"); //Open to rewrite
                writeCSV(write_teacher, data_out_teacher);           //Write into files

                //Delete in user.csv
                data_out_user.clear(); 
                std::fstream user_data(".\\data\\user.csv", std::fstream::in); 
                readCSV(user_data, data_out_user);       
                
                for (int i = 0; i < data_out_user.size(); i++)
                {
                    if (data_out_user[i][0] == query[count])
                    {
                        std::cout << "Delete " << data_out_user[i][0] << " successfully.\n" << std::endl;
                        data_out_user.erase(data_out_user.begin() + i);
                        break;
                    }
                }
                std::ofstream write_user(".\\data\\user.csv"); //Open to rewrite
                writeCSV(write_user, data_out_user);           //Write into files
            }
            // Delete by No. in find result
            else
            {
                int position = std::stoi(query[count]);
                std::string ID = search_result[position - 1][0];

                data_out_teacher.clear(); 
                std::fstream teacher_data(".\\data\\teacher.csv", std::fstream::in); // Read identity path (identity is const char* because the path to the file must be constant)
                readCSV(teacher_data, data_out_teacher);                             //Use readCSV function to read and split each data in order to push back to vector and store.
                
                for (int i = 0; i < data_out_teacher.size(); i++)
                {
                    if (data_out_teacher[i][0] == ID)
                    {
                        data_out_teacher.erase(data_out_teacher.begin() + i);
                        break;
                    }
                }
                std::ofstream write_teacher(".\\data\\teacher.csv", std::ofstream::out | std::ofstream::trunc); //Open to rewrite
                writeCSV(write_teacher, data_out_teacher);           //Write into files

                //Delete in user.csv 
                data_out_user.clear();
                std::fstream user_data(".\\data\\user.csv", std::fstream::in); // Read identity path (identity is const char* because the path to the file must be constant)
                readCSV(user_data, data_out_user);                             //Use readCSV function to read and split each data in order to push back to vector and store.
                
                for (int i = 0; i < data_out_user.size(); i++)
                {
                    if (data_out_user[i][0] == ID)
                    {
                        std::cout << "Delete " << data_out_user[i][0] << " successfully.\n" << std::endl; 
                        data_out_user.erase(data_out_user.begin() + i);
                        break;
                    }
                }
                std::ofstream write_user(".\\data\\user.csv", std::ofstream::out | std::ofstream::trunc); //Open to rewrite
                writeCSV(write_user, data_out_user);           //Write into files
            }
    }
    else    //Delete student
    {
        for (int count = 1; count < query.size(); count++)
            if (query[count] > "1000000")       //Delete by ID
            {
                data_out_student.clear();
                std::fstream student_data(".\\data\\student.csv", std::fstream::in); // Read identity path (identity is const char* because the path to the file must be constant)
                readCSV(student_data, data_out_student);                             //Use readCSV function to read and split each data in order to push back to vector and store.
                
                for (int i = 0; i < data_out_student.size(); i++)
                {
                    if (data_out_student[i][0] == query[count])
                    {
                        data_out_student.erase(data_out_student.begin() + i);
                        break;
                    }
                }
                std::ofstream write_student(".\\data\\student.csv", std::ofstream::out | std::ofstream::trunc); //Open to rewrite
                writeCSV(write_student, data_out_student);           //Write into files

                //Delete in user.csv
                data_out_user.clear();
                std::fstream user_data(".\\data\\user.csv", std::fstream::in); // Read identity path (identity is const char* because the path to the file must be constant)
                readCSV(user_data, data_out_user);                             //Use readCSV function to read and split each data in order to push back to vector and store.
                
                for (int i = 0; i < data_out_user.size(); i++)
                {
                    if (data_out_user[i][0] == query[count])
                    {
                        std::cout << "Delete " << data_out_user[i][0] << " successfully.\n" << std::endl; 
                        data_out_user.erase(data_out_user.begin() + i);
                        break;
                    }
                }
                std::ofstream write_user(".\\data\\user.csv", std::ofstream::out | std::ofstream::trunc); //Open to rewrite
                writeCSV(write_user, data_out_user);           //Write into files
            }
            else    //Delete by No. in search result
            {
                int position = std::stoi(query[count]);
                std::string ID = search_result[position - 1][0];

                data_out_student.clear();
                std::fstream student_data(".\\data\\student.csv", std::fstream::in); // Read identity path (identity is const char* because the path to the file must be constant)
                readCSV(student_data, data_out_student);                             //Use readCSV function to read and split each data in order to push back to vector and store.
                
                for (int i = 0; i < data_out_student.size(); i++)
                {
                    if (data_out_student[i][0] == ID)
                    {
                        data_out_student.erase(data_out_student.begin() + i);
                        break;
                    }
                }
                std::ofstream write_student(".\\data\\student.csv", std::ofstream::out | std::ofstream::trunc); //Open to rewrite
                writeCSV(write_student, data_out_student);           //Write into files

                //Delete in user.csv
                data_out_user.clear();
                std::fstream user_data(".\\data\\user.csv", std::fstream::in); // Read identity path (identity is const char* because the path to the file must be constant)
                readCSV(user_data, data_out_user);                             //Use readCSV function to read and split each data in order to push back to vector and store.
                
                for (int i = 0; i < data_out_user.size(); i++)
                {
                    if (data_out_user[i][0] == ID)
                    {
                        std::cout << "Delete " << data_out_user[i][0] << " successfully.\n" << std::endl; 
                        data_out_user.erase(data_out_user.begin() + i);
                        break;
                    }
                }
                std::ofstream write_user(".\\data\\user.csv", std::ofstream::out | std::ofstream::trunc); //Open to rewrite
                writeCSV(write_user, data_out_user);           //Write into files
            }
    }
}

void Admin::Add(int j)
{
    std::vector<std::vector<std::string> > user;
    std::vector<std::vector<std::string> > data;
    std::vector<std::string> add;
    std::string input;
    bool done = 0;
    bool exist = 0;
    std::fstream userfile(".\\data\\user.csv", std::fstream::in);
    readCSV(userfile, user);
    userfile.close();

    std::cout << "Enter ID: ";
    getline(std::cin, input);
    add.push_back(input);
    for (int i = 0; i < user.size(); i++)
    {
        if (user[i][0] == add[0])
        {
            std::cout << "The ID has already existed" << std::endl;
            exist = 1;
        }
    }
    if (!exist)
    {
        add.push_back(input);
        if (j == 1)
        {
            add.push_back("teacher");
            for (int i = 1; i < user.size(); i++)
                if (user[i][2] != user[i + 1][2])
                {
                    user.insert(user.begin() + i + 1, add);
                    break;
                }
        }
        else
        {
            add.push_back("student");
            user.push_back(add);
        }
        done = 1;

        std::ofstream writeuser(".\\data\\user.csv", std::fstream::out);
        writeCSV(writeuser, user);
        add.clear();
    }

    if ((done == 1) && (j == 1))
    {
        std::fstream infile(".\\data\\teacher.csv", std::fstream::in);
        readCSV(infile, data);
        std::cout << data.size() << std::endl;

        add.push_back(input);
        std::cout << "Enter full name: ";
        getline(std::cin, input);
        add.push_back(input);
        std::cout << "Enter birthday (yyyy-mm-dd): ";
        getline(std::cin, input);
        add.push_back(input);
        std::cout << "Enter phone number: ";
        getline(std::cin, input);
        input = "\"" + input + "\"";
        add.push_back(input);
        std::cout << "Enter address: ";
        getline(std::cin, input);
        input = "\"" + input + "\"";
        add.push_back(input);

        data.push_back(add);
        
        std::ofstream writes(".\\data\\teacher.csv");
        writeCSV(writes, data);
        std::cout << "User has been added successfully!" << std::endl;
    }
    if ((done == 1) && (j == 0))
    {
        std::fstream infile(".\\data\\student.csv", std::fstream::in);
        readCSV(infile, data);

        add.push_back(input);
        std::cout << "Enter full name: ";
        getline(std::cin, input);
        add.push_back(input);
        std::cout << "Enter birthday (yyyy-mm-dd): ";
        getline(std::cin, input);
        add.push_back(input);
        std::cout << "Enter address: ";
        getline(std::cin, input);
        input = "\"" + input + "\"";
        add.push_back(input);
        data.push_back(add);
        
        std::ofstream writes(".\\data\\student.csv");
        writeCSV(writes, data);
        std::cout << "User has been added successfully!" << std::endl;
    }
    system("pause");
}

std::string Admin::checkType(std::string &input)
{
    int i = input.find("\"");
    if (i != std::string::npos)
        return "address";
    else 
    {
        std::vector<std::string> query;
        split(input, " ", query);
        if (query[1] < "A")
            return "phone";
        else    
            return "name";
    }
}

bool Admin::checkName(std::string full_name, std::string query)
{
    int position = full_name.find(query);
    if (position == -1)
        return false;
    else if (position != 0)
    {
        if (position + query.length() == full_name.length()) //Correct last name
        {
            if (full_name[position - 1] == ' ') 
                return true;
            else
                return false;
        }
        else if (full_name[position + query.length()] == ' ')   //Correct mid name
        {
            if (full_name[position - 1] == ' ')
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else if (position == 0)     //Correct family name
    {
        if (full_name[position + query.length()] == ' ')
            return true;
        else 
            return false;
    }
}

void Admin::Find(int type, std::string &input)
{
    search_result.clear();  //Clear to ready 

    if (type == 0)  //student
    {
        system("cls");
        std::cout << "------------------------------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(5) << "No.";
        std::cout << std::left << std::setw(15) << "ID";
        std::cout << std::left << std::setw(30) << "Name";
        std::cout << std::left << std::setw(20) << "Birthday";
        std::cout << std::left << std::setw(30) << "Address" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------\n";

        std::string check = checkType(input);
        if (check == "name")        //Find by student's name
        {    
            std::vector<std::string> query;
            split(input, " ", query);
            
            std::fstream student_data(".\\data\\student.csv", std::fstream::in);
            data_out_student.clear();
            readCSV(student_data, data_out_student);
            
            for (int i = 0; i < data_out_student.size(); i++)
            {
                if (checkName(data_out_student[i][1], query[1]))
                {
                    search_result.push_back(data_out_student[i]);
                    std::cout << std::left << std::setw(5) << search_result.size();
                    std::cout << std::left << std::setw(15) << data_out_student[i][0];
                    std::cout << std::left << std::setw(30) << data_out_student[i][1];
                    std::cout << std::left << std::setw(20) << data_out_student[i][2];
                    std::cout << std::left << std::setw(30) << data_out_student[i][3];
                    std::cout << std::endl;
                }
            }
        }
        else if (check == "address")    //Find by student's address
        {
            std::fstream student_data(".\\data\\student.csv", std::fstream::in);
            data_out_student.clear();
            readCSV(student_data, data_out_student);
            
            std::vector<std::string> query;
            split(input, " \"", query);
            std::string address = query[1].substr(1, query[1].length() - 2);    //Only get string without "

            for (int i = 0; i < data_out_student.size(); i++)
                if (checkName(data_out_student[i][3], address))
                {
                    search_result.push_back(data_out_student[i]);
                    std::cout << std::left << std::setw(5) << search_result.size();
                    std::cout << std::left << std::setw(15) << data_out_student[i][0];
                    std::cout << std::left << std::setw(30) << data_out_student[i][1];
                    std::cout << std::left << std::setw(20) << data_out_student[i][2];
                    std::cout << std::left << std::setw(30) << data_out_student[i][3];
                    std::cout << std::endl;
                }
        }
        std::cout << "------------------------------------------------------------------------------------------------------\n";
    }
    else if (type == 1)     //Teacher
    {
        system("cls");
        std::cout << "------------------------------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(5) << "No.";
        std::cout << std::left << std::setw(15) << "ID";
        std::cout << std::left << std::setw(30) << "Name";
        std::cout << std::left << std::setw(15) << "Birthday";
        std::cout << std::left << std::setw(20) << "Phone";
        std::cout << std::left << std::setw(30) << "Address" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------\n";

        std::string check = checkType(input);
        if (check == "name")
        {
            std::vector<std::string> query;
            split(input, " ", query);
            
            std::fstream teacher_data(".\\data\\teacher.csv", std::fstream::in);
            data_out_teacher.clear();
            readCSV(teacher_data, data_out_teacher);
            
            for (int i = 0; i < data_out_teacher.size(); i++)
            {
                if (checkName(data_out_teacher[i][1], query[1]))
                {
                    search_result.push_back(data_out_teacher[i]);
                    std::cout << std::left << std::setw(5) << search_result.size();
                    std::cout << std::left << std::setw(15) << data_out_teacher[i][0];
                    std::cout << std::left << std::setw(30) << data_out_teacher[i][1];
                    std::cout << std::left << std::setw(15) << data_out_teacher[i][2];
                    std::cout << std::left << std::setw(20) << data_out_teacher[i][3];
                    std::cout << std::left << std::setw(30) << data_out_teacher[i][4];
                    std::cout << std::endl;
                }
            }
        }
        else if (check == "phone")
        {
            std::vector<std::string> query;
            split(input, " ", query);
            
            std::fstream teacher_data(".\\data\\teacher.csv", std::fstream::in);
            data_out_teacher.clear();
            readCSV(teacher_data, data_out_teacher);

            for (int i = 0; i < data_out_teacher.size(); i++)
            {
                if (data_out_teacher[i][3].find(query[1]) != std::string::npos)
                {
                    search_result.push_back(data_out_teacher[i]);
                    std::cout << std::left << std::setw(5) << search_result.size();
                    std::cout << std::left << std::setw(15) << data_out_teacher[i][0];
                    std::cout << std::left << std::setw(30) << data_out_teacher[i][1];
                    std::cout << std::left << std::setw(15) << data_out_teacher[i][2];
                    std::cout << std::left << std::setw(20) << data_out_teacher[i][3];
                    std::cout << std::left << std::setw(30) << data_out_teacher[i][4];
                    std::cout << std::endl;
                }
            }
        }
        else if (check == "address")
        {
            std::fstream teacher_data(".\\data\\teacher.csv", std::fstream::in);
            data_out_teacher.clear();
            readCSV(teacher_data, data_out_teacher);
            
            std::vector<std::string> query;
            split(input, " \"", query);
            std::string address = query[1].substr(1, query[1].length() - 2);    //Only get string without "

            for (int i = 0; i < data_out_teacher.size(); i++)
                if (checkName(data_out_teacher[i][4], address))
                {
                    search_result.push_back(data_out_teacher[i]);
                    std::cout << std::left << std::setw(5) << search_result.size();
                    std::cout << std::left << std::setw(15) << data_out_teacher[i][0];
                    std::cout << std::left << std::setw(30) << data_out_teacher[i][1];
                    std::cout << std::left << std::setw(15) << data_out_teacher[i][2];
                    std::cout << std::left << std::setw(20) << data_out_teacher[i][3];
                    std::cout << std::left << std::setw(30) << data_out_teacher[i][4];
                    std::cout << std::endl;
                }
        }
        std::cout << "------------------------------------------------------------------------------------------------------\n";
    }
}

void Admin::action(std::string cmd)
{
    std::vector<std::string> choose;
    split(cmd, " ", choose);

    //Add users
    if (choose[0] == "as") //Student
    {
        Add(0); //Add info of student into student and user csv files
    }
    else if (choose[0] == "at")
    {
        Add(1); //Add info of teacher into teacher and user csv files
    }
    else if (choose[0] == "rs")
    {
        Remove(0, cmd); //Remove info of student into student and user csv files
    }
    else if (choose[0] == "rt")
    {
        Remove(1, cmd); //Remove info of teacher into teacher and user csv files
    }
    else if (choose[0] == "p")
    {
        ChangePwd();
    }
    else if (choose[0] == "fs")
    {
        Find(0, cmd);
    }
    else if (choose[0] == "ft")
    {
        Find(1, cmd);
    }
    else if (choose[0] == "q")
    {
        exit(0);
    }
}

void Admin::display()
{
    std::cout << "--------------------- Admin ---------------------\n";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "1. Change password [p]";
    
    std::cout << std::left << std::setw(40) << "2. Find user [fs/ft] (Keyword)";

	std::cout << std::left << std::setw(30) << "3. Add user [as/at]" << std::endl;

	std::cout << std::left << std::setw(30) << "4. Remove user [rs/rt] ID";

	std::cout << std::left << std::setw(30) << "5. Exit [q]";

	std::cout << std::endl;

	std::cout << "Choose your option : ";
}

void Admin::split(std::string s, std::string c, std::vector<std::string> &v)
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

// 2D vector v nên được lưu tại private
void Admin::readCSV(std::fstream &input, std::vector<std::vector<std::string> > &v)
{
    while (!input.eof())
    {
        std::string person;
        std::vector<std::string> person_data;
        getline(input, person);
        split(person, ",", person_data);
        v.push_back(person_data);
    }
    input.close();
}