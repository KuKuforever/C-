//Kan Xue
#include "Roster.h"
#include "Student.h"
#include <string>
#include <iostream>
#include <cstdlib>

using std::string;
using namespace std;

void Roster::addStudent(const Student& a) {
	if (enrolled < size) {
		studentList[enrolled] = a;
		enrolled++;
	}
	else {
		grow();
		studentList[enrolled] = a;
		enrolled++;
	}
        sortStudent();
}


const int Roster::searchStudent(string fName, string lName) const{
int result = -1;
        if(enrolled > 0){
	        for(int i=0; i<enrolled; i++){
			if((fName.compare(studentList[i].getFirstName()) == 0) && (lName.compare(studentList[i].getLastName()) == 0))
				result = i;
	   }
        }
        return result;
}


void Roster::deleteStudent(string fName, string lName){
int position = searchStudent(fName, lName);
	if(position >= 0){
		for(int i=position; i<enrolled; i++){
			studentList[i] = studentList[i+1];
		}

	enrolled--;
	cout << "student" <<fName << " " << lName << "has been deleted."<<endl;
	}
	else{
		cout <<"This student does not exist." << endl;
	}
		
}

Roster::Roster() {
        size         =  10;
	enrolled     =  0;
	courseCode   =  0;
	courseCredit =  0;
	courseName   =  " ";
	instructor   =  " ";  
	studentList  =  new Student[size];
}

Roster::Roster(int cCode, int cCredit, string cName, string prof, int classSize){
   
	if((cCode < 0) || (cCredit < 0) || (classSize < 0)){
        	cout << "invalid entry." << endl;
        	exit(1);
   }
      
   enrolled     =   0;
   courseCode   =   cCode;
   courseCredit =   cCredit;
   courseName   =   cName;
   instructor   =   prof;
   size         =   classSize;
   studentList  =   new Student[size];
   
}

Roster::Roster(const Roster & r){
Student* temp = NULL;
	temp = studentList;
	size = r.getSize();
	studentList = new Student[size];
	
	for (int i = 0; i < size; i++) {
		studentList[i] = r.getStudentList()[i];
	}
	
	delete[] temp;
	enrolled = r.getEnrolled();
	courseCode = r.getCourseCode();
	courseCredit = r.getCourseCredit();
	courseName = r.getCourseName();
	instructor = r.getInstructor();

}
   
void Roster::setCourseCode(int cCode){
	if(cCode < 0){
        	cout << "invalid entry." << endl;
        	exit(1);
	}
      
   	courseCode = cCode;         
}
   
void Roster::setCourseCredit(int cCredit){
   	if(cCredit < 0){
      		cout << "invalid entry." << endl;
      		exit(1);
   	}
   	courseCredit = cCredit;
}
   
void Roster::setCourseName(string cName){
   	courseName = cName;
}
   
void Roster::setInstructor(string prof){
   	instructor = prof;
}

const int Roster::getSize()const {
	return size;
}

const Student * Roster::getStudentList() const{
	return studentList;
}

const int Roster::getEnrolled()const {
	return enrolled;
}
const int Roster::getCourseCode()const {
   	return courseCode;
}
const int Roster::getCourseCredit()const {
   	return courseCredit;
}
const string Roster::getCourseName()const {
   	return courseName;
}
const string Roster::getInstructor()const {
   	return instructor;
}

void Roster::display() const{
	cout << "course name: " << courseName << endl;
	cout << "course code: " << courseCode << endl;
	cout << "course credit: " << courseCredit << endl;
	cout << "instructor: " << instructor << endl;
	cout << "students enrolled: " << endl;
	
	for (int i = 0; i < enrolled; i++) {
		cout << studentList[i].getFirstName() << " " << studentList[i].getLastName() << endl;
	}
}

std::ostream& operator <<(std::ostream& out, Roster& r) {
	out << "course name: " << r.courseName << endl;
	out << "course code: " << r.courseCode << endl;
	out << "course credit: " << r.courseCredit << endl;
	out << "instructor: " << r.instructor << endl;
	out << "students enrolled: " << endl;
	for (int i = 0; i < r.enrolled; i++) {
		cout << r.studentList[i].getFirstName() << " " << r.studentList[i].getLastName() << endl;
	}
	return out;
}
std::istream& operator >>(std::istream& in, Roster& r) {
	cout << "Enter the course name: " << endl;
	in >> r.courseName;
	cout << "Enter the course code: " << endl;
	in >> r.courseCode;
	cout << "Enter the course credit: " << endl;
	in >> r.courseCredit;
	cout << "Enter instructor's name: " << endl;
	in >> r.instructor;
	
	return in;
}

void Roster::sortStudent() {
Student least;
	if (enrolled > 1) {
		for (int i = 0; i < enrolled-1; i++) {
			least = studentList[i];
			for (int j = i; j < enrolled; j++) {
				if (least > studentList[j]) {
					swap(studentList[i], studentList[j]);
					least = studentList[i];
				}
			}
			cout << endl;
		}
	}
}
void Roster::swap(Student& a, Student& b) {
Student temp =   a;
	a    =   b;
	b    =   temp;
}

void Roster::grow() {
Student* temp = NULL;

	temp = studentList;
	size = size * 2 + 1;
	studentList = new Student[size];

	for (int i = 0; i < enrolled; i++) {
		studentList[i] = temp[i];
	}
	delete[] temp;
}

Roster& Roster::operator = ( Roster& a) {
Student* temp = NULL;

	temp         =   studentList;
	size         =   a.getSize();
	studentList  =   new Student[size];
	
	for (int i = 0; i < size; i++) {
		studentList[i] = a[i];
	}
	delete[] temp;
	enrolled     =   a.getEnrolled();
	courseCode   =   a.getCourseCode();
	courseCredit =   a.getCourseCredit();
	courseName   =   a.getCourseName();
	instructor   =   a.getInstructor();

	return *this;
}

 const Student& Roster::operator[](int index)
{
	if (index < 0 || index > size) {
		cout << "Invalid entry" << endl;
		exit(1);
	}
	return studentList[index];
}

Roster::~Roster() {
	if (studentList != NULL) {
		delete[] studentList;
		studentList = NULL;
	}
}
