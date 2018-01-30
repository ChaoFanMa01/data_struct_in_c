#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCALE      100
#define LINE_LEN   20
#define SLEEP_LEN  1

void insertion_sort(int [], int);
void rand_ints(int [], int);
void print_ints(int [], int);
void print_line();
void print_msg(const char *);
void exit_msg(const char *);
void delay_print_n_nums(int [], int, int, int);
void hightlight_single_int(int [], int, int);

int main(int argc, char *argv[]) {
    int size;
    srand(time(NULL));

    if (argc != 2) 
        exit_msg("arguments misconfigure.");
    size = atoi(argv[1]);
    printf("%d\n", size);

    int nums[size];
    rand_ints(nums, size);
    print_ints(nums, size);
    print_line();
    insertion_sort(nums, size);
    print_msg("sorted integers: ");
    print_ints(nums, size);

    return 0;
}

void insertion_sort(int nums[], int size) {
    for (int i = 0, temp; i < size - 1; i++) {
        hightlight_single_int(nums, size, i);
        for (int j = i + 1; j > 0; j--){
            if (nums[j] < nums[j - 1]) {
                temp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] =temp;
            } else {
                break;
            }
            delay_print_n_nums(nums, size, j - 1, j);
        }
    }
}

void rand_ints(int nums[], int size) {
    for (int i = 0; i < size; i++)
        nums[i] = rand() % SCALE;
}

void print_ints(int nums[], int size) {
    for (int i = 0; i < size; i++)
        printf("%5d ", nums[i]);
    printf("\n");
}

void print_line() {
    for (int i = 0; i < LINE_LEN; i++) 
        printf("-");
    printf("\n");
}

void print_msg(const char *msg) {
    printf("%s\n", msg);
}

void exit_msg(const char *msg) {
    printf("%s\n", msg);
    exit(-1);
}

void delay_print_n_nums(int nums[], int size, int b, int e) {
    for (int i = 0; i < size; i++)
        if (i < b || i > e)
            printf("%5d ", nums[i]);
        else
            printf("\033[31m %5d\033[0m", nums[i]);
    printf("\n");
    sleep(SLEEP_LEN);
}

void hightlight_single_int(int nums[], int size, int num) {
    for (int i = 0; i < size; i++)
        if (i == num)
            printf("\033[37m %5d\033[0m", nums[i]);
        else 
            printf("%5d ", nums[i]);
    printf("\n");
}