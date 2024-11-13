#include <stdlib.h>
#include <sys/time.h> /* for gettimeofday system call */
#include "lab.h"

/**
 * @brief Standard insertion sort that is faster than merge sort for small array's
 *
 * @param A The array to sort
 * @param p The starting index
 * @param r The ending index
 */
static void insertion_sort(int A[], int p, int r)
{
  int j;

  for (j = p + 1; j <= r; j++)
    {
      int key = A[j];
      int i = j - 1;
      while ((i > p - 1) && (A[i] > key))
        {
	  A[i + 1] = A[i];
	  i--;
        }
      A[i + 1] = key;
    }
}


void mergesort_s(int A[], int p, int r)
{
  if (r - p + 1 <=  INSERTION_SORT_THRESHOLD)
    {
      insertion_sort(A, p, r);
    }
  else
    {
      int q = (p + r) / 2;
      mergesort_s(A, p, q);
      mergesort_s(A, q + 1, r);
      merge_s(A, p, q, r);
    }

}

void merge_s(int A[], int p, int q, int r)
{
  int *B = (int *)malloc(sizeof(int) * (r - p + 1));

  int i = p;
  int j = q + 1;
  int k = 0;
  int l;

  /* as long as both lists have unexamined elements */
  /*  this loop keeps executing. */
  while ((i <= q) && (j <= r))
    {
      if (A[i] < A[j])
        {
	  B[k] = A[i];
	  i++;
        }
      else
        {
	  B[k] = A[j];
	  j++;
        }
      k++;
    }

  /* now only at most one list has unprocessed elements. */
  if (i <= q)
    {
      /* copy remaining elements from the first list */
      for (l = i; l <= q; l++)
        {
	  B[k] = A[l];
	  k++;
        }
    }
  else
    {
      /* copy remaining elements from the second list */
      for (l = j; l <= r; l++)
        {
	  B[k] = A[l];
	  k++;
        }
    }

  /* copy merged output from array B back to array A */
  k = 0;
  for (l = p; l <= r; l++)
    {
      A[l] = B[k];
      k++;
    }

  free(B);
}

void mergesort_mt(int *A, int n, int num_thread) {

  //multithread case:
  if (num_thread > 1) {
    struct parallel_args arg = {A, 0, n - 1, num_thread};

    pthread_t mt;

    pthread_create(&mt, NULL, parallel_mergesort, &arg);
    pthread_join(mt, NULL);  
  } 

  //single thread case:
  else {
    mergesort_s(A, 0, n - 1);
  }
}

void *parallel_mergesort(void *args) {
  struct parallel_args *p = (struct parallel_args *)args;

  int start = p->start;
  int end = p->end;
  int center = (start + end) / 2;

  if (start >= end) {
    return NULL;
  }

  //creating left and right arguments, cutting the number of available threads in half for each
  struct parallel_args left = {p->A, start, center, p->tid / 2};
  struct parallel_args right = {p->A, center +1, end, p->tid / 2};

  pthread_t left_t;
  pthread_t right_t;

  // keep sorting left side of the array
  if (left.tid > 1) {
    pthread_create(&left_t, NULL, parallel_mergesort, &left);
  } else {
    parallel_mergesort(&left); 
  }

  // keep sorting right side of the array
  if (right.tid > 1) {
    pthread_create(&right_t, NULL, parallel_mergesort, &right);
  } else {
    parallel_mergesort(&right); 
  }


  if (left.tid > 1) {pthread_join(left_t, NULL);}
  if (right.tid > 1) {pthread_join(right_t, NULL);}

  merge_s(p->A, start, center, end);

  return NULL;
}

double getMilliSeconds()
{
  struct timeval now;
  gettimeofday(&now, (struct timezone *)0);
  return (double)now.tv_sec * 1000.0 + now.tv_usec / 1000.0;
}