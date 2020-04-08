# Ju
#include <stdio.h>
#include <stdlib.h>

void main() {

	int list[5];
	int *plist[5]={NULL,}; //포인터배열의 처음요소를 NULL로 초기화

	plist[0]=(int *)malloc(sizeof(int)); //배열의 첫번째 요소를 int형으로 동적할당
	list[0]=1; //배열의 첫번째 요소를 1로 초기화
	list[1]=100; //배열의 두번째 요소를 100으로 초기화

	*plist[0]=200; //포인터배열의 처음요소가 가리키는 곳의 값을 200으로 설정

	printf("-----[신주영] [2019038044]-----\n");
	printf("value of list[0]        =%d\n",list[0]); //처음요소를 1로 초기화했음.
	printf("address of list[0]      =%p\n",&list[0]); //첫번째 요소의 주소값
	printf("value of list           =%p\n",list); //그냥 배열의 이름은 첫번째 요소의 주소값을 나타냄
	printf("address of list (&list) =%p\n",&list); //&[배열이름]은 첫번째 요소의 주소값을 나타냄

	printf("------------------------------------\n\n");
	printf("value of list[1]  =%d\n",list[1]); //두번째 요소를 100으로 초기화했음.
	printf("address of list[1]=%p\n",&list[1]); //두번째 요소의 주소값
	printf("value of *(list+1)=%d\n",*(list+1)); //배열의 처음에서 1증가한 두번째 요소를 가리키는 값
	printf("address of list+1 =%p\n",list+1); //배열의 두번째 요소의 주소

	printf("------------------------------------\n\n");

	printf("value of *plist[0] =%d\n",*plist[0]); //위에 plist가 가리키는 값을 200으로 설정해줬음.
	printf("&plist[0]          =%p\n",&plist[0]); //배열 포인터의 주소(포인터 주소임)
	printf("&plist             =%p\n",&plist); //&[배열이름]꼴은 배열의 첫번째 주소임
	printf("plist              =%p\n",plist); //배열이름만 출력하면 첫번째 주소값이 나옴.
	printf("plist[0]           =%p\n",plist[0]); //포인터 배열이므로 첫번째 요소의 주소값 출력
	printf("plist[1]           =%p\n",plist[1]); //두번째 요소의 주소값 출력
	printf("plist[2]           =%p\n",plist[2]); //세번째 요소의 주소값 출력
	printf("plist[3]           =%p\n",plist[3]); //네번째 요소의 주소값 출력
	printf("plist[4]           =%p\n",plist[4]); //다섯번째 요소의 주소값 출력

	free(plist[0]); //다 사용 후 해제해줘야 함.
}
