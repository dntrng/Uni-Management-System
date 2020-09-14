#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Teacher
{
private:
	int check_course;
	std::vector<std::vector<std::string> > user_course;
	std::string ID, PWD;
	void split(std::string &s, char c, std::vector<std::string> &v);
	void readCSV(std::ifstream &input, std::vector<std::vector<std::string> > &v);
	void writeCSV(std::fstream &input, std::vector<std::vector<std::string> > &v);

	void change_pwd(void);
	void open_course(void);
	void summarize_course(string code);
	void modify_course(string code);
public:
	Teacher(std::string MSGV, std::string PSS);
	void display();
	void action(std::string cmd);
};

void Teacher::split(std::string &s, char c, std::vector<std::string> &v) 
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

void Teacher::readCSV(std::ifstream &input, std::vector<std::vector<std::string> > &v) 
{
	while (!input.eof())
	{
		std::string person;
		std::vector<std::string> person_data;
		getline(input, person);
		split(person, ',', person_data);
		v.push_back(person_data);
	}
	input.close();
}

void Teacher::writeCSV(std::fstream &output, std::vector<std::vector<std::string> > &v) 
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[0].size(); j++)
		{
			if (j < v[0].size() - 1)
				output << v[i][j] << ",";
			else
				output << v[i][j];
		}
		if (i != v.size() - 1)
			output << std::endl;
	}
	output.close();
}

Teacher::Teacher(std::string MSGV, std::string PSS) : ID(MSGV), PWD(PSS)
{
	check_course = 0;
	std::vector<std::vector<std::string> > course;
	std::ifstream course_in(".\\data\\course.csv");
	readCSV(course_in, course);
	for (int i = 0; i < course.size(); i++) {
		if (course[i][1] == MSGV)
		{
			user_course.push_back(course[i]);
			check_course++;
		}
	}
	course.clear();
}

void Teacher::display()
{
	system("cls");
	std::cout << "\n--------------------- TEACHER: " << ID << " ---------------------\n";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "1. Change password [cp]";

	std::cout << std::left << std::setw(30) << "2. Open course [oc]";

	std::cout << std::left << std::setw(40) << "3. Summarize course [sc] [Course code]";

	std::cout << std::endl;

	std::cout << std::left << std::setw(40) << "4. Modify course [mc] [Course code]";

	std::cout << std::left << std::setw(20) << "5. Exit [q]";

	std::cout << std::endl;

	std::cout << "Choose your option : ";
}

void Teacher::action(std::string cmd) 
{	
	bool valid = false;
	vector<string> check_cmd;
	if (cmd.find("sc") != -1) {

		if (cmd[0] != 's' || cmd[1] != 'c') {
			system("cls");
			string hold;
			cout << "Your input format is incorrect. Please hit Enter and try again. ";
			getline(cin, hold);
		}
		else {
			for (int i = 2; i < cmd.size(); i++) {
				if ((cmd[i] != 's' && cmd[i] != 'c' && cmd[i] != ' ' && cmd[i - 1] == ' ') || ((cmd[i] == 's' || cmd[i] == 'c') && cmd[i - 1] == ' ')) {
					valid = true;
					break;
				}
			}

			if (valid == true) {
				split(cmd, ' ', check_cmd);
				summarize_course(check_cmd[1]);
			}
			else {
				system("cls");
				string hold;
				cout << "Your input format is incorrect. Please hit Enter and try again. ";
				getline(cin, hold);
			}
		}
	}
	else if (cmd.find("mc") != -1) {

		if (cmd[0] != 'm' || cmd[1] != 'c') {
			system("cls");
			string hold;
			cout << "Your input format is incorrect. Please hit Enter and try again. ";
			getline(cin, hold);
		}
		else {
			for (int i = 2; i < cmd.size(); i++) {
				if ((cmd[i] != 'm' && cmd[i] != 'c' && cmd[i] != ' ' && cmd[i - 1] == ' ') || ((cmd[i] == 'm' || cmd[i] == 'c') && cmd[i - 1] == ' ')) {
					valid = true;
					break;
				}
			}

			if (valid == true) {
				split(cmd, ' ', check_cmd);
				modify_course(check_cmd[1]);
			}
			else {
				system("cls");
				string hold;
				cout << "Your input format is incorrect. Please hit Enter and try again. ";
				getline(cin, hold);
			}
		}
	}
	if (cmd == "q")
	{
		system("cls");
		string ans;
		cout << "Are you sure that you want to end the program? (y/n) ";
		getline(cin, ans);
		if (ans == "Y" || ans == "y") {
			exit(0);
		}
	}
	else if (cmd == "cp")
	{
		system("cls");
		change_pwd();
		system("pause");
	}
	else if (cmd == "oc")
	{
		system("cls");
		open_course();
		system("pause");
	}
}

