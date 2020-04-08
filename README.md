# Ju
#include<stdio.h>

struct student1{ //struct 구조체 선언 1번째 방법
	char lastName;
	int studentId;
	char grade;
};

typedef struct{ //2번째 방법
	char lastName;
	int studentId;
	char grade;
}student2; //끝에 이름붙힘.

int main()
{
	student1 st1 = {'A',100,'A'}; //각각 lastName,studentId,grade를 나타냄

	printf("----[신주영] [2019038044]----\n");
	printf("st1.lastName  = %c\n",st1.lastName); //A출력
	printf("st1.studentId = %d\n",st1.studentId); //100출력
	printf("st1.grade     = %c\n",st1.grade); //A출력

	student2 st2 = {'B',200,'B'}; //각각 lastName,studentId,grade를 나타냄

	printf("\nst2.lastName  = %c\n",st2.lastName); //B출력
	printf("st2.studentId = %d\n",st2.studentId); //200출력
	printf("st2.grade     = %c\n",st2.grade); //B출력

	student2 st3; //student형 st3변수 선언

	st3=st2; //st2의 값을 st3에 저장해줌

	printf("\nst3.lastName  = %c\n",st3.lastName); //st2의 각 요소들이 st3에 그대로 복사됐기 때문에 st2와 같은 값이 출력
	printf("st3.studentId = %d\n",st3.studentId);
	printf("st3.grade     = %c\n",st3.grade);
	if(st3.lastName==st2.lastName) //st3==st2로 비교 X.student형이기 때문에 st3.last이런식으로 비교해줘야함.
		printf("equal\n");
	else
		printf("not equal\n");

	return 0;
}
