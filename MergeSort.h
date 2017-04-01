#pragma once
#include <vector>
#include "Employee.h"

using namespace std;

class MergeSort {
public:
	void mergeSort(vector<Employee>& array) { vector<Employee> result = array; mergesort(array, result, 0, array.size() - 1); }
private:
	void mergesort(vector<Employee>& array, vector<Employee>& result, int lowerBand, int upperBand);
	void merge(vector<Employee>& array, vector<Employee>& result, int lowerPointer, int higherPointer, int upperBound);
};