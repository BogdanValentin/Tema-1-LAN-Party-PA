#include "stive.h"

StackData *top(StackNode *top){
	return top->val;
} 

void push(StackNode**top, StackData *v) {
	StackNode* newNode=(StackNode*)malloc(sizeof(StackNode));
	newNode->val=v;
	newNode->next=*top;
	*top=newNode;
}

StackData *pop(StackNode**top) {
	StackNode *temp=(*top); 		
	StackData *aux=temp->val;	
	*top=(*top)->next;      		
	free(temp);
	return aux;
}

int isStackEmpty(StackNode*top){
	return top==NULL;
}
	
void deleteStack(StackNode**top){
	StackNode  *temp;
	while (!isStackEmpty(*top)) {
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
}

void functiebelea(StackNode *stackCopy, FILE *file) {
        fprintf(file, "%-34s-  %.2f\n", stackCopy->val->name, findTeamScore(stackCopy->val));
		if(stackCopy->next != NULL) {
			functiebelea(stackCopy->next, file);
		}
}
