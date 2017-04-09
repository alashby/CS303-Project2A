// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#include "Pqueue.h"
#include "omp.h"
#include "ExpressionError.h"
#include <iostream>
#include <string>

using namespace std;

/*Figures priority of a given employee
@param array Queue in vector form of employees
@param index Index of employee to find priority of
@return Priority of the employee in interger form figured by its wait time minus its retain time*/
int priority(vector<Employee>& array, int index)
{ return (array[index].getWaitTime() - array[index].getRetainTime()); }


void Pqueue::push(const Employee& emp)
{
	data.push_back(emp);
	int child = size() - 1; // The index of the employee just pushed
	raiseInQueue(child); // Change its priority accordingly
}

void Pqueue::pop() {
	if (size() == 0)
		throw Expression_Error("Cannot pop from empty queue");
	if (size() == 1) // Only one items needs no extra work
		data.pop_back();
	else {
		int parent = 0; 
		swap(data[parent], data[size() - 1]); // Swap highest priority and lowest priority employees
		data.pop_back(); // Pop the last in queue (now highest priority employee)
		lowerInQueue(parent); // Lower lowest priority employee accordingly
	}
}

void Pqueue::update(string employee, int wait_time, int retain_time) {
	if (empty()) // No updaitng employees in an empty queue
		return;

	int i = 0;
	while (i < size() && data[i].getName() != employee) // Find index of given employee
		i++;
	if (i == size())
		return;

	int new_waitTime = wait_time + data[i].getWaitTime();
	int new_retainTime = retain_time + data[i].getRetainTime();
	data[i].setWaitTime(new_waitTime);
	data[i].setRetainTime(new_retainTime);
	
	raiseInQueue(i);
	lowerInQueue(i);
}

void Pqueue::lowerInQueue(int index) {
	int parent = index;
	while (true) {
		int lchild = parent * 2 + 1;
		int rchild = parent * 2 + 2;
		int maxchild;
		if (lchild < size()) {
			if (rchild >= size() || priority(data, lchild) >= priority(data, rchild))
				maxchild = lchild;
			else
				maxchild = rchild;
			if (priority(data, parent) < priority(data, maxchild)) {
				swap(data[parent], data[maxchild]);
				parent = maxchild;
			}
			else
				return;
		}
		else
			return;
	}
}

void Pqueue::raiseInQueue(int index) {
	int child = index;
	while (true) {
		int parent = (child - 1) / 2;
		if (parent >= 0 && priority(data, child) > priority(data, parent)) {
			swap(data[child], data[parent]);
			child = parent;
		}
		else
			return;
	}
}