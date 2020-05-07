/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int data;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("[----[2019038044] [신주영]----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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

int initialize(headNode** h) { //headnode의 주소값을 받기위해 이중포인터 매개변수 이용
	if (*h != NULL) //헤드가 비어있지 않다면
		freeList(*h); //해제해줌

	*h = (headNode*)malloc(sizeof(headNode)); //headNode크기만큼 동적할당 해준다
	(*h)->first = NULL; //헤드를 NULL로 초기화
}

int freeList(headNode* h) { //모든 노드를 해제
	listNode* node = h;

	listNode* prev = NULL;
	while (node != NULL) {
		prev = node; //현재 노드를 이전값으로 해준 후
		node = node->rlink; //노드를 다음으로 넘김
		free(prev); //이전노드였던 것을 해제
	}
	free(h); //헤드도 해제
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}


/**
 * list의 마지막에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { 

	listNode* node = h->first;
	listNode* temp = (listNode*)malloc(sizeof(*temp));
	temp->data = key;
	temp->rlink = NULL;
	temp->llink = NULL;

	if (h->first == NULL) { //리스트가 비었을 경우
		h->first = temp; //temp를 헤드로 지정
		node->rlink = NULL; //헤드의 다음을 NULL로
		node->llink = NULL; //헤드의 이전을 NULL로
		return 0;
	}

		while (node->rlink != NULL) { //노드의 다음이 NULL이 되기 전까지 반복
			node = node->rlink;
		}
		node->rlink = temp; //node의 다음을 새로운 노드로
		temp->llink = node; //새로운 노드의  이전을 node로
		return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(*node));
	listNode* temp = (listNode*)malloc(sizeof(*temp));
	node = h->first;
	temp->data = key;

	temp->rlink = node; //노드의 다음을 현재node가 가리는 헤드로 지정
	node->llink = temp; //현재node의 이전을 temp로 지정
	h->first = temp; //temp를 헤드로 지정

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //끝
	
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->data = key;
	temp->rlink = NULL;
	temp->llink = NULL;
	

	if (h->first == NULL) { //리스트가 비었을 경우
		h->first = temp; //temp를 헤드로 지정
		temp->rlink = NULL; //temp의 다음과 이전을 NULL로 초기화
		temp->llink = NULL; 
		return 0;
	}
	listNode* node = h->first;

		while (node != NULL) { //node가 NULL이 될때까지 반복
				if (node->data >= key) { //node보다 앞에 집어넣음
					if (node == h->first) { //node가 헤드일 경우
						h->first = temp; //temp를 헤드로 지정
						temp->rlink = node; //temp의 다음을 현재node가 가리키는 곳으로 지정
						node->llink = temp; //node가 가리키는 곳의 이전을 temp로 지정
					}
					else { //node가 중간노드이거나 마지막 노드일 경우
						temp->llink = node->llink; //현재node가 가리키는 곳의 이전을 temp의 이전으로 만들어줌
						temp->rlink = node; //temp의 다음을 현재node가 가리키는 곳으로 지정
						node->llink->rlink = temp; //현재node노드가 가리키는 이전이 가리키는 다음을 temp로 지정
						node->llink = temp; //node의 이전을 temp로 지정
					} //화살표 4개 완성
					return 0;
				}
				
			node = node->rlink; //노드를 다음으로 넘겨줌
		}
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* node = h->first;
	if (h->first == NULL) { //리스트가 비었을 경우
		printf("리스트가 비어있습니다.\n");
		return 0;
	}

	if (node->rlink == NULL) { //node가 헤드일 경우
		h->first = NULL; //헤드를 NULL로 만들어줌
		free(node); //노드 해제
		return 0;
	}
		while (node->rlink != NULL) { //node가 마지막노드를 가리킬때까지 반복
			node = node->rlink;
		}
		node->llink->rlink = NULL; //node를 가리키는 화살표 제거
		node->llink = NULL; //node가 가리키는 이전을 향하는 화살표 제거
		free(node); //마지막 노드 삭제
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { 
	listNode* node = h->first;
	
	if (h->first == NULL) { //리스트가 비었을 경우
		printf("리스트가 비어있습니다.\n");
		return 0;
	}
		
	h->first = node->rlink; //두번째 노드를 헤드로 지정
	node->rlink->llink = NULL; //두번째 노드가 가리키는 이전을 NULL로 만든다
	node->rlink = NULL; //노드의 다음을 NULL로 만든다
	free(node); //헤드 삭제
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { 
	listNode* node = h->first;
	listNode* temp = (listNode*)malloc(sizeof(*temp));
	temp->data = key;

	if (h->first == NULL) { //리스트가 비었을 경우
		printf("리스트가 비어있습니다.\n");
		return 0;
	}

		while (node->data != key) { //node의 값이 key와 같아질 때까지 반복
			node = node->rlink;
		} //같아져서 while문 나오면

		if (node->llink == NULL) { //첫번째 노드일 경우
			node->rlink->llink = NULL; //첫번째 노드를 가리키는 화살표 제거
			h->first = node->rlink; //두번째노드를 헤드로 지정
			node->rlink = NULL; //첫번째 노드가 가리키는 화살표 제거
			free(node); //첫번째 노드 삭제
		}
		else if(node->rlink==NULL) { //마지막 노드일 경우
			node->llink->rlink = NULL; //미자막 노드를 가리키는 화살표 제거
			node->llink = NULL; //마지막 노드가가리키는 화살표 제거
			free(node); //마지막 노드 삭제
		}

		else { //중간노드일 경우
			node->llink->rlink = node->rlink; //node의 이전이 가리키는 화살표를 현재 node의 다음으로 향하게
			node->rlink->llink = node->llink; //node의 다음이 가리키는 화살표를 현재 node의 이전으로 향하게
			free(node); //해당 중간노드 삭제
		}
	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* head = h->first; //헤드를 가리키는 포인터
	listNode* middle = NULL; //역순을 만들어 낼 포인터
	listNode* tail = NULL; //임시저장 포인터

	while (head != NULL) {
		tail = middle; //middle값을 임시저장
		middle = head; //middle은 헤드를 따라감
		head = head->rlink; //헤드를 다음으로 넘겨줌
		middle->rlink = tail; //middle을 임시저장한 tail과 연결
	}
	h->first = middle; //마지막노드를 헤드로 옮김
	return 0;
}
