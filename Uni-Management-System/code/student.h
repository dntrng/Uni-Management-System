#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

class Student
{
  private:
  /*
    TẤT CẢ CÁC HÀM PHỤ-CON viết ở private
  */
    std::string ID, PWD;
	std::vector<std::vector<std::string> > grade;
	std::vector<std::vector<std::string> > registed_course;

    void split(std::string &s, char c, std::vector<std::string> &v);
	void readCSV(std::ifstream &input, std::vector<std::vector<std::string> > &v);
	void writeCSV(std::ofstream &output, std::vector<std::vector<std::string> > &v);

	void Change_password(void);
	void View_courses(void);
	std::string replace(std::string, std::string);
	void Join_course(void);
	std::string lower_string(std::string s);
	void Un_course(void);
	void Exit(void);
	void Help(void);

	void Search(std::string);
	bool checkName(std::string full_name, std::string query);
  public:
    // Truyền MSSV khi khởi tạo 1 object Student
    Student(std::string MSSV, std::string PWD);
    void display();
    void action(std::string cmd);
};

Student::Student(std::string MSSV, std::string PWD)
{
	std::vector<std::vector<std::string> > data;
	this -> ID = MSSV;
	this -> PWD = PWD;
	std::vector<std::string> temp;
	std::ifstream grade_in(".\\data\\grade.csv"); //Khởi tạo biến input user.csv
	readCSV(grade_in, data); //Đọc file và ghi thông tin vào mảng data[][]
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i][3] >= "0" && data[i][1] == ID)
		{
			temp = data[i];
			grade.push_back(temp);
		}
		else if (data[i][3] < "0" && data[i][1] == ID)
		{
			temp = data[i];
			registed_course.push_back(temp);
		}
	}
	data.clear();
}

void Student::display(void)
{
	std::cout << "--------------------- Student:" << ID << " ---------------------\n";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "1. Change password [p]";

	std::cout << std::left << std::setw(30) << "2. View my courses [c]";

	std::cout << std::left << std::setw(30) << "3. Search course [scn]";

	std::cout << std::left << std::setw(30) << "4. Join course [j]";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "5. Un-course [u]";

	std::cout << std::left << std::setw(30) << "6. Exit [q]";

	std::cout << std::left << std::setw(30) << "7. Help [h]";

	std::cout << "\n";

	std::cout << "Choose your option : ";
}

void Student::action(std::string cmd)
{
	std::vector<std::string> choose;
    split(cmd,' ', choose);


	if (cmd == "p")
	{
		Change_password();
	}
	else if (cmd == "c")
	{
		View_courses();
	}
	else if (cmd == "j")
	{
		Join_course();
	}
	else if (cmd == "u")
	{
		Un_course();
	}
	else if (cmd == "q")
	{
		Exit();
	}
	else if (cmd == "h")
	{
		Help();
	}
	else if (choose[0] == "scn")
	{
		Search(cmd);
	}
}

void Student::Change_password(void)
{
	std::vector<std::vector<std::string> > data;
	std::string new_password;	//Khởi tạo mảng password mới
	std::ifstream user_in(".\\data\\user.csv"); //Khởi tạo biến input user.csv
	readCSV(user_in, data); //Đọc file và ghi thông tin vào mảng data[][]
	std::cout << "Please input your new password : ";
	getline(std::cin, new_password); //Đọc password mới từ bàn phím
	for (int i = 0; i < data.size(); i++) //Chạy vòng lặp dò từ đầu đến cuối 
	{
		if (data[i][0] == ID) //Nếu thông tin trùng với ID 
		{
			data[i][1] = new_password; //Thay đổi password
		}
	}
	std::ofstream user_out(".\\data\\user.csv", std::ofstream::trunc); //Khởi tạo biến output user.csv
	writeCSV(user_out, data); //Ghi đè mảng data[][] và file user.csv
	data.clear(); //Làm trống mảng data[][]
	std::cout << "CHANGE PASSWORD SUCCESSFULLY !!\n";
	system("pause");
	exit(0);
}

