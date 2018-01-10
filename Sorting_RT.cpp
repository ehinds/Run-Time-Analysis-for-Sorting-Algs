#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


//***********************************************
//Insertion Sort function
//************************************************
void ALG1(int A[], int n)
{
	int key, i;

	for (int j = 1; j < n; j++)
	{
		key = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > key)
		{
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

//***********************************************
//Merge function for Merge sort
//************************************************
void Merge(int A[], int p, int q, int r)
{
	int i, j;

	int n1 = q - p + 1;
	int n2 = r - q;

	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];

	for (i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}
	L[n1] = R[n2] = RAND_MAX + 1;
	i = j = 0;

	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}

	delete[] L;
	delete[] R;
}

//***********************************************
//Merge Sort function
//************************************************
void ALG2(int A[], int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		ALG2(A, p, q);
		ALG2(A, q + 1, r);
		Merge(A, p, q, r);
	}
}

//***********************************************
//Partition for quicksort function
//************************************************
int Partition(int A[], int p, int r)
{
	int x = A[r];
	int i = p - 1;
	int tempStorage = 0;

	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i++;
			tempStorage = A[i];
			A[i] = A[j];
			A[j] = tempStorage;
		}
	}
	tempStorage = A[i + 1];
	A[i + 1] = A[r];
	A[r] = tempStorage;

	return i + 1;
}

//***********************************************
//Quicksort function
//************************************************
void ALG3(int A[], int p, int r)
{
	if (p < r)
	{
		int q = Partition(A, p, r);
		ALG3(A, p, q - 1);
		ALG3(A, q + 1, r);
	}
}


int main()
{
	const int Nf = 100000;
	int i = 0, j = Nf;
	int Ns = 5000;
	int delta = 5000;
	double sum = 0;
	const int m = 10;
	clock_t t1, t2;

	//*************************************************
	//Declare 2D array A for storing random values
	//***********************************************
	int **A = new int*[m];

	for (i = 0; i < m; i++)
	{
		A[i] = new int[Nf + 1];
	}
	//*************************************************

	//*****************************************************************************
	//Declare 3 dynamic arrays: B, C, and D for copying array A and sorting them
	//*****************************************************************************
	int *B = new int[Nf + 1];
	int *C = new int[Nf + 1];
	int *D = new int[Nf + 1];
	//*********************************************************

	//*********************************************************
	//Dynamic arrays for storing the run-time
	double **tALG1 = new double*[m];
	for (i = 0; i < m; i++)
	{
		tALG1[i] = new double[Nf + 1];
	}
	double *Tavg_ALG1 = new double[Nf + 1];

	double **tALG2 = new double*[m];
	for (i = 0; i < m; i++)
	{
		tALG2[i] = new double[Nf + 1];
	}
	double *Tavg_ALG2 = new double[Nf + 1];
	
	double **tALG3 = new double*[m];
	for (i = 0; i < m; i++)
	{
		tALG3[i] = new double[Nf + 1];
	}
	double *Tavg_ALG3 = new double[Nf + 1];
	//**********************************************************************

	//***********************************************************************
	//Initialize Array A with random elements
	//***********************************************************************
	for (i = 0; i < m; i++)
	{
		//cout << "Array A[" << i << ", " << j << "] is: ";
		for (j = 0; j < Nf; j++)
		{
			A[i][j] = rand();
			//cout << A[i][j] << " ";
		}
		//cout << endl << endl;
	}

	//*********************************************************************
	//Algorithm 1: insertion Sort RT
	//*********************************************************************
	int n = Ns;
	int k = Ns;
	while (n <= Nf)
	{
		for (i = 0; i < m; i++)
		{
			//cout << "Array B[" << i << ", " << k << "] is: ";
			for (k = 0; k < n; k++)
			{
				B[k] = A[i][k];
				//cout << B[k] << " ";
			}
			t1 = clock();
			ALG1(B, n);
			/*for (int l = 0; l < n; l++)
			{
				cout << B[l] << " ";
			}*/
			t2 = clock();
			tALG1[i][n] = (t2 - t1)/ (CLOCKS_PER_SEC / 1000);
			sum = sum + tALG1[i][n];
			//cout << endl << endl;
		}
		Tavg_ALG1[n] = ((sum) / m);
		sum = 0;

		cout << "The average for Ns = " << n << " for ALG1 is " << Tavg_ALG1[n] << " milliseconds" << endl;
		n = n + delta;
		k = k + delta;
	}
	//**********************************************************************

	//*********************************************************************
	//Algorithm 2: Merge Sort RT
	//*********************************************************************
	n = Ns;
	k = Ns;
	while (n <= Nf)
	{
		for (i = 0; i < m; i++)
		{
			//cout << "Array C[" << i << ", " << k << "] is: ";
			for (k = 0; k < n; k++)
			{
				C[k] = A[i][k];
				//cout << C[k] << " ";
			}
			t1 = clock();
			ALG2(C, 0, n - 1);
			/*for (int l = 0; l < n; l++)
			{
			cout << C[l] << " ";
			}*/
			t2 = clock();
			tALG2[i][n] = (t2 - t1) / (CLOCKS_PER_SEC / 1000);
			sum = sum + tALG2[i][n];
			//cout << endl << endl;
		}
		Tavg_ALG2[n] = (sum/m);
		sum = 0;

		cout << "The average for Ns = " << n << " for ALG2 is " << Tavg_ALG2[n] << " milliseconds" << endl;
		n = n + delta;
		k = k + delta;
	}
	//***********************************************************************

	//*********************************************************************
	//Algorithm 3: Quick Sort RT
	//*********************************************************************
	n = Ns;
	k = Ns;
	sum = 0;
	while (n <= Nf)
	{
		for (i = 0; i < m; i++)
		{
			//cout << "Array D[" << i << ", " << k << "] is: ";
			for (k = 0; k < n; k++)
			{
				D[k] = A[i][k];
				//cout << D[k] << " ";
			}
			t1 = clock();
			ALG3(D, 0, n - 1);
			/*for (int l = 0; l < n; l++)
			{
			cout << D[l] << " ";
			}*/
			t2 = clock();
			tALG3[i][n] = (t2 - t1) / (CLOCKS_PER_SEC / 1000);
			sum = sum + tALG3[i][n];
			//cout << endl << endl;
		}
		Tavg_ALG3[n] = (sum/m);
		sum = 0;

		cout << "The average for Ns = " << n << " for ALG3 is " << Tavg_ALG3[n] << " milliseconds" <<  endl;
		n = n + delta;
		k = k + delta;
	}
	//**********************************************************************

	//*******************************************************
	//Delete the dynamic arrays from memory
	//*******************************************************
	for (i = 0; i < m; i++)
	{
		delete[] A[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;
	for (i = 0; i < m; i++)
	{
		delete[] tALG1[i];
	}
	delete[] tALG1;
	delete[] Tavg_ALG1;
	for (i = 0; i < m; i++)
	{
		delete[] tALG2[i];
	}
	delete[] tALG2;
	delete[] Tavg_ALG2;
	for (i = 0; i < m; i++)
	{
		delete[] tALG3[i];
	}
	delete[] tALG3;
	delete[] Tavg_ALG3;
	//**************************************************************

	return 0;
}