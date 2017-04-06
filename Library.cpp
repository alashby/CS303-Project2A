#include "Library.h"
#include "ExpressionError.h"
#include <iostream>

using namespace std;

void Library::circulateBook(string book, Date start_date) {
	for (list<Book>::iterator itr = circBooks.begin(); itr != circBooks.end(); itr++) { // book already added
		if (itr->getName() == book) {
			itr->setStartDate(start_date);
			itr->setLastPassed(start_date);
			return;
		}
	}
	// book not added
	Book new_book(book);
	new_book.setStartDate(start_date);
	new_book.setLastPassed(start_date);
	circBooks.push_back(new_book);
}

void Library::updateEmployee(string emp, int wait_time, int retain_time, Date pass_date) {
	for (list<Book>::iterator itr_book = circBooks.begin(); itr_book != circBooks.end(); itr_book++) {
		if (!itr_book->isArchived())
			itr_book->getEmployees().update(emp, wait_time, retain_time);
	}
}

void Library::passOn(string book, Date pass_date) {
	list<Book>::iterator itr = circBooks.begin();
	while (itr->getName() != book && itr != circBooks.end())
		itr++;
	if (itr == circBooks.end())
		throw Expression_Error("Book not in circulation");
	if (itr->newCirculation)
		itr->populateQueue(Employees);
	itr->newCirculation = false;

	int days_since_last_passed = pass_date - itr->getLastPassed();
	
	omp_set_num_threads(4);
#pragma omp parallel for
		for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
			if (itr->getRetainer() != itr_emp->getName() && !itr_emp->isRetaining) {
				itr_emp->setWaitTime(days_since_last_passed + itr_emp->getWaitTime()); // update system list
				updateEmployee(itr_emp->getName(), days_since_last_passed, 0, pass_date); // update wait times of other employees
			}
			else {
				updateEmployee(itr->getRetainer(), 0, days_since_last_passed, pass_date);
				itr_emp->setRetainTime(days_since_last_passed + itr_emp->getRetainTime()); // update system list
			}
		}
		
		string old_retainer = itr->getRetainer();

		itr->passNextEmp(Employees);
		itr->setLastPassed(pass_date);
		if (itr->isArchived()) {
			archBooks.push_back(*itr);
			circBooks.remove(*itr);
			omp_set_num_threads(4);
#pragma omp parallel for
			for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
				if (old_retainer == itr_emp->getName())
					itr_emp->isRetaining = false;
			}
		}
		else
			cout << old_retainer << " passed " << itr->getName() << " to " << itr->getRetainer() << " after " << days_since_last_passed << " days." << endl << endl;

}
