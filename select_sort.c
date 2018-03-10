#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"

void delay_print_array(int nums[], int b, int e, int p, int sec);
void print_array(int nums[], int b, int e);
int get_min(int nums[], int b, int e);
void swap(int nums[], int a, int b);
void select_sort(int nums[], int b, int e);

int
main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));
    int num;
	if (argc != 2)
	    error_dump("parameter error");
	num = atoi(argv[1]);

	int array[num];
	for (int i = 0; i < num; i++)
	    array[i] = rand() % 100;

	print_array(array, 0, num - 1);

	select_sort(array, 0, num - 1);

	print_array(array, 0, num - 1);

	return 0;
}

void
delay_print_array(int nums[], int b, int e, int p, int sec) {
    for (int i = b; i <= e; i++)
	    if (i == p)
		    printf("\033[1;31m[%d] \033[0m", nums[i]);
		else  if (i < p)
		    printf("\033[1;37m[%d] \033[0m", nums[i]);
		else
		    printf("[%d] ", nums[i]);
	sleep(sec);
	printf("\n");
}

void
print_array(int nums[], int b, int e) {
    for (int i = b; i <= e; i++)
	    printf("[%d] ", nums[i]);
	printf("\n");
}

int
get_min(int nums[], int b, int e) {
    int min = b;
    for (int i = b + 1; i <= e; i++)
	    if (nums[min] > nums[i])
		    min = i;
	return min;
}

void
swap(int nums[], int a, int b) {
    int temp = nums[a];
	nums[a] = nums[b];
	nums[b] = temp;
}

void
select_sort(int nums[], int b, int e) {
    int min;
    for (int i = b; i < e; i++) {
	    min = get_min(nums, i, e);
		if (i != min)
		    swap(nums, i, min);
		delay_print_array(nums, b, e, i, 2);
	}
}
