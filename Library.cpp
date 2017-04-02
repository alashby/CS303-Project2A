#include "Library.h"
#include "ExpressionError.h"
#include <iostream>

using namespace std;

void Library::circulateBook(string book, Date start_date) {
	for (list<Book>::iterator itr = circBooks.begin(); itr != circBooks.end(); itr++) { // book already added
		if (itr->getName() == book) {
			itr->setStartDate(start_date);
			itr->setLastPassed(start_date);
			itr->populateQueue(Employees);
			return;
		}
	}
	// book not added
	Book new_book(book);
	new_book.setStartDate(start_date);
	new_book.setLastPassed(start_date);
	new_book.populateQueue(Employees);
	circBooks.push_back(new_book);
}

void Library::updateEmployee(string emp, int wait_time, int retain_time, Date pass_date) {
	list<Employee>::iterator itr_emp = Employees.begin();
	while (itr_emp->getName() != emp)
		itr_emp++;


	omp_set_num_threads(2);
#pragma omp parallel for
	for (list<Book>::iterator itr_book = circBooks.begin(); itr_book != circBooks.end(); itr_book++) {
		itr_book->getEmployees().update(emp, wait_time, retain_time);
	}
}

void Library::passOn(string book, Date pass_date) {
	list<Book>::iterator itr = circBooks.begin();
	while (itr->getName() != book && itr != circBooks.end())
		itr++;
	if (itr == circBooks.end())
		throw Expression_Error("Book not in circulation");
	updateEmployee(itr->getRetainer(), 0, pass_date - itr->getLastPassed(), pass_date);
	for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
		if (itr_emp->getName() == itr->getRetainer())
			itr_emp->setRetainTime((pass_date - itr->getLastPassed()) + itr_emp->getRetainTime()); // update system list
	}
	cout << itr->getRetainer() << " retained " << itr->getName() << " for " << pass_date - itr->getLastPassed() << " days.\n";
	omp_set_num_threads(2);
#pragma omp parallel for
		for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
			if (itr_emp->getName() != itr->getRetainer()) {
				itr_emp->setWaitTime((pass_date - itr->getLastPassed()) + itr_emp->getWaitTime()); // update system list
				updateEmployee(itr_emp->getName(), pass_date - itr->getLastPassed(), 0, pass_date); // update wait times of other employees
			}
		}
		itr->passNextEmp();
		itr->setLastPassed(pass_date);
		if (itr->isArchived())
			archBooks.push_back(*itr);

	/*updateEmployee(itr->getRetainer(), 0, pass_date - itr->getLastPassed(), pass_date); // update retain time for employee
	cout << book << " retained for " << pass_date - itr->getLastPassed() << " days by " << itr->getRetainer() << endl;
	itr->passNextEmp();
#pragma omp parallel for
	for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
		if (itr_emp->getName() != itr->getRetainer())
			updateEmployee(itr_emp->getName(), pass_date - itr->getLastPassed(), 0, pass_date); // update wait times of other employees
	}
	*/
}
