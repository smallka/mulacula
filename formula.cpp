#include "formula.h"

#include <stack>
#include <vector>

#ifdef SINGLE_RUN
#include "stdio.h"
#define ERRORF(fmt, ...)	printf(fmt, __VA_ARGS__); printf("\n")
#define ERRORS(fmt)	printf(fmt); printf("\n")
#else
#include "log.h"
#endif

#define SAFE_TOP(var) if (stk.empty()) \
	{ \
		ERRORF("empty stack for type %u op %u", elem->type, elem->u.op); \
		stk.push(0.0f); \
	} \
	var = stk.top();


float CalcRPN(const std::vector<RPNElem>& elems, const std::vector<float>& vars)
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
				ERRORF("index out of range: %u",
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
						ERRORS("division by 0");
					}
					else
					{
						stk.top() = left / right;
					}
					break;
				default:
					ERRORF("unknown binary op %u",
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
					ERRORF("unknown binary op %u",
							elem->u.op);
			}
		}
	}

	if (stk.size() != 1)
	{
		ERRORF("wrong stack size %lu", stk.size());
		return 0.0f;
	}

	return stk.top();
}