void Teacher::change_pwd(void) 
{
	std::string new_pass, check;
	std::vector<std::vector<std::string> >  all_data;
	std::cout << std::endl << "==============================CHANGE PASSWORD==============================" << std::endl << std::endl;
	std::cout << "Please enter your new password:       ";
	getline(std::cin, new_pass);
	std::cout << "Please enter again your new password: ";
	getline(std::cin, check);
	if (check == new_pass) {
		std::ifstream infile(".\\data\\user.csv");
		readCSV(infile, all_data);

		for (int i = 0; i < all_data.size(); i++) {
		
			if (all_data[i][0] == ID)
			{
				all_data[i][1] = new_pass;
				break;
			}
		}
		std::fstream outfile(".\\data\\user.csv");
		writeCSV(outfile, all_data);
		all_data.clear();
		std::cout << "\n=======================PASSWORD CHANGED SUCCESSFULLY !======================\n" << std::endl;
	}
	else {
		std::cout << endl << endl;
		std::cout << "\n=====================ERROR: WRONG CONFIRM PASSWORD !!!======================\n";
	}

}

void Teacher::open_course(void)
{
	if (check_course < 5)
	{
		std::cout << "\n================================OPEN COURSE===============================\n" << std::endl;
		std::cout << "Please input information of the course ( COURSE_ID | COURSE_NAME | SLOT ):" << std::endl;
		std::string info;
		std::vector<std::string> new_course;

		getline(std::cin, info);
		new_course.push_back(info);
		new_course.push_back(ID);
		getline(std::cin, info);
		new_course.push_back(info);
		new_course.push_back("0");
		getline(std::cin, info);
		new_course.push_back(info);

		std::vector<std::vector<std::string> > all_data;
		std::ifstream infile(".\\data\\course.csv");
		readCSV(infile, all_data);
		int k = 0;
		for (int i = 0; i < all_data.size(); i++)
		{
			if (all_data[i][1] == ID)
			{
				if (all_data[i][0] == new_course[0])
				{
					std::cout << "\n===================THE ID OF COURSE HAS ALREADY EXISTED !!!================\n";
					getchar();
					k = 1;
					break;
				}
			}
		}
		if (k == 0) {
			for (int i = 0; i < all_data.size(); i++) {
				if (all_data[i][1] == ID)
				{
					all_data.insert(all_data.begin() + i, new_course);
					break;
				}
				else if (i == all_data.size() - 1) {
					all_data.push_back(new_course);
					break;
				}
			}

			std::fstream outfile(".\\data\\course.csv", std::fstream::out);
			writeCSV(outfile, all_data);

			std::cout << "\n=======================OPEN COURSE " << new_course[0] << " SUCCESSFULLY=========================\n" << std::endl;
			all_data.clear();
			new_course.clear();
		}
	}
				
	else
		std::cout << "=============================CANNOT OPEN MORE COURSE(S)===============================" << std::endl;
}


