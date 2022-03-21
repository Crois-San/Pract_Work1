
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum Sex
{
	Male, Female
};
struct Student
{
    string fullName;
	Sex sex;
	int classNumber;
	int classListNumber;
	int grades[8];
};
void Menu();

void StudentInput()
{
	cout << "\n" << "Entering the student's info into the log.";
	Student s;
	cout << "\n" << "Student's full name:\t";
	cin >> s.fullName;
	cout << "Student's sex:\n\t 0 - Male\n\t 1 - Female\t";
	bool sexInput;
	cin >> sexInput;
	s.sex = static_cast<Sex>(sexInput);
	cout << "Student's class:\t";
	cin >> s.classNumber;
	cout << "Student's placement in the class:\t";
	cin >> s.classListNumber;
	cout << "Student's grades:\t\n";
	for (int i = 0; i < 8; i++)
	{
		cout << "grade #" << i+1 <<":\t";
		cin >> s.grades[i];
	}

	ofstream studentLog;
	studentLog.open("Student Log.txt", ios::app);
	if (studentLog.is_open())
	{
		studentLog << s.fullName<< "\n";
		studentLog << s.sex << "\n";
		studentLog << s.classNumber << "\n";
		studentLog << s.classListNumber << "\n";
		for (int i = 0; i < 8; i++)
		{
			studentLog << s.grades[i] << " ";
		}
		studentLog << "\n";
		studentLog.close();
		cout << "\n" << "This student is saved into the log.";
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	bool confirmation;
	cout << "\n" << "Enter the next student into the log? 1/0\t";
	cin >> confirmation;
	if (confirmation)
	{
		StudentInput();
	}
	else
	{
		cout << "\n" << "Returning to the menu...\n";
		Menu();
	}
}

int StudentCount()
{
	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		int temp = 0;
		string data;
		while (!studentLog.eof())
		{
			getline(studentLog, data);
			temp++;
		}
		studentLog.close();
		int n;
		n = temp / 5;
		return n;
	}
	else
	{
		cout << "\n" << "Error opening file.";
		return 0;
	}
}
 
void StudentOutput()
{
	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		cout << "\n" << "Showing the data of all students:";
		int count = StudentCount();
		Student* s = new Student[count];
		if (count > 0)
		{
			int temp = 0;
			for (int i = 0; i < count; i++)
			{
				studentLog >> s[i].fullName;
				studentLog >> temp;
				s[i].sex = static_cast<Sex>(temp);
				studentLog >> s[i].classNumber;
				studentLog >> s[i].classListNumber;
				for (int j = 0; j < 8; j++)
				{
					studentLog >> s[i].grades[j];
				}
			}

			for (int i = 0; i < count; i++)
			{
				cout << "\n\t" << "Full name:";
				cout << "\n\t" << s[i].fullName;
				cout << "\n\t" << "Sex:";
				switch (s[i].sex)
				{
				case 0:
					cout << "\n\t" << "Male";
					break;
				case 1:
					cout << "\n\t" << "Female";
					break;
				default:
					break;
				}
				cout << "\n\t" << "Class:";
				cout << "\n\t" << s[i].classNumber;
				cout << "\n\t" << "Placement:";
				cout << "\n\t" << s[i].classListNumber;
				cout << "\n\t" << "Grades:\n\t";
				for (int j = 0; j < 8; j++)
				{
					cout << s[i].grades[j] << " ";
				}
			}
			
		}
		else
		{
			cout << "\n\t" << "The log is empty.";
		}
		delete[] s;
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();
}

void StudentEdit()
{
	int studentNum = 0;
	int count = StudentCount();
	cout << "\n" << "Enter a number of a student's data you want to edit (The log start with 0):\t";
	cin >> studentNum;
	if (studentNum < count)
	{
		Student* s = new Student[count];

		fstream studentLog;
		studentLog.open("Student Log.txt", ios::in);
		if (studentLog.is_open())
		{
			bool temp;
			for(int i = 0; i < count; i++)
			{
				studentLog >> s[i].fullName;
				studentLog >> temp;
				s[i].sex = static_cast<Sex>(temp);
				studentLog >> s[i].classNumber;
				studentLog >> s[i].classListNumber;
				for (int j = 0; j < 8; j++)
				{
					studentLog >> s[i].grades[j];
				}
					
			}


		}
		else
		{
			cout << "\n" << "Error opening file.";
		}
		studentLog.close();

		cout << "\n" << "Student's full name:\t";
		cin >> s[studentNum].fullName;
		cout << "Student's sex:\n\t 0 - Male\n\t 1 - Female\t";
		bool sexInput;
		cin >> sexInput;
		s[studentNum].sex = static_cast<Sex>(sexInput);
		cout << "Student's class:\t";
		cin >> s[studentNum].classNumber;
		cout << "Student's placement in the class:\t";
		cin >> s[studentNum].classListNumber;
		cout << "Student's grades:\t\n";
		for (int i = 0; i < 8; i++)
		{
			cout << "grade #" << i + 1 << ":\t";
			cin >> s[studentNum].grades[i];
		}


		studentLog.open("Student Log.txt", ios::out);
		if (studentLog.is_open())
		{
			for (int i = 0; i < count; i++)
			{
				studentLog << s[i].fullName << "\n";
				studentLog << s[i].sex << "\n";
				studentLog << s[i].classNumber << "\n";
				studentLog << s[i].classListNumber << "\n";
				for (int j = 0; j < 8; j++)
				{
					studentLog << s[i].grades[j] << " ";
				}
				studentLog << "\n";
			}
			
			studentLog.close();
			cout << "\n" << "This student has been edited.";
		}
		else
		{
			cout << "\n" << "Error opening file.";
		}

		delete[] s;
	}
	else
	{
		cout << "The number is out of range. A student with this number doesn't exist";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();

}

void StudentSameClass()
{
	cout << "Students from which class you need?\t";
	int studentClass;
	cin >> studentClass;

	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		cout << "Showing the data of students in a " << studentClass << "class:";
		bool classFound = 0;
		int count = StudentCount();
		Student* s = new Student[count];
		bool temp;
		for (int i = 0; i < count; i++)
		{
			studentLog >> s[i].fullName;
			studentLog >> temp;
			s[i].sex = static_cast<Sex>(temp);
			studentLog >> s[i].classNumber;
			studentLog >> s[i].classListNumber;
			for (int j = 0; j < 8; j++)
			{
				studentLog >> s[i].grades[j];
			}
		}

		for (int i = 0; i < count; i++)
		{
			if (studentClass == s[i].classNumber)
			{
				classFound = 1;
				cout << "\n\t" << "Full name:";
				cout << "\n\t" << s[i].fullName;
				cout << "\n\t" << "Sex:";
				switch (s[i].sex)
				{
				case 0:
					cout << "\n\t" << "Male";
					break;
				case 1:
					cout << "\n\t" << "Female";
					break;
				default:
					break;
				}
				cout << "\n\t" << "Placement:";
				cout << "\n\t" << s[i].classListNumber;
				cout << "\n\t" << "Grades:\n\t";
				for (int j = 0; j < 8; j++)
				{
					cout << s[i].grades[j] << " ";
				}
			}
		}
		if(!classFound)
		{
			cout << "\n" << "Class hasn't been found.";
		}
		delete[] s;
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();
}

void StudentRating()
{
	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		cout << "\n" << "Showing the rating of students:";
		bool classFound = 0;
		int count = StudentCount();
		Student* s = new Student[count];
		bool temp;
		for (int i = 0; i < count; i++)
		{
			studentLog >> s[i].fullName;
			studentLog >> temp;
			s[i].sex = static_cast<Sex>(temp);
			studentLog >> s[i].classNumber;
			studentLog >> s[i].classListNumber;
			for (int j = 0; j < 8; j++)
			{
				studentLog >> s[i].grades[j];
			}
		}

		float *gradeAverages= new float[count]();
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				gradeAverages[i] += s[i].grades[j];
			}
			gradeAverages[i] = gradeAverages[i] / 8;
		}


		float temp1 = 0;
		string temp2 = "";
		for (int i = 0; i < count-1;i++)
		{
			for (int j = i+1; j < count;j++)
			{
				if (gradeAverages[i] < gradeAverages[j])
				{
					temp1 = gradeAverages[j];
					gradeAverages[j] = gradeAverages[i];
					gradeAverages[i] = temp1;

					temp2 = s[j].fullName;
					s[j].fullName = s[i].fullName;
					s[i].fullName = temp2;
				}
			}
		}

		for (int i = 0; i < count; i++)
		{
			cout << "\n" << i + 1 << ":";
			cout << s[i].fullName << "    " << gradeAverages[i];
		}

		delete[] gradeAverages;
		delete[] s;
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();
}

