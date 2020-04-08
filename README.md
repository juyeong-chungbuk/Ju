# Ju
#include<stdio.h>

void print1(int *ptr, int rows);

int main()
{
	int one[]={0, 1, 2, 3, 4};

	printf("-----[신주영] [2019038044]-----\n");
	printf("one      = %p\n",one); //3개 다 one의 첫번째 요소의 주소값이 출력
	printf("&one     = %p\n",&one);
	printf("&one[0]  = %p\n",&one[0]);
	printf("\n");

	print1(&one[0], 5); //one의 첫번째 요소의 주소값을 포인터배열 ptr로 전달/5는 배열의 크기

	return 0;
}

void print1(int *ptr, int rows)
{
	int i;
	printf("Address \t Contents\n");
	for(i=0;i<rows;i++)
		printf("%p \t  %5d\n",ptr+i,*(ptr+i)); //ptr+i :int형이기 때문에 4바이트 단위로 주소가 이동, *(ptr+i)=ptr[i]
	printf("\n");
}
