# SPr-CourseWork

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 10000

int a[10000]; 
int b[10000];

void RandomGenerator()
{	
	int n, N, i, j, rep;

	printf("Insert number of Numbers: ");
	scanf("%d", &rep);	
	printf("\n");

	printf("Declare end of the Numbers Diapason from '0' to '**': ");
	scanf("%d", &N);
	printf("\n");
	
	for(i = 0; i < rep; i++)
	{
		n = rand() % N;
		printf("%d  ",n);
		a[i] = n;
	}
	printf("\nEnd of generator!\n\n");
}

void merge(int low, int mid, int high) 
{
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) 
   {
      if(a[l1] <= a[l2])
         b[i] = a[l1++];
      else
         b[i] = a[l2++];
   }

   while(l1 <= mid)    
      b[i++] = a[l1++];

   while(l2 <= high)   
      b[i++] = a[l2++];

   for(i = low; i <= high; i++)
      a[i] = b[i];
}

typedef struct sort_range
{
   int low;
   int high;
} sort_range;

void *sort(void* __void_range) 
{
   int mid;
   pthread_t lefter;
   pthread_t righter;
 
   sort_range *range = (sort_range*)__void_range;

   if(range->low < range->high) 
   {
      mid = (range->low + range->high) / 2;

      sort_range leftrange;
      leftrange.low = range->low;
      leftrange.high = mid;
      
      sort_range rightrange;
      rightrange.low = mid + 1;
      rightrange.high = range->high;

      pthread_create(&lefter, NULL, sort, (void*)&leftrange);
      pthread_create(&righter, NULL, sort, (void*)&rightrange);
      pthread_join(lefter, NULL);
      pthread_join(righter, NULL);

      //  sort(low, mid);
      //  sort(mid+1, high);
      merge(range->low, mid, range->high);
   }
   else 
   { 
      return;
   }   
}

int main() 
{ 
   clock_t begin, end;
   double time_spent;
   
   int i, ticks;

   begin = clock();

   RandomGenerator();

   // printf("List before sorting\n");
   
   // for(i = 0; i <= max; i++)
   //    printf("%d ", a[i]);

   sort_range range;
   range.low = 0;
   range.high = max;
   sort((void*)&range);

   printf("\nList after sorting: \n");
   
   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);
  	printf("\n");

   end = clock();
   ticks = end - begin;
   printf("%d ticks\n", ticks);
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("%f seconds\n", time_spent);

   return 0;
  }
