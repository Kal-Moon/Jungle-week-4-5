//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

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
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
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


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
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

void moveEvenItemsToBack(LinkedList *ll)
{
	/* add your code here */
	//3. moveOddItemsToBack 방법을 써도 되겠으나 이번에는 다르게 시도해볼 예정
	/* 다르게 시도한 이유는 시간복잡도가 3번은 O(n^2)가 나왔고, 예전 기수의 선배님이 O(n)으로 구현한 것을 보고 4번은 O(n)으로 할 수 있게 시도해봄
	 절차과정은 다음과 같음
	 1. 리스트 size 확인. 리스트의 맨 마지막 노드 주소를 확인해 마지막 노드까지 확인이 되면 검사는 종료됨
	 2. 짝수 정의(3번 문제에서 홀수 정의한 방식과 동일)
	 3. 짝수가 맞을 경우 리스트 맨 뒤로 이동시킴
	 4. 노드 값이 홀수라면 지나감
	 5. 최종 결과 반환
	*/
	
	if (ll == NULL || ll->head == NULL)				//리스트가 비어있는 상태거나 리스트의 헤드가 비어있는 상태면 종료. 즉 더 이상 탐색이 할 게 없을 경우 종료하고 결과 반환
		return;

	//변수 선언

	ListNode *last = findNode(ll, ll->size - 1);  // 원래 마지막 노드 — 종료 기준이자 tail의 시작값
	ListNode *tail = last;							//마지막 노드
	ListNode *prenode = NULL; 						//이전노드
	ListNode *cur = ll->head;						//현재노드

	//노드 탐색이 끝나기 전까지 계속 반복
	while (cur != NULL)				//현재 노드가 NULL 상태가 아니라면
	{
		//노드를 탐색하기 전 준비해야할 것들
		ListNode *next = cur->next;      // next변수에 현재 노드의 다음 노드를 저장. cur을 건드리기 전에 원래 다음 자리를 챙겨둠
		int isLast = (cur == last);      // 정수형 isLast는 현재 노드 = 마지막. 이번이 원래 마지막 노드를 보는 차례인지

		//짝수를 뒤로 옮기는 과정
		if (cur->item % 2 == 0)          // 짝수일 경우 
		{
			if (cur != tail)              // 현재 노드가 tail에 위치하지 않을 경우. 이미 tail 자리면 옮길 필요 없음(자기 자신에게 붙는 걸 방지)
			{
				if (prenode == NULL)	//이전 노드가 비어있는 상태면
					ll->head = next;	//리스트의 헤드는 다음으로 이동
				else
					prenode->next = next;	//이전 노드의 다음은 다음으로. 다음 노드로 이동시킴

				tail->next = cur;		//tail의 next가 현재 노드
				cur->next = NULL;		//현재 노드 다음이 비어있는 상태. 즉 더 셀 노드가 없다면
				tail = cur;				//tail은 현재 노드
			}
			// prenode는 그대로 — 방금 빠진 자리에 새로 들어온 노드가 다음 번 "앞 노드" 후보
		}
		else                               // 홀수 → 그대로 둠
		{
			prenode = cur;		//prenode는 현재 노드. 홀수일 경우 넘어가기
		}

		if (isLast)
			break;		//종료 선언

		cur = next;		//현재 노드는 다음 노드로
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
