//Kan Xue
#ifndef ROSTERMANAGEMENT_H
#define ROSTERMANAGEMENT_H

#include "Date.h"
#include "Roster.h"
#include "Student.h"


class RosterManagement {
public:
	RosterManagement();
	RosterManagement(const RosterManagement& other);
	RosterManagement& operator =(const RosterManagement& other);
	~RosterManagement();
	const int getSize()const;
	const int getTaken()const;

private:
	int size;
	int taken;
	Roster* rosterList;
	void supervisorMode();
	void supervisorSub();
	void userMode();
	bool authentication();
	void grow();
	void addCourse();
	void addCourse(Roster& r);
	void dropCourse(int cNumber);
	void displayRoster(int cNumber)const;
	void displayRosters()const;
	const int search(int cNumber)const;
	void displayStudents(int courseCode) const;
	void endRoster() const;
	void readInData();
	void createRoster();
	
};

#endif