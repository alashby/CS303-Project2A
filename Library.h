// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#pragma once
#include "Book.h"
#include "Employee.h"
#include "Date.h"
#include "Pqueue.h"
#include "omp.h"
#include <list>

using namespace std;

class Library {
public:
	/*Adds a new book to the list of circulating books (circBooks)
	@param book The title of the new book
	*/
	void addBook(string book) { circBooks.push_back(Book(book)); }

	/*Adds a new employee to the list of employees (Employees)
	@param emp The name of the new employee
	*/
	void addEmployee(string emp) { Employees.push_back(Employee(emp)); }

	/*Sets the circulation date for a book
	@param book The title of the book
	@param start_date Date the book will begin circulation*/
	void circulateBook(string book, Date start_date);

	/*Passes the book to the employee with the highest priority in the book's queue on a certain date
	@param book Title of the book
	@param pass_date Date the book is passed*/
	void passOn(string book, Date pass_date);

	/*Completely optional function that couts employees' waiting/retaining statuses. Used for testing.*/
	void announceStatus() {
		for (list<Employee>::iterator itr = Employees.begin(); itr != Employees.end(); itr++) {
			cout << itr->getName() << endl << "---" << endl;
			for (list<Book>::iterator itr_book = circBooks.begin(); itr_book != circBooks.end(); itr_book++) {
				if (itr_book->getRetainer() == itr->getName())
					cout << "Currently Retaining: " << itr_book->getTitle() << endl;
			}
			cout << "Wait Time: " << itr->getWaitTime() << endl <<"Retain Time: " << itr->getRetainTime() << endl << endl;
			}
	}
private:
	/*Updates an employee's waiting and retaining time for all queues that employee is in
	@param emp Name of the employee
	@param wait_time New accumulated waiting time of the employee
	@param retain_time New accumulated retaining time of the employee*/
	void updateEmployee(string emp, int wait_time, int retain_time);

	//Data
	//List of objects of class Book representing books in circulation
	list<Book> circBooks;
	//List of objects of class Book representing books that have been archived
	list<Book> archBooks;
	//List of object of class Employee representing the employees in the system
	list<Employee> Employees;
};