void Student::View_courses(void)
{
	system("cls");
	std::cout << "-------------------------------------Courses during semester-------------------------------------------\n";

	std::cout << "------------------------------------------------------------------------------------------------------\n";

	std::cout << std::left << std::setw(10) << "INDEX";

	std::cout << std::left << std::setw(30) << "TEACHER";

	std::cout << std::left << std::setw(30) << "COURSE NAME";

	std::cout << std::left << std::setw(10) << "SCORE";

	std::cout << std::left << std::setw(30) << "PASS/FAIL";

	std::cout << "\n";

	std::cout << "------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < grade.size(); i++) //Chạy vòng lặp dò từ đầu đến cuối 
	{
			std::cout << std::left << std::setw(10) << (i+1); //Số thứ tự

			std::cout << std::left << std::setw(30) << replace(grade[i][2], "t") + "(" + grade[i][2] + ")"; //Tên giáo viên bộ môn (hàm replace xem ở dưới)

			std::cout << std::left << std::setw(30) << replace(grade[i][0], "c"); //Tên bộ môn (hàm replace xem ở dưới)

			std::cout << std::left << std::setw(10) << grade[i][3]; //Điểm trung bình

			if (grade[i][3] < "5") //Kiểm tra đậu hay rới môn
			{
				std::cout << std::left << std::setw(30) << "";
			}
			else
			{
				std::cout << std::left << std::setw(30) << "X";
			}


			std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "----------------------------------------Registed courses----------------------------------------------\n";

	std::cout << std::left << std::setw(10) << "INDEX";

	std::cout << std::left << std::setw(30) << "TEACHER";

	std::cout << std::left << std::setw(30) << "COURSE NAME";

	std::cout << std::left << std::setw(10) << "SCORE";

	std::cout << "\n";

	std::cout << "------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < registed_course.size(); i++) //Chạy vòng lặp dò từ đầu đến cuối 
	{
		std::cout << std::left << std::setw(10) << (i + 1); //Số thứ tự

		std::cout << std::left << std::setw(30) << replace(registed_course[i][2], "t") + "(" + registed_course[i][2] + ")"; //Tên giáo viên bộ môn (hàm replace xem ở dưới)

		std::cout << std::left << std::setw(30) << replace(registed_course[i][0], "c"); //Tên bộ môn (hàm replace xem ở dưới)

		std::cout << std::left << std::setw(10) << registed_course[i][3]; //Điểm trung bình

		std::cout << "\n";
	}
	std::cout << "------------------------------------------------------------------------------------------------------\n";
	std::cout << "\n";

}

void Student::Join_course(void)
{
	std::vector<std::vector<std::string> > data;
	std::string course_ID, teacher_ID;
	std::vector<std::string> temp;	//Khởi tạo vecto nháp để xử lý trong hàm
	std::ifstream course_in(".\\data\\course.csv"); //Khởi tạo biến input course.csv
	readCSV(course_in, data); //Đọc file và ghi thông tin vào mảng data[][]
	std::cout << "Input the course ID you want to join : "; //Nhập tên lớp học 
	getline(std::cin, course_ID);
	bool find = false;
	for (int i = 0; i < data.size(); i++)
	{
		if (course_ID == data[i][0]) //Nêu tìm thấy lớp học thì in ra màn hình
		{
			std::cout << "Course : " << data[i][2] << "\tTeacher : " << replace(data[i][1], "t") << "(" << data[i][1] << ")\t" << "Student : " << data[i][3] << "/" << data[i][4] << "\n";
			find = true;
		}
	}
	if (find == false)	//Nếu không tìm thấy
	{
		std::cout << "Can not find your course !!\n";
		return;
	}
	std::cout << "Input (teacher ID) you want to choose : "; //Nhập mã số gv
	getline(std::cin, teacher_ID);
	for (int i = 0; i < grade.size(); i++) //Kiểm tra trong grade nếu đã đăng ký rồi thì không cho đăng ký nữa
	{
		if (course_ID == grade[i][0] && teacher_ID == grade[i][2])
		{
			std::cout << "Your have already sign in this course !!\n";
			system("pause");
			system("cls");
			return;
		}
	}
	for (int i = 0; i < registed_course.size(); i++) //Kiểm tra trong registed_course nếu đã đăng ký rồi thì không cho đăng ký nữa
	{
		if (course_ID == registed_course[i][0] && teacher_ID == registed_course[i][2])
		{
			std::cout << "Your have already sign in this course !!\n";
			system("pause");
			system("cls");
			return;
		}
	}
	int count = 0; //Biếm đếm dùng để xác định vị trí thêm dùng cho hàm insert
	for (int i = 0; i < data.size(); i++)
	{
		if (course_ID == data[i][0] && teacher_ID == data[i][1])
			//Nếu trùng tên và cả mã số gv thì cộng 1 thêm số học sinh
		{
			count += std::stoi(data[i][3],NULL,10); //Biến đếm tất cả số học sinh ở các lớp trước đó và cả trong lớp đang chọn
			data[i][3] = std::to_string(std::stoi(data[i][3],NULL,10) + 1); //Công 1 cho số học sinh trong lớp đang đăng ký
			temp.push_back(data[i][0]); //Mã số lớp học
			temp.push_back(ID); //ID sinh viên
			temp.push_back(data[i][1]); //Mã số giáo viên
			temp.push_back("-1"); //Điểm khởi tạo
			temp.push_back("181"); //Học kỳ cho mặc định là 181
			break;
		}
		else
		{
			count += std::stoi(data[i][3],NULL,10); //Biến đếm tất cả số học sinh ở các lớp trước đó và cả trong lớp đang chọn
		}
		if (i == (data.size() - 1)) //Nếu không tìm thấy
		{
			std::cout << "Can not find your course or your teacher !!\n";
			return;
		}
	}
	std::ofstream course_out(".\\data\\course.csv", std::ofstream::out); //Khởi tạo biến output course.csv
	writeCSV(course_out, data); //Ghi đè data vào file
	data.clear(); //Làm trống mảng data[][]
	std::ifstream grade_in(".\\data\\grade.csv"); //Khởi tạo biến input grade.csv
	readCSV(grade_in,data); //Đọc file và ghi thông tin vào mảng data[][]
	data.insert(data.begin() + count, temp); //Chèn hàng mới tạo ở trên và data
	std::ofstream grade_out(".\\data\\grade.csv", std::ofstream::out); //Khởi tạo biến output grade.csv
	writeCSV(grade_out, data);//Ghi vào file
	data.clear(); //Làm trống mảng data[][]
	std::cout << "ASSIGN FOR THE COURSE SUCCESSFULLY !!\n";
	system("pause");
	system("cls");
	//exit(0);
}

void Student::Un_course(void)
{
	std::vector<std::vector<std::string> > data;
	std::string course_ID, teacher_ID;
	std::cout << "----------------------------------------Registed courses----------------------------------------------\n";

	std::cout << "------------------------------------------------------------------------------------------------------\n";

	std::cout << std::left << std::setw(10) << "INDEX";

	std::cout << std::left << std::setw(30) << "TEACHER";

	std::cout << std::left << std::setw(30) << "COURSE NAME";

	std::cout << std::left << std::setw(10) << "SCORE";

	std::cout << "\n";

	std::cout << "------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < registed_course.size(); i++) //Chạy vòng lặp dò từ đầu đến cuối 
	{
		std::cout << std::left << std::setw(10) << (i + 1); //Số thứ tự

		std::cout << std::left << std::setw(30) << replace(registed_course[i][2], "t") + "(" + registed_course[i][2] + ")"; //Tên giáo viên bộ môn (hàm replace xem ở dưới)

		std::cout << std::left << std::setw(30) << replace(registed_course[i][0], "c") + "(" + registed_course[i][0] + ")"; //Tên bộ môn (hàm replace xem ở dưới)

		std::cout << std::left << std::setw(10) << registed_course[i][3]; //Điểm trung bình

		std::cout << "\n";
	}
	std::cout << "------------------------------------------------------------------------------------------------------\n";
	std::cout << "------------------------------------------------------------------------------------------------------\n";
	std::cout << "\n";
	std::cout << "Input the course ID you want to leave : "; //Nhập tên lớp học 
	getline(std::cin, course_ID);
	std::cout << "Input (teacher ID) : "; //Nhập mã số gv
	getline(std::cin, teacher_ID);
	for (int i = 0; i < registed_course.size(); i++) //Kiểm tra nếu chưa đăng ký hoặc đang học thì ko cho un-course
	{
		if (course_ID == registed_course[i][0] && teacher_ID == registed_course[i][2])
			//Kiểm tra tên và số ID giáo viên vừa nhập
		{
			break;
		}
		if (i == registed_course.size() - 1)
		{
			std::cout << "Can not find this course !!\n";
			system("pause");
			system("cls");
			return;
		}
	}
	std::ifstream grade_in(".\\data\\grade.csv"); //Khởi tạo biến input grade.csv
	readCSV(grade_in, data); //Đọc file và ghi thông tin vào mảng data[][]
	for (int i = 0; i < data.size(); i++) //Dò trong data[][] và xóa dòng có chứa thông tin
	{
		if (course_ID == data[i][0] && teacher_ID == data[i][2] && ID == data[i][1])
		{
			data.erase(data.begin()+i);
			break;
		}
	}
	std::ofstream grade_out(".\\data\\grade.csv", std::ofstream::out); //Khởi tạo biến output grade.csv
	writeCSV(grade_out, data);//Ghi vào file
	data.clear();
	std::ifstream course_in(".\\data\\course.csv"); //Khởi tạo biến input course.csv
	readCSV(course_in, data); //Đọc file và ghi thông tin vào mảng data[][]
	for (int i = 0; i < data.size(); i++) //Dò trong data[][] giảm số học sinh
	{
		if (course_ID == data[i][0] && teacher_ID == data[i][1])
		{
			data[i][3] = std::to_string(std::stoi(data[i][3], NULL, 10) - 1);
			break;
		}
	}
	std::ofstream course_out(".\\data\\course.csv", std::ofstream::out); //Khởi tạo biến output course.csv
	writeCSV(course_out, data);//Ghi vào file
	data.clear();
	std::cout << "LEAVE THE COURSE SUCCESSFULLY !!\n";
	system("pause");
	system("cls");

}

void Student::Exit(void)
{
	exit(0);
}

void Student::Help(void)
{
	system("cls");

	std::cout << "--------------------------------------- Student:" << ID << " ---------------------------------------\n";

	std::cout << std::left << std::setw(30) << "* Change password";

	std::cout << std::left << std::setw(10) << "[p]";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "* View all courses";

	std::cout << std::left << std::setw(10) << "[c]";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "* Search course";

	std::cout << "\n";

	std::cout << (char)192 << (char)196 << (char)196;

	std::cout << std::left << std::setw(30) << " Search course by name";

	std::cout << std::left << std::setw(10) << "[scn]";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "* Join course";

	std::cout << std::left << std::setw(10) << "[j]";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "* Un-course";

	std::cout << std::left << std::setw(10) << "[u]";

	std::cout << "\n";

	std::cout << std::left << std::setw(30) << "* Exit";

	std::cout << std::left << std::setw(10) << "[q]";

	std::cout << "\n";

	system("pause");
	 
	system("cls");

}

void Student::Search(std::string name)
{
	std::vector<std::string> choose;
    split(name,' ', choose);
	system("cls");
	
	//Check correct format input
	if (choose.size() == 1)
	{
		std::cout << "Wrong format input. Please input again in form of [scn] NAME.\n" << std::endl;
		return;
	}

	std::vector<std::vector<std::string> > data_course;
	std::ifstream course(".\\data\\course.csv");
	readCSV(course, data_course);

	std::cout << "---------------------------------------------------------------------------------------------------------\n";
	std::cout << std::left << std::setw(10) << "ID";
	std::cout << std::left << std::setw(20) << "Teacher ID";
	std::cout << std::left << std::setw(30) << "Course name";
	std::cout << std::left << std::setw(10) << "Registed";
	std::cout << std::left << std::setw(10) << "Slot";
	std::cout << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------------------\n";	

	for (int i = 0; i < data_course.size(); i++)
		if (checkName(lower_string(data_course[i][2]), lower_string(choose[1])))
		{
			std::cout << std::left << std::setw(10) << data_course[i][0];
			std::cout << std::left << std::setw(20) << data_course[i][1];
			std::cout << std::left << std::setw(30) << data_course[i][2];
			std::cout << std::left << std::setw(10) << data_course[i][3];
			std::cout << std::left << std::setw(10) << data_course[i][4];
			std::cout << std::endl;
		}

	std::cout << "----------------------------------------------------------------------------------------------------------\n\n";
}

void Student::split(std::string &s, char c, std::vector<std::string> &v)
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
void Student::readCSV(std::ifstream &input, std::vector<std::vector<std::string> > &v) 
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

void Student::writeCSV(std::ofstream &output, std::vector<std::vector<std::string> > &v) 
{
		for (int i = 0; i < v.size(); i++)
		{
			if (i == v.size() - 1)
				for (int j = 0; j < v[i].size(); j++)
				{
					if (j == v[i].size() - 1)
					{
						output << v[i][j];
					}
					else
					{
						output << v[i][j] + ",";
					}
				}	
			else
				for (int j = 0; j < v[i].size(); j++)
				{
					if (j == v[i].size() - 1)
					{
						output << v[i][j] << std::endl;
					}
					else
					{
						output << v[i][j] + ",";
					}
				}
		}	
		output.close();
}

/*
Hàm replace dùng để thay id của teacher hoặc course bằng tên tương ứng của nó
VD: CC01 -> replace(CC01,"c") -> Mo hinh hoa
S0951 -> replace(S0951,"t") -> BUI QUOC TRUNG
trong đó "c" tương ứng với course
"t" tương ứng với teacher
*/
std::string Student::replace(std::string id, std::string op)
{
	//std::vector<std::vector<std::string> > temp;
	std::vector<std::string> v;
	if (op == "t") //Nếu option bằng "t" thì dò trong teacher.csv
	{
		std::ifstream teacher_in(".\\data\\teacher.csv"); //Khởi tạo biến input teacher.csv
		//readCSV(teacher_in, temp); //Đọc file và ghi thông tin vào mảng temp[][]
		while (!teacher_in.eof())
		{
			std::string line;
			getline(teacher_in,line);
			int position = line.find(id);
			if (position != std::string::npos)
			{
				split(line,',', v);
				return v[1];
			}
		}
		/*
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i][0] == id)
			{
				return temp[i][1]; //Dò trong mảng nếu trùng khớp id thì trả về tên ở cột 1
			}
		}
		*/
	}
	else if (op == "c") //Nếu option bằng "c" thì dò trong course.csv
	{
		std::ifstream course_in(".\\data\\course.csv"); //Khởi tạo biến input course.csv
		//readCSV(course_in, temp); //Đọc file và ghi thông tin vào mảng temp[][]
		while (!course_in.eof())
		{
			std::string line;
			getline(course_in, line);
			int position = line.find(id);
			if (position != std::string::npos)
			{
				split(line, ',', v);
				return v[2];
			}
		}
		/*
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i][0] == id)
			{
				return temp[i][2]; //Dò trong mảng nếu trùng khớp id thì trả về tên ở cột 2
			}
		}
		*/
	}
}

std::string Student::lower_string(std::string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

bool Student::checkName(std::string full_name, std::string query)
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