#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define MAX_NODE 15

typedef struct node{
	int data;
	struct node* next;
	struct node* prev;
}node_t;

typedef struct linked_list{
	struct node* head;
}linked_list_t;

struct screenDimensions{
	int sw;
	int sh;
	int nodeRndrCount;
}screenDimensions;

typedef struct nodeRender{
	Rectangle dataBounds;
	Rectangle nextBounds;
	Rectangle prevBounds;
	Rectangle headBounds;
	float paddingBdr;
	float elWidth;
	float elHeight;
	float scaleGaps;
	float scaleStack;
	int nodeIndex;
}nodeRender;

linked_list_t* init_list();
void append_list(linked_list_t* dll, int data);
void print_list_all(linked_list_t* dll); 
void print_reverse_all(linked_list_t* dll);
void gameRender(struct screenDimensions sd, struct nodeRender nr, nodeRender* nodesArr[MAX_NODE]);
void nodeElState(int index, nodeRender* nr);
void renderNode(int index, nodeRender* nr);
void gameState(struct screenDimensions* sd, struct nodeRender *nr, nodeRender* nodesArr[MAX_NODE]);

int main(){
	struct screenDimensions sd;
	struct nodeRender nr;
	nr.nodeIndex = 1;

	sd.sw = 1200;
	sd.sh = 800;
	sd.nodeRndrCount = 0;
	nodeRender* nodesArr [MAX_NODE] = {0};

	InitWindow(sd.sw, sd.sh, "DLL");
	SetTargetFPS(144);

	while(!WindowShouldClose()){
		gameState(&sd, &nr, nodesArr);
		BeginDrawing();
			ClearBackground(DARKGRAY);
			gameRender(sd, nr, nodesArr);
		EndDrawing();
	}

	return 0;
}

linked_list_t* init_list(){
	linked_list_t* list = (linked_list_t*)malloc(sizeof(linked_list_t));
	printf("[TASK]Initialized new double-linked list...\n");
	list->head = NULL;
	return list;
}

void append_list(linked_list_t* dll, int data){
	node_t* cur = dll->head;
	if(dll->head == NULL){
		printf("[TASK]No existing node, creating head...\n");
		node_t* new_head = (node_t*)malloc(sizeof(node_t));
		new_head->data = data;
		new_head->next = NULL;
		dll->head = new_head;
		printf("[TASK]Head created...\n");
		if(dll->head != NULL){
			printf("[TASK]Succesfully created head...\n");
		}else{
			printf("[ERR]: Failed to create head...\n");
			return;
		}
	}else{
		printf("[TASK]Appending to valid list...\n");
		while(cur->next != NULL){
			cur = cur->next;
		}
		node_t* new_node = (node_t*)malloc(sizeof(node_t));
		new_node->data = data;
		new_node->next = NULL;
		new_node->prev = cur;
		cur->next = new_node;
		if(cur->next != NULL){
			printf("[TASK]Appending succesful...\n");
		}
	}
}

void print_list_all(linked_list_t* dll){
	if(dll->head == NULL){
		printf("[ERR]: Empty list...");
		return;
	}
	node_t* cur = dll->head;
	int index = 0;
	while(cur->next != NULL){
		cur = cur->next;
		printf("[%d]: %d\n", index, cur->data);
		index += 1;
	}
}

void print_reverse_all(linked_list_t* dll){
	if(dll->head == NULL){
		printf("[ERR]: Empty list...");
		return;
	}
	node_t* cur = dll->head;
	int index = 0;
	while(cur->next != NULL){
		cur = cur->next;
	}
	while(cur->prev != NULL){
		printf("[%d]: %d\n", index, cur->data);
		cur = cur->prev;
		index += 1;
	}
}

void gameRender(struct screenDimensions sd, struct nodeRender nr, nodeRender* nodesArr[MAX_NODE]){
	if(nodesArr[0] == NULL){
		return;
	}
	for(int i = 0; i < sd.nodeRndrCount; i++){
		nodeElState(i, nodesArr[i]);
		renderNode(i, nodesArr[i]);
	}
}

void gameState(struct screenDimensions* sd, struct nodeRender *nr, nodeRender* nodesArr[MAX_NODE]){
	if(IsKeyPressed(KEY_W)){
	sd->nodeRndrCount += 1;
		for(int i = 0; i < sd->nodeRndrCount; i++){
			nodeRender* newnode = (nodeRender*)malloc(sizeof(nodeRender));
			nodesArr[i] = newnode;
		}
	}
	if(sd->nodeRndrCount > MAX_NODE){
		sd->nodeRndrCount = MAX_NODE;
	}
}

void nodeElState(int index, nodeRender* nr){
	nr->nodeIndex = index;
	nr->elWidth = 60;
	nr->elHeight = 20;
	nr->scaleGaps = nr->elWidth + 20;
	nr->paddingBdr = 10.0f;
	nr->scaleStack = 30;
	nr->headBounds = (Rectangle){nr->paddingBdr, nr->paddingBdr, nr->elWidth, nr->elWidth};
}

void renderNode(int index, nodeRender* nr){
	Rectangle newNodeNext = {(nr->scaleGaps * index) + nr->paddingBdr, nr->paddingBdr, nr->elWidth, nr->elHeight};
	Rectangle newNodeData = {(nr->scaleGaps * index) + nr->paddingBdr, nr->scaleStack, nr->elWidth, nr->elHeight}; 
	Rectangle newNodePrev = {(nr->scaleGaps * index) + nr->paddingBdr, (nr->scaleStack * 2) - 10.0f, nr->elWidth, nr->elHeight}; 
	DrawRectangleRec(newNodeNext, WHITE);
	DrawRectangleRec(newNodeData, GRAY);
	DrawRectangleRec(newNodePrev, WHITE);
	DrawText("NEXT", (nr->scaleGaps * index) + nr->paddingBdr, nr->paddingBdr, 14, BLACK);
	DrawText("DATA", (nr->scaleGaps * index) + nr->paddingBdr, nr->scaleStack, 14, BLACK);
	DrawText("PREV", (nr->scaleGaps * index) + nr->paddingBdr, (nr->scaleStack * 2) - 10.0f, 14, BLACK);
}
