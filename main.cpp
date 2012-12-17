
#include <vector>
#include "stdio.h"
#include "formula.h"

int main()
{
	std::vector<float> vars(1);

	vars[0] = 2;

	std::vector<RPNElem> elems(5);

	elems[0].type = RPN_VALUE;
	elems[0].u.value = 3;
	elems[1].type = RPN_VALUE;
	elems[1].u.value = 2.5;
	elems[2].type = RPN_VARIABLE;
	elems[2].u.index = 0;
	elems[3].type = RPN_BINARY_OP;
	elems[3].u.op = BINARY_OP_TIMES;
	elems[4].type = RPN_BINARY_OP;
	elems[4].u.op = BINARY_OP_PLUS;

	float ret = CalcRPN(elems, vars);
	printf("%f\n", ret);

	return 0;
}
