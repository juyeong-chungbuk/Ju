/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int data;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->data = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = h->first; //헤드를 가리킬 포인터
	listNode* pre=(listNode*)malloc(sizeof(*pre)); //이전값을 가리킬 포인터
	listNode* temp = (listNode*)malloc(sizeof(*temp)); //들어온 값을 가리킬 포인터
	temp->data = key;
	temp->link = NULL;
	pre = NULL;

		if (h->first == NULL)  //노드가 없을 경우
			h->first = temp; //들어온 값을 헤드로 지정

		else { //노드가 있을 경우
			if (node->data > temp->data) { //처음값이 넣을 key보다 클 경우
				temp->link = node; 
				h->first = temp; //key를 맨앞에 삽입
			}
			else { //두번째 값부터 탐색
					while (node != NULL && node->data < temp->data) { //key보다 큰 값이 나오면
						pre = node; //이전을 노드로 지정해주고
						node = node->link; //노드를 다음으로 넘김
					}
					if (node != NULL) { //리스트의 중간에 삽입
						temp->link = node; //temp를 현재node에 연결해주고
						pre->link = temp; //이전노드와 temp를 연결
					}
					else { //끝에 삽입
						pre->link = temp; //끝값을 temp와 연결
					}
			}
		}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 맨 끝에 추가
 */
int insertLast(headNode* h, int key) {

	listNode* temp = (listNode*)malloc(sizeof(*temp));
	listNode* node = h->first; //첫번째 노드를 가리키도록.

	temp->data = key; //temp의 data에다가 key깂 넣어줌

	if (h->first != NULL) { //노드가 있음
		while (node->link != NULL) {
			node = node->link; //node의다음이 NULL이 될때까지 node를 다음으로 넘김.
		}
		node->link = temp; //맨끝에 key값 추가
	}
	else { //아직 노드 x(처음에 노드 삽입하는거임)
		node = temp;
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	h->first = h->first->link;
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { 

	listNode* temp= (listNode*)malloc(sizeof(*temp));
	listNode* pre= (listNode*)malloc(sizeof(*pre));
	listNode* node = h->first; //헤드를 가리키도록 설정
	temp->data = key;

	if (temp->data == node->data) { //key가 첫번째 노드일 경우

		h->first = node->link; //node의 다음을 헤드로 지정
		free(node); //메모리 해제
	}

	else { //key가 중간이나 마지막 노드일 경우
		while (node != NULL) {
			pre = node;
			node = node->link; //node를 다음으로 넘김
			if (node->data == temp->data) { //node의 값이 key와 같음
				if (node->link != NULL) { //중간노드일 경우
					pre = node;
					node = node->link;
					free(node); //메모리 해제
				}
				else { //마지막 노드일 경우
					pre->link = node->link;; //pre의 다음을 node의 다음으로 연결하고
					free(node); //메모리 해제
				}
			}
		}
	}
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* node = h->first;
	listNode* pre= (listNode*)malloc(sizeof(*pre));

	if (node == NULL) //노드가 없음
		return 0;

	else {
		pre = h->first;
		while (node->link != NULL) { //노드의 다음이 NULL이 될때까지 반복
			pre = node;
			node = node->link;
		}
		free(node); //노드 해제해주고
		pre->link = NULL;	//pre의 다음을 NULL로 만든다.
		return 0;
	}
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* head = h->first;
	listNode* middle;
	listNode* trail;
	middle = NULL;
	trail = NULL;

	while (head != NULL) { //헤드가 NULL이 될때까지 반복
		trail = middle; //middle를 잠시 trail에 넣어준 후
		middle = head; //middle에 헤드값을 넣음
		head = head->link; //헤드를 다음으로 옮기고
		middle->link = trail; //잠시 넣어뒀던 middle을 다음으로 넘김
	}
	h->first = middle; //middle을 헤드로 만들어줌
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->data);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

