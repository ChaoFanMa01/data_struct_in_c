#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void swap(int *, int *);
void bubble_sort(int [], int);
void delay_show_array(int [], int, int, int);

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
    bubble_sort(array, num);

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int nums[], int size) {
    for (int i = size - 1; i > 0; i--)
        for (int j = 0; j < i; j++) {
            if (nums[j] > nums[j + 1])
                swap(nums + j, nums + j + 1);
            delay_show_array(nums, size, j, 1);
        }
}

void delay_show_array(int nums[], int size,
        int highlight, int sec) {
    int i;
    for (i = 0; i < highlight; i++)
        printf("[%d] ", nums[i]);
    printf("\033[1;32m[%d] \033[0m", nums[i++]);
    printf("\033[1;32m[%d] \033[0m", nums[i++]);
    for ( ; i < size; i++)
        printf("[%d] ", nums[i]);
    printf("\n");
    sleep(sec);
}