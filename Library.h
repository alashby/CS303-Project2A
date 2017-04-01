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
private:
	void updateEmployee(string emp, int wait_time, int retain_time);
	list<Book> circBooks;
	list<Book> archBooks;
	list<Employee> Employees;
};