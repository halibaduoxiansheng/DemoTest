#include <stdio.h>
#include <stdlib.h>



int main()
{
    int *ptr;
	const static int ptr_size = 12;
	ptr = (int*)calloc(ptr_size, sizeof(int));
	if (ptr == NULL) {
		printf("memory failed\n");
		return 1;
	}

	for (int i = 0; i < ptr_size; i++) {
		ptr[i] = i;
		printf("%d ", ptr[i]);
	}
}