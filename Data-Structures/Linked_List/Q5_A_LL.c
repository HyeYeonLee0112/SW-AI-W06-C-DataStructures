//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList1(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);
void frontBackSplitLinkedList2(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

void testSplit(int arr[], int n){
    LinkedList ll, front, back;

    ll.head = front.head = back.head = NULL;
    ll.size = front.size = back.size = 0;

    // 배열 → 리스트
    for(int i = 0; i < n; i++){
        insertNode(&ll, ll.size, arr[i]);
    }

    printf("Original: ");
    printList(&ll);

    frontBackSplitLinkedList2(&ll, &front, &back);

    printf("Front: ");
    printList(&front);

    printf("Back: ");
    printList(&back);
    printf("\n");

    removeAllItems(&ll);
    // removeAllItems(&front);
    // removeAllItems(&back);
}

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	// int c, i;
	// LinkedList ll;
	// LinkedList resultFrontList, resultBackList;

	// //Initialize the linked list as an empty linked list
	// ll.head = NULL;
	// ll.size = 0;

	// //Initialize the front linked list as an empty linked list
	// resultFrontList.head = NULL;
	// resultFrontList.size = 0;

	// // Initialize the back linked list as an empty linked list
	// resultBackList.head = NULL;
	// resultBackList.size = 0;

	// printf("1: Insert an integer to the linked list:\n");
	// printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	// printf("0: Quit:\n");

	// while (c != 0)
	// {
	//     printf("Please input your choice(1/2/0): ");
	// 	scanf("%d", &c);

	// 	switch (c)
	// 	{
	// 	case 1:
	// 		printf("Input an integer that you want to add to the linked list: ");
	// 		scanf("%d", &i);
	// 		insertNode(&ll, ll.size, i);
	// 		printf("The resulting linked list is: ");
	// 		printList(&ll);
	// 		break;
	// 	case 2:
	// 		printf("The resulting linked lists after splitting the given linked list are:\n");
	// 		frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
	// 		printf("Front linked list: ");
	// 		printList(&resultFrontList);
	// 		printf("Back linked list: ");
	// 		printList(&resultBackList);
	// 		printf("\n");
	// 		removeAllItems(&ll);
	// 		removeAllItems(&resultFrontList);
	// 		removeAllItems(&resultBackList);
	// 		break;
	// 	case 0:
	// 		removeAllItems(&ll);
	// 		removeAllItems(&resultFrontList);
	// 		removeAllItems(&resultBackList);
	// 		break;
	// 	default:
	// 		printf("Choice unknown;\n");
	// 		break;
	// 	}
	// }

	int a1[] = {2,3,5,6,7};   // 홀수 개
    int a2[] = {1,2,3,4};     // 짝수 개
    int a3[] = {10};          // 1개

    testSplit(a1, 5);
    testSplit(a2, 4);
    testSplit(a3, 1);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

//주어진 함수 활용
void frontBackSplitLinkedList1(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	int size = ll->size;
	ListNode *curNode = ll->head;

	for(int i =0; i<size; ++i){
		
		if(i < ((size+1)/2))
			insertNode(resultFrontList, i, curNode->item);
		else
			insertNode(resultBackList, i-((size+1)/2), curNode->item);
		
		curNode = curNode->next;
	}
}

//얕은 복사
void frontBackSplitLinkedList2(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	int size = ll->size;
	int startOfBack = (size+1)/2;

	//resultFrontList 헤드
	resultFrontList->head = ll->head;

	
	ListNode *cur = ll->head;
	ListNode *tmp; //resultBackList리스트의 시작 노드 저장용

	//백 리스트가 시작되는 인덱스까지 가기
	for(int i=0; i<(startOfBack); ++i){
		
		if(i == (startOfBack-1)){

			//resultBackList 시작 노드 임시 저장
			tmp = cur->next;

			//resultFrontList 꼬리 처리
			cur->next = NULL; 

			//resultBackList 시작 처리
			resultBackList->head = tmp;

		}

		// if(cur->next == NULL)
		// 	break;

		cur = cur->next;
		
	}
	
	//두 리스트의 개수 처리
	resultFrontList->size = startOfBack;
	resultBackList->size = size-startOfBack;

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


ListNode * findNode(LinkedList *ll, int index){

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
