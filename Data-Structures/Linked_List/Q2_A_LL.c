//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)		//두 개의 연결 리스트   ex. [1,2,3,4] [5,6,7] = [1,5,2,6,3,7,4]
{
    /* add your code here */

	//1. 2번 리스트에 있는 첫 번째 노드를 뺸다
	//2. 뺀 노드는 1부터 시작해 매 회차마자 2씩 늘어남
	//3. 2번 리스트에 들어있는 노드값이 전부 비워질 때까지 이 과정을 반복한다
	//4. 결과값을 반환한다
	int value;
	int index = -1;

	//3. 노드값이 비워질 때까지 반복
	while (ll2->size > 0){
	value = ll2 -> head -> item;
	//1. ll2리스트에 있는 노드 뺴기
	removeNode(ll2, 0);
	//2. ll2리스트에서 뺀 노드 ll1에 넣기. 끼워넣는 위치는 1부터 시작해 매 회차마다 2씩 늘어남
	int result = insertNode(ll1, index+2, value);
	index = index + 2;
	if (result == -1){
		insertNode(ll1, ll1 -> size, value);
	}
	}
	//4. 결과값 반환
	return;		
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){		//리스트 출력. ll가 가리키는 주소에 LinkedList구조체가 있음. ll은 LinkedList 구조체를 가리키는 포인터
	//리스트의 head부터 끝까지 순회하며 각 노드의 값을 출력

	ListNode *cur;
	if (ll == NULL)				//ll이 NULL 상태라면 조건문
		return;					//종료
	cur = ll->head;				//cur은 ll이 가리키는 head

	if (cur == NULL)			//cur이 NULL 상태라면 조건문
		printf("Empty");		//Empty라 출력
	while (cur != NULL)			//cur이 NULL 상태가 아니라면 아래를 반복
	{
		printf("%d ", cur->item);	//정수. cur이 가리키는 item값을 출력
		cur = cur->next;			//cur은 cur이 가리키는 next
	}
	printf("\n");				//출력. 줄바꿈
}


void removeAllItems(LinkedList *ll)		//모든 아이템 제거
	//리스트의 모든 노드를 순회하며 free()로 메모리 해제, head를 NULL, size를 0으로 초기화
{
	ListNode *cur = ll->head;		//cur는 ll이 가리키는 head의 포인터
	ListNode *tmp;					//tmp는 ListNode 구조체를 가리키는 포인터

	while (cur != NULL){			//cur가 NULL 상태가 아닐 동안 반복
		tmp = cur->next;			//tmp는 cur가 가리키는 next값
		free(cur);					//cur에 할당된 메모리 반납
		cur = tmp;					//cur에 tmp값을 덮음
	}
	ll->head = NULL;				//ll가 가리키는 head가 NULL상태
	ll->size = 0;					//ll가 가리키는 size값이 0
}


ListNode *findNode(LinkedList *ll, int index){		//노드 찾기
	//주어진 index 위치의 노들르 찾아 그 포인터를 반환

	ListNode *temp;	

	if (ll == NULL || index < 0 || index >= ll->size)		//ll이 NULL상태 또는 index가 0보다 작거나 또는 index가 ll이 가리키는 size값보다 크거나 같을 때 조건문 실행
		return NULL;										//NULL 반환

	temp = ll->head;										//temp는 ll이 가리키는 head

	if (temp == NULL || index < 0)							//temp가 NULL 상태거나 index가 0보다 작을 때
		return NULL;										//NULL 반환

	while (index > 0){										//index가 0보다 클 때 아래를 반복
		temp = temp->next;									//temp는 temp가 가리키는 next값
		if (temp == NULL)									//temp가 NULL상태일 때
			return NULL;									//NULL반환
		index--;											//index 값 1씩 감소
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){		//Node추가
	//index 위치에 value값을 가진 새 노드를 삽입
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)	//ll이 NULL상태거나 index가 0보다 작거나 ll이 가리키는 size+1 값보다 크다면
		return -1;											//실패했음을 반환

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){					//ll이 가리키는 head가 NULL상태거나 index 값이 0일 경우
		cur = ll->head;										//cur은 ll이 가리키는 head로 덮임		//새 노드를 만들 기 전 기존 head를 cur에 백업해두는 것
		ll->head = malloc(sizeof(ListNode));				//ll이 가리키는 head는 ListNode사이즈에 맞게 메모리를 빌리고
		ll->head->item = value;								//ll이 가리키는 head가 가리키는 item은 value값으로 덮음
		ll->head->next = cur;								//ll이 가리키는 head가 가리키는 next는 cur로 덮음
		ll->size++;											//ll이 가리키는 size값은 1씩 증가
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){			//findNode에 ll과 index-1를 찾아 pre에 저장. 그 값이 NULL과 같지 않을 경우
		cur = pre->next;									//cur은 pre가 가리키는 next로 덮음
		pre->next = malloc(sizeof(ListNode));				//pre가 가리키는 next는 ListNode사이즈에 맞게 메모리 빌림
		pre->next->item = value;							//새로 만든 노드(pre -> next)의 item 을 value로 설정
		pre->next->next = cur;								//새로 만든 노드 다음을 cur로 설정. 새 노드가 원래 다음 노드를 가리키게 연결
		ll->size++;											//ll의 size값을 1씩 증가
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){						//노드 제거
	//index 위치의 노드를 삭제
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)			// ll이 NULL상태거나 index가 0보다 작거나 ll이 가리키는 size값보다 크거나 같을 경우
		return -1;												// 실패했음을 반환

	// If removing first node, need to update head pointer
	if (index == 0){											//index값이 0일 경우
		cur = ll->head->next;									//cur는 첫 노드 다음 노드로 설정
		free(ll->head);											//첫 노드 메모리 반환
		ll->head = cur;											//head를 cur로 교체. 그 노드가 새로운 첫 노드가 됨
		ll->size--;												//size값을 1씩 감소시킴

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){				//findNode가 ll과 index-1를 찾아 pre에 저장. 이 값이 NULL과 같지 않을 경우

		if (pre->next == NULL)									//pre의 다음이 NULL상태일 경우
			return -1;											//실패했음을 반환

		cur = pre->next;										//cur은 pre가 가리키는 next
		pre->next = cur->next;									//pre -> next를 cur -> next로 덮음. cur를 건너뛰고 연결
		free(cur);												//cur의 메모리 반납
		ll->size--;												//size값을 1씩 감소
		return 0;
	}

	return -1;
}
