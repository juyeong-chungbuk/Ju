# Ju
#include<stdio.h>

#define MAX_SIZE 100

float sum(float [],int);
float input[MAX_SIZE],answer;
int i;
void main()
{
	for(i=0;i<MAX_SIZE;i++)
		input[i]=i; //input의 i번째요소에 i를 저장

	printf("-----[신주영] [2019038044]-----\n");
	printf("address of input = %p\n",input); //input의 주소

	answer=sum(input, MAX_SIZE); //sum함수를 호출해 0부터 100까지의 합을 answer에 저장
	printf("The sum is: %f\n",answer); //0+1+...+100=4950 ->float형으로 4950.0000

}

float sum(float list[], int n)
{
	printf("value of list = %p\n",list); //list는 input배열을 가리키고 있으므로 input의 주소값을 가지고있음.
	printf("address of list = %p\n\n",&list); //list의 주소는 input의 주소와 다름.&list는 가리키는 곳말고 list자체의 주소값을 말함.

	int i;
	float tempsum=0; //합을 0으로 초기화
	for(i=0;i<MAX_SIZE;i++)
		tempsum+=list[i]; //tempsum에 input으로 받은 값을 반복문을 이용해 저장
	return tempsum; //0부터100까지 합을 리턴
}
