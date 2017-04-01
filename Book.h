#pragma once
#include <list>
#include "Date.h"
#include "Employee.h"
#include "Pqueue.h"

using namespace std;

class Book {

public:
	Book() { ; }
	Book(string new_book) { name = new_book; isArchived = false; }
	string getName() { return name; };
	Date getStartDate() { return startDate; };
	Date getEndDate() { return endDate; };
	void setStartDate(Date sd) { startDate = sd; }
	void setEndDate(Date ed) { endDate = ed; }
	Pqueue& getEmployees() { return Employees; }
	void populateQueue(list<Employee>& emps) {
		if (emps.empty())
			return;
		for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++)
			Employees.push(Employee(itr->getName()));
		currentRetainer = Employees.top();
		Employees.pop();
	}
	string getRetainer() { return currentRetainer.getName(); }
	void setRetainer(Employee& emp) { currentRetainer = emp;}
	Date getLastPassed() { return lastPassed; }
	void setLastPassed(Date passed) { lastPassed = passed; }
	void passNextEmp() { 
		Employees.pop();
		if (!Employees.empty())
			currentRetainer = Employees.top();
		else 
			isArchived = true; }

private:
	Date lastPassed;
	Date startDate;
	Date endDate;
	string name;
	bool isArchived;
	Pqueue Employees;
	Employee currentRetainer;
};