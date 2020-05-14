/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int data;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("[-----[신주영] [2019038044]-----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->data = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	listNode* node = NULL;
	while (node != NULL) {
		node = h; //node에 헤드를 넣어주고
		h = h->rlink; //헤드를 다음으로 옮긴다
		free(node); //node에 넣어준 노드 해제
	}
	free(h); //마지막 노드 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->data);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->data, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* temp = (listNode*)malloc(sizeof(*temp));
	temp->data = key;
	temp->rlink = NULL;
	temp->llink = NULL;

	if (h->data == -9999) { //노드가 없을 경우
		h->rlink->data = key; //헤드의 다음의 값에 key를 넣어줌
		h->llink = temp; //헤드노드의 다음을 새로운 노드로 연결
		h->rlink = temp; //헤드노드의 이전도 새로운 노드로 연결
		temp->llink = h; //새로운 노드의 이전을 헤드와 연결
		temp->rlink = h; //새로운노드의 다음을 헤드로 연결
		return 0;
	}

	/*노드가 존재할 경우*/
	temp->llink = h->llink; //첫노드의 이전에 새로운 노드를 연결
	temp->rlink = h; //새로운 노드의 다음을 첫노드와 연결
	temp->llink->rlink = temp;
	temp->rlink->llink = temp;  /*마지막 노드를 새로운 노드와 연결해서 원형으로 만듦*/

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* node = h->llink;

	if (h->data == -9999) { //노드가 존재하지 않는 경우
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}

	node->llink->rlink = node->rlink; 
	node->rlink->llink = node->llink; /*마지막에서 두번째 노드를 첫노드와 연결하여 다시 원형으로 만듦*/
	free(node); //마지막 노드 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->data = key;
	temp->rlink = temp->llink = NULL;
	listNode* node = h;

	if (h->data == -9999) { //노드가 존재하지 않을 경우
		h->rlink->data = key;
		h->llink = temp;
		h->rlink = temp;
		temp->llink = h;
		temp->rlink = h;
		return 1;
	}

	/*노드가 존재할 경우*/
	temp->llink = h;  //새로운 노드의 이전을 h와 연결
	temp->rlink = h->rlink; //마지막 노드와 새로운 노드를 연결
	temp->llink->rlink = temp; //h와 새로운 노드를 연결
	temp->rlink->llink = temp; //마지막 노드와 새로운 노드 연결

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h->data == -9999) { //노드가 존재하지 않을 경우
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}

	listNode* head = h->rlink;

	head->llink->rlink = head->rlink; 
	head->rlink->llink = head->llink; /*첫번째에서 두번째 노드와 마지막 노드를 다시 연결시켜 원형으로 만듦*/
	free(head); //처음노드 해제

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* node = h->rlink;
	if (h->data == -9999) { //노드가 존재하지 않을 경우
		printf("노드가 없습니다.\n");
		return 0;
	}
	listNode* trail;
	listNode* middle = h; //첫노드를 가리도록 설정

	while (node != h) { //node가 첫노드를 가리키기 전까지 반복
		trail = middle; //trail은 middle을 따라가도록 설정
		middle = node; //middle는 node에 따라감
		node = node->rlink; //node를 다음으로 넘겨주고
		middle->rlink = trail; //middle의 다음은 middle이 다시 들어오도록
	}
	h = h->rlink; //마지막 노드가 헤드가 될 수 있게함
	node->rlink = middle; //첫노드의 다음은 middle이 가리키는 곳이 됨
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->data = key;
	temp->rlink = temp->llink = NULL;
	listNode* node = h->rlink;

	if (h ->data== -9999) { //노드가 존재하지 않을 경우
		h->rlink->data = key;
		h->llink = temp;
		h->rlink = temp;
		temp->llink = h;
		temp->rlink = h;
		return 0;
	}
	
	while (node->rlink != h) { //node의 다음이 h가 되기 전까지 반복
		if (node->data>=key) { //만약 들어온 key보다 큰값이 나타나면
			if (node->llink == h) //그 노드가 헤드일 경우
				insertFirst(h, key);
			else { //중간 노드일 경우
				temp->rlink = node; //새로운 노드의 다음을 node와 연결
				temp->llink = node->llink; //새로운 노드의 이전이 현재node의 이전을 가리키도록 설정
				node->llink->rlink = temp; //node의 이전노드가 가리키는 다음 녿가 새로운 노드가 되도록 설정
			}
			return 0;
		} 
		node = node->rlink; //노드를 다음으로 넘겨줌
	}
	if (node->data >= key) { //1.마지막에서 두번째에 삽입하는 경우 2.첫노드에 삽입하는 경우에 해당하는 조건
		temp->rlink = node;
		temp->llink = node->llink;
		node->llink->rlink = temp; 
	}
	else //현재 node의 값보다 key가 클 경우
		insertLast(h, key); //마지막에 새로운 노드 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->data == -9999) { //노드가 존재하지 않을 경우
		printf("삭제할 노드가 없습니다.\n");
		return 1;
	}

	listNode* node = h->rlink;

	while (node->rlink != h) { //node가 마지막 노드가 될때까지
		if (node->data == key) { //node의 값과 key가 일치할 경우

			if (node->llink == h) { //node의 이전이 헤드노드라면
				deleteFirst(h); //첫노드 삭제 함수 호출
			}

			else { //중간노드라면
				node->llink->rlink = node->rlink; //현재node의 이전노드가 가리키는 다음노드를 node의 다음으로 잇는다.
				node->rlink->llink = node->llink; //현재node의 다음노드가 가리키는 이전노드를 node의 이전으로 잇는다.
				free(node);
			}
			return 1;
		}
		node = node->rlink; //node를 다음으로 넘겨줌
	}
	
	if (node->data == key)
		deleteLast(h, key); //마지막 노드삭제 함수 호출
	else
		printf("해당 값을 찾을 수 없습니다. = %d\n", key);
	return 1;
}
