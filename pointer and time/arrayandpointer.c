// 自由的c语言 即使越界，照样正常输出
int *ptr1 = NULL; 
ptr1 = malloc(10 * sizeof(int));
for (int i = 0; i < 10; i++) {
	ptr1[i] = i;
}
for (int i = 0; i < 200; i++) {
	printf("%d ", ptr1[i]);
}

int **ptr2 = NULL;
ptr2 = malloc(10 * sizeof(int *)); // 这里还只是未分配的内存区域，需要再分配内存
// ptr2 只是一个数组 里面有10 个 int* 类型的指针，且每个指针都是指向未分配的地址
for (int i = 0; i < 10; i++) {
	ptr2[i] = malloc(10 * sizeof(int)); // 如此，ptr2[i]指向一个分配了10个int大小的内存区域
	for (int j = 0; j < 10; j++) {
		ptr2[i][j] = i * 10 + j;
	}
}

for (int i = 0; i < 10; i++) {
	for (int j = 0; j < 10; j++) {
		printf("%d ", ptr2[i][j]);
	}
}

int *ptr2[11] = {NULL}; // 和 int string[11] = {NULL}; 一样
for (int i = 0; i < 11; i++) {
	ptr2[i] = malloc(10 * sizeof(int));
	printf("%d : %p  selfbody\n",i, (void *)&ptr2[i]);
	printf("%d : %p  point to\n",i, (void *)ptr2[i]); // 即 ptr2[0]指向的地址就是 ptr2[0][0]的地址
	// 类推：  ptr2[3]指向的地址就是 ptr2[3][0]的地址
	for (int j = 0; j < 10; j++) {
		printf("%p\n", (void *)&ptr2[i][j]);
	}
}