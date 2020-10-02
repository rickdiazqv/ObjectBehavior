#include "useful.h"

int pow(int a, int x) {
	int res = 1;

	for (int i = 0; i < x; i++) {
		res *= a;
	}

	return res;
}