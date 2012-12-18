
#include <vector>
#include "stdio.h"
#include "time.h"
#include "formula.h"

static long get_mono_time()
{
	timespec ts;

	if ( -1 == clock_gettime(CLOCK_MONOTONIC, &ts))
	{
		return 0;
	}
	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

int main()
{
	RPNElem elems[7];

	elems[0].type = RPN_VALUE;
	elems[0].u.value = 3;

	elems[1].type = RPN_VALUE;
	elems[1].u.value = 2.5;
	elems[2].type = RPN_VARIABLE;
	elems[2].u.index = 0;
	elems[3].type = RPN_BINARY_OP;
	elems[3].u.op = BINARY_OP_TIMES;

	elems[4].type = RPN_VARIABLE;
	elems[4].u.index = 1;
	elems[5].type = RPN_BINARY_OP;
	elems[5].u.op = BINARY_OP_MINUS;

	elems[6].type = RPN_BINARY_OP;
	elems[6].u.op = BINARY_OP_PLUS;

	long start;
	int val;

	val = 0;
	start = get_mono_time();
	for (int i = 0; i < 100000; i++)
	{
		val += 3 + (2 * 2.5 - 4);
	}
	printf("%d %ld\n", val, get_mono_time() - start);

	val = 0;
	start = get_mono_time();
	for (int i = 0; i < 100000; i++)
	{
		val += CalcRPN2(elems, 7, 2, 4);
	}
	printf("%d %ld\n", val, get_mono_time() - start);

	return 0;
}