void Teacher::summarize_course(string code) 
{
	while (true) 
	{
		system("cls");
		string ans_quit, ans_continue;
		float student_grade;
		int passed_num = 0, failed_num = 0, ungraded_num = 0, total_student_num = 0;
		string line_grade, line_student, line_passed, line_failed, line_ungraded;
		string course_name, student_name;
		bool found = false;
		vector<string> grade_data, student_ID_Name;
		vector< vector<string> > passed_list, failed_list, ungraded_list;
		fstream grade;
		fstream student;
		stringstream ss;

		//THIS while() LOOP CHECKS IF THE TEACHER HAS THE COURSE WITH THE CODE THAT HE/SHE ENTERED
		//IF THE TEACHER HAS THAT COURSE, THE COURSE CODE WILL BE STORED IN VARIABLE code
		//IF THE TEACHER DOES NOT HAVE THAT COURSE, A WARNING WILL BE SHOWED AND THE TEACHER WILL BE ASKED TO ENTER THE COURSE CODE AGAIN
		while (true)
		{
			for (int i = 0; i < user_course.size(); i++)
			{
				if (user_course[i][0] == code)
				{
					found = true;
					course_name = user_course[i][2];
					break;
				}
			}
			if (found == false)
			{
				cout << "---------------------------------------------------WARNING----------------------------------------------------" << endl;
				cout << "The course code you entered is not among the codes of your current courses. Please re-enter a valid course code.\n";
				cout << "If you want to return to the function menu, please input 'q'.\n";
				getline(cin, code);
				if (code == "q") {
					break;
				}
				system("cls");
				continue;
			}
			else
				break;
		}

		if (code == "q") {
			break;
		}

		//CHANGE THE PATHS TO OPEN THE grade.csv AND student.csv FILES
		cout << "---------------------" << code << " - " << course_name << "---------------------\n\n";
		grade.open(".\\data\\grade.csv", ios::in);
		student.open(".\\data\\student.csv", ios::in);

		//THIS while() LOOP PRINTS THE ID, NAME AND GRADE OF STUDENTS OF THE SAME COURSE, OF THE SAME TEACHER
		cout << "Student's ID" << setw(3) << right << "|" << setw(20) << right << "Full Name" << setw(14) << right << "|" << setw(10) << right << "Grade" << setw(7) << right << "|" << endl;
		cout << "------------------------------------------------------------------\n";
		while (!grade.eof())
		{
			student_name.clear();
			grade_data.clear();
			getline(grade, line_grade);

			if (line_grade.find(code) != -1 && line_grade.find(ID) != -1)
			{

				total_student_num++;

				while (!student.eof())
				{

					getline(student, line_student);
					split(line_grade, ',', grade_data);

					if (line_student.find(grade_data[1]) != -1)
					{
						student_name = line_student.substr(line_student.find(',') + 1, line_student.find(',', line_student.find(',') + 1) - (line_student.find(',') + 1));
						break;
					}
					else
						continue;
				}

				if (grade_data[3] == "-1")
				{
					cout << setw(10) << right << grade_data[1] << setw(5) << right << "|" << setw(25) << right << student_name << setw(9) << right << "|" << setw(13) << right << "Not graded" << setw(4) << right << "|" << endl;
				}
				else
				{
					cout << setw(10) << right << grade_data[1] << setw(5) << right << "|" << setw(25) << right << student_name << setw(9) << right << "|" << setw(10) << right << grade_data[3] << setw(7) << right << "|" << endl;
				}
			}
		}

		student.clear();
		grade.clear();
		student.seekg(0, student.beg);
		grade.seekg(0, grade.beg);
		passed_list.clear();
		failed_list.clear();
		ungraded_list.clear();

		while (!grade.eof())
		{
			ss.clear();
			student_name.clear();
			grade_data.clear();
			student_ID_Name.clear();

			getline(grade, line_passed);

			if (line_passed.find(code) != -1 && line_passed.find(ID) != -1)
			{
				while (!student.eof())
				{

					getline(student, line_student);
					split(line_passed, ',', grade_data);

					if (line_student.find(grade_data[1]) != -1)
					{
						student_name = line_student.substr(line_student.find(',') + 1, line_student.find(',', line_student.find(',') + 1) - (line_student.find(',') + 1));
						break;
					}
					else
						continue;
				}

				if (grade_data[3] != "-1")
				{
					ss << grade_data[3];
					ss >> student_grade;
				}
				else
				{
					student_ID_Name.push_back(grade_data[1]);
					student_ID_Name.push_back(student_name);
					ungraded_list.push_back(student_ID_Name);
					ungraded_num++;
					continue;
				}

				if (student_grade >= 5)
				{
					student_ID_Name.push_back(grade_data[1]);
					student_ID_Name.push_back(student_name);
					passed_list.push_back(student_ID_Name);
					passed_num++;
				}
				else
				{
					student_ID_Name.push_back(grade_data[1]);
					student_ID_Name.push_back(student_name);
					failed_list.push_back(student_ID_Name);
					failed_num++;
				}
			}
		}

		cout << "\n\n-----------LIST OF STUDENTS WHO PASSED-----------\n";
		cout << "Student's ID" << setw(3) << right << "|" << setw(20) << right << "Full Name" << setw(14) << right << "|" << endl;
		cout << "-------------------------------------------------\n";
		if (!passed_list.empty())
		{
			for (int i = 0; i < passed_list.size(); i++)
			{
				cout << setw(10) << right << passed_list[i][0] << setw(5) << right << "|" << setw(25) << right << passed_list[i][1] << setw(9) << right << "|" << endl;
			}
		}
		else
			cout << setw(25) << right << "NONE";

		cout << "\n\n-----------LIST OF STUDENTS WHO FAILED-----------\n";
		cout << "Student's ID" << setw(3) << right << "|" << setw(20) << right << "Full Name" << setw(14) << right << "|" << endl;
		cout << "-------------------------------------------------\n";
		if (!failed_list.empty())
		{
			for (int i = 0; i < failed_list.size(); i++)
			{
				cout << setw(10) << right << failed_list[i][0] << setw(5) << right << "|" << setw(25) << right << failed_list[i][1] << setw(9) << right << "|" << endl;
			}
		}
		else
			cout << setw(25) << right << "NONE";

		cout << "\n\n-----LIST OF STUDENTS WHO ARE NOT YET GRADED-----\n";
		cout << "Student's ID" << setw(3) << right << "|" << setw(20) << right << "Full Name" << setw(14) << right << "|" << endl;
		cout << "-------------------------------------------------\n";
		if (!ungraded_list.empty())
		{
			for (int i = 0; i < ungraded_list.size(); i++)
			{
				cout << setw(10) << right << ungraded_list[i][0] << setw(5) << right << "|" << setw(25) << right << ungraded_list[i][1] << setw(9) << right << "|" << endl;
			}
		}
		else
			cout << setw(25) << right << "NONE";

		cout << "\n\n---------------STATISTICS---------------\n";
		cout << "PASSED:     " << passed_num << " student(s) ==> " << setprecision(2) << fixed << (float(passed_num) / total_student_num) * 100 << " %\n";
		cout << "FAILED:     " << failed_num << " student(s) ==> " << setprecision(2) << fixed << (float(failed_num) / total_student_num) * 100 << " %\n";
		cout << "NOT GRADED: " << ungraded_num << " student(s) ==> " << setprecision(2) << fixed << (float(ungraded_num) / total_student_num) * 100 << " %\n";

		cout << "\n\nWhen you want to quit, please hit Enter.\n";
		getline(cin, ans_quit);
		student.close();
		grade.close();
		system("cls");
		

		cout << "Would you like to continue to view the summary of a different course? (y/n) ";
		getline(cin, ans_continue);
		if (ans_continue == "Y" || ans_continue == "y")
		{
			system("cls");
			cout << "Please enter the course code. ";
			getline(cin, code);
			continue;
		}
		else 
			break;
	}
}

