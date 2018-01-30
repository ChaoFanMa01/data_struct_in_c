#include <stdio.h>

#define print_color(color, num) ({\
    printf("|\033[%s%3d\033[0m|\n", color, num);\
})

int main(void){
    char cmd[10] = "31m";

	print_color(cmd, 5);
	return 0;
}
