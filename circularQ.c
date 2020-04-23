#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐의 최대크기

typedef char element;
typedef struct QueueType *queuePointer;

typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I': //큐에 원소를 삽입
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': //큐에서 원소를 제거
			deQueue(cQ, &data);
			break;
		case 'p': case 'P': //큐의 원소들 출력
			printQ(cQ);
			break;
		case 'b': case 'B': //디버깅
			debugQ(cQ);
			break;
		case 'q': case 'Q': //종료
			break;
		default: //다시입력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //원형큐를 동적할당
	cQ->front = 0; //초기화
	cQ->rear = 0;
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = "); //큐의 원소를 입력
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ) //원형큐가 비었는지 체크
{
	if (cQ->front == cQ->rear) //front와rear가 같으면 비었음
		return 1;
	else
		return 0;
}

/* complete the function */
int isFull(QueueType *cQ) //원형큐가 가득 찼는지 비교
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == (cQ->front)) //rear+1과front가 같으면 가득참
		return 1;
	else
		return 0;
}

/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if (isFull(cQ))
		printf("큐가 가득차있습니다.\n");
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear를 뒤로 한칸 이동
		cQ->queue[cQ->rear] = item; //데이터를 큐에 삽입
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ))
		printf("큐가 비어있습니다.\n");
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front를 뒤로 한칸 이동
		*item=cQ->queue[cQ->front]; //처음값을 제거함
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; 
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; 

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]); //front 원소부터 rear-1원소까지 출력함
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