void Teacher::modify_course(string code) 
{
	while (true) 
	{
		system("cls");
		string ans;
		string line_grade, line_student, line_grade2, line_check_ID;
		string course_name, student_name, student_id, new_grade;
		bool found = false, valid;
		vector<string> grade_data, change_grade, check_ID;
		vector< vector<string> > grade_rewrite;
		fstream grade;
		fstream student;

		//THIS while() LOOP CHECKS IF THE TEACHER HAS THE COURSE WITH THE CODE THAT HE/SHE ENTERED
		//IF THE TEACHER HAS THAT COURSE, THE COURSE CODE WILL BE STORED IN VARIABLE code
		//IF THE TEACHER DOES NOT HAVE THAT COURSE, A WARNING WILL BE SHOWED AND THE TEACHER WILL BE ASKED TO ENTER THE COURSE CODE AGAIN
		while (true)
		{
			for (int i = 0; i < user_course.size(); i++)
			{
				if (user_course[i][0] == code)
				{
					found = true;
					course_name = user_course[i][2];
					break;
				}
			}
			if (found == false)
			{
				cout << "---------------------------------------------------WARNING----------------------------------------------------" << endl;
				cout << "The course code you entered is not among the codes of your current courses. Please re-enter a valid course code.\n";
				cout << "If you want to return to the function menu, please input 'q'.\n";
				getline(cin, code);
				if (code == "q") {
					break;
				}
				system("cls");
				continue;
			}
			else
				break;
		}

		if (code == "q") {
			break;
		}

		while (true)
		{
			system("cls");
			valid = false;
			cout << "---------------------" << code << " - " << course_name << "---------------------\n\n";
			grade.open(".\\data\\grade.csv", ios::in);
			student.open(".\\data\\student.csv", ios::in);

			//THIS while() LOOP PRINTS THE ID, NAME AND GRADE OF STUDENTS OF THE SAME COURSE, OF THE SAME TEACHER
			cout << "Student's ID" << setw(3) << right << "|" << setw(20) << right << "Full Name" << setw(14) << right << "|" << setw(10) << right << "Grade" << setw(7) << right << "|" << endl;
			cout << "------------------------------------------------------------------\n";
			while (!grade.eof())
			{
				student_name.clear();
				grade_data.clear();
				getline(grade, line_grade);

				if (line_grade.find(code) != -1 && line_grade.find(ID) != -1)
				{
					while (!student.eof())
					{

						getline(student, line_student);
						split(line_grade, ',', grade_data);

						if (line_student.find(grade_data[1]) != -1)
						{
							student_name = line_student.substr(line_student.find(',') + 1, line_student.find(',', line_student.find(',') + 1) - (line_student.find(',') + 1));
							break;
						}
						else
							continue;
					}

					if (grade_data[3] == "-1")
					{
						cout << setw(10) << right << grade_data[1] << setw(5) << right << "|" << setw(25) << right << student_name << setw(9) << right << "|" << setw(13) << right << "Not graded" << setw(4) << right << "|" << endl;
					}
					else
					{
						cout << setw(10) << right << grade_data[1] << setw(5) << right << "|" << setw(25) << right << student_name << setw(9) << right << "|" << setw(10) << right << grade_data[3] << setw(7) << right << "|" << endl;
					}
				}
			}

			student.close();

			cout << "\n\nPlease choose the student whose grade you want to modify by his/her Student's ID.\nIf you want to change the student's grade status to 'Not graded', please input '-1'\nIf you want to quit the current session, please input 'q'\n\n";
			getline(cin, student_id);

			//THIS while() LOOP CHECKS IF THE TEACHER ENTERS A VALID STUDENT ID
			//IF THE INPUT IS INVALID, A WARNING WILL BE SHOWED AND THE TEACHER WILL BE ASKED TO ENTER THE STUDENT ID AGAIN
			while (true)
			{
				grade.clear();
				grade.seekg(0, grade.beg);
				while (getline(grade, line_check_ID))
				{
					check_ID.clear();
					split(line_check_ID, ',', check_ID);
					//THIS if STATEMENT CHECKS IF THE STUDENT ID ENTERED BY THE TEACHER IS VALID OR NOT
					//IF THE STUDENT ID IS VALID, valid BECOMES true; OTHERWISE, valid STAYS false
					if (check_ID[0] == code && check_ID[1] == student_id && check_ID[2] == ID)
					{
						valid = true;
						break;
					}
					//THIS CONDITION IS FOR WHEN THE TEACHER ENTERS 'q' TO QUIT
					else if (student_id == "q")
					{
						valid = true;
						break;
					}
					else
						continue;
				}
				//IF valid IS STILL false, THIS WARNING WILL BE SHOWED
				//OTHERWISE, IF valid IS true, WE BREAK OUT OF THE while() LOOP
				if (valid == false)
				{
					cout << "---------------------------------------------------WARNING----------------------------------------------------" << endl;
					cout << "The student's ID you entered is INVALID. Please re-enter a valid student's ID.\n";
					getline(cin, student_id);
				}
				else
					break;
			}

			//IF THE TEACHER ENTERS 'q', THE CONDITION IS SATIFIED AND WE BREAK OUT OF THE CURRENT while() LOOP
			//THEN THE TEACHER WILL BE ASKED IF HE/SHE WANTS TO MODIFY ANOTHER COURSE (SCROLL DOWN TO SEE)
			//IF THIS CONDITION IS WRONG, THE PROGRAM CONTINUES
			if (student_id == "q" && valid == true)
			{
				break;
			}

			cout << "\n\nStudent " << student_id << " chosen. Please enter new grade: ";
			getline(cin, new_grade);

			//THIS while() LOOP SCANS THE grade.csv FILE FOR THE STUDENT THAT THE TEACHER HAS CHOSEN
			grade.clear();
			grade.seekg(0, grade.beg);
			grade_rewrite.clear();
			while (!grade.eof())
			{
				change_grade.clear();
				getline(grade, line_grade2);
				if (line_grade2.find(code) != -1 && line_grade2.find(student_id) != -1 && line_grade2.find(ID) != -1)
				{
					split(line_grade2, ',', change_grade);
					change_grade[3] = new_grade;
					grade_rewrite.push_back(change_grade);
				}
				else
				{
					split(line_grade2, ',', change_grade);
					grade_rewrite.push_back(change_grade);
				}
			}

			grade.close();

			grade.open(".\\data\\grade.csv", ios::out | ios::trunc);
			writeCSV(grade, grade_rewrite);
		}

		system("cls");
		cout << "Would you like to continue to modify the grades of a different course? (y/n) ";
		getline(cin, ans);
		if (ans == "Y" || ans == "y")
		{
			system("cls");
			cout << "Please enter the course code. ";
			getline(cin, code);
			continue;
		}
		else
		{
			break;
		}
	}
}