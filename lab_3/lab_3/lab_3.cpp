// lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//answer =  18  24  30
//			54  69  84 
//			86  114 138
#include <iostream>
using namespace std;

int** create2DArray(int size);

int** multiply(int **numArray1, int **numArray2);

int main()
{
	int multi;
	int count = 1;
	int size = 3;

	int** numArray1 = create2DArray(size);
	int** numArray2 = create2DArray(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; i++) {
			numArray1[i][j] = count;
			numArray2[i][j] = count;
			count++;
		}
	}
	//int numArray1[3][3] = { { 1,2,3 } ,{ 4,5,6 } ,{ 7,8,9 } };
	//int numArray2[3][3] = { { 7,8,9 } ,{ 4,5,6 } ,{ 1,2,3 } };

	int** my2DArray = multiply(numArray1, numArray2);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << my2DArray[i][j] << " ";
		}
		cout << "\n";
	}

	cin >> multi;
    return 0;
}

int** create2DArray(int size)
{
	int** array2D = 0;
	array2D = new int*[size];

	for (int h = 0; h < 3; h++)
	{
		array2D[h] = new int[size];

		for (int w = 0; w < size; w++)
		{
			// fill in some initial values
			// (filling in zeros would be more logic, but this is just for the example)
			array2D[h][w] = 0;
		}
	}

	return array2D;
}

int** multiply(int **numArray1, int **numArray2) 
{
	//int(*rPointer);
	int** resultArray = create2DArray(3);

	int sum;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += numArray1[i][k] * numArray2[k][j];
			}
			resultArray[i][j] = sum;
		}
	}

	return resultArray;
}