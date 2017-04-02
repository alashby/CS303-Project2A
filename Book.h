#pragma once
#include <list>
#include "Date.h"
#include "Employee.h"
#include "Pqueue.h"
#include <iostream>
#include <string>

using namespace std;

class Book {

public:
	Book() { ; }
	Book(string new_book) { name = new_book; archived = false; }
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
		cout << name << " begins circulation with " << currentRetainer.getName() << endl;
	}
	string getRetainer() { return currentRetainer.getName(); }
	void setRetainer(Employee& emp) { currentRetainer = emp;}
	Date getLastPassed() { return lastPassed; }
	void setLastPassed(Date passed) { lastPassed = passed; }
	void passNextEmp() { 
		prevRetainer = currentRetainer;
		if (!Employees.empty()) {
			currentRetainer = Employees.top();
			Employees.pop();
		}
		else {
			archived = true;
			endDate = lastPassed;
			cout << name << " archived by " << currentRetainer.getName() << endl;
		}
	}
	bool isArchived() { if (archived) return true; else return false; }
private:
	Date lastPassed;
	Date startDate;
	Date endDate;
	string name;
	Pqueue Employees;
	bool archived;
	Employee currentRetainer;
	Employee prevRetainer;
};