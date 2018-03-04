#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void array_before_insert(int [], int, int, int);
void array_after_insert(int [], int, int, int);
void insert_sort(int [], int);
void insert(int [], int, int);

int
main(void) {
	// random seed.
    srand((unsigned)time(NULL));
    const int num = 10;
    int array[num];

    /* Create a random integer array */
    for (int i = 0; i < num; i++)
        array[i] = rand() % 100;
    /* Print the previously generated array */
    for (int i = 0; i < num; i++)
        printf("[%d] ", array[i]);
    printf("\n");
    /* bubble sort */
    insert_sort(array, num);

    return 0;
}

void insert_sort(int nums[], int size) {
	for (int i = 1; i < size; i++) {
		printf("before insert:\n");
		array_before_insert(nums, size, i, 1);
		for (int j = 0; j < i; j++)
			if (nums[j] > nums[i]) {
				insert(nums, j, i);
				break;
			}
		printf("after insert:\n");
		array_after_insert(nums, size, i, 1);
	}
}

void insert(int nums[], int j, int i) {
	int temp = nums[i];
	for (int m = i; m > j; m--)
		nums[m] = nums[m - 1];
	nums[j] = temp;
}

void array_before_insert(int nums[], int size, 
	int to, int sec) {
	int i;
	for (i = 0; i < to; i++)
		printf("\033[1;32m[%d] \033[0m", nums[i]);
	printf("\033[1;31m[%d] \033[0m", nums[i++]);
	for ( ; i < size; i++)
		printf("[%d] ", nums[i]);
	printf("\n");
	sleep(sec);
}

void array_after_insert(int nums[], int size,
	int to, int sec) {
	int i;
	for (i = 0; i <= to; i++)
		printf("\033[1;32m[%d] \033[0m", nums[i]);
	for ( ; i < size; i++)
		printf("[%d] ", nums[i]);
	printf("\n");
	sleep(sec);
}