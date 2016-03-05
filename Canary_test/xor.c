#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

// MACRO Definitions
#define NUM_DIG 16
#define THRESH 0.5
#define TRAIN_ITER 100
#define ENABLE 1
#define DISABLE 0

// Switch to allow training
#define TRAINING_MODE DISABLE 
// Defining Neurons 
#define N1 2
#define N2 2
#define N3 1

// Defining a 3 layer NN
double *theta1[N1+1];	// weights for the 1st --> 2nd layer
double *theta2[N2+1];	// weights for the 2nd --> 3rd layer

//Defining the activation layers
int* a1[N1+1];
int* a2[N2+1];
int* a3[N3];


// Nomenclature based on Andrew NG's Machine Learning Course (Coursera)
// Activation Layers: a_{i}
// Weights: Theta_{i}_{j}

// -------      --------------    --------
// x1	O | 	|Bias	0    |    |
// x2	O |-----|A1	O    |----|Output O
// Bias	0 |	|A2	O    |    |
// -------      --------------    --------
// Layer 1|	|Hidden Layer|	  |Layer 3

// Function Declarations
void initLayers(int*[], int);
void initLayersDbl(double*[], int);
void initWts(double *[], int , int);
float sig (float);
void dec2bin(int, int*);
int bin2dec(int*);
void matMul (double*[], int*[], double*[], int, int, int);
bool isNumber(char *);
void transpose(int *[], int* [], int, int);
void sigArr(double* [], int* [], int,int);
void training(double* [], double* []);

void initLayers(int * a[], int num_neurons)
{
	int neurons;
	for (neurons = 0; neurons<=num_neurons; neurons++ )
	{
		a[neurons] = (int *) malloc(NUM_DIG*sizeof(int));
	}
}

void initLayersDbl(double * a[], int num_neurons)
{
        int neurons;
        for (neurons = 0; neurons<=num_neurons; neurons++ )
        {
                a[neurons] = (double *) malloc(NUM_DIG*sizeof(double));
        }
}


