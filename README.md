# Ju
#include<stdio.h>

struct student{
	char lastName[13]; //4byte짜리가 3개이고 나머지 1byte가 필요하므로 나머지공간은 padding해서 총 16byte
	int studentId; //4byte
	short grade; //short형이 2byte인데 나머지 공간을 padding해서 총 4byte
};

int main()
{
	struct student pst;

	printf("-----[신주영] [2019038044]-----\n");
	printf("size of student = %d\n",sizeof(struct student)); //16byte + 4byte + 4byte = 24byte
	printf("size of int = %d\n",sizeof(int)); //int는 4byte
	printf("size of short = %d\n",sizeof(short)); //short는 2byte

	return 0;
}
