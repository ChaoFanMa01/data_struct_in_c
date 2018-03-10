#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "binary_heap.h"

void heapsort(int nums[], int b, int e);
void print_array(int nums[], int b, int e);
void delay_print_array(int nums[], int b, int e, int p, int sec);

int
main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));
    int num;

	if (argc != 2)
	    error_dump("parameter error");
	num = atoi(argv[1]);

	int array[num];
	for (size_type i = 0; i < num; i++)
	    array[i] = rand() % 100;

    print_array(array, 0, num - 1);
	heapsort(array, 0, num - 1);
	print_array(array, 0, num - 1);

	return 0;
}

void
heapsort(int nums[], int b, int e) {
    pb_heap pbh;
	size_type hld;
	value_type temp;

	if ((pbh = array_create(nums, b, e)) == NULL)
	    return;
	hld = pbh->heap_length;
	build_max_heap(pbh);
	for (size_type i = pbh->heap_length - 1; i > 0; i--) {
		temp = pbh->array[i];
		pbh->array[i] = pbh->array[0];
		pbh->array[0] = temp;
		pbh->heap_length--;
		delay_print_array(pbh->array, 0, pbh->array_size - 1, i, 2);
		build_max_heap(pbh);
	}

	for (size_type i = 0; i <= e; i++)
	    nums[i] = pbh->array[i];
}

void
print_array(int nums[], int b, int e) {
    for (int i = b; i <= e; i++)
	    printf("[%d] ", nums[i]);
	printf("\n");
}

void
delay_print_array(int nums[], int b, int e, int p, int sec) {
    for (int i = b; i <= e; i++)
	    if (i == p)
		    printf("\033[1;31m[%d] \033[0m", nums[i]);
		else if (i < p)
		    printf("\033[1;37m[%d] \033[0m", nums[i]);
		else
		    printf("[%d] ", nums[i]);
	printf("\n");
	sleep(sec);
}
