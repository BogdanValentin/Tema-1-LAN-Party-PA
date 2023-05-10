#include "../headers/queue.h"

Queue *createQueue(){
	Queue *q;
	q = malloc(sizeof(Queue));
	if (q == NULL) {
		mallocError();
	}
	q->front = q->rear=NULL;
	return q;	
}

void enQueue(Queue *q, Match *v){
	QueueNode* newNode = malloc(sizeof(QueueNode));
	if (newNode == NULL) {
		mallocError();
	}
	newNode->val = v;
	newNode->next = NULL;
	if (q->rear == NULL) {
		q->rear = newNode;
	}
	else{
		(q->rear)->next = newNode;
		(q->rear) = newNode;
	}
	if (q->front == NULL) {
		q->front = q->rear;
	} 
}
 
Match *deQueue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }
    QueueNode *aux = q->front;
    Match *d = aux->val;
    if (q->front == q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    free(aux);
    return d;
}


int isQueueEmpty(Queue *q){
	return (q->front==NULL);
}

void deleteQueue(Queue *q){
	QueueNode* aux;
	while (!isQueueEmpty(q)) {
		aux = q->front;
		q->front = q->front->next;
		free(aux);
	}
	free(q);
	q = NULL;
}	
