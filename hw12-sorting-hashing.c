//Sorting & Hashing

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 13	// prime number
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE

int initialize(int **a); 
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a); // 선택정렬
int insertionSort(int *a); // 삽입정렬
int bubbleSort(int *a);    // 버블정렬
int shellSort(int *a);     // 셸정렬
int quickSort(int *a, int n);  // 퀵정렬, recursive function으로 구현
int hashCode(int key);         // hash code generator, key % MAX_HASH_TABLE_SIZE
int hashing(int *a, int **ht); // array a에 대한 hash table을 만든다.
int search(int *ht, int key);  // hash table에서 key를 찾아 hash table의 index return


int main()
{
	char command; // 변수 command
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
    printf("[----- [Kim Yun Seo] [2020021016] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기

		switch(command) {
		case 'z': case 'Z': // command 값이 z 또는  일 경우
			initialize(&array);
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			freeArray(array);
			break;
		case 's': case 'S': // command 값이 s 또는 S 일 경우
			selectionSort(array);
			break;
		case 'i': case 'I': // command 값이 i 또는 I 일 경우
			insertionSort(array);
			break;
		case 'b': case 'B': // command 값이 b 또는 B 일 경우
			bubbleSort(array);
			break;
		case 'l': case 'L': // command 값이 l 또는 L 일 경우
			shellSort(array);
			break;
		case 'k': case 'K': // command 값이 k 또는 K 일 경우
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);
			break;

		case 'h': case 'H': // command 값이 h 또는 H 일 경우
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': // command 값이 e 또는 E 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': // command 값이 p 또는 P 일 경우
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행
	return 1;
}

// 배열 초기화 
int initialize(int** a)
{
	int *temp = NULL;
	// array가 NULL인 경우 메모리 할당
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // temp에 int type으로 주소 받기
		*a = temp;  // 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else
		temp = *a;

	// 랜덤값을 배열의 값으로 저장
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

// 메모리 해제 
int freeArray(int *a)
{
	if(a != NULL) // a가 NULL이 아닐 경우
		free(a); // 메모리 해제
	return 0;
}

// 배열 출력
void printArray(int *a)
{
	if (a == NULL) { // a가 NULL일 경우
		printf("nothing to print.\n"); 
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

// 선택 정렬
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	// 주어진 리스트 중 최소값을 찾아서 맨 앞에 위치한 값과 교체
	// 맨 처음 위치를 뺸 나머지 리스트를 같은 방법으로 교체
	for (i = 0; i < MAX_ARRAY_SIZE; i++){
		minindex = i; 
		min = a[i]; // 최소값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++){
			if (min > a[j]){ // 기준이 되는 최솟값보다 작을 경우
				min = a[j];
				minindex = j;
			}}
		a[minindex] = a[i];
		a[i] = min; // 최소값과 맨 앞의 값 교체
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}

// 삽입 정렬
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열출력
	// 새로운 레코드를 i개의 정렬된 레코드 리스트에 끼워 넣어 
	// 크기가 i+1인 정렬된 결과 레코드 리스트 생성
	for(i = 1; i < MAX_ARRAY_SIZE; i++){
		t = a[i]; 
		j = i;
		while (a[j-1] > t && j > 0){
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열출력
	return 0;
}

// 버블 정렬
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	// 첫번째 원소부터 인접 원소끼리 비교하여 자리 교환
	for(i = 0; i < MAX_ARRAY_SIZE; i++){ // 첫번째 원소부터 마지막 원소까지 반복
		for (j = 0; j < MAX_ARRAY_SIZE; j++){
			if (a[j-1] > a[j]){ // 앞의 원소값이 뒤의 원소값보다 클 경우
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t; // 자리 교환
			}}}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}

// 셸 정렬
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	// 부분집합의 기준이 되는 간격을 매개변수 h에 저장
	// 한 단계가 수행할 때마다 h값 감소
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2){
		for (i = 0; i < h; i++){
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h){
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v){
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}}}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 출력
	return 0;
}

// 퀵 정렬
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	// 기준값을 중심으로 왼쪽 부분집합과 오른쪽 부분집합으로 분할하여 정렬
	// 기준값: 피폿
	if (n > 1){
		v = a[n-1];
		i = -1;
		j = n - 1;
		while(1){
			while(a[++i] < v); // 피봇보다 작은 key값 찾기 (왼쪽 -> 오른쪽)
			while(a[--j] > v); // 피봇보다 큰 key값 찾기 (오른쪽 -> 왼쪽)
			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}
	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // (MAX_HASH_TABLE_SIZE = MAX_ARRAY_SIZE = 13)
}

int hashing(int *a, int **ht)
{
	// array a에 대한 hash table 만들기
	int *hashtable = NULL;

	// hash table이 NULL인 경우 메모리 할당
	if(*ht == NULL) { // ht가 NULL일 경우
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // hashtable에 int type으로 주소 받기
		*ht = hashtable; // 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else {
		hashtable = *ht; // hash table이 NULL이 아닌경우, table 재활용, reset to -1
	}
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	// for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
	//	printf("hashtable[%d] = %d\n", i, hashtable[i]);

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		// printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		if (hashtable[hashcode] == -1){
			hashtable[hashcode] = key;
		} else 	{
			index = hashcode;
			while(hashtable[index] != -1){
				index = (++index) % MAX_HASH_TABLE_SIZE;
				// printf("index = %d\n", index);
			} hashtable[index] = key;
		}} 
	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);
	if(ht[index] == key) // ht[index] 값이 key 값과 같을 경우
		return index; 
	while(ht[++index] != key) // ht[index] 값이 key 값과 같지 않을 경우
		index = index % MAX_HASH_TABLE_SIZE; // (MAX_HASH_TABLE_SIZE = MAX_ARRAY_SIZE = 13)
	return index;
}
