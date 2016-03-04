#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

// MACRO Definitions
#define NUM_DIG 16

// Function Declarations
float sig (float);
void dec2bin(int, int, int*, int*);
void matMul (int*[], int*[], int*[], int, int, int);
bool isNumber(char *);

float sig(float n)
{
	float sigmoid =0.0;
	float num = 1.0;
	float den = (1 + exp(-1*n));
	
	sigmoid = num / den ;
	return sigmoid;
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
/*
	printf("Input two numbers\n");
	printf("first number:\n");
	scanf("%d",&a);
	printf("second number:\n");
	scanf("%d",&b);
*/
	// Defining temporary arrays to store the input numbers
	int arr_a[NUM_DIG];
	int arr_b[NUM_DIG];

	dec2bin(a,b,arr_a,arr_b);


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



