// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#include "Library.h"
#include "ExpressionError.h"
#include <iostream>

using namespace std;

void Library::circulateBook(string book, Date start_date) {
	// Book already added to circulation list (used circulateBook())
	for (list<Book>::iterator itr = circBooks.begin(); itr != circBooks.end(); itr++) { 
		if (itr->getTitle() == book) {
			itr->setStartDate(start_date);
			itr->setLastPassed(start_date); // Last date book was "passed" was when it began circulating
			return;
		}
		for (list<Book>::iterator itr = archBooks.begin(); itr != archBooks.end(); itr++)
			if (itr->getTitle() == book)
				Expression_Error("Book has already been archived");
	}

	// Book not in circulation list (didn't use circulateBook())
	Book new_book(book);
	new_book.setStartDate(start_date);
	new_book.setLastPassed(start_date); // Last date book was "passed" was when it began circulating
	circBooks.push_back(new_book);
}

void Library::updateEmployee(string emp, int wait_time, int retain_time) {
	for (list<Book>::iterator itr_book = circBooks.begin(); itr_book != circBooks.end(); itr_book++) {
		if (!itr_book->isArchived()) // Don't bother updating books with no employees
			itr_book->getEmployees().update(emp, wait_time, retain_time);
	}
}

void Library::passOn(string book, Date pass_date) {
	// Find the book being passed in circulation
	list<Book>::iterator itr = circBooks.begin();
	while (itr->getTitle() != book && itr != circBooks.end())
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
				itr_emp->setWaitTime(days_since_last_passed + itr_emp->getWaitTime()); // Update wait times in system list
				updateEmployee(itr_emp->getName(), days_since_last_passed, 0); // Update wait times in queues
			}
			else {
				updateEmployee(itr->getRetainer(), 0, days_since_last_passed); // Update retain times in queues
				itr_emp->setRetainTime(days_since_last_passed + itr_emp->getRetainTime()); // Update retain times in system list
			}
		}
		
		string old_retainer = itr->getRetainer();

		itr->passNextEmp(Employees);
		itr->setLastPassed(pass_date);

		// Update archival status if applicable
		if (itr->isArchived()) {
			archBooks.push_back(*itr);
			circBooks.remove(*itr);

			omp_set_num_threads(4);
#pragma omp parallel for
			for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
				if (old_retainer == itr_emp->getName())
					itr_emp->isRetaining = false; // Employee to send book to archiving is no longer retaining
			}
		}

		else
			// Cout for testing
			cout << old_retainer << " passed " << itr->getTitle() << " to " << itr->getRetainer() << " after " << days_since_last_passed << " days." << endl << endl;

}
