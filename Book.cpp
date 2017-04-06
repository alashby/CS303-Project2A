#include "Book.h"

using namespace std;

void Book::populateQueue(list<Employee>& emps) {
	if (emps.empty())
		return;
	for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++)
		Employees.push(Employee(itr->getName(), itr->getWaitTime(), itr->getRetainTime(), itr->isRetaining));
	currentRetainer = Employees.top();

	omp_set_num_threads(3);
#pragma omp parallel for
	for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++) {
		if (itr->getName() == currentRetainer.getName())
			itr->isRetaining = true;
	}
	Employees.pop();
	cout << name << " begins circulation with " << currentRetainer.getName() << endl;
}

void Book::passNextEmp(list<Employee>& emps) {
	if (!Employees.empty()) {

		omp_set_num_threads(3);
#pragma omp parallel for
		for (list<Employee>::iterator itr = emps.begin(); itr != emps.end(); itr++) {
			if (itr->getName() == currentRetainer.getName())
				itr->isRetaining = false;
			else if (itr->getName() == Employees.top().getName())
				itr->isRetaining = true;
		}

		currentRetainer = Employees.top();
		Employees.pop();
	}
	else {
		archived = true;
		endDate = lastPassed;
		cout << name << " archived by " << currentRetainer.getName() << endl << endl;
		currentRetainer = Employee("");
	}
}
