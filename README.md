# Ju
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int list[5];
	int *plist[5];

	list[0]=10; //배열의 첫번째 요소를 10으로 초기화
	list[1]=11; //두번째 요소를 11로 초기화

	plist[0]=(int *)malloc(sizeof(int)); //plist포인터배열의 첫번째 요소에 int형의 공간을 할당해줌.

	printf("-----[신주영] [2019038044]-----\n");
	printf("list[0] \t         =%d\n",list[0]); //첫번째 값=10
	printf("address of list \t =%p\n",list); //첫번째 요소의 주소값
	printf("address of list[0] \t =%p\n",&list[0]); //첫번째 요소의  주소값
	printf("address of list+0 \t =%p\n",list+0); //list+n=&list[n]
	printf("address of list+1 \t =%p\n",list+1); //int형 이므로 전 요소의 주소값에 +4씩 증가한다.
	printf("address of list+2 \t =%p\n",list+2);
	printf("address of list+3 \t =%p\n",list+3);
	printf("address of list+4 \t =%p\n",list+4);
	printf("address of list[4] \t =%p\n",&list[4]); //4번째 요소의 주소값

	free(plist[0]); //배열 공간 사용 후 해제해줘야 함.
}
