//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{					//_listnode는 개발자들에게만 표시되는 구조체 이름		//typedef는 기존 자료형에 새로운 이름을 붙이는 것. struct는 구조체
	int item;								
	struct _listnode *next;					//listnode의 주소를 가리키는 포인터를 next라는 이름으로 부르겠다는 과정
} ListNode;			// You should not change the definition of ListNode			//여기 ListNode는 위에 있는 _listnode와 같음. ListNode는 사용자가 실제로 사용할 이름

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);		//정수형 함수 선언. 변수는 linkedlist주소와 정수형 item

void printList(LinkedList *ll);		//void: 함수가 끝나도 값을 안 돌려줌. 동작만 실행함
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);		//ListNode를 찾는 포인터
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)		//오름차순으로 삽입하는 함수
{
	/* add your code here */
	//개수 세는 변수 0에서 시작
	int index = 0;
	ListNode *cur;
//ll 포인터 자체가 NULL인 경우 실패했다 반환
	if (ll == NULL)
		return -1;
	//순회를 head부터 시작
	cur = ll->head;
	//노드값이 새로 넣을 값보다 작을 동안 반복/ 더 이상 노드가 없다면 같이 멈춤
	while (cur != NULL && cur->item < item) {
	//하나 지나갈 때마다 변수 1증가. 다음 노드로 이동
		index++;
		cur = cur->next;
	}
	//이미 같은 값이 존재하면 삽입하지 않고 -1 반환
	if (cur != NULL && cur->item == item)
		return -1;
	//insertNode가 0과 같은 경우 인덱스 반환/ 실패시 -1반환
	if (insertNode(ll, index, item) == 0)
		return index;
	else
		return -1;

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){		//리스트 출력

	ListNode *cur;
if (ll == NULL)
		return;			//ll 포인터가 NULL인 경우 아무것도 안 하고 함수를 끝냄
	cur = ll->head;		//head에 cur를 위치

	if (cur == NULL)
		printf("Empty");		//cur(head)가 비어있다면 Empty를 출력
	while (cur != NULL)			//cur가 안 비어있다면 아래 반복문을 실행
	{
		printf("%d ", cur->item);		//cur가 가리키고 있는 item을 출력
		cur = cur->next;				//head에서 next로 이동
	}
	printf("\n");			//줄바꿈
}


void removeAllItems(LinkedList *ll)		//모든 아이템 제거
{
	ListNode *cur = ll->head;		//포인터 cur가 가리키는 곳은 head
	ListNode *tmp;					//포인터 tmp

	while (cur != NULL){			//cur가 NULL 상태가 아니면
		tmp = cur->next;			//tmp에 cur가 가리키는 노드의 next 주소를 저장
		free(cur);					//cur가 가리키고 있는 메모리 반납
		cur = tmp;					//cur=tmp
	}
	ll->head = NULL;				//head는 비어있는 상태
	ll->size = 0;					//size는 0
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)			//ll가 NULL 상태거나 index가 0보다 작거나 또는 index가 ll가 가리키는 size 값보다 이상일 경우
		return NULL;											// NULL반환

	temp = ll->head;											// temp는 ll가 가리키는 head 주소를 저장

	if (temp == NULL || index < 0)								//temp가 NULL 상태거나 index가 0보다 작을 경우
		return NULL;											//NULL 반환

	while (index > 0){											//index가 0보다 클 경우
		temp = temp->next;										//temp는 temp가 가리키는 next 주소를 저장
		if (temp == NULL)										//temp가 NULL일 경우
			return NULL;										//NULL 반환
		index--;												//index를 1만큼 줄이는 연산자 사용
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)		// ll의 값이 NULL 상태거나 index가 0보다 작거나 index가 ll이 가리키는 size 값+1보다 클 경우
		return -1;												// return -1(함수에서 오류가 발생했거나 특정 상태가 있음을 알리는 용도)를 반환

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){						// ll가 가리키는 head가 NULL 상태거나 또는 index 값이 0일 때
		cur = ll->head;											// head에 cur을 위치
		ll->head = malloc(sizeof(ListNode));					// ll가 가리키는 head는 ListNode사이즈에 맞게 동적 메모리 할당을 시키고
		ll->head->item = value;									// ll가 가리키는 head가 가리키는 item 값에 value를 대입
		ll->head->next = cur;									// ll가 가리키는 head는 next를 가리키고, 이것은 cur에 위치
		ll->size++;												// ll의 size에 1을 더함
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){				//findNode로 index-1 노드를 찾아 pre에 저장. 그 결과가 NULL이 아닐 경우 조건문 실행
		cur = pre->next;										//pre가 가리키는 next값을 cur에 저장
		pre->next = malloc(sizeof(ListNode));					//ListNode 크기만큼 힙에 새 메모리 할당, 그 주소를 pre가 가리키는 next에 저장
		pre->next->item = value;								//pre가 가리키는 next가 가리키는 item 값에 value를 대입
		pre->next->next = cur;									//pre가 가리키는 next가 가리키는 next 값에 cur를 대입
		ll->size++;												// ll의 size에 1을 더함
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)	//ll이 가리키는 size값보다 index가 크거나 같을 경우
		return -1;										// return -1반환

	// If removing first node, need to update head pointer
	if (index == 0){									//index값이 0일경우
		cur = ll->head->next;							//cur에 ll이 가리키는 head의 next. 즉, 두 번째 노드의 주소를 저장
		free(ll->head);									// ll가 가리키는 head의 메모리 반납
		ll->head = cur;									//ll을 가리키는 head에 cur를 대입
		ll->size--;										// ll의 size에 1을 뺌

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){		//findNode로 index-1 노드를 찾아 pre에 저장. 그 결과가 NULL이 아닐 경우 조건문 실행

		if (pre->next == NULL)							//pre가 가리키는 next같이 NULL상태일 경우
			return -1;									//-1을 반환

		cur = pre->next;								//cur는 pre가 가리키는 next
		pre->next = cur->next;							//pre가 가리키는 next에 cur가 가리키는 next를 대입
		free(cur);										//cur가 가리키는 메모리 반납
		ll->size--;										//ll의 size에 1을 뺌
		return 0;
	}

	return -1;
}
