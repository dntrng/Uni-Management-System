# Assignment for OISP Programming Fundamentals 2018

- Exe file: [Link](https://github.com/dntrng/Uni-Management-System/tree/master/Uni-Management-System)
- Code directory: [Link](https://github.com/dntrng/Uni-Management-System/tree/master/Uni-Management-System/code)

***|EDUCATION SOFTWARE FOR MANAGING COURSE AND GRADE IN UNIVERSITY|***

This is a software designed specially for students and teachers dealing with courses
and grades more precisely and in a convenient way.

**|Prerequisties|**

Before compiling and running source code of this program, please take following steps carefully
in order to run the software properly:

1/ For end-users who only need a software to control their schedule:
- In this case, our team had prepared a ".exe file" in order to make it easier for 
users, which means that when users want to run the program, they just need to run
the .exe file in the folder we provide.
- However, for some computers, they will encounter system errors about missing DLL
files and to avoid that, we had already contain many back up DLL files for these
situations. And if those files cannot help you, please enter the link below to 
download your missing files:

*(http://www.dll-files.com)*

2/ For coder who are using Code Blocks and MinGW :
- First, put all the software's files, folder data into one folder and open the main.cpp with Code Blocks.
- Second, because Code Blocks uses GNU GCC compiler, we have to add compiler flags "g++ follow 
the C++11" for this software to access standard libraries from C++. And the Way
to add g++ to your compiler is that after opening the source code, please go to: 

*(Settings -> Compiler-> compiler setting -> tick on "Have g++ follow the C++11 ISO C++ langauage standard [-std=C++11]")*

Notice: if you cannot find the path to config the compiler, you can check the instruction folder 
we sent with program itself and follow the pictures in there steps by steps to set up the compiler
crrectly.

- After compiling, the .exe file will be created in the same folder that contains main.cpp and other .h files. They can either
use .exe file to run the software or just run it directly in Code Blocks (recommend run .exe file).

3/ For coder who are using Visual Studio:
- First, you have to build a C++ project with your visual studio.
- Second, extract the software's .cpp file into source files folder and .h files into header folder.
- Third, press F5 to compile the program.

Notice: if you have error like "missing ucrtbased.dll", you can fix it temporary by copying it in: *(C:\Windows\System32\ucrtbased.dll)*
and put in your project folder. However, if you install Visual Studio correctly, the error above 
will not happen and that's the reason we recommend to reinstall your visual studio if you encounter 
this system error.

- Afteer compiling, a console window will open for you to use the software through the Visual Studio. However, I recommend
build the .exe file by clicking Build on the header tab or pressing "Ctrl + Shift + B". The .exe file will be in Debug folder
which is inside project's folder and because of that, remember to copy the data folder of the software into Debug folder to
run the .exe file properly.

**|Suitable IDEs that have been tested|**

When developing this program, our team had test it on Visual Studio 2017, Code Blocks and it run perfectly
without any error. Because of that, if your editor cannot compile it, please try to install the editor above.

**|Running the test|**

When you open the software successfully, you will have to login into the system. Different accounts will have
different function depends on roles (student, teacher, admin). Therefore, after loginning, in each line of
command there will be a short instruction to execute the program so please follow it precisely.

If you are still confuse about some command, please open the manual(report) to look for more details.

***|THANK YOU FOR READING|***

