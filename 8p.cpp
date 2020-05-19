
#include <stdio.h>


#define ROW 3
#define COL 3
#define EMPTY 0
#define Maxlength 100

typedef struct{
	int EightPuzzles[ROW][COL];
	int empROW;
	int empCOL;
}State;

typedef struct Node{
	State state;
	struct Node* parent;
	int f;
	int g;
	int h;
	int no_func;
}Node;


typedef struct{
	Node* Elements[Maxlength];
	int size;
}List;

void makeNull_List(List *L){
	L->size = 0;
}

int empty_List(List list){
	return list.size == 0;
}

int isEmpty_List(List L){
	return L.size == 0;
}

Node* element_at(int p, List list){
	return list.Elements[p-1];
}

int full_List(List list){
	return list.size == Maxlength;
}

//Them phan tu vao vi tri position trong danh sach
void push_List(Node* x, int position, List *list){
	if(!full_List(*list)){
		int q;
		for(q = list->size; q >= position; q--)
			list->Elements[q] = list->Elements[q-1];
		list->Elements[position-1]=x;
		list->size++;
	}
	else printf("List day!!!\n");
}

void delete_List(int position, List *list){
	if(empty_List(*list))
		printf("List rong!!\n");
	else if(position<1 || position>list->size)
		printf("Vi tri khong hop le!\n");
	else{
		int i;
		for (i=position-1; i<list->size; i++)
			list->Elements[i]=list->Elements[i+1];
		list->size--;
	}
}

int empDOWN(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empRowCurrent < 2){
		result->empROW = empRowCurrent + 1;
		result->empCOL = empColCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent + 1][empColCurrent];
		result->EightPuzzles[empRowCurrent + 1][empColCurrent] = EMPTY;
		return 1;
	}
	return 0;
}

int empUP(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empRowCurrent > 0){
		result->empROW = empRowCurrent - 1;
		result->empCOL = empColCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent - 1][empColCurrent];
		result->EightPuzzles[empRowCurrent - 1][empColCurrent] = EMPTY;
		return 1;
	}
	return 0;
}

int empLEFT(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empColCurrent > 0){
		result->empCOL = empColCurrent - 1;
		result->empROW = empRowCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent][empColCurrent - 1];
		result->EightPuzzles[empRowCurrent][empColCurrent - 1] = EMPTY;
		return 1;
	}
	return 0;
}

int empRIGHT(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empColCurrent < 2){
		result->empCOL = empColCurrent + 1;
		result->empROW = empRowCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent][empColCurrent + 1];
		result->EightPuzzles[empRowCurrent][empColCurrent + 1] = EMPTY;
		return 1;
	}
	return 0;
}

int compareStates(State state1, State state2){
	if(state1.empROW != state2.empROW || state1.empCOL != state2.empCOL)
		return 0;
	int row, col;
	for(row=0; row<ROW; row++)
		for(col=0; col<COL; col++)
			if(state1.EightPuzzles[row][col] != state2.EightPuzzles[row][col])
				return 0;
	return 1;
}

int checkGoal(State state, State goal){
	return compareStates(state, goal);
}

int heuristic1(State state, State goal){
	int row, col, count=0;
	for(row=0; row<ROW; row++)
		for(col=0; col<COL; col++)
			if(state.EightPuzzles[row][col] != goal.EightPuzzles[row][col])
				count++;
	return count;	
}

int heuristic2(State state, State goal) {
    int count = 0;
    int row, col, row_g, col_g;
	for (row = 0; row < ROW; row++) {
        for (col = 0; col < COL; col++) {
            if (state.EightPuzzles[row][col] != EMPTY) {
                for (row_g = 0; row_g < ROW; row_g++) {
                    for (col_g = 0; col_g < COL; col_g++) {
                        if (state.EightPuzzles[row][col] == goal.EightPuzzles[row_g][col_g]){
                            count += abs(row - row_g) + abs(col - col_g);
                            col_g = COL; //break loop col_g
							row_g = ROW; //break loop row_g
                        }
                    }
                }
            }
        }
    }
    return count;
}

//void printSate(State state){
//		for(int i = 0; i < ROW; i++){
//			printf("\n");
//			for (int j = 0; j < COL; j++){
//				fscanf(testCase, "%d", &state.EightPuzzles[i][j]);
//				if(state.EightPuzzles[i][j] == 0){
//					state.empROW = i;
//					state.empCOL = j;
//				}
//			printf(" %d", state.EightPuzzles[i][j]);
//		}
//	}
//}


int main(){
	State state, result;
	
	
	
	FILE *testCase = fopen("testCase.txt", "r");
	
	
	for(int i = 0; i < ROW; i++){
		printf("\n");
		for (int j = 0; j < COL; j++){
			fscanf(testCase, "%d", &state.EightPuzzles[i][j]);
			if(state.EightPuzzles[i][j] == 0){
				state.empROW = i;
				state.empCOL = j;
			}
			printf(" %d", state.EightPuzzles[i][j]);
		}
	}
	
	empRIGHT(state, &result);
	printf("\n");
	
	for(int i = 0; i < ROW; i++){
		printf("\n");
		for (int j = 0; j < COL; j++){
			printf(" %d", result.EightPuzzles[i][j]);
		}
	}
	
	List L;
	makeNull_List(&L);
	
	if(isEmpty_List(L)) printf("ok");
	
	
	
	
	 
}

