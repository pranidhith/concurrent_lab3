// lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int** create2DArray(int size);

int** multiply(int size, int **numArray1, int **numArray2);

int** fillValuesRandomly(int **Array2D, int size);

int main()
{
	srand((int)time(0));
	//int n = atoi(argv[1]);

	int multi;

	int count = 1;
	//int size = 3;

	for (int i = 200; i < 2001; i = i + 200) {
		cout<< "size: " << i;
		int size = i;

		int** inital2DArray1 = create2DArray(size);
		int** inital2DArray2 = create2DArray(size);

		int** valuesAdded2DArray1 = fillValuesRandomly(inital2DArray1, size);
		int** valuesAdded2DArray2 = fillValuesRandomly(inital2DArray2, size);

		int** my2DArray = multiply(size, valuesAdded2DArray1, valuesAdded2DArray2);
	}

	cin >> multi;
    return 0;
}

int** create2DArray(int size)
{
	int** array2D;

	array2D = new int*[size];

	for (int h = 0; h < size; h++)
	{
		array2D[h] = new int[size];
	}

	return array2D;
}

int** fillValuesRandomly(int **Array2D, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double r = rand();
			Array2D[i][j] = r;
		}
	}
	return Array2D;
}

int** multiply(int size, int **numArray1, int **numArray2) 
{
	int** resultArray = create2DArray(size);
	int sum;

	double start = omp_get_wtime();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int sum = 0;
			for (int k = 0; k < size; k++) {
				sum += numArray1[i][k] * numArray2[k][j];
			}
			resultArray[i][j] = sum;
		}
	}

	double end = omp_get_wtime();
	double totalTime = end - start;

	cout << endl << "Time for Sequential Multiplication: " << totalTime << endl;

	return resultArray;
}