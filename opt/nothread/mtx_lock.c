#ifndef REGTEST
#include <threads.h>

int mtx_lock(mtx_t *mtx)
{
	if(*mtx == 0) {
		*mtx = 1;
		return thrd_success;
	} else return thrd_error;
}
#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif