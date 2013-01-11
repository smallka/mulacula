
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

	std::vector<RPNElem> elem_list;
	for (int i = 0; i < 7; i++)
	{
		elem_list.push_back(elems[i]);
	}

	long start;
	float val;

	float a = 2;
	float b = 4;
	val = 0;
	start = get_mono_time();
	for (int i = 0; i < 1000000; i++)
	{
		val += 3 + (a * 2.5 - b);
	}
	printf("c %f %ld\n", val, get_mono_time() - start);

	val = 0;
	start = get_mono_time();
	for (int i = 0; i < 1000000; i++)
	{
		val += CalcRPN2RAW(elems, 7, 2, 4);
	}
	printf("raw %f %ld\n", val, get_mono_time() - start);

	val = 0;
	start = get_mono_time();
	for (int i = 0; i < 1000000; i++)
	{
		val += CalcRPN2(&elem_list, 2, 4);
	}
	printf("vector %f %ld\n", val, get_mono_time() - start);

	val = 0;
	start = get_mono_time();
	for (int i = 0; i < 1000000; i++)
	{
		val += CalcRPN2STACK(&elem_list, 2, 4);
	}
	printf("stack %f %ld\n", val, get_mono_time() - start);

	val = 0;
	std::vector<RPNElem> elem_list_attr;
	RPNElem elem_attr;
	elem_list_attr.clear();
	elem_attr.type = 1;
	elem_attr.u.value = 2.0;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 5;
	elem_attr.u.index = 1;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 2;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 2;
	elem_attr.u.index = 0;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 5;
	elem_attr.u.index = 2;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 1;
	elem_attr.u.value = 4.0;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 4;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 3;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 1;
	elem_list_attr.push_back(elem_attr);
	// 2.0-p.level+a*(p.attack/4)

	Player player;
	player.level = 10;
	player.attack = 9;
	player.defence = 4;

	start = get_mono_time();
	for (int i = 0; i < 1000000; i++)
	{
		val += CalcRPN2Player(&elem_list_attr, &player, 2, 4);
	}
	printf("player %f %ld\n", val, get_mono_time() - start);

	// ------------------------------------------------------

	val = 0;
	elem_list_attr.clear();
	elem_attr.type = 1;
	elem_attr.u.value = 2.0;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 5;
	elem_attr.u.index = 1;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 2;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 2;
	elem_attr.u.index = 0;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 5;
	elem_attr.u.index = 2;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 1;
	elem_attr.u.value = 4.0;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 4;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 3;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 1;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 1;
	elem_attr.u.value = 0.1;
	elem_list_attr.push_back(elem_attr);
	elem_attr.type = 4;
	elem_attr.u.op = 6;
	elem_list_attr.push_back(elem_attr);
	// max(2.0-p.level+a*(p.attack/4), 0.1)

	player.level = 10;
	player.attack = 9;
	player.defence = 4;

	printf("ans %f\n", CalcRPN2Player(&elem_list_attr, &player, 2, 4));

	return 0;
}
