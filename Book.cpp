// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#include "Book.h"

using namespace std;

void Book::populateQueue(list<Employee>& emps) {
	// Populating the queue
	if (emps.empty())
		return;
	for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++)
		Employees.push(Employee(itr->getName(), itr->getWaitTime(), itr->getRetainTime(), itr->isRetaining));
	currentRetainer = Employees.top();

	// Setting the first employee to retain the book
	omp_set_num_threads(4);
#pragma omp parallel for
	for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++) {
		if (itr->getName() == currentRetainer.getName()) // If employee is the current retainer of the book
			itr->isRetaining = true; // Update its retaining status
	}

	Employees.pop();

	cout << title << " begins circulation with " << currentRetainer.getName() << endl; // Cout for testing
}

void Book::passNextEmp(list<Employee>& emps) {
	if (!Employees.empty()) {
		omp_set_num_threads(3);
#pragma omp parallel for
		for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++) {
			if (itr->getName() == currentRetainer.getName()) 
				itr->isRetaining = false; // Old retainer is no longer retaining
			else if (itr->getName() == Employees.top().getName())
				itr->isRetaining = true; // New retaining is retaining
		}

		currentRetainer = Employees.top();
		Employees.pop();
	}

	else { // No more employees in queue means book needs archived
		archived = true;
		endDate = lastPassed;
		cout << title << " archived by " << currentRetainer.getName() << endl << endl; //Cout for testing
		currentRetainer = Employee("");
	}
}
