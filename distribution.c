#include <stdio.h>
#include <time.h>
#include <stdlib.h> /* Needed for both */
#include <math.h> /* Needed for exponential*/

int* uniform_distribution(int min, int max) {
  double r = rand()/(1.0 + RAND_MAX);
  int range = max - min + 1;
	int r_scaled = (r * range) + min;

	return r_scaled;
}

int* exponential_distribution(int mean){
	double r = rand()/(1.0 + RAND_MAX);
	int num = -mean*log(r) + 1;
	return num;
}

int main(void){
	srand(time(NULL)); /* MUST INCLUDE THIS once FOR THE FUNCTIONS TO WORK PROPERLY */
	int i;
	int size = 20;

	int* uniform = uniform_distribution(1,10);
	int* exponential = exponential_distribution(5);

	printf("Uniform\n");
	for(i = 0; i < size; i++)
		printf("%d ", uniform[i]);

	printf("\n\nExponential\n");
	for(i = 0; i < size; i++)
		printf("%d ", exponential[i]);

	printf("\n");
	return 0;
}
