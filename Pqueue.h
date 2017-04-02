#pragma once
#include <vector>
#include <string>
#include "Employee.h"

class Pqueue {
public:
	Pqueue() { ; }
	void push(const Employee& emp);
	void pop();
	bool empty() const { return data.empty(); }
	size_t size() const { return data.size(); }
	const Employee& top() const { return data.front(); }
	void update(string employee, int wait_time, int retain_time);
private:
	vector<Employee> data;
	void raiseInQueue(int index);
	void lowerInQueue(int index);
};