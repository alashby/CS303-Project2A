// Al Ashby
// CS303
// 4/9/2017
// Project 2A

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

	/*Book Constructor
	@param new_book The title of the new book
	*/
	Book(string new_book) { title = new_book; archived = false; newCirculation = true; }

	/*Populates a priority queue of employees for the book using existing employee list
	@param emps The list of Employee class consisting of data to fill the priority queue with*/
	void populateQueue(list<Employee>& emps);

	/*Chooses the highest priority employee to retain the book. 
	If the Employees (employee priority queue) is empty, it will archive the book.
	@param emps The list of Employee class of the system to receive data changes*/
	void passNextEmp(list<Employee>& emps);

	/*States whether the book has been archived or not
	@return true if the book has been archived; false if it has not*/
	bool isArchived() { if (archived) return true; else return false; }

	/*Equality comparison overload
	@param b1 object of Book class to be compared on the left-hand side
	@param b2 object of Book class to be compared on the right-hand side
	@return true if the title data for the books is the same; false if otherwise*/
	friend bool operator== (const Book& b1, const Book& b2) {
		return (b1.title == b2.title);
	}

	/*States whether the book is new to circulation (hasn't been passed from the first retainer)*/
	bool newCirculation;

	//Getters And Setters
	string getTitle() { return title; };

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

	// Title of the book
	string title;
	// Date when the book begins circulation
	Date startDate;
	// Date when the book stopped circulating
	Date endDate;
	// Priority queue of Employee class objects to retain books
	Pqueue Employees;
	// Current employee retaining the book
	Employee currentRetainer;
	// Date when the book was last passed from one employee to another
	Date lastPassed;
	// Archival status of the book
	bool archived;
};