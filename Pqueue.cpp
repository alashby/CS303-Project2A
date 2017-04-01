#include "Pqueue.h"
#include "omp.h"
#include "ExpressionError.h"

using namespace std;


int priority(vector<Employee>& array, int index)
{ return (array[index].getWaitTime() - array[index].getRetainTime()); }


void Pqueue::push(const Employee& emp)
{
	data.push_back(emp);
	int child = size() - 1;
	raiseInQueue(child);
	/* Linear Vector
	while ((new_emp - 1) >= 0 &&
		priority(data, new_emp) < priority(data, new_emp - 1)) {
		swap(data[new_emp], data[new_emp - 1]);
		new_emp--;
	}
	*/
}

void Pqueue::pop() {
	if (size() == 0)
		throw Expression_Error("Cannot pop from empty queue");
	if (size() == 1)
		data.pop_back();
	else {
		int parent = 0;
		swap(data[parent], data[size() - 1]);
		data.pop_back();
		lowerInQueue(parent);
	}
}

void Pqueue::update(string employee, int wait_time, int retain_time) {
	int i = 0;
	while (i < size() - 1 && data[i].getName() != employee)
		i++;
	int new_waitTime = wait_time + data[i].getWaitTime();
	int new_retainTime = retain_time + data[i].getRetainTime();
	data[i].setWaitTime(new_waitTime);
	data[i].setRetainTime(new_retainTime);

	raiseInQueue(i);
	lowerInQueue(i);

	/* Linear Vector
	// while i is higher priority, raise child to front of queue (back of vector)
	while (priority(data, i) > priority(data, i + 1))
	{
		swap(data[i], data[i + 1]);
		i++;
	}
	*/
	/* Linear Vector
	// while parent is lower priority, lower parent to back of queue (front of vector)
	while (priority(data, i) < priority(data, i - 1)) {
		swap(data[i], data[i - 1]);
		i++;
	}
	*/
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