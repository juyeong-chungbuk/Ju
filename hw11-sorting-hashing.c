/*
* hw5-sorting.c
*
*  Created on: May 22, 2019
*
*  Homework 5: Sorting & Hashing
*  Department of Computer Science at Chungbuk National University
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do {
		printf("[-----[신주영] [2019038044]-----]\n");
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
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if (a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) //선택정렬: 각 i값에서 최대 배열사이즈까지 비교하여 크기순으로 맞추기
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //i번째 값보다 작은 수가 나올 경우
			{
				min = a[j]; //최소값을 바꿔줌
				minindex = j; //최소인데스가 j가 됨
			}
		}
		a[minindex] = a[i]; //i번째 값과 최소값의 위치 체인지
		a[i] = min; //i번째 일때 나온 최종 최소값을 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //a의 주소를 print함수의 인자로 넣어줌
	return 0;
}

int insertionSort(int *a) //삽입정렬:j값을 감소시켜가면서 큰값이 나오면 뒤로 옮겨주고 더 이상 큰값이 안나올 경우 그때의 j번째에 반복문 처음에 비교했던 a[i]를 넣어줌
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j - 1] > t && j > 0) //i번째 값보다 i-1의 값이 더 크고, j가 0보다 클때
		{
			a[j] = a[j - 1]; //큰값을 뒤로 보내고
			j--; //j를 하나 감소
		}
		a[j] = t; //j번째 인덱스에 a[i]값 대입해서 크기 순서대로 맞추기
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //버블정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j - 1] > a[j]) //앞에값이 더 클경우
			{
				t = a[j - 1]; //t에 j-1번째 임시로 값 넣어주고
				a[j - 1] = a[j]; //j-1번째에 작은값 대입
				a[j] = t; //j번째에는 임시로 넣었던 t대입
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a) //셸정렬: h만큼 떨어진 곳과 비교하여 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) //h를 1/2씩 줄여가면서 비교
	{
		for (i = 0; i < h; i++) //h 간격에 있는 요소들을 정렬
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //v에 j번째 값을 넣어줌
				k = j; //k에 인덱스 j를 넣어줌
				while (k > h - 1 && a[k - h] > v) //h만큼 떨어져 있는 인덱스의 값과 비교하여 뒤인덱스의 값이 더 작은경우 반복
				{
					a[k] = a[k - h]; //h만큼 떨어진 곳에 값이 더 큰 a[k-h]를 대입
					k -= h; //h만큼 빼서
				}
				a[k] = v; //k번째에 h만큼 뒤에 있는 값을 대입하거나 while문을 안들어갔을 경우는 값 그대로 유지
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //퀵정렬: 기준값을 중심으로 왼쪽, 오른쪽으로 분할하여 정렬
{ 
	int v, t;
	int i, j;

	if (n > 1) //배열의 크기가 1보다 크면
	{
		v = a[n - 1]; //v에 마지막 원소 대입
		i = -1;
		j = n - 1; //마지막 인덱스를 기준점으로 함

		while (1) //무한반복
		{
			while (a[++i] < v); //i를 증가시키면서 마지막 값보다 작은 값 찾기
			while (a[--j] > v); //마지막인덱스부터 줄여나가면서 마지막 값보다 큰 값 찾기

			if (i >= j) break; //i가 j보다 크거나 같아지면 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t; //오른쪽 부분집합과 왼쪽 부분집합을 체인지하는 코드
		}
		t = a[i]; 
		a[i] = a[n - 1];
		a[n - 1] = t; //기준점의 값을 j위치로 바꿈

		quickSort(a, i); //
		quickSort(a + i + 1, n - i - 1);
	}


	return 0;
}

int hashCode(int key) {
	return key % MAX_HASH_TABLE_SIZE; //
}

int hashing(int *a, int **ht) //해싱함수 ht는 해시테이블 가리킴
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //해시테이블이 모두 -1이 되도록함

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key; //해시테이블에 배열의 값을 저장
		}
		else {

			index = hashcode;

			while (hashtable[index] != -1) //해시테이블이 -1이될때까지 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //나머지를 대입시키면서 비교해봄
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //-1이 발견되면 key대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //해시코드함수에 입력한 key값을 인수로 넣어줘서 반환받은 값을 인덱스에 key대입

	if (ht[index] == key) //key값과 해당 인덱스의 값이 같을 경우
		return index; //해당 인덱스 반환

	while (ht[++index] != key) //key값을 발견할때까지 반복
	{
		index = index % MAX_HASH_TABLE_SIZE; //나머지 값을 대입시켜가면서
	}
	return index; //값 발견해서 나올경우 인덱스 반환
}
