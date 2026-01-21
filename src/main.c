#include "main.h"
#include "stdlib.h"

int main() {
    Longlong *pa = malloc(sizeof(Longlong));
    ll_mul1(pa, 8, 16);
	free(pa);
	return 0;
}