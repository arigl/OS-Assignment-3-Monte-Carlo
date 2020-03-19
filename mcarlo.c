/*
   Name: Alex Rigl
   ID: 2300146
   Class: Operating Systems
   Assignment: #3
   Email: crigl@chapman.edu
   Project Description:
   Write a multithreaded version of this algorithm in C/C++ that creates a 
   separate thread to generate a number of random points. The thread will 
   count the number of points that occur within the circle and store that 
   result in a global variable. When this thread has exited, the parent 
   thread will calculate and output the estimated value of π. It is worth 
   experimenting with the number of random points generated. As a general 
   rule, the greater the number of points, the closer the approximation to π.
   
   References:
   - Random number generation from prompt 
   - Ishan pthreads calculation
*/

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Function Declaration
double random_double();
void *monteCarlo(void *param);

// Variable Declaration
int individual = 0;
int total = 0;

// Execute program
int main(int argc, char *argv[])
{
	pthread_t tid;
  pthread_t tid2;

	if (argc != 2)
  {
		fprintf(stderr,"Needs two non-negative integers to function\n");
		return -1;
	}

	if (atoi(argv[1]) < 0)
  {
		fprintf(stderr,"Please enter non-negative integers\n",atoi(argv[1]));
		return -1;
	}

	total = atoi(argv[1]);

	pthread_create(&tid, NULL, monteCarlo, argv[1]);
  pthread_create(&tid2, NULL, monteCarlo, argv[1]);

	pthread_join(tid,NULL);
  pthread_join(tid2,NULL);

	printf("Estimated Value of Pi = %f\n", (4.0*individual/total));

  return 0;
}

double random_double()
{
	return random() / ((double)RAND_MAX + 1);
}

void *monteCarlo(void *param)
{
  srand(time(NULL));
	int hit_count = 0;

  // Check for points inside circle
	for (int i = 0; i < total; i++)
  {
		float x = random_double() * 2.0 - 1.0;
		float y = random_double() * 2.0 - 1.0;

		if (sqrt(x*x + y*y) < 1.0 )
    {
      ++hit_count;
    }
	}

	individual = hit_count;
	pthread_exit(0);
}
