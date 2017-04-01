#include "Library.h"
#include "ExpressionError.h"

using namespace std;

void Library::circulateBook(string book, Date start_date) {
	for (list<Book>::iterator itr = circBooks.begin(); itr != circBooks.end(); itr++) {
		if (itr->getName() == book) {
			itr->setStartDate(start_date);
			itr->populateQueue(Employees);
			return;
		}
	}
	Book new_book(book);
	new_book.setStartDate(start_date);
	new_book.setLastPassed(start_date);
	new_book.populateQueue(Employees);
	circBooks.push_back(new_book);
}

void Library::updateEmployee(string emp, int wait_time, int retain_time) {
	list<Employee>::iterator itr_emp = Employees.begin();
	while (itr_emp->getName() != emp)
		itr_emp++;
	int new_waitTime = itr_emp->getWaitTime() + wait_time;
	int new_retainTime = itr_emp->getRetainTime() + retain_time;
	itr_emp->setWaitTime(new_waitTime);
	itr_emp->setRetainTime(new_retainTime);

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
	updateEmployee(itr->getRetainer(), 0, pass_date - itr->getLastPassed()); // update retain time for employee
	omp_set_num_threads(2);
#pragma omp parallel for
	for (list<Employee>::iterator itr_emp = Employees.begin(); itr_emp != Employees.end(); itr_emp++) {
		if (itr_emp->getName() != itr->getRetainer())
			updateEmployee(itr_emp->getName(), pass_date - itr->getLastPassed(), 0); // update retain times of other employees
	}
	itr->passNextEmp();

}
