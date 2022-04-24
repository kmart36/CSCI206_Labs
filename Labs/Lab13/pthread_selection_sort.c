#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
/*
 * Students need to fill in the TODO places
 */
struct param_t {
  double * array;
  int from;
  int len;

};
// swap two locations (i,j) in the array
void swap(double arr[], int i, int j) 
{
	double tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void merge(double arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;          // number on left
  int n2 = r - m;            // number on right

  /* create temp arrays */
  double *L = malloc(sizeof(double) * n1);
  double *R = malloc(sizeof(double) * n2);

  /* Copy data to temp arrays L[] and R[] */
  memcpy(L, arr + l, n1 * sizeof(double));
  memcpy(R, arr + m + 1, n2 * sizeof(double));

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while ((i < n1) && (j < n2))
	{
	  if (L[i] <= R[j])
		arr[k++] = L[i++];
	  else
		arr[k++] = R[j++];
	}

  /* Copy the remaining elements of L[], if there    are any */
  while (i < n1) arr[k++] = L[i++];
  /* Copy the remaining elements of R[], if there are any */
  while (j < n2) arr[k++] = R[j++];

  free(L);
  free(R);
}

void merge_block(double * arr, int nums, int threads) {
  int block_size = nums/threads;
  int l, r, m;
  while (block_size <= nums/2) {
	for (int i = 0; i < nums; i += block_size * 2) {
	  l = i; 
	  r = i + block_size * 2 - 1;
	  m = i + block_size - 1;
	  merge(arr, l, m, r);
	}
	block_size *= 2;
  }
}

void * selection_sort(void *param) 
{
	/*
	TODO write selection sort.

	Step 1: Set MIN to location 0 in the array
	Step 2: Search the minimum element in the unsorted part of array [MIN..len-1]
	Step 3: Swap with value at location MIN
	Step 4: Increment MIN to point to next element
	Step 5: Repeat until MIN points to the end of the array
	*/
  struct param_t *p = (struct param_t *)param;
  int min_index;
  for (int i = p->from; i < p->from + p->len - 1; i++) {
	min_index = i; 
	for (int j = i + 1; j < p->from + p->len; j++) {
	  if (p->array[j] < p->array[min_index])
		min_index = j;
 	}
	swap(p->array, min_index, i);
  }
  return NULL;
}

/* UTILITY FUNCTIONS */
// print an array of size n
void print_array(double * a, int n)
{
	int i;
	if(n <= 16){
		// print the whole thing
		printf("[");
		for (i=0; i<n-1; i++){
			printf("%f, ", a[i]);
		}
		printf("%f]\n", a[i]);
	} else {
		// truncate the printout
		printf("[");
		// print first 8
		for (i=0; i<8; i++){	
			printf("%f, ", a[i]);
		}
		printf("..., ");
		// print last 8
		for (i=n-9; i < n-1; i++){
			printf("%f, ", a[i]);
		}
	  printf("%f]\n", a[i]);
	}
}

// pseudo random array filler
void fill_array(int seed, double * a, int n){
	if (n == 16){
		// constant data if n == 16 (do not change this!)
		const double d[16] = {4,4,4,4,7,7,7,7,1,1,1,1,5,5,5,5};
		memcpy(a, d, sizeof(double)*16);
		return;
	}
	srand(seed);
	while(n--){
		// rand returns an int between 0 and RAND_MAX, this maps it to [0...1]
		*a++ = (double)rand() / (double)RAND_MAX;
	}
}

// check if an array is sorted, return 1 if true, 0 if not.
int is_sorted(double arr[], int n)
{
	int i;
	// check for any out of order elements
	for (i=0; i<n-1; i++){
		if (arr[i] > arr[i+1])
			return 0;
	}
	return 1;
}

/* Driver program to test above functions */
int main(int argc, char *argv[])  
{
	int NUM_THREADS;              // how many threads to use
	int NUM_VALS;                 // how many values to sum
	double * a = NULL;            // the array of values

	switch (argc){
		case 1:   // no arguments, use default values
			NUM_VALS = 16;
			NUM_THREADS = 1;
			break;
		case 2:   // just one argument, NUM_VALS
			NUM_VALS = atof(argv[1]);
			NUM_THREADS = 1;
			break;
		default:  // command line sets both values
			NUM_VALS = atof(argv[1]);
			NUM_THREADS = atoi(argv[2]);
	}
	printf("%s using %d threads on array of %d elements.\n",
		argv[0],
		NUM_THREADS,
		NUM_VALS);
	if (NUM_VALS % NUM_THREADS != 0){
		printf("ERROR: array size must be evenly divisible by the number of threads!\n");
		exit(1);
	}
	pthread_t * worker;      // worker threads, this is an array                                                                                 
	struct param_t * param;  // parameter, array, from, len                                                                                      
	unsigned int array[NUM_VALS];
	int length = NUM_VALS/NUM_THREADS;

	worker = malloc(sizeof(pthread_t)*NUM_THREADS);
	param = malloc(sizeof(struct param_t)*NUM_THREADS);

	a = malloc(sizeof(double)*NUM_VALS);  // allocate memory for array
	fill_array(7891, a, NUM_VALS);        // initialize with random values
	
	printf("Generated array ");
	print_array(a, NUM_VALS);

	for (int i = 0; i < NUM_THREADS; i ++) {
      param[i].array = a;
      param[i].from = i*length;
      param[i].len = length;

      int ret_v = pthread_create(&(worker[i]), NULL, selection_sort, (void*)&(param[i]));
      if (ret_v) {
		printf("ERROR; return code from pthread_create() is %d\n", ret_v);
		exit(-1);
      }
	}

	for (int i = 0; i < NUM_THREADS; i++) {
	  pthread_join(worker[i], NULL);
	}

	printf("Sorting. . .\n");
	merge_block(a, NUM_VALS, NUM_THREADS);

	printf("Sorted array is ");
	print_array(a, NUM_VALS);

	printf("Is sorted: %s\n",
	is_sorted(a, NUM_VALS) ? "YES": "NO -- FAILED");

  free(a);

  return 0;
}
