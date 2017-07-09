// lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <fstream>

using namespace std;

double** create2DArray(int size);

double** fillValuesRandomly(double **Array2D, int size);

double multiplySerial(int size, double **numArray1, double **numArray2);

double multiplyParallel(int size, double **numArray1, double **numArray2);

int main()
{
	srand((double)time(0));
	//int n = atoi(argv[1]);

	int multi;

	//int count = 1;
	//int size = 3;
	ofstream outputFile;
	outputFile.open("results.txt");

	outputFile << "Sequential run Results: " << endl;
	for (int i = 200; i < 2001; i = i + 200) {
		cout<< "size: " << i;
		int size = i;

		double** inital2DArray1 = create2DArray(size);
		double** inital2DArray2 = create2DArray(size);

		double** valuesAdded2DArray1 = fillValuesRandomly(inital2DArray1, size);
		double** valuesAdded2DArray2 = fillValuesRandomly(inital2DArray2, size);

		double seqTime = multiplySerial(size, valuesAdded2DArray1, valuesAdded2DArray2);

		outputFile << size << " : " << seqTime << endl;
	}

	outputFile <<"\n"<< "Parallel run Results: " << endl;
	for (int i = 200; i < 2001; i = i + 200) {
		cout << "size: " << i;
		int size = i;

		double** inital2DArray1 = create2DArray(size);
		double** inital2DArray2 = create2DArray(size);

		double** valuesAdded2DArray1 = fillValuesRandomly(inital2DArray1, size);
		double** valuesAdded2DArray2 = fillValuesRandomly(inital2DArray2, size);

		double parTime = multiplyParallel(size, valuesAdded2DArray1, valuesAdded2DArray2);

		outputFile << size << " : " << parTime << endl;
	}

	outputFile.close();

	cin >> multi;
    return 0;
}

double** create2DArray(int size)
{
	double** array2D;

	array2D = new double*[size];

	for (int h = 0; h < size; h++)
	{
		array2D[h] = new double[size];
	}

	return array2D;
}

double** fillValuesRandomly(double **Array2D, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double r = rand();
			Array2D[i][j] = r;
		}
	}
	return Array2D;
}

double multiplySerial(int size, double **numArray1, double **numArray2)
{
	double** resultArray = create2DArray(size);
	double sum;

	double start = omp_get_wtime();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double sum = 0;
			for (int k = 0; k < size; k++) {
				sum += numArray1[i][k] * numArray2[k][j];
			}
			resultArray[i][j] = sum;
		}
	}

	double end = omp_get_wtime();
	double totalTime = end - start;

	cout << endl << "Time for Sequential Multiplication: " << totalTime << endl;

	return totalTime;
	//return resultArray;
}

double multiplyParallel(int size, double **numArray1, double **numArray2)
{
	double** resultArray = create2DArray(size);
	double sum;

	double start = omp_get_wtime();

	//#pragma omp parallel shared ( numArray1, numArray2, resultArray, size ) private ( i, j, k, sum )

	#pragma omp parallel for
	for (int i = 0; i < size; i++) {
		//#pragma omp parallel for
		for (int j = 0; j < size; j++) {
			double sum = 0;
			for (int k = 0; k < size; k++) {
				sum += numArray1[i][k] * numArray2[k][j];
			}
			resultArray[i][j] = sum;
		}
	}

	double end = omp_get_wtime();
	double totalTime = end - start;

	cout << endl << "Time for Parallel Multiplication: " << totalTime << endl;

	return totalTime;
	//return resultArray;
}