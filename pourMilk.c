#include <stdio.h>
#include <stdlib.h>

#define empty 0

#define Xcapacity 10
#define Ycapacity 5
#define Zcapacity 6

#define Maxlength 100

#define goal 5


typedef struct{
	int x, y;
}State;

typedef struct{
	State state;
	struct Node* parent;
	int no_function;
}Node;

typedef struct{
	Node* Element[Maxlength];
	int Top_idx;
}Stack;


int makeNull_stack(Stack stack){
	return stack.Top_idx = 0;
}


int isFull_Stack(Stack stack){
	return stack.Top_idx == 0;
}

int isEmpty_Stack(Stack stack){
	return stack.Top_idx == Maxlength;
}

void push(Node* x, Stack *stack){
	if(isFull_Stack(*stack)){
		printf("Error! Stack is full!!!");
	}
	else{
		stack->Top_idx -= 1;
		stack->Element[stack->Top_idx] = x;
	}
}

void pop(Stack *stack){
	if(!isEmpty_Stack(*stack)){
		stack->Top_idx += 1;
	}
	else{
		printf("Stack is empty!!!");
	}
}

Node *top(Stack stack){
	if(!isEmpty_Stack(stack)){
		return stack.Element[stack.Top_idx];
	}
	return NULL;
}

void makeNull_State(State *state){
	state->x = empty;
	state->y = empty;
}

int compareState(State state1, State state2){
	if(state1.x == state2.x && state1.y == state2.y)
		return 1;
	else 
		return 0;
}

int find_State(State state, Stack openStack){
	while(!isEmpty_Stack(openStack)){
		if(compareState(top(openStack)->state, state))
			return 1;
		pop(&openStack);
	}
	return 0;
}

int check_goal(State state){
	if(state.x == goal || state.x == goal)
		return 1;
	else
		return 0;
}


void setStartState(State *state, int x, int y){
	state->x = x;
	state->y = y;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int pourXY(State state, State *result){
	if(state.x > 0 && state.x < Xcapacity){
		result->x = max(state.x - (Ycapacity - state.y), empty);
		result->y = min(state.y + state.x, Ycapacity);
		return 1;
	}
	return 0;
}

int pourYX(State state, State *result){
	if(state.y > 0 && state.y < Ycapacity){
		result->x = min(state.x + state.y, Xcapacity);
		result->y = max(state.y - (Xcapacity - state.x), empty);
		return 1;
	}
	return 0;
}

int pourfullX(State state, State *result){
	if(state.x < Xcapacity){
		result->x = Xcapacity;
		result->y = state.y;
		return 1;
	}
	return 0;
}

int pourfullY(State state, State *result){
	if(state.y < Ycapacity){
		result->y = Ycapacity;
		result->x = state.x;
		return 1;
	}
	return 0;

	
}

int makeNullX(State state, State *result){
	if(result->x != empty){
		result->x = empty;
		result->y = state.y;
		return 1;
	}
	return 0;
}

int makeNullY(State state, State *result){
	if(result->y != empty){
		result->y = empty;
		result->x = state.x;
		return 1;
	}
	return 0;
}


int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourfullX(cur_state, result);
		case 2: return pourfullY(cur_state, result);
		case 3: return makeNullX(cur_state, result);
		case 4: return makeNullY(cur_state, result);
		case 5: return pourXY(cur_state, result);
		case 6: return pourYX(cur_state, result);
		default: printf("Wrong operator, restart the program and try again!");
			return 0;
	}
}


const char* action[] = {"First State", "Pour water full X", "Pour water full Y", "Make empty X", "Make empty Y", "Pour water X to Y", "Pour water Y to X"};



Node* DFS_Algorithm(State state){
	//tao stack open & close
	Stack Open_DFS, Close_DFS;
	
	makeNull_stack(Open_DFS);
	makeNull_stack(Close_DFS);

	//tao nut parent state
	
	Node* root = (Node*)malloc(sizeof(Node));
	
	root->state = state;
	root->parent = NULL;
	root->no_function = 0;
	
	push(root, &Open_DFS);
	
	while(!isEmpty_Stack(Open_DFS)){
		//lay 1 dinh trong Stack
		Node* node = top(Open_DFS);
		pop(&Open_DFS);
		push(node, &Close_DFS);
		
		//check node là goal hay không
		
		if(check_goal(node->state)){
			return node;
		} 
		
		int option;
		
		for (option = 1; option <= 6; option++){
			State new_State;
			makeNull_State(&new_State);
			if(call_operator(node->state, &new_State, option)){
				if(find_State(new_State, Close_DFS) || find_State(new_State, Open_DFS)){
					continue;
				}
				
				Node* new_Node = (Node*)malloc(sizeof(Node));
				
				new_Node->state = new_State;
				new_Node->parent = node;
				new_Node->no_function = option;
				push(new_Node, &Open_DFS);
			}
		}
		
	}
	return NULL;
}


int main(){
	State cur_state, result;
	
	setStartState(&cur_state, 9, 1);
	
	printf("%d %d\n", cur_state.x, cur_state.y);
	
	DFS_Algorithm(cur_state);
	
//	call_operator(cur_state, &result, 1);
//
//	int opt;
//	
//	for (opt = 1; opt <= 6; opt++){
//		int enforce = call_operator(cur_state, &result, opt);
//		if(enforce == 1){
//			printf("Execute %s success!\n", action[opt]);
//			printf("%d %d\n", result.x, result.y);
//		}
//		else {
//			printf("\nExecute %s failed!\n", action[opt]);
//		}
//	}

	return 0;
}
