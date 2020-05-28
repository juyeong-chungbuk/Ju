/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
int recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("[-----[신주영] [2019038044]-----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		//case 'p': case 'P':
		//	printStack();
		//	break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


int recursiveInorder(Node* ptr) //수정 //재귀중위순회
{

	if (ptr != NULL) {
		recursiveInorder(ptr->left); //ptr의 왼쪽을 인자로 넘겨줌
		printf(" [%d] ", ptr->key); //중위 프린트
		recursiveInorder(ptr->right); //ptr의 오른쪽은 인자로 넘겨줌
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //반복중위순회
{
	int top = -1; //top 초기화

	while (1) {
		while (node != NULL) { //node가 NULL이 되기 전까지 반복
			push(node); //stack의 top에 node를 넣어줌
			node = node->left; //노드를 왼쪽으로 이동
		}
		node = pop(); //node가 NULL이 돼서 나오면 node에 pop한 곳의 주소를 넣어줌
		if (node == NULL) { //node가 NULL이라면
			break;	//반복문 빠져나감
		}
		printf(" %d ", node->key); //pop해온 node를 프린트
		node = node->right; //node를 오른쪽으로 넘김
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	int front = 0;
	int rear = 0; //큐의 front와 rear 초기화

	if (ptr == NULL) //ptr이 NULL이면
		return; //함수 종료
	enQueue(ptr); //ptr을 큐에 넣어두고

	while (1) {
		ptr = deQueue(); //디큐해서 ptr에 저장
		if (ptr) { //ptr이 NULL이 아니라면
			printf(" %d", ptr->key); //ptr값 프린트
			if (ptr->left) //ptr의 왼쪽이 NULL이아니면
				queue[rear++] = ptr->left; //인큐
			if (ptr->right) //ptr의 오른쪽이 NULL이 아니면
				queue[rear++] = ptr->right; //인큐
		}
		else
			break; //ptr이 NULL이면 break
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* root; //현재 노드의 부모노드를 가리키기 위함
	Node* node = head->left;

	while (node != NULL) {
		root = node; //node의 부모노드는 root
		if (key == node->key) //값을 발견하면 반복문 종료
			break;
		else if (key > node->key) //key가 현재노드보다 크면 오른쪽으로 이동
			node = node->right;
		else //key가 현재노드보다 작으면 왼쪽으로 이동
			node = node->left;
	}
	if (node->left == NULL && node->right == NULL) { //자식노드가 없을 경우
		if (root->left == node) //부모노드의 왼쪽이 key와 같다면 
			root->left = NULL; //왼쪽을 NULL로 만듦
		else if (root->right == node) //부모노드의 오른쪽이 key와 같다면 
			root->right = NULL; //오른쪽을 NULL로 만듦
	}
	else if (node->left != NULL && node->right != NULL) { //양쪽에 자식노드가 있을 경우
		if (root->left == node) { //부모노드의 왼쪽에 있는 노드라면
			root->left = node->right; //부모노드의 왼쪽을 node의 자식노드 중 값이 더 큰 오른쪽 노드와 연결
			node->right = node->left; //부모노드와 연결된 node의 오른쪽 노드의 자식노드가 node의 왼쪽노드가 되도록 연결
		}
		else if (root->right == node) { //부모노드의 오른쪽에 있는 노드라면
			root->right = node->left; //부모노드의 오른쪽을 node의 자식노드 중 값이 더 작은 왼쪽 노드와 연결
			node->left = node->right; //부모노드와 연결된 node의 왼쪽 노드의 자식노드가 node의 오른쪽노드가 되도록 연결
		}
		free(node); //메모리 해제
	}
	else { //하나의 자식노드만 있을 경우
		if (node->left == NULL) //오른쪽 노드만 있을경우
		{
			if (root->right == node) //node가 부모노드의 오른쪽에 있다면
				root->right = node->right; //부모노드의 오른쪽을 node의 오른쪽 노드와 연결
			else
				root->left = node->right; //부모노드의 왼쪽을 node의 오른쪽과 연결
		}
		else { //왼쪽 노드만 있을경우
			if (root->left == node) //node가 부모노드의 왼쪽에 있다면
				root->left = node->left; //부모노드의 왼쪽을 node의 왼쪽과 연결
			else
				root->right = node->left; //부모노드의 오른쪽을 node의 왼쪽과 연결
		}
		free(node); //메모리 해제
	}
	return 1;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

/* for stack */ //후입선출

Node* pop()
{
	Node* node = NULL;
	if (top == -1) //스택이 비었다면
		return node; //NULL반환

	node = stack[top]; //스택의 탑을 node에 저장
	top--; //탑을 한칸 앞으로
	return node; //스택의 탑에 있던 값 반환
}

void push(Node* aNode)
{
	if (top >= MAX_STACK_SIZE - 1) //스택이 꽉찼다면
		return; //함수종료

	top++; //top값 플러스
	stack[top] = aNode; //받은 aNode를 스택의 탑에 저장
}

/* for queue */ //선입선출

Node* deQueue()
{
	Node* node = NULL;

	node = queue[front]; //node에 큐의 front 값을 저장
	front++; //front플러스
	return node; //node 반환
}

void enQueue(Node* aNode)
{
	if (front == rear) //큐가 비었다면 
		return; //함수 종료

	rear++; //rear 플러스
	queue[rear] = aNode; //받은 aNode를 큐에 저장
}

