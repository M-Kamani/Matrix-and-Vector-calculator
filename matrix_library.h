#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cctype>
using namespace std;

const int MAX = 1000;

// متغیرهای global
extern double mA[MAX][MAX], mB[MAX][MAX], mC[MAX][MAX];
extern double vA[MAX], vB[MAX], vC[MAX];
extern int rows, cols, rowsB, colsB;
extern int vSize, vSizeB;

// اعلان توابع
template <class T>
void ReadV (int vSize, T V[]);

double VMagnitude(double vec[], int size);
void VNormalize(double vec[], int size, double result[]);
double VDotProduct(double vec1[], double vec2[], int size);
void VCrossProduct(double vec1[], double vec2[], double result[]);
void VAddition (double vec1[], double vec2[], int vSize);
double MDeterminantR(vector<vector<double>> M);
void VSubtraction (double vec1[], double vec2[], int vSize);
void MInverse();

void twoVectorOperations();
void twoMatrixMenu();
void VectorOperations();
void MatrixOperations();

#endif
