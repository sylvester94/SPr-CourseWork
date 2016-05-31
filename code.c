#include <stdio.h>
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
	printf("Result: ");

	for(i = 0; i < rep; i++)
	{
		n = rand() % N;
		a[i] = n;
	}
	printf("\nEnd of generator!\n\n");
}

void merge(int low, int mid, int high) 
{
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
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

void sort(int low, int high) 
{
   int mid;
   
   if(low < high) {
      mid = (low + high) / 2;
      sort(low, mid);
      sort(mid+1, high);
      merge(low, mid, high);
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

   printf("List before sorting\n");
   
   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);

   sort(0, max);

   printf("\nList after sorting\n");
   
   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);
  	printf("\n");

  	end = clock();
   ticks = end - begin;
   printf("%d ticks\n", ticks);
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("%f seconds\n", time_spent);
  }
