#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void illustrate(int nums[], int b, int e, int cnt, int incre);
void array_before_insert(int [], int, int, int);
void array_after_insert(int [], int, int, int);
int incre_cmp(int a, int b);
void shell_sort(int nums[], int b, int e, int interval, int (*cmp)(int, int));
void print_array(int nums[], int b, int e);

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
	print_array(array, 0, num);

	shell_sort(array, 0, num, 3, incre_cmp);

	print_array(array, 0, num);
    return 0;
}

void
print_array(int nums[], int b, int e) {
    for (int i = b; i < e; i++)
	    printf("[%2d] ", nums[i]);
	printf("\n");
}

int 
incre_cmp(int a, int b) {
    if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}

void
shell_sort(int nums[], int b, int e, int interval, int (*cmp)(int, int)) {
    for (int incre = interval; incre > 0; incre /= 2)
	    for (int cnt = b; cnt < incre; cnt++)
		    for (int i = cnt + incre; i < e; i += incre) {
				int temp = nums[i];
			    for (int j = i - incre; j >= cnt; j -= incre) {
				    if (cmp(temp, nums[j]) < 0) {
					    nums[j + incre] = nums[j];
						if (j == cnt)
						    nums[j] = temp;
					} else {
					    nums[j + incre] = temp;
						break;
					}
				}
				illustrate(nums, b, e, cnt, incre);
			}
}

void
illustrate(int nums[], int b, int e, int cnt, int incre) {
    for (int i = b, j = 0; i < e; i++)
	    if (i == cnt + j * incre) {
		    printf("\033[1;31m[%d] \033[0m", nums[i]);
			j++;
		} else {
		    printf("[%d] ", nums[i]);
		}
		printf("\n");
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
