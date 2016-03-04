#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

// MACRO Definitions
#define NUM_DIG 16

// Defining Neurons 
#define N1 2
#define N2 2
#define N3 1

// Defining a 3 layer NN
double **theta_1;	// weights for the 1st --> 2nd layer
double **theta_2;	// weights for the 2nd --> 3rd layer

//Defining the activation layers
int* a1[N1+1];
int* a2[N2+1];
int* a3[N3];



// x1	O | 	|Bias	0    |    |
// x2	O |-----|A1	O    |----|Output O
// Bias	0 |	|A2	O    |    |
// -------      --------------    --------
// Layer 1|	|Hidden Layer|	  |Layer 3

// Function Declarations
void initLayers(int*[], int);
void initWts(int *[], int , int);
float sig (float);
void dec2bin(int, int, int*, int*);
void matMul (int*[], int*[], int*[], int, int, int);
bool isNumber(char *);
void transpose(int *[], int* [], int, int);


void initLayers(int * a[], int num_neurons)
{
	int neurons;
	for (neurons = 0; neurons<num_neurons; neurons++ )
	{
		a[neurons] = (int *) malloc(NUM_DIG*sizeof(int));
	}
}

void initWts (int* theta[], int rows, int cols)
{
	int i;
	int j;
	for (i=0; i<rows; i++)
	{
		for (j=0; j<cols; j++)
		{
			theta[i][j]=rand();
		}
	}
}

float sig(float n)
{
	float sigmoid =0.0;
	float num = 1.0;
	float den = (1 + exp(-1*n));
	
	sigmoid = num / den ;
	return sigmoid;
}

void transpose(int* in[], int* out[], int rows, int cols)
{
	int i;
	int j;

	for (i=0 ; i<rows; i++)
	{
		for (j=0 ; j<cols; j++)
		{
			out[j][i]=in[i][j];
		} 
	}
}

// Func used to determine whether input is a valid number or not
bool isNumber(char number[])
{
    int i = 0;
    bool status = 1;
    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}
// converting the decimal values to arrays for usage
void dec2bin(int a, int b, int* arr_a, int* arr_b)
{
	int i;

	// Defining temporary variables	
	int temp_a = a;
	int temp_b = b;

	// Converting the numbers to binary and storing 
	// each digit in an array
	for (i=0;i<=NUM_DIG;i++)
	{
		arr_a[i]= temp_a % 2;
		arr_b[i]= temp_b % 2;
		temp_a  = temp_a / 2;
		temp_b  = temp_b / 2;
	}
}

// Theta: (mxn); X: (nxp); Z(mxp)
void matMul(int* theta[], int* X[], int* z[], int m, int n, int p)
{
	// i --> 0 to m
	// k --> 0 to n
	// j --> 0 to p
	int i;
	int k;
	int j;
	// Initialising the out array
	for (i=0; i<m; i++)
	{
		for (j=0; j<p; j++)
		{
			z[i][j]=0;
		}
	}
	int sum;
	for (i=0; i<m; i++)
	{
		for (j=0; j<p; j++)
		{
			sum = 0;
			for (k=0; k<n; k++)
			{
				sum = sum + (theta[i][k]*X[k][j]);
			}
			z[i][j]=sum;
		}
	}
}

int main(int argc, char *argv[])
{

    if ( argc != 3 ) // argc should be 3 for correct execution
    	{
        /* We print argv[0] assuming it is the program name */
        printf( "Correct usage: %s <input 1> <input 2>\n\n", argv[0] );
    	}
    else 
	{

	initLayers(a1, N1);
	initLayers(a2, N2);
	initLayers(a3, N3);
	int a;
	int b;

	if (isNumber(argv[1]) && isNumber(argv[2]))
	{
		// Input numbers
		a = atoi(argv[1]);
		b = atoi(argv[2]);
	}
	else
	{
		printf ("Incorrect inputs\n");
		return 0;
	}
	// Output number
	int c;

	// Defining temporary arrays to store the input numbers
	int arr_a[NUM_DIG];
	int arr_b[NUM_DIG];

	dec2bin(a,b,arr_a,arr_b);

// Testing section


//*
	//Test code section
	int num;
	for (num =NUM_DIG-1; num >= 0; num--)
	{
		printf("%d",arr_a[num]);
	}
	printf ("\nTest\n");

	printf ("Testing sigmoid function\n");
	
	float sigm = sig(b);
	printf("The number: %d, The sigmoid: %.5f\n", b, sigm);
	int i, j;
	int m=3;
	int n=2;
	int p=2;
	int *A[m];
	int *B[n];
	int *C[m];
	// Creating array A
	for (i=0; i<m;i++)
	{
		A[i]=(int*) malloc(n*sizeof(int));
		C[i]=(int*) malloc(p*sizeof(int));
	}
	for (i=0; i<n; i++)
	{
		B[i]=(int*) malloc(p*sizeof(int));
	}

        for (i=0; i<m;i++)
        {
                for (j=0; j<n; j++)
                {
                        A[i][j] = j+i;
                }
        }


        for (i=0; i<n;i++)
        {
                for (j=0; j<p; j++)
                {
                        B[i][j] = (j+1)*(i+1);
                }
        }

	matMul(A,B,C,m,n,p);

        for (i=0; i<m;i++)
        {
		printf("%d th row:", (i+1));
                for (j=0; j<p; j++)
                {
                        printf("%d\t",C[i][j]);
                }
		printf("\n");
        }


//****/



	}
	return 0;
}



