#include "formula.h"

#include <stack>
#include <vector>
#include "stdio.h"
#include "share_const.h"

#define SAFE_TOP(var) if (stk.empty()) \
	{ \
		printf("empty stack for type %u op %u\n", elem->type, elem->u.op); \
		stk.push(0.0f); \
	} \
	var = stk.top();

float CalcRPN(const std::vector<float>& vars, const std::vector<RPNElem>& elems)
{
	std::stack<float> stk;
	float left, right;

	for (std::vector<RPNElem>::const_iterator elem = elems.begin();
			elem != elems.end();
			elem++)
	{
		if (elem->type == RPN_VALUE)
		{
			stk.push(elem->u.value);
		}
		else if (elem->type == RPN_VARIABLE)
		{
			if (elem->u.index >= vars.size())
			{
				printf("index out of range: %u\n",
						elem->u.index);
				stk.push(0.0f);
			}
			else
			{
				stk.push(vars[elem->u.index]);
			}
		}
		else if (elem->type == RPN_BINARY_OP)
		{
			SAFE_TOP(left);
			stk.pop();
			SAFE_TOP(right);
			switch (elem->u.op)
			{
				case BINARY_OP_PLUS:
					stk.top() = left + right;
					break;
				case BINARY_OP_MINUS:
					stk.top() = left - right;
					break;
				case BINARY_OP_TIMES:
					stk.top() = left * right;
					break;
				case BINARY_OP_DIVIDE:
					if (right == 0.0f)
					{
						printf("division by 0\n");
					}
					else
					{
						stk.top() = left / right;
					}
					break;
				default:
					printf("unknown binary op %u\n",
							elem->u.op);
			}
		}
		else  // RPN_UNARY_OP
		{
			SAFE_TOP(left);
			switch (elem->u.op)
			{
				case UNARY_OP_NEGATIVE:
					stk.top() = -left;
				default:
					printf("unknown binary op %u\n",
							elem->u.op);
			}
		}
	}

	if (stk.size() != 1)
	{
		printf("wrong stack size %lu\n", stk.size());
		return 0.0f;
	}

	return stk.top();
}

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

	float ret = CalcRPN(vars, elems);
	printf("%f\n", ret);

	return 0;
}
