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
// Queue의 front가 rear의 값보다 크게끔 초기화(5번문제 출력 테스트 용)
void init_queue2(QueueType* q)
{
	q->front = 3;
	q->rear = -1;

	printf("Q is initialized!! (front =3, rear =-1)\n");
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

// Print queue - need to consider two cases:
// Case 1: q->front <= q->rear
// Case 2: q->front > q->rear
// Print the items starting from data[q->front] through data[q->rear]
void queue_print(QueueType* q)
{
	// Case 1
	if (q->front <= q->rear)
	{
		printf("Queue List(front->rear) ->  ");
		for (int i = q->front ; i <= q->rear; i++)
		{
			if (q->rear == -1) // dequeue 출력시, q[-1]출력 방지
				break;
			printf("q[%d] : %d  ", i, q->data[i]);
		}
		printf("\n");
	}
	//Case 2
	else if (q->front > q->rear)
	{
		printf("Queue List(front->rear) ->  ");
		for (int i = q->front; i <= MAX_QUEUE_SIZE-1; i++)
		{
			printf("q[%d] : %d  ", i, q->data[i]);
		}
		for (int i = 0; i <= q->rear; i++)
		{
			if (q->rear == -1)
				break;
			printf("q[%d] : %d  ", i, q->data[i]);
		}
		printf("\n");
	}
}
int main(void)
{
	QueueType queue;
	int x;

	init_queue(&queue);

	printf("== Data Input ==\n");
	while (!is_full(&queue))
	{
		
		scanf_s("%d", &x);
		enqueue(&queue, x);
		queue_print(&queue);
	}
	printf("Q is full now!!\n\n");

	printf("== Data Output ==\n");
	while (!is_empty(&queue))
	{
		x = dequeue(&queue);
		printf("Dequeued item: %d \n", x);
		queue_print(&queue);
	}
	printf("Q is now empty!!\n");


	//front > rear 인 값으로 queue 초기화

	printf("\n\n\n");
	init_queue2(&queue);
	printf("== Data Input ==\n");
	while (!is_full(&queue))
	{

		scanf_s("%d", &x);
		enqueue(&queue, x);
		queue_print(&queue);
	}
	printf("Q is full now!!\n\n");

	printf("== Data Output ==\n");
	while (!is_empty(&queue))
	{
		x = dequeue(&queue);
		printf("Dequeued item: %d \n", x);
		queue_print(&queue);
	}
	printf("Q is now empty!!\n");
	return 0;
}