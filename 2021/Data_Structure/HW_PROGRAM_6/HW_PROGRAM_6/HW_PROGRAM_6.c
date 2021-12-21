#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { 
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// Error Handling
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// Queue initialization
void init_queue(QueueType *q)
{
	q->front = -1;
	q->rear = -1;	

	printf("Q is initialized!!\n");
}

// Check if queue is empty
int is_empty(QueueType *q)
{
	if (q->front == -1 && q->rear == -1)
		return 1;
	else
		return 0;
}

// Check if queue is full
int is_full(QueueType *q)
{
	if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front)
		return 1;
	else
		return 0;
}

// Add an item into queue
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		error("Queue is full!!");
		return;
	}

	// if queue is empty (i.e. front == rear == -1)
	if (is_empty(q)){
		q->front += 1;
		q->rear += 1;
	}

	// if there are more than or equal to one item in queue
	else
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // 모듈로 연산을 통해 배열의 0번 인덱스로 돌아 감

	q->data[q->rear] = item;	
	// q->data[++(q->rear)] = item; 
}


// Remove and return an item from queue
element dequeue(QueueType *q)
{
	element item;

	if (is_empty(q)) {
		error("Queue is empty!!");
		return -1;
	}

	item = q->data[q->front];
	// int item = q->data[++(q->front)];

	// if there is only one item in queue (i.e., front == rear)
	if (q->front == q->rear){
		q->front = -1;
		q->rear = -1;
	}

	// if there are more than or equal to two items in queue 
	else	
		q->front = (q->front + 1) % MAX_QUEUE_SIZE; // 모듈로 연산을 통해 배열의 0번 인덱스로 돌아 감
	
	return item;
}

// Check the item in the front
element peek(QueueType *q)
{
	if (is_empty(q))
		error("Q is empty!!");

	return q->data[q->front];
}

int get_count(QueueType* q, int x)
{
	int count = 0;
	if (is_empty(q)) {
		printf("큐가 비어있습니다.");
		exit(1);
	}
	// Case 1
	if (q->front <= q->rear)
	{
		for (int i = q->front; i <= q->rear; i++)
		{
			if (x == q->data[i])
				count++;
		}
	}
	//Case 2
	else if (q->front > q->rear)
	{

		for (int i = q->front; i <= MAX_QUEUE_SIZE - 1; i++)
		{
			if (x == q->data[i])
				count++;
		}
		for (int i = 0; i <= q->rear; i++)
		{
			if (x == q->data[i])
				count++;
		}

	}
	return count;
}
int main(void)
{
	QueueType q;
	
	init_queue(&q);

	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	enqueue(&q, 4);
	dequeue(&q);
	enqueue(&q, 3);
	dequeue(&q);
	enqueue(&q, 5);
	enqueue(&q, 6);

	printf("enqueue(1); \n");
	printf("enqueue(2); \n");
	printf("enqueue(3); \n");
	printf("enqueue(4); \n");
	printf("dequeue; \n");
	printf("enqueue(3); \n");
	printf("dequeue; \n");
	printf("enqueue(5); \n");
	printf("enqueue(6); \n");

	printf(" \n %d, %d", get_count(&q, 3), get_count(&q, 7));
}