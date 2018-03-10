#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"


void delay_print_array(int nums[], int b, int e, int nb, int ne, int p, int sec);
void print_array(int nums[], int b, int e);
int decre_order_cmp(int a, int b);
int incre_order_cmp(int a, int b);
void quicksort(int nums[], int b, int e, int (*cmp)(int, int));
int partition(int nums[], int b, int e, int (*cmp)(int, int));
void swap(int nums[], int a, int b);

int
main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));
    int num;
    if (argc != 3)
	    error_dump("parameter error");
	num = atoi(argv[1]);

	int array[num];
	for (int i = 0; i < num; i++)
	    array[i] = rand() % 100;
	
	print_array(array, 0, num - 1);
    
	if (argv[2][0] == 'i')
    	quicksort(array, 0, num - 1, incre_order_cmp);
	else if (argv[2][0] == 'd')
	    quicksort(array, 0, num - 1, decre_order_cmp);
	else
	    error_dump("parameter error");

	print_array(array, 0, num - 1);

	 return 0;
}

void
print_array(int nums[], int b, int e) {
    for (int i = b; i <= e; i++)
	    printf("[%d] ", nums[i]);
	printf("\n");
}

void
delay_print_array(int nums[], int b, int e, int nb, int ne, 
                  int p, int sec) {
    for (int i = b; i <= e; i++)
	    if (i == p)
		    printf("\033[1;31m[%d] \033[0m", nums[i]);
		else if (i >= nb && i < p)
		    printf("\033[1;37m[%d] \033[0m", nums[i]);
		else if (i <= ne && i > p)
		    printf("\033[1;37m[%d] \033[0m", nums[i]);
		else
		    printf("[%d] ", nums[i]);
	printf("\n");
	sleep(sec);
}

int 
decre_order_cmp(int a, int b) {
    if (a < b) return 1;
	else if (a == b) return 0;
	else return -1;
}

int
incre_order_cmp(int a, int b) {
    if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}

void
quicksort(int nums[], int b, int e, int (*cmp)(int, int)) {
    int pivot;
    if (b < e) {
	    pivot = partition(nums, b, e, cmp);
		delay_print_array(nums, 0, 9, b, e, pivot, 2);
		quicksort(nums, b, pivot - 1, cmp);
		quicksort(nums, pivot + 1, e, cmp);
	}
}

int
partition(int nums[], int b, int e, int (*cmp)(int, int)) {
    int pivot = b - 1, temp;
	for (int i = b; i <= e - 1; i++)
	    if (cmp(nums[i], nums[e]) < 0)
		    swap(nums, i, ++pivot);
	swap(nums, e, ++pivot);
	return pivot;
}

void
swap(int nums[], int a, int b) {
    int temp;
	temp = nums[a];
	nums[a] = nums[b];
	nums[b] = temp;
}
