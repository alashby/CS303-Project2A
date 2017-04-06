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
	void addBook(string book) { circBooks.push_back(Book(book)); }
	void addEmployee(string emp) { Employees.push_back(Employee(emp)); }
	void circulateBook(string book, Date start_date);
	void passOn(string book, Date pass_date);
	void announceStatus() {
		for (list<Employee>::iterator itr = Employees.begin(); itr != Employees.end(); itr++) {
			cout << itr->getName() << endl << "---" << endl;
			for (list<Book>::iterator itr_book = circBooks.begin(); itr_book != circBooks.end(); itr_book++) {
				if (itr_book->getRetainer() == itr->getName())
					cout << "Currently Retaining: " << itr_book->getName() << endl;
			}
			cout << "Wait Time: " << itr->getWaitTime() << endl <<"Retain Time: " << itr->getRetainTime() << endl << endl;
			}
	}
private:
	void updateEmployee(string emp, int wait_time, int retain_time, Date pass_date);
	list<Book> circBooks;
	list<Book> archBooks;
	list<Employee> Employees;
};