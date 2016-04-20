//Kan Xue
#include "Date.h"
#include "Roster.h"
#include "Student.h"
#include "RosterManagement.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

RosterManagement::RosterManagement() {
char input = 'z';
taken = 0;
size  = 10;
	rosterList = new Roster[size];
	readInData();
	cout << "welcome to the roster management page." << endl;
	cout << "enter A for Supervisor Mode," << endl
		 << "enter B for User Mode," << endl
		 << "enter C to exit." << endl;
	cin  >> input;
	while (input != 'C') {
		switch (input) {
		case 'A':
			if (authentication()) {
				supervisorMode();
			}
			else
				cout << "wrong user name or password." << endl;
			break;
		case 'B': 
			userMode();
			break;
		case 'C':
			exit(1);
		}
		cout << "enter A for Supervisor Mode," << endl
			<< "enter B for User Mode," << endl
			<< "enter C to exit." << endl;
		cin >> input;
	}
}

RosterManagement::RosterManagement(const RosterManagement & other) {
	size = other.getSize();
	taken = other.getTaken();
	for (int i = 0; i < size; i++) {
		rosterList[i] = other.rosterList[i];
	}
}

RosterManagement & RosterManagement::operator=(const RosterManagement & other) {
	if (rosterList != NULL) {
		delete [] rosterList;
		rosterList = NULL;
	}
	size = other.getSize();
	taken = other.getTaken();
	for (int i = 0; i < size; i++) {
		rosterList[i] = other.rosterList[i];
	}
	return *this;
}

RosterManagement::~RosterManagement() {
	if (rosterList != NULL) {
		delete[] rosterList;
		rosterList = NULL;
	}
}

const int RosterManagement::getSize() const {
	return size;
}

const int RosterManagement::getTaken() const {
	return taken;
}

void RosterManagement::supervisorMode() {
int courseNumber;
int supervisorMain = 0;
	while (supervisorMain != 6) {
		cout << "You are on the main menu of the supervisor mode." << endl
			 << "Enter 1 to create a new roster." << endl
			 << "Enter 2 to drop a Roster." << endl
			 << "Enter 3 to display roster info." << endl
			 << "Enter 4 to display all roster." << endl
			 << "Enter 5 to enter the sub menu." << endl
			 << "Enter 6 to exit the program." << endl;
		cin  >> supervisorMain;
		switch (supervisorMain) {
		case 1:
			createRoster();
			break;
		case 2:
			cout << "Please enter the course number that you want to drop: " << endl;
			cin  >> courseNumber;
			dropCourse(courseNumber);
			break;
		case 3:
			cout << "Please enter the course number for the course that you want to display: " << endl;
			cin  >> courseNumber;
			displayRoster(courseNumber);
			break;
		case 4:
			displayRosters();
			break;
		case 5:
			supervisorSub();
			break;
		case 6:
			break;
		}
	}
	endRoster();
}

void RosterManagement::supervisorSub() {
char input;
int courseNumber;
int index;
int studentIndex;
Student a;
string firstName;
string lastName;

	cout << "select your course by entering the course number." << endl;
	cin >> courseNumber;
	index = search(courseNumber);
	if (index != -1) {
		cout << "enter a to insert new student." << endl;
		cout << "enter b to remove a student." << endl;
		cout << "enter c to update a student info." << endl;
		cout << "enter d to display all students in this roster." << endl;
		cin >> input;
		switch (input) {
		case 'a':
			cin >> a;
			rosterList[index].addStudent(a);
			break;
		case 'b':
			cout << "enter the last name of the student: " << endl;
			cin >> lastName;
			cout << "enter the first name of the student: " << endl;
			cin >> firstName;
			rosterList[index].deleteStudent(firstName, lastName);
			break;
		case 'c':
			cout << "enter the last name of the student: " << endl;
			cin >> lastName;
			cout << "enter the first name of the student: " << endl;
			cin >> firstName;
			studentIndex = rosterList[index].searchStudent(firstName, lastName);
			if (studentIndex != -1) {
				rosterList[index].deleteStudent(firstName, lastName);
				Student a;
				cin >> a;
				rosterList[index].addStudent(a);			
			}
			else { cout << "student not found" << endl; }
			break;
		case 'd':
			rosterList[index].display();
			break;
		}
	}
	else {
		cout << "course does not exist" << endl;
		return;
	}
}

void RosterManagement::userMode() {
char input;
int courseNumber;
int index;
int studentIndex;
Student a;
string firstName;
string lastName;
	cout << "select your course by entering the course number." << endl;
	cin  >> courseNumber;
	index = search(courseNumber);
	if (index != -1) {
		cout << "enter a to insert new student." << endl;
		cout << "enter b to remove a student." << endl;
		cout << "enter c to update a student info." << endl;
		cin >> input;
		switch (input) {
		case 'a':
			cin >> a;
			rosterList[index].addStudent(a);
			break;
		case 'b':
			cout << "enter the last name of the student: " << endl;
			cin >> lastName;
			cout << "enter the first name of the student: " << endl;
			cin >> firstName;
			rosterList[index].deleteStudent(firstName, lastName);
			break;
		case 'c':
			cout << "enter the last name of the student: " << endl;
			cin >> lastName;
			cout << "enter the first name of the student: " << endl;
			cin >> firstName;
			studentIndex = rosterList[index].searchStudent(firstName, lastName);
			if (studentIndex != -1) {
				rosterList[index].deleteStudent(firstName, lastName);
				Student a;
				cin >> a;
				rosterList[index].addStudent(a);
			}
			else { cout << "student not found" << endl; }
			break;
		}
	}
	else { 
		cout << "course does not exist" << endl;
		return;
	}
	endRoster();
}

bool RosterManagement::authentication() {
ifstream in ("database.txt");
int wrong = 0;
string userName;
string password;
string inputUserName;
string inputPassword;
bool   result = false;

	if (in.is_open()) {
		getline(in, userName);
		getline(in, password);
		in.close();
	}
	else 
		cout << "failed to open file." << endl;

	cout << "enter your user name : " << endl;
	cin  >> inputUserName;
	cout << "enter your password : " << endl;
	cin  >> inputPassword;
	if (!(userName.compare(inputUserName)) && !(password.compare(inputPassword))) {
		result = true;
	}
	else {
		wrong++;
		if (wrong > 3) {
			cout << "Entered wrong username/password too many times." << endl;
			exit(0);
		}
	}
	return result;
}

void RosterManagement::grow() {
	Roster* temp = rosterList;
	size = size * 2 + 1;
	rosterList = new Roster[size];

	for (int i = 0; i < taken; i++) {
		rosterList[i] = temp[i];
	}
	delete[] temp;
}

void RosterManagement::addCourse() {
	if (taken >= size) {
		grow();
	}
	cin >> rosterList[taken];
	taken++;
}

void RosterManagement::addCourse(Roster & r){
	if (taken > size) {
		grow();
	}
	rosterList[taken] = r;
	taken++;
}

void RosterManagement::dropCourse(int cNumber){
int index = search(cNumber);
	if (index != -1) {
		for (int i = index; i < taken; i++) {
			rosterList[i] = rosterList[i + 1];
			taken--;
		}
	}
	else {
		cout << "Course does not exist." << endl;
	}
}

void RosterManagement::displayRoster(int courseNumber) const {
int index = search(courseNumber);
	if (index != -1) {
		cout << rosterList[index];
	}
	else
		cout << "course not found." << endl;
}

void RosterManagement::displayRosters() const {
	if (taken > 0) {
		for (int i = 0; i < taken; i++) {
			cout << rosterList[i] << endl;
		}
	}
	else { cout << "No rosters available" << endl; }
}

const int RosterManagement::search(int cNumber) const {
int index = -1;
	for (int i = 0; i < taken; i++) {
		if (cNumber == rosterList[i].getCourseCode())
			index = i;
	}
	return index;
}

void RosterManagement::displayStudents(int index) const{
	rosterList[index].display();
}

void RosterManagement::endRoster() const {
ofstream write("rosters.txt");
	for (int i = 0; i < taken; i++) {
		if (write.is_open()) {
			write << rosterList[i].getCourseName() << '|'
				<< rosterList[i].getCourseCode() << '|'
				<< rosterList[i].getCourseCredit() << '|'
				<< rosterList[i].getInstructor() << '\n';
			for (int j = 0; j < rosterList[i].getEnrolled(); j++) {
				write << rosterList[i].getStudentList()[j].getFirstName() << '|'
					<< rosterList[i].getStudentList()[j].getLastName() << '|'
					<< rosterList[i].getStudentList()[j].getIdNumber() << '|'
					<< rosterList[i].getStudentList()[j].getStanding() << '|'
					<< rosterList[i].getStudentList()[j].getCredit() << '|'
					<< rosterList[i].getStudentList()[j].getGPA() << '|'
					<< rosterList[i].getStudentList()[j].getDOB().getMonthNum() << '/'
					<< rosterList[i].getStudentList()[j].getDOB().getDay() << '/'
					<< rosterList[i].getStudentList()[j].getDOB().getYear() << '|'
					<< rosterList[i].getStudentList()[j].getDOB().getMonthNum() << '/'
					<< rosterList[i].getStudentList()[j].getDOB().getDay() << '/'
					<< rosterList[i].getStudentList()[j].getDOB().getYear() << '\n';
			}
		}
		write << "end_roster" << '|' << endl;
	}
	write.close();
}

void RosterManagement::readInData(){
int courseCode;
int id;
int numberCredits;
int credits;
double gpa;
int month, day, year;
ifstream readIn("rosters.txt");
string courseName;
string professor;
string firstName;
string lastName;
string standing;
string endofRoster;
stringstream toNumber;
stringstream ss;
Roster r;

	if (readIn.is_open()) {
		getline(readIn, endofRoster);
		while (!readIn.eof()){
			if (endofRoster.compare("end_roster|") != 0 && endofRoster.compare("") != 0) {
				ss << endofRoster;
				getline(ss, courseName, '|');
				r.setCourseName(courseName);
				getline(ss, endofRoster, '|');
				toNumber << endofRoster;
				toNumber >> courseCode;
				r.setCourseCode(courseCode);
				toNumber.clear();
				getline(ss, endofRoster, '|');
				toNumber << endofRoster;
				toNumber >> numberCredits;
				r.setCourseCredit(numberCredits);
				toNumber.clear();
				getline(ss, professor, '\n');
				r.setInstructor(professor);
				addCourse(r);
				getline(readIn, endofRoster);
			}

			while (endofRoster.compare("end_roster|") != 0 && endofRoster.compare("") != 0) {
					ss.clear();
					ss << endofRoster;
					getline(ss, firstName, '|');
					getline(ss, lastName, '|');
					getline(ss, endofRoster, '|');
					toNumber << endofRoster;
					toNumber >> id;
					toNumber.clear();
					getline(ss, standing, '|');
					getline(ss, endofRoster, '|');
					toNumber << endofRoster;
					toNumber >> credits;
					toNumber.clear();
					getline(ss, endofRoster, '|');
					toNumber << endofRoster;
					toNumber >> gpa;
					toNumber.clear();
					getline(ss, endofRoster, '/');
					toNumber << endofRoster;
					toNumber >> month;
					toNumber.clear();
					getline(ss, endofRoster, '/');
					toNumber << endofRoster;
					toNumber >> day;
					toNumber.clear();
					getline(ss, endofRoster, '|');
					toNumber << endofRoster;
					toNumber >> year;
					toNumber.clear();
					Date dob(month, day, year);
					getline(ss, endofRoster, '/');
					toNumber << endofRoster;
					toNumber >> month;
					toNumber.clear();
					getline(ss, endofRoster, '/');
					toNumber << endofRoster;
					toNumber >> day;
					toNumber.clear();
					getline(ss, endofRoster, '\n');
					toNumber << endofRoster;
					toNumber >> year;
					toNumber.clear();
					Date matricDate(month, day, year);
					Student s(lastName, firstName, credits, gpa, dob, matricDate, id);
					rosterList[taken-1].addStudent(s);
					getline(readIn, endofRoster);
			}
		}
		readIn.close();
	}
}

void RosterManagement::createRoster(){
	Roster r;
	cin >> r;
	addCourse(r);
}
