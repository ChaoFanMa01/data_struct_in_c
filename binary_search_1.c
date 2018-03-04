#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int binary_search(int [], int, int, int);
void swap(int *, int *);
void bubble_sort(int [], int);
void array_edge(int [], int, int, int, int, int);

int
main(void) {
	// random seed.
    srand((unsigned)time(NULL));
    const int num = 10;
    int array[num];
    int key, index;

    /* Create a random integer array */
    for (int i = 0; i < num; i++)
        array[i] = rand() % 100;
    /* bubble sort */
    bubble_sort(array, num);
    /* Print the previously generated array */
    for (int i = 0; i < num; i++)
        printf("[%d] ", array[i]);
    printf("\n");

    printf("Enter an integer to be searched: ");
    scanf("%d", &key);

    if ((index = binary_search(array, key, 0, num - 1)) < 0) {
    	printf("Cannot find this number\n");
    	return -1;
    }
    printf("key = %d, index = %d, value = %d\n", 
    	key, index, array[index]);
    return 0;
}

int binary_search(int nums[], int key, int b, int e) {
    int begin = b, end = e, mid = begin + (end - begin) / 2;

    for ( ; mid != begin && mid != end && nums[mid] != key; 
        mid = begin + (end - begin) / 2) {
        array_edge(nums, e - b, begin, end, mid, 2);
        if (key > nums[mid]) begin = mid + 1;
        else end = mid - 1;
    }

    array_edge(nums, e - b, begin, end, mid, 2);
    if (nums[mid] == key) return mid;

    return -1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int nums[], int size) {
    for (int i = size - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (nums[j] > nums[j + 1])
                swap(nums + j, nums + j + 1);
}

void array_edge(int nums[], int size, int start, 
	int end, int mid, int sec) {
	for (int i = 0; i < size; i++)
		if (i >= start && i <= end && i != mid)
			printf("\033[1;32m[%d] \033[0m", nums[i]);
		else if (i == mid)
			printf("\033[1;31m[%d] \033[0m", nums[i]);
		else
			printf("[%d] ", nums[i]);
	printf("\n");
	sleep(sec);
}