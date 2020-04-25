#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/*stack내에서 우선순위, '('가 가장낮음*/
typedef enum {
	lparen = 0, //왼쪽 괄호
	rparen = 9, //오른쪽 괄호
	times = 7, //곱셈
	divide = 6, //나눗셈
	plus = 5, //덧셈
	minus = 4, //뺄셈
	operand = 1 //숫자
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; //중위표기법 식 들어감
char postfixExp[MAX_EXPRESSION_SIZE]; //후위 표기법 식 들어감
char postfixStack[MAX_STACK_SIZE]; //연산자만 들어가는 스택
int evalStack[MAX_STACK_SIZE]; //계산을 위해 필요한 스택(int형), 숫자만 계산해서 하나씩 쌓이는 스택

int postfixStackTop = -1; //postfixStack용 top, 스택에 몇개 들어갔는지
int evalStackTop = -1;  //evalStack용 top

int evalResult = 0; //최종 계산해서 나온 결과값

void postfixPush(char x)  //연산자만 스택에 넣음
{
	postfixStack[++postfixStackTop] = x; //해당 연산자를 스택에 삽입
}

char postfixPop() //연산자를 스택에서 제거
{
	char x;
	if (postfixStackTop == -1) //연산자스택에 아무것도 없을 경우
		return '\0';
	else {
		x = postfixStack[postfixStackTop--]; //top에 있던 연산자를 x에 대입후, top--
	}
	return x; //x연산자 리턴
}

void evalPush(int x) //스택에 정수 삽입
{
	evalStack[++evalStackTop] = x; //받은 정수x를 evalStack의 top에 삽입
}

int evalPop() //스택에서 연산자 두개 빼낼때 사용하는 함수
{
	if (evalStackTop == -1) //evalStack이 빈 경우
		return -1;
	else 
		return evalStack[evalStackTop--];
}

void getInfix() //중위 표기법으로 식 입력받음
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen; //0
	case ')': return rparen; //9
	case '+': return plus; //5
	case '-': return minus; //4
	case '/': return divide; //6
	case '*': return times; //7
	default: return operand; //1
	}
}

precedence getPriority(char x) //기호에 해당하는 숫자로 우선순위 판단
{
	return getToken(x);
}

/*문자 하나를 전달 받아 postfixExp에 추가*/
void charCat(char* c) //문자가 들어올때 이용할 함수
{
	if (postfixExp == '\0') //후위 표기법식 스택에 아무것도 없을 경우
		strncpy(postfixExp, c, 1); //c를 postfixExp로 복사
	else
		strncat(postfixExp, c, 1); //c를 postfixExp뒤에 이어붙임
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */

void toPostfix() //중위식을 후위식으로 바꿈(바꾸기만함, 계산x)
{
	char *exp = infixExp; //infixExp의 문자 하나씩을 읽기위한 포인터
	char x; //문자 하나를 임시로 저장하기 위한 변수
	char str; //Pop한 문자를 임시저장할 변수

/*exp를 증가시켜가면서 문자를 읽고 postfix로 변경*/
	while (*exp != '\0') //infixExp가 NULL이 되기 전까지 반복
	{
		x = getToken(*exp);

		if (x == 0) { // '('기호일경우
			postfixPush(*exp); //'('를 postfixStack에 삽입
			exp++;
		}

		else if (x == 9) { // ')'기호일 경우
			while (postfixStack[postfixStackTop] != '(') { // '('나오기전까지의 연산자만 스택에서 pop하여 후위표기법 배열에 삽입
				str = postfixPop();
				charCat(&str);
			} 
			postfixPop(); // '('를 삭제
			exp++;
		}

		else if (x >= 4 && x <= 7) { //연산자일 경우

			if (postfixStack[postfixStackTop] != '\0') { //스택이 비었을때

				if (getPriority(*exp) < getPriority(postfixStack[postfixStackTop]))
				{ //현재들어온 연산자보다 스택에 있는 연산자가 우선순위가 높은 경우
					str = postfixPop(); //스택에서 우선순위 높은것을 빼내어 후위표기법 배열에 삽입
					charCat(&str); //postfixExp에 삽입
					postfixPush(*exp); //현재 들어온 우선순위낮은 연산자를 스택에 넣어줌
					exp++;
				}
				else {
					postfixPush(*exp); //스택에 연산자 삽입
					exp++;
				}
			}

			else {
				postfixPush(*exp); //현재 연산자를 스택에 삽입
				exp++;
			}
			
		}

		else if (x == 1) { //숫자일 경우
			charCat(exp); //postfixExp배열에 숫자를 이어붙임
			exp++;
		}

		else
			exp++;
	}
	
	while (postfixStackTop > -1) { //스택이 비지 않을때까지
		str = postfixPop();
		charCat(&str);
		postfixStackTop--;
	}

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //중위표기법으로 나타낸 식 출력
	printf("postExp =  %s\n", postfixExp); //후위표기법으로 나타낸 식 출력
	printf("eval result = %d\n", evalResult); //계산된 최종 결과값 출력

	printf("postfixStack : "); //스택에 남아있는 연산자 출력
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // '* /' 이런식으로 출력

	printf("\n");
}

void reset() //스택 초기화
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() //postfixExp, evalSack을 이용하여 계산
{
	char *token =postfixExp;
	int op1, op2;

		while (*token != '\0') { //해당 토큰이 NULL이 아니면 루프반복

			if (getToken(*token) == operand) {  //토큰이 숫자일 경우
				evalPush(*token); //evalStack배열에 숫자삽입
				token++;
			}

			else {  //토큰이 문자일 경우
				op1 = evalPop(); //evalStack에서 상위2개 숫자를 팝
				op2 = evalPop();

				if (*token == '+') {
					evalPush(op1 + op2); //token이 '+' 일 경우
					printf("%d ", evalStack[evalStackTop]);
					token++;
				}
				else if (*token == '-') {
					evalPush(op1 - op2); //token이 '-' 일 경우
					printf("%d ", evalStack[evalStackTop]);
					token++;
				}
				else if (*token == '*') {
					evalPush(op1 * op2); //token이 '*' 일 경우
					printf("%d ", evalStack[evalStackTop]);
					token++;
				}
				else if (*token == '/') {
					evalPush(op1 / op2); //token이 '/' 일 경우
					printf("%d ", evalStack[evalStackTop]);
					token++;
				}
				else
					break;
			}
			
		}
	evalResult = evalStack[0]; //최종 결과값
}

int main()
{
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix(); //중위표기법으로 식 입력
			break;
		case 'p': case 'P':
			toPostfix(); //후위 표기법으로 변환
			break;
		case 'e': case 'E':
			evaluation(); //결과값 계산
			break;
		case 'd': case 'D':
			debug(); //결과값 출력
			break;
		case 'r': case 'R':
			reset(); //스택 초기화
			break;
		case 'q': case 'Q':
			break; //종료
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //다시입력
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;
}
