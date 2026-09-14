//////////////////////////////////////////////////////////////////////////////////
// Unit tests for Q1_A_LL.c
//
// Build:
//   gcc -Wall -o test_Q1_A_LL test_Q1_A_LL.c
// Run:
//   ./test_Q1_A_LL
//////////////////////////////////////////////////////////////////////////////////

#include <assert.h>

// Rename the original file's main() while it's being included, so it doesn't
// conflict with this file's own main() below.
#define main original_main
#include "Q1_A_LL.c"
#undef main

// Verifies the list matches `expected[0..expectedSize-1]` in order, and that
// ll->size agrees.
static void checkList(LinkedList *ll, int *expected, int expectedSize)
{
	assert(ll->size == expectedSize);

	ListNode *cur = ll->head;
	for (int i = 0; i < expectedSize; i++) {
		assert(cur != NULL);
		assert(cur->item == expected[i]);
		cur = cur->next;
	}
	assert(cur == NULL);
}

static void test_insert_into_empty_list(void)
{
	LinkedList ll = { .head = NULL, .size = 0 };

	int index = insertSortedLL(&ll, 5);
	assert(index == 0);
	int expected[] = { 5 };
	checkList(&ll, expected, 1);

	removeAllItems(&ll);
	printf("PASS: test_insert_into_empty_list\n");
}

static void test_insert_ascending_order(void)
{
	LinkedList ll = { .head = NULL, .size = 0 };

	assert(insertSortedLL(&ll, 5) == 0);
	assert(insertSortedLL(&ll, 3) == 0);
	assert(insertSortedLL(&ll, 8) == 2);
	assert(insertSortedLL(&ll, 1) == 0);
	assert(insertSortedLL(&ll, 4) == 2);

	int expected[] = { 1, 3, 4, 5, 8 };
	checkList(&ll, expected, 5);

	removeAllItems(&ll);
	printf("PASS: test_insert_ascending_order\n");
}

static void test_insert_duplicate_values(void)
{
	LinkedList ll = { .head = NULL, .size = 0 };

	assert(insertSortedLL(&ll, 5) == 0);
	// Current implementation stops at the first node with item >= new item,
	// so a duplicate is inserted *before* the existing equal-valued node.
	assert(insertSortedLL(&ll, 5) == 0);

	int expected[] = { 5, 5 };
	checkList(&ll, expected, 2);

	removeAllItems(&ll);
	printf("PASS: test_insert_duplicate_values\n");
}

static void test_findNode_bounds(void)
{
	LinkedList ll = { .head = NULL, .size = 0 };
	insertSortedLL(&ll, 10);
	insertSortedLL(&ll, 20);
	insertSortedLL(&ll, 30);

	assert(findNode(&ll, -1) == NULL);
	assert(findNode(&ll, 3) == NULL);   // index == size is out of range
	assert(findNode(&ll, 100) == NULL);

	assert(findNode(&ll, 0)->item == 10);
	assert(findNode(&ll, 1)->item == 20);
	assert(findNode(&ll, 2)->item == 30);

	removeAllItems(&ll);
	printf("PASS: test_findNode_bounds\n");
}

static void test_removeNode(void)
{
	LinkedList ll = { .head = NULL, .size = 0 };
	insertSortedLL(&ll, 1);
	insertSortedLL(&ll, 2);
	insertSortedLL(&ll, 3);
	insertSortedLL(&ll, 4);
	// list: 1 2 3 4

	// Invalid indices leave the list untouched.
	assert(removeNode(&ll, -1) == -1);
	assert(removeNode(&ll, 4) == -1);
	int unchanged[] = { 1, 2, 3, 4 };
	checkList(&ll, unchanged, 4);

	// Remove head.
	assert(removeNode(&ll, 0) == 0);
	int afterHead[] = { 2, 3, 4 };
	checkList(&ll, afterHead, 3);

	// Remove middle.
	assert(removeNode(&ll, 1) == 0);
	int afterMiddle[] = { 2, 4 };
	checkList(&ll, afterMiddle, 2);

	// Remove tail.
	assert(removeNode(&ll, 1) == 0);
	int afterTail[] = { 2 };
	checkList(&ll, afterTail, 1);

	removeAllItems(&ll);
	printf("PASS: test_removeNode\n");
}

static void test_removeAllItems(void)
{
	LinkedList ll = { .head = NULL, .size = 0 };
	insertSortedLL(&ll, 1);
	insertSortedLL(&ll, 2);
	insertSortedLL(&ll, 3);

	removeAllItems(&ll);
	assert(ll.head == NULL);
	assert(ll.size == 0);

	printf("PASS: test_removeAllItems\n");
}

int main(void)
{
	test_insert_into_empty_list();
	test_insert_ascending_order();
	test_insert_duplicate_values();
	test_findNode_bounds();
	test_removeNode();
	test_removeAllItems();

	printf("All tests passed!\n");
	return 0;
}
