#include "memory.h"

int is_in(int *array, int size, int item) {
	int i;
	for(i=0;i<size;i++){
		if(array[i] == item){
			return 1;
		}
	}
	return 0;
}
