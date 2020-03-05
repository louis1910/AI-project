#include <stdio.h>


#define ROW 3
#define COL 3
#define EMPTY 0

typedef struct{
	int EightPuzzles[ROW][COL];
	int empROW;
	int empCOL;
}State;

void empDOWN(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empRowCurrent < 2){
		result->empROW = empRowCurrent + 1;
		result->empCOL = empColCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent + 1][empColCurrent];
		result->EightPuzzles[empRowCurrent + 1][empColCurrent] = EMPTY;
	}
}

void empUP(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empRowCurrent > 0){
		result->empROW = empRowCurrent - 1;
		result->empCOL = empColCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent - 1][empColCurrent];
		result->EightPuzzles[empRowCurrent - 1][empColCurrent] = EMPTY;
	}
}

void empLEFT(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empColCurrent > 0){
		result->empCOL = empColCurrent - 1;
		result->empROW = empRowCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent][empColCurrent - 1];
		result->EightPuzzles[empRowCurrent][empColCurrent - 1] = EMPTY;
	}
}

void empRIGHT(State state, State *result){
	*result = state;
	int empRowCurrent = state.empROW, empColCurrent = state.empCOL;
	
	if(empColCurrent < 2){
		result->empCOL = empColCurrent + 1;
		result->empROW = empRowCurrent;
		result->EightPuzzles[empRowCurrent][empColCurrent] = state.EightPuzzles[empRowCurrent][empColCurrent + 1];
		result->EightPuzzles[empRowCurrent][empColCurrent + 1] = EMPTY;
	}
}

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
	
	
	
	
	 
}