void StudentSexCount()
{
	
	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		cout << "\n" << "Showing the number of male and female students:";
		int M = 0, F = 0;
		int count = StudentCount();
		Student* s = new Student[count];
		bool temp;
		for (int i = 0; i < count; i++)
		{
			studentLog >> s[i].fullName;
			studentLog >> temp;
			s[i].sex = static_cast<Sex>(temp);
			studentLog >> s[i].classNumber;
			studentLog >> s[i].classListNumber;
			for (int j = 0; j < 8; j++)
			{
				studentLog >> s[i].grades[j];
			}
		}

		for (int i = 0; i < count; i++)
		{
			if (s[i].sex == Male)
			{
				M++;
			}
			else
			{
				F++;
			}
		}
		cout << "\n" << "Male students:\t" << M;
		cout << "\n" << "Female students:\t" << F;

		delete[] s;
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();
}

void StudentGrades()
{
	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		int count = StudentCount();
		Student* s = new Student[count];
		bool temp;
		for (int i = 0; i < count; i++)
		{
			studentLog >> s[i].fullName;
			studentLog >> temp;
			s[i].sex = static_cast<Sex>(temp);
			studentLog >> s[i].classNumber;
			studentLog >> s[i].classListNumber;
			for (int j = 0; j < 8; j++)
			{
				studentLog >> s[i].grades[j];
			}
		}

		bool* hasThrees = new bool[count]();
		bool* hasFours = new bool[count]();
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (s[i].grades[j] < 4)
				{
					hasThrees[i] = 1;
				}
				if (s[i].grades[j] < 5)
				{
					hasFours[i] = 1;
				}
			}
		}

		cout << "\n" << "Showing students without scholarship:";
		for (int i = 0; i < count; i++)
		{
			if (hasThrees[i])
			{
				cout << "\n\t" << "Full name:";
				cout << "\n\t" << s[i].fullName;
				cout << "\n\t" << "Sex:";
				switch (s[i].sex)
				{
				case 0:
					cout << "\n\t" << "Male";
					break;
				case 1:
					cout << "\n\t" << "Female";
					break;
				default:
					break;
				}
				cout << "\n\t" << "Class:";
				cout << "\n\t" << s[i].classNumber;
				cout << "\n\t" << "Placement:";
				cout << "\n\t" << s[i].classListNumber;
				cout << "\n\t" << "Grades:\n\t";
				for (int j = 0; j < 8; j++)
				{
					cout << s[i].grades[j] << " ";
				}
			}
		}

		cout << "\n" << "Showing students with grades of 4 and 5:";
		for (int i = 0; i < count; i++)
		{
			if (!hasThrees[i] && hasFours[i])
			{
				cout << "\n\t" << "Full name:";
				cout << "\n\t" << s[i].fullName;
				cout << "\n\t" << "Sex:";
				switch (s[i].sex)
				{
				case 0:
					cout << "\n\t" << "Male";
					break;
				case 1:
					cout << "\n\t" << "Female";
					break;
				default:
					break;
				}
				cout << "\n\t" << "Class:";
				cout << "\n\t" << s[i].classNumber;
				cout << "\n\t" << "Placement:";
				cout << "\n\t" << s[i].classListNumber;
				cout << "\n\t" << "Grades:\n\t";
				for (int j = 0; j < 8; j++)
				{
					cout << s[i].grades[j] << " ";
				}
			}
		}

		cout << "\n" << "Showing students with grades of 5 only:";
		for (int i = 0; i < count; i++)
		{
			if (!hasThrees[i] && !hasFours[i])
			{
				cout << "\n\t" << "Full name:";
				cout << "\n\t" << s[i].fullName;
				cout << "\n\t" << "Sex:";
				switch (s[i].sex)
				{
				case 0:
					cout << "\n\t" << "Male";
					break;
				case 1:
					cout << "\n\t" << "Female";
					break;
				default:
					break;
				}
				cout << "\n\t" << "Class:";
				cout << "\n\t" << s[i].classNumber;
				cout << "\n\t" << "Placement:";
				cout << "\n\t" << s[i].classListNumber;
				cout << "\n\t" << "Grades:\n\t";
				for (int j = 0; j < 8; j++)
				{
					cout << s[i].grades[j] << " ";
				}
			}
		}
		

		delete[] hasFours;
		delete[] hasThrees;
		delete[] s;
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();
}

