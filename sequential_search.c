#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void array_show(int [], int, int, int);
int sequential_search(int [], int, int);

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
    /* Print the previously generated array */
    for (int i = 0; i < num; i++)
        printf("[%d] ", array[i]);
    printf("\n");

    printf("Enter an integer to be searched: ");
    scanf("%d", &key);

    if ((index = sequential_search(array, key, num)) < 0) {
    	printf("Cannot find this number\n");
    	return -1;
    }
    printf("key = %d, index = %d, value = %d\n", 
    	key, index, array[index]);

    return 0;
}

int sequential_search(int nums[], int key, int size) {
	for (int i = 0; i < size; i++) {
		array_show(nums, size, i, 1);
		if (nums[i] == key) return i;
	}
	return -1;
}

void array_show(int nums[], int size, int index, int sec) {
	for (int i = 0; i < size; i++)
		if (i == index)
			printf("\033[1;32m[%d] \033[0m", nums[i]);
		else
			printf("[%d] ", nums[i]);
	printf("\n");
	sleep(sec);
}