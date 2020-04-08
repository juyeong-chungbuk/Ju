# Ju
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int **x;

	printf("-----[신주영] [2019038044]-----\n");
	printf("sizeof(x) = %lu\n",sizeof(x)); //x는 주소를 저장하고 있기때문에 8byte
	printf("sizeof(*x) = %lu\n",sizeof(*x)); //*x도 주소를 저장하고 있기때문에 8byte
	printf("sizeof(**x) = %lu\n",sizeof(**x)); //**x는 두번 이동해서 간 값이 int형이기 때문에 4byte
}