void StudentPlacement()
{
	cout << "Students with which placement in a class you need?\t";
	int studentPlacement;
	cin >> studentPlacement;

	ifstream studentLog("Student Log.txt");
	if (studentLog.is_open())
	{
		cout << "Showing the data of students in a " << studentPlacement << "st/nd/th placement of a class:";
		bool classFound = 0;
		int count = StudentCount();
		Student* s = new Student[count];
		bool temp;
		for (int i = 0; i < count; i++)
		{
			studentLog >> s[i].fullName;
			studentLog >> temp;
			s[i].sex = static_cast<Sex>(temp);
			studentLog >> s[i].classNumber;
			studentLog >> s[i].classListNumber;
			for (int j = 0; j < 8; j++)
			{
				studentLog >> s[i].grades[j];
			}
		}

		for (int i = 0; i < count; i++)
		{
			if (studentPlacement == s[i].classListNumber)
			{
				classFound = 1;
				cout << "\n\t" << "Full name:";
				cout << "\n\t" << s[i].fullName;
				cout << "\n\t" << "Sex:";
				switch (s[i].sex)
				{
				case 0:
					cout << "\n\t" << "Male";
					break;
				case 1:
					cout << "\n\t" << "Female";
					break;
				default:
					break;
				}
				cout << "\n\t" << "Class:";
				cout << "\n\t" << s[i].classNumber;
				cout << "\n\t" << "Grades:\n\t";
				for (int j = 0; j < 8; j++)
				{
					cout << s[i].grades[j] << " ";
				}
			}
		}
		if (!classFound)
		{
			cout << "\n" << "This placement in a class hasn't been found.";
		}
		delete[] s;
	}
	else
	{
		cout << "\n" << "Error opening file.";
	}

	cout << "\n" << "Returning to the menu...\n";
	Menu();
}

void Menu()
{
	cout << "Welcome to the student log menu! Please choose your option";
	cout << "\n\t0 - Enter a student's info;";
	cout << "\n\t1 - Show info of all students;";
	cout << "\n\t2 - Edit a student's info;";
	cout << "\n\t3 - Show info of students in a same class;";
	cout << "\n\t4 - Show a rating of students;";
	cout << "\n\t5 - Show a number of male and female students;";
	cout << "\n\t6 - Show info about a students' grades;";
	cout << "\n\t7 - Show info of students with a same placement inside a class;";
	cout << "\n\t8 - Exit the program.\n\t";

	int choice = 0;
	cin >> choice;
	switch (choice)
	{
		case 0:
			StudentInput();
			break;
		case 1:
			StudentOutput();
			break;
		case 2:
			StudentEdit();
			break;
		case 3:
			StudentSameClass();
			break;
		case 4:
			StudentRating();
			break;
		case 5:
			StudentSexCount();
			break;
		case 6:
			StudentGrades();
			break;
		case 7:
			StudentPlacement();
			break;
		case 8:
			exit;
			break;
		default:
			cout << "\n" << "Nonexistant option";
			exit;
			break;
	}
}

int main()
{
	Menu();
	return 0;
}
