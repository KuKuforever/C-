//Kan Xue
#include "Student.h"
#include "Date.h"
#include <string>
#include <iostream>
#include <cstdlib>

using std::string;
using namespace std;

Student::Student(string lName, string fName, int cred, double gpa, const Date& dob, const Date& matricDate, int id) :
	lastName(lName), firstName(fName), credit(cred), gpa(gpa), dob(dob), matricDate(matricDate), idNumber(id) {

	if (credit < 0 || gpa < 0.0) {
		cout << "invalid entry" << endl;
		exit(1);
	}

	setStanding(cred);
	
}

Student::Student() {
	lastName = " ";
	firstName = " ";
	standing = "lowerFreshman";
	credit = 0;
	gpa = 0.0;
}

void Student::output() const {
	cout << "name: " << firstName << " " << lastName << endl;
	cout << "standing: " << standing << endl;
	cout << "credits earned: " << credit << endl;
	cout << "grade point average: " << gpa << endl;
	dob.output();
	matricDate.output();
}

void Student::input() {
	cout << "Please enter your first name: " << endl;
	cin >> firstName;
	cout << "Please enter your last name: " << endl;
	cin >> lastName;
	cout << "Please enter the total credits you earned: " << endl;
	cin >> credit;

	if (credit < 0) {
		cout << "invalid entry" << endl;
		exit(1);
	}

	setStanding(credit);

	cout << "Please enter your gpa: " << endl;
	cin >> gpa;

	if (gpa < 0.0) {
		cout << "invalid entry" << endl;
		exit(1);
	}

	cout << "Please enter your date of birth(mm/dd/yyyy): " << endl;
	cin >> dob;
	cout << "Please enter the date you started the school(mm/dd/yyyy): " << endl;
	cin >> matricDate;

}

const string Student::getLastName() const {
	return lastName;
}
const string Student::getFirstName() const {
	return firstName;
}
const string Student::getStanding() const {
	return standing;
}
const int Student::getCredit() const {
	return credit;
}
const double Student::getGPA() const {
	return gpa;
}
const Date& Student::getDOB() const {
	return dob;
}
const Date& Student::getMatricDate() const {
	return matricDate;
}

void Student::setLastName(string lName) {
	lastName = lName;
}

void Student::setFirstName(string fName) {
	firstName = fName;
}

void Student::setCredit(int cred) {
	credit = cred;
	if (credit < 0) {
		cout << "invalid entry" << endl;
		exit(1);
	}
	setStanding(cred);
}

void Student::setIDNumber(int id) {
	 idNumber = id;
}

void Student::setGPA(double gpa) {
	gpa = gpa;
}
void Student::setDOB(Date& dob) {
	dob = dob;
}
void Student::setMatricDate( Date& matricDate) {
	 matricDate = matricDate;
}

void Student::setStanding(int credit) {

	if (credit >= 0 && credit < 16) {
		standing = "lowerFreshMan";
	}
	else if (credit > 15 && credit < 31) {
		standing = "upperFreshman";
	}
	else if (credit > 30 && credit < 46) {
		standing = "lowerSophomore";
	}
	else if (credit > 45 && credit < 61) {
		standing = "upperSophomore";
	}
	else if (credit > 60 && credit < 76) {
		standing = "lowerJunior";
	}
	else if (credit > 75 && credit < 91) {
		standing = "upperJunior";
	}
	else if (credit > 90 && credit < 106) {
		standing = "lowerSenior";
	}
	else {
		standing = "upperSenior";
	}
}

const int Student::getIdNumber() const{
	return idNumber;
}

bool Student::operator == (const Student& a) {
bool result = false;
	if (firstName.compare(a.getFirstName()) == 0 && lastName.compare(a.getLastName()) == 0 && (idNumber == a.getIdNumber())) {
		result = true;
	}
	return result;
}
bool  Student::operator != (const Student& a) {
	return !(*this == a);
}
bool  Student::operator > (const Student& a) {
bool result = false;
	if (*this != a) {
		if (isGreater(lastName, a.getLastName()) || (isEqual(lastName, a.getLastName()) && isGreater(firstName, a.getFirstName()))
			|| (isEqual(lastName, a.getLastName()) && isEqual(firstName, a.getFirstName()) && idNumber > a.getIdNumber())) {
			result = true;
		}
	}
	return result;
}

bool  Student::operator < (const Student& a) {
	return (!(*this > a) && (*this != a));
}

bool  Student::operator <= (const Student& a) {
	return ((*this < a) || (*this == a));
}

bool  Student::operator >= (const Student& a) {
	return ((*this > a) || (*this == a));
}
std::istream&  operator >> (std::istream& in, Student& a) {
	cout << "Please enter your first name: " << endl;
	in >> a.firstName;
	cout << "Please enter your last name: " << endl;
	in >> a.lastName;
	cout << "Please enter the total credits you earned: " << endl;
	in >> a.credit;

	if (a.credit < 0) {
		cout << "invalid entry" << endl;
		exit(1);
	}
	a.setStanding(a.credit);

	cout << "Please enter your gpa: " << endl;
	in >> a.gpa;

	if (a.gpa < 0.0) {
		cout << "invalid entry" << endl;
		exit(1);
	}

	cout << "Please enter your date of birth: " << endl;
	in >> a.dob;
	cout << "Please enter the date you started the school: " << endl;
	in >> a.matricDate;
	cout << "Please enter your student ID: " << endl;
	in >> a.idNumber;

	return in;
}
std::ostream& operator << (std::ostream& out, const Student& a) {

	out << "name: " << a.getFirstName() << " " << a.getLastName() << endl;
	out << "standing: " << a.getStanding() << endl;
	out << "ID number: " << a.getIdNumber() << endl;
	out << "credits earned: " << a.getCredit() << endl;
	out << "grade point average: " << a.getGPA() << endl;
	out << "Birth ";
	a.getDOB().output();
	out << "Matriculation ";
	a.getMatricDate().output();

	return out;
}

bool Student::isGreater(const string& name1, const string& name2) const {
bool result = false;
	int length = name1.length();
	if (name1.length() > name2.length()) {
		length = name2.length();
	}
	for (int i = 0; i < length; i++) {
		if (name1.at(i) == name2.at(i)) {
			continue;
		}
		else if (name1.at(i) > name2.at(i)) {
			result = true;
			break;
		}
		else if (name1.at(i) < name2.at(i)) { 
			result = false;
			break;
		}
	}
	return result;
}

bool Student::isEqual(const string& name1, const string& name2) const {
bool result = true;
	if (name1.length() != name2.length()) {
		result = false;
	}else{
		for (int i = 0; i < name1.length(); i++) {
			if (name1.at(i) != name2.at(i)) {
				result = false;
			}
		}
	}
	return result;
}