void initWts (double* theta[], int rows, int cols)
{
	int r;
	for (r=0;r<rows;r++)
	{
		theta[r]=(double*) malloc(cols*sizeof(double));
	}

	int i;
	int j;
	for (i=0; i<rows; i++)
	{
		for (j=0; j<cols; j++)
		{
			theta[i][j]=(rand()%50)-25;
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
        return 0;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

// converting the decimal values to arrays for usage
void dec2bin(int a, int* arr_a)
{
	int i;

	// Defining temporary variables	
	int temp_a = a;

	// Converting the numbers to binary and storing 
	// each digit in an array
	for (i=0;i<NUM_DIG;i++)
	{
		arr_a[i]= temp_a % 2;
		temp_a  = temp_a / 2;
	}
}

int bin2dec(int* arr)
{
        int i;
	int sign=1;
	int sum=0;
        // Converting the numbers to binary and storing 
        // each digit in an array
        for (i=0;i<NUM_DIG;i++)
        {
		sum = sum + (arr[i]*pow(2, i));
        }
	return sum;
}


// Theta: (mxn); X: (nxp); Z(mxp)
void matMul(double* theta[], int* X[], double* z[], int m, int n, int p)
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

void sigArr(double* in[], int* out[], int row,int col)
{
	int i;
	int j;

	for (i=0; i<row; i++)
	{
//	   printf("\n");
	   for (j=0;j<col; j++)
	   {
//		printf("%.3f   ", sig(in[i][j]));
		if (sig(in[i][j]) >=THRESH)
		{
			out[i][j]=1;
		}
		else 
		{
			out[i][j]=0;
		}
	   }
	}
}

// Training code based on 
// Andrew NG's Machine Learning Course
// & http://mnemstudio.org/neural-networks-backpropagation-xor.htm

void training(double* theta1[], double* theta2[])
{
	int x_train[4][3];
	double y_train[4];

	x_train[0][0]   =  1;
    	x_train[0][1]   =  0;
    	x_train[0][2]   =  1; 
    	y_train[0]      =  1;

    	x_train[1][0]   =  0;
    	x_train[1][1]   =  1;
    	x_train[1][2]   =  1; 
    	y_train[1]      =  1;

    	x_train[2][0]   =  1;
    	x_train[2][1]   =  1;
    	x_train[2][2]   =  1; 
    	y_train[2]      =  0;

    	x_train[3][0]   =  0;
    	x_train[3][1]   =  0;
    	x_train[3][2]   =  1; 
    	y_train[3]      =  0;

        // initializing the weights for each layer with random numbers
        initWts(theta1, N1+1, N2);
        initWts(theta2, N2+1, N3);

	// training input picked at random
	// Training Algorithm executed TRAIN_ITER times.
	int iter;
	int i;
	int m;
	int j;
	int k;
	double des_op;
	int test[3];
	double hid_lay[3][1];
	hid_lay[0][0]=1;
	double err=0;
	double err_sum=0.0;
	double calc_op;
	for (iter=0 ; iter < TRAIN_ITER; iter++)
	{
		err_sum=0.0;
		// We find that there are 4 training inputs in this case.
		for (i=0; i<4; i++)
		{
			des_op = y_train[i];
			for(m=0;m<3;m++) 
			test[m] = x_train[i][m];
		
			for (m=1; m<3;m++)
			{
				int sum=0;
				for (j=0; j<3; j++)
				{
				   sum += theta1[m-1][j]*test[j];
				} 
				hid_lay[m][0] = sig (sum);
			} 
			double sum2=0.0;
			for (m=0; m<3;m++)
			{
				sum2 += theta2[0][m]*hid_lay[m][0];
			}
			calc_op = sig(sum2);
			
			err = calc_op - des_op;
			//printf("%f" ,err);
			err_sum +=(err*err);
			double delta;

			// begin by Calculating delta from Output to Hidden Layer
		    	for(m = 0; m < N2; m++)
        		{
				delta =  err * hid_lay[m][0];
        			theta2[0][k] = theta2[0][k] + delta;
			}
			// delta from hidden to first layer
			for(i = 0; i < N2; i++)
			{
				delta =0;
        			for(k = 0; k < N1; k++)
				{
            				delta = test[k]*err*sig(hid_lay[i][0])*(1-sig(hid_lay[i][0]));
            				theta1[k][i] = theta1[k][i] + delta;
        			}
    			}
		}// end sweep through different train_inputs
		err_sum = err_sum/4;
	}// end sweep through iterations
}// end training function

int main(int argc, char *argv[])
{

    if ( argc != 3 ) // argc should be 3 for correct execution
    	{
        	/* We print argv[0] assuming it is the program name */
        	printf( "Correct usage: %s <input 1> <input 2>\n\n", argv[0] );
    	}
   else 
	{
	// initializing the layers
	initLayers(a1, N1);
	initLayers(a2, N2);
	initLayers(a3, N3);


	// initializing the weights for each layer
	initWts(theta1, N1+1, N2);
	initWts(theta2, N2+1, N3);

	if (!TRAINING_MODE)
	{
	theta1[0][0]=-1;
        theta1[0][1]= 2;
        theta1[0][2]= 2;
        theta1[1][0]= 3;
        theta1[1][1]=-2;
        theta1[1][2]=-2;

        theta2[0][0]=-3;
        theta2[0][1]= 2;
        theta2[0][2]= 2;
	}
	else
	{
	training(theta1, theta2);

        printf("theta1:\n%f\t",theta1[0][0]);//=-1;
        printf("%f\t",theta1[0][1]);
        printf("%f\n",theta1[0][2]);
        printf("%f\t",theta1[1][0]);
        printf("%f\t",theta1[1][1]);
        printf("%f\n",theta1[1][2]);
	
        printf("theta2:\n%f\t",theta2[0][0]);
        printf("%f\t",theta2[0][1]);
        printf("%f\n",theta2[0][2]);
	}
        theta1[0][1]= 2;
        theta1[0][2]= 2;
        theta1[1][0]= 3;
        theta1[1][1]=-2;
        theta1[1][2]=-2;

        theta2[0][0]=-3;
        theta2[0][1]= 2;
        theta2[0][2]= 2;



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
		printf ("Incorrect inputs. Inputs should be non-negative integers.\n");
		return 0;
	}
	// Output number
	int c;

	// Defining temporary arrays to store the input numbers
	int arr_a[NUM_DIG];
	int arr_b[NUM_DIG];

	dec2bin(a,arr_a);
	dec2bin(b,arr_b);
	int idx;

	//Preparing activation Layer 1
	for (idx=0;idx<NUM_DIG;idx++)
	{
		a1[0][idx]=1;
		a1[1][idx]=arr_a[idx];
		a1[2][idx]=arr_b[idx];
	}

	// Forward Propogation

	double *out1[N2];
	double *out2[N3];
	int *h1[N2];
	int *h2[N3];
	initLayersDbl(out1, N2-1);
	initLayersDbl(out2, N3-1);
	initLayers(h1, N2-1);
	initLayers(h2, N3-1);


	matMul(theta1, a1, out1, N2, N1+1, NUM_DIG);
	sigArr(out1, h1, N2, NUM_DIG);

        for (idx=0;idx<NUM_DIG;idx++)
        {
                a2[0][idx]=1;
                a2[1][idx]=h1[0][idx];
                a2[2][idx]=h1[1][idx];
        }

	matMul(theta2, a2, out2, N3, N2+1, NUM_DIG);
	sigArr(out2, h2, N3, NUM_DIG);

	printf("%d XOR %d = %d\n",a,b ,bin2dec(h2[0]));


	}
     return 0;
}



