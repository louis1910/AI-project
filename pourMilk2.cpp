#include <stdio.h>

#define empty 0

#define Xcapacity 10
#define Ycapacity 5
#define Zcapacity 6


typedef struct{
	int x, y, z;
}State;

void setStartState(State *state, int x, int y, int z){
	state->x = x;
	state->y = y;
	state->z = z;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

void pourXY(State state, State *result){
	if(state.x > 0 && state.x < Xcapacity){
		result->x = max(state.x - (Ycapacity - state.y), empty);
		result->y = min(state.y + state.x, Ycapacity);
		result->z = state.z;
	}
}

void pourXZ(State state, State *result){
	if(state.x > 0 && state.x < Xcapacity){
		result->x = max(state.x - (Zcapacity - state.z), empty);
		result->z = min(state.z + state.x, Zcapacity);
		result->y = state.y;
	}
}

void pourYX(State state, State *result){
	if(state.y > 0 && state.y < Ycapacity){
		result->x = min(state.x + state.y, Xcapacity);
		result->y = max(state.y - (Xcapacity - state.x), empty);
		result->z = state.z;
	}
}

void pourYZ(State state, State *result){
	if(state.y > 0 && state.y < Ycapacity){
		result->x = state.x;
		result->y = max(state.y - (Xcapacity - state.x), empty);
		result->z = min(state.z + state.y, Zcapacity);
	}
}

void pourZX(State state, State *result){
	if(state.z > 0 && state.z < Zcapacity){
		result->x = min(state.x + state.z, Xcapacity);
		result->y = state.y;
		result->z = max(state.z - (Xcapacity - state.x), empty);
	}
}

void pourZY(State state, State *result){
	if(state.z > 0 && state.z < Zcapacity){
		result->x = state.x;
		result->y = min(state.y + state.z, Ycapacity);
		result->z = max(state.z - (Ycapacity - state.y), empty);
	}
}





//void pourfullX(State state, State *result){
//	result->x = Xcapacity;
//}
//
//void pourfullY(State state, State *result){
//	result->y = Ycapacity;
//}
//
//void makeNullX(State state, State *result){
//	result->x = empty;
//}
//
//void makeNullY(State state, State *result){
//	result->y = empty;
//}


int main(){
	State state, result;
	
	setStartState(&state, 9, 1, 2);
	
	printf("%d %d %d\n", state.x, state.y, state.z);

	
	pourZY(state, &result);

//	makeNullY(state, &result);
	
	printf("%d %d %d", result.x, result.y, result.z);

	return 0;
}
