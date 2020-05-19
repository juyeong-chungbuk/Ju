/*
 * Binary Search Tree #1
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
	int data;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */ //중위순회법
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */ //전위 순회법
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */ //후위순회법
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("[-----[신주영] [2019038044]-----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->data, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->data, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
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
	(*h)->data = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) //중위순회
{
	if (ptr == NULL) //ptr이 NULL이 되면
		return 1; //1을 반환하여 값을 프린트 하게 됨
	inorderTraversal(ptr->left); //재귀함수 이용하여 ptr을 왼쪽으로 넘겨주고
	printf("%5d", ptr->data); 
	inorderTraversal(ptr->right); //재귀함수를 이용하여 ptr을 오른쪽으로 넘겨줌
}

void preorderTraversal(Node* ptr) //전위순회
{
	if (ptr == NULL) //ptr이 NULL이 되면
		return 0; //1을 반환하여 값을 프린트 하게 됨
	printf("%5d", ptr->data); //처음에 프린트
	preorderTraversal(ptr->left); //재귀함수 이용하여 ptr을 왼쪽으로 넘겨주고
	preorderTraversal(ptr->right); //재귀함수를 이용하여 ptr을 오른쪽으로 넘겨줌
}

void postorderTraversal(Node* ptr) //후위순회
{
	if (ptr == NULL) //ptr이 NULL이 되면
		return 0; //1을 반환하여 값을 프린트 하게 됨
	postorderTraversal(ptr->left); //재귀함수 이용하여 ptr을 왼쪽으로 넘겨주고
	postorderTraversal(ptr->right); //재귀함수를 이용하여 ptr을 오른쪽으로 넘겨줌
	printf("%5d", ptr->data); //마지막 프린트
}


int insert(Node* head, int key)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* node = head->left;
	Node* root;
	temp->data = key;
	temp->left = NULL;
	temp->right = NULL;
	if (head->left==NULL) { //노드가 하나만 있을 경우
		head->left = temp; //헤드의 왼쪽에 노드 삽입
		return 1;
	}

	while (node != NULL) { //node가 NULL이 되면 종료
		root = node; //node의 부모노드를 가리킴
		if (node->data > key) //node의 값이 key보다 크면
			node = node->left; //node를 왼쪽으로 이동
		else
			node = node->right; //node를 오른쪽으로 이동
	}
		if (root->data > key) { //부모노드의 값이 key보다 크면
			root->left = temp; //부모노드의 완쪽에 삽입
			return 1;
		}
		else {
			root->right = temp; //부모노드의 오른쪽에 삽입
			return 1;
		}
}

int deleteLeafNode(Node* head, int key)
{
	Node* root; //현재 노드의 부모노드를 가리키기 위함
	Node* node = head->left;

	while (node!=NULL) {
		root = node; //node의 부모노드는 root
		if (key == node->data) //값을 발견하면 반복문 종료
			break;
		else if (key > node->data) //key가 현재노드보다 크면 오른쪽으로 이동
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
			if (root->right==node) //node가 부모노드의 오른쪽에 있다면
				root->right = node->right; //부모노드의 오른쪽을 node의 오른쪽 노드와 연결
			else
				root->left = node->right; //부모노드의 왼쪽을 node의 오른쪽과 연결
		}
		else { //왼쪽 노드만 있을경우
			if (root->left==node) //node가 부모노드의 왼쪽에 있다면
				root->left = node->left; //부모노드의 왼쪽을 node의 왼쪽과 연결
			else
				root->right = node->left; //부모노드의 오른쪽을 node의 왼쪽과 연결
		}
		free(node); //메모리 해제
	}
}

Node* searchRecursive(Node* ptr, int key) //재귀적 탐색
{
		if (ptr->data == key) //같은 값이 발견되면
			return ptr; //해당 노드 주소 반환
		else if (ptr->data > key) //탐색할 key보다 큰값이 나오면
			searchRecursive(ptr->left, key); //재귀함수 이용, 매개변수 ptr이 왼쪽으로 이동된 주소를 받게해줌
		else
			searchRecursive(ptr->right, key); //재귀함수 이용, 매개변수 ptr이 오른쪽으로 이동된 주소를 받게해줌
		
		if (ptr == NULL) //ptr이 NULL이 되면
			return NULL; //값을 찾을 수 없으므로 NULL반환

}

Node* searchIterative(Node* head, int key) //반복탐색
{
	Node* node = head->left; //값이 있는 첫노드를 가리킴
	while (node!=NULL) { //node가 NULL이되기 전까지 반복
		if (key == node->data) //같은 값이 발견되면
			return node; //그 node의 주소값 반환
		else if (key > node->data) //탐색할 key보다 작은 값이 나오면
			node = node->right; //노드를 오른쪽으로 이동
		else //탐색할 key보다 큰 값이 나오면
			node = node->left; //노드를 왼쪽으로 이동
	}
	return NULL; //값을 찾을 수 없을 경우 NULL반환
}


int freeBST(Node* head)
{
	Node* root; //현재노드의 부모노드를 가리킬 포인터
	Node* node = head;

	if (node->left != NULL) { //node의 왼쪽이 NULL이 아닐 경우
		root = node; //부모노드 가리키도록
		freeBST(node->left); //node의 왼쪽이 NULL이 될때까지 호출됨
		root->left = NULL; 
		root->right = NULL; //부모노드의 다음을 NULL로 만들어줘서 현재node삭제
	}

	if (node->right != NULL) { //node의 오른쪽이 NULL이 아닐경우
		root = node; //부모노드 가리키도록
		freeBST(node->right); //node의 오른쪽이 NULL이 될때까지 호출됨
		root->left = NULL;
		root->right = NULL;	//부모노드의 다음을 NULL로 만들어줘서 현재node삭제
	}
	free(node); //node해제
	return 1;
}
