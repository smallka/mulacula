#include "formula.h"
#include <vector>
#include "stdio.h"

#define ERRORF(fmt, ...)	printf(fmt, __VA_ARGS__); printf("\n")
#define ERRORS(fmt)	printf(fmt); printf("\n")

#define MAX_STACK 1000

#define SAFE_PUSH(var) if (stk_idx >= MAX_STACK) \
	{ \
		ERRORS("stack overflow"); \
		return 0.0f; \
	} \
	stk[++stk_idx] = var


#define SAFE_TOP(var) if (stk_idx == -1) \
	{ \
		ERRORF("empty stack for type %u op %u", elem->type, elem->u.op); \
		stk[++stk_idx] = 0.0f; \
	} \
	var = stk[stk_idx];


float CalcRPN2(RPNElem elem_list[], int elem_count, float arg0, float arg1)
{
	static float stk[MAX_STACK+1];
	int stk_idx = -1;
	float left, right;

	for (RPNElem *elem = elem_list; elem != elem_list + elem_count; elem++)
	{
		if (elem->type == RPN_VALUE)
		{
			SAFE_PUSH(elem->u.value);
		}
		else if (elem->type == RPN_VARIABLE)
		{
			switch (elem->u.index)
			{
				case 0:
					SAFE_PUSH(arg0);
					break;
				case 1:
					SAFE_PUSH(arg1);
					break;
				default:
					ERRORF("index out of range: %u", elem->u.index);
					SAFE_PUSH(0.0f);
			}
		}
		else if (elem->type == RPN_BINARY_OP)
		{
			SAFE_TOP(right);
			stk_idx--;	// valid index guaranteed by SAFE_TOP
			SAFE_TOP(left);
			switch (elem->u.op)
			{
				case BINARY_OP_PLUS:
					stk[stk_idx] = left + right;
					break;
				case BINARY_OP_MINUS:
					stk[stk_idx] = left - right;
					break;
				case BINARY_OP_TIMES:
					stk[stk_idx] = left * right;
					break;
				case BINARY_OP_DIVIDE:
					if (right == 0.0f)
					{
						ERRORS("division by 0");
					}
					else
					{
						stk[stk_idx] = left / right;
					}
					break;
				default:
					ERRORF("unknown binary op %u", elem->u.op);
			}
		}
		else  // RPN_UNARY_OP
		{
			SAFE_TOP(left);
			switch (elem->u.op)
			{
				case UNARY_OP_NEGATIVE:
					stk[stk_idx] = -left;
				default:
					ERRORF("unknown unary op %u", elem->u.op);
			}
		}
	}

	if (stk_idx != 0)
	{
		ERRORF("wrong stack index %d", stk_idx);
		return 0.0f;
	}

	return stk[0];
}
