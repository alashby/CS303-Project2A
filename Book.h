#pragma once
#include <list>
#include "omp.h"
#include "Date.h"
#include "Employee.h"
#include "Pqueue.h"
#include <iostream>
#include <string>

using namespace std;

/*The Book class is an object that stores information of a book as well as provide the function
to pass a book off to another employee.*/

class Book {

public:

	//Book() { name = ""; archived = false; newCirculation = true; }
	Book(string new_book) { name = new_book; archived = false; newCirculation = true; }

	void populateQueue(list<Employee>& emps);
	void passNextEmp(list<Employee>& emps);
	bool isArchived() { if (archived) return true; else return false; }
	bool newCirculation;
	friend bool operator== (const Book& b1, const Book& b2) {
		return (b1.name == b2.name);
	}

	//Getters And Setters
	string getName() { return name; };

	Date getStartDate() { return startDate; };
	void setStartDate(Date sd) { startDate = sd; }

	Date getEndDate() { return endDate; };
	void setEndDate(Date ed) { endDate = ed; }

	Pqueue& getEmployees() { return Employees; }

	string getRetainer() { return currentRetainer.getName(); }
	void setRetainer(Employee& emp) { currentRetainer = emp; }


	Date getLastPassed() { return lastPassed; }
	void setLastPassed(Date passed) { lastPassed = passed; }

private:
	// Data
	string name;
	Date startDate;
	Date endDate;
	Pqueue Employees;
	Employee currentRetainer;
	Date lastPassed;
	bool archived;
};