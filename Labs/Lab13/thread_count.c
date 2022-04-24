/*
 * Use pthread to count number of even elements in an array
 */

#include <stdio.h>
#include <pthread.h>    // for threads
#include <stdlib.h>     // for rand(3)
#include <time.h>       // for time(3)

int NUM_THREADS = 5;    // number of threads
int TOTAL_NUMS = 100;   // total number of elements in array

// Struct to pass parameters to the worker thread
struct param_t {
   unsigned int * array;
   int            from;       // start index
   int            len;        
   int            count;      // result
};

// declrations
void gen_array(unsigned int * array, int len);
void print_array(unsigned int * array, int len);
int merge_result(struct param_t *p, int len);
void* count_even(void *param);

int main(int argc, char *argv[]) 
{
   if (argc == 2){
	  TOTAL_NUMS = atoi(argv[1]);
   } else if (argc == 3) {
	  TOTAL_NUMS = atoi(argv[1]);
	  NUM_THREADS = atoi(argv[2]);
   }

   pthread_t * worker;      // worker threads, this is an array
   struct param_t * param;  // parameter, array, from, len
   unsigned int array[TOTAL_NUMS];
   int length = TOTAL_NUMS/NUM_THREADS;

   gen_array(array, TOTAL_NUMS);
   
   worker = malloc(sizeof(pthread_t)*NUM_THREADS);
   param = malloc(sizeof(struct param_t)*NUM_THREADS);

   for (int i = 0; i < NUM_THREADS; i ++) {
	  param[i].array = array;
	  param[i].from = i*length;
	  param[i].len = length;
	  
	  int ret_v = pthread_create(&(worker[i]), NULL, count_even, (void*)&(param[i]));
	  if (ret_v) {
		 printf("ERROR; return code from pthread_create() is %d\n", ret_v);
		 exit(-1);
	  }
   }

   for (int i = 0; i < NUM_THREADS; i ++) {  // join the threads
	  pthread_join(worker[i], NULL);
   }

   printf("Number of elements %d, number of threads %d\n", TOTAL_NUMS, NUM_THREADS);
   printf("Total number of evens is %d\n", merge_result(param, NUM_THREADS));

   pthread_exit(NULL);

   return 0;
}

void gen_array(unsigned int *array, int len) 
{
   srand(time(NULL));
   for (int i = 0; i < len; i ++) {
     array[i] = rand() % 500; // some random values 0-499
   }
}

void * count_even(void *param) 
{  
   struct param_t *p = (struct param_t *)param;
   p->count = 0;
   
   for (int i = p->from; i < p->from + p->len; i ++) {
	  if (p->array[i] % 2 == 0) // even
		 p->count ++;
   }
   return NULL;
}

int merge_result(struct param_t *p, int len) 
{   
   int total = 0;
   for (int i = 0; i < len; i ++)
	  total += p[i].count;

   return total;
}

void print_array(unsigned int * array, int len) 
{
   for (int i = 0; i < len; i ++) {
	  printf("%5d ", array[i]);
	  if ((i + 1) % 10 == 0)
		 printf("\n");
   }
}
