#include "formula.h"
#include <vector>
#include <stack>
#include "stdio.h"

#define ERRORF(fmt, ...)	printf(fmt, __VA_ARGS__); printf("\n")
#define ERRORS(fmt)	printf(fmt); printf("\n")

#define MAX_STACK 1000

#define PUSH(var) if (stk_idx >= MAX_STACK) \
	{ \
		ERRORS("stack overflow"); \
		return 0.0f; \
	} \
	stk[++stk_idx] = var


#define TOP(var) if (stk_idx == -1) \
	{ \
		ERRORF("empty stack for type %u op %u", elem->type, elem->u.op); \
		stk[++stk_idx] = 0.0f; \
	} \
	var = stk[stk_idx];

float CalcRPN2(const std::vector<RPNElem> *rpn_list, float arg0, float arg1)
{
	static float stk[MAX_STACK+1];
	int stk_idx = -1;
	float left, right;

	for (std::vector<RPNElem>::const_iterator elem = rpn_list->begin();
			elem != rpn_list->end();
			elem++)
	{
		switch (elem->type)
		{
			case RPN_VALUE:
				PUSH(elem->u.value);
				break;

			case RPN_VARIABLE:
				switch (elem->u.index)
				{
					case 0:
						PUSH(arg0);
						break;
					case 1:
						PUSH(arg1);
						break;
					default:
						ERRORF("index out of range: %u", elem->u.index);
						PUSH(0.0f);
				}
				break;

			case RPN_BINARY_OP:
				TOP(right);
				stk_idx--;	// valid index guaranteed by TOP
				TOP(left);
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
				break;

			case RPN_UNARY_OP:
				TOP(left);
				switch (elem->u.op)
				{
					case UNARY_OP_NEGATIVE:
						stk[stk_idx] = -left;
					default:
						ERRORF("unknown unary op %u", elem->u.op);
				}
				break;

			default:
				ERRORF("unknown rpn type %u", elem->type);
				break;
		}
	}

	if (stk_idx != 0)
	{
		ERRORF("wrong stack index %d", stk_idx);
		return 0.0f;
	}

	return stk[0];
}

float CalcRPN2Player(const std::vector<RPNElem> *rpn_list, const Player *player, float arg0, float arg1)
{
	static float stk[MAX_STACK+1];
	int stk_idx = -1;
	float left, right;

	for (std::vector<RPNElem>::const_iterator elem = rpn_list->begin();
			elem != rpn_list->end();
			elem++)
	{
		switch (elem->type)
		{
			case RPN_VALUE:
				PUSH(elem->u.value);
				break;

			case RPN_VARIABLE:
				switch (elem->u.index)
				{
					case 0:
						PUSH(arg0);
						break;
					case 1:
						PUSH(arg1);
						break;
					default:
						ERRORF("index out of range: %u", elem->u.index);
						PUSH(0.0f);
				}
				break;

			case RPN_ATTR:
				switch (elem->u.index)
				{
					case PLAYER_LEVEL:
						PUSH(player->level);
						break;
					case PLAYER_ATTACK:
						PUSH(player->attack);
						break;
					case PLAYER_DEFENCE:
						PUSH(player->defence);
						break;
					default:
						ERRORF("unknown attr: %u", elem->u.index);
						PUSH(0.0f);
				}
				break;

			case RPN_BINARY_OP:
				TOP(right);
				stk_idx--;	// valid index guaranteed by TOP
				TOP(left);
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
				break;

			case RPN_UNARY_OP:
				TOP(left);
				switch (elem->u.op)
				{
					case UNARY_OP_NEGATIVE:
						stk[stk_idx] = -left;
					default:
						ERRORF("unknown unary op %u", elem->u.op);
				}
				break;

			default:
				ERRORF("unknown rpn type %u", elem->type);
				break;
		}
	}

	if (stk_idx != 0)
	{
		ERRORF("wrong stack index %d", stk_idx);
		return 0.0f;
	}

	return stk[0];
}

float CalcRPN2RAW(RPNElem rpn_list[], int rpn_count, float arg0, float arg1)
{
	static float stk[MAX_STACK+1];
	int stk_idx = -1;
	float left, right;

	for (RPNElem *elem = rpn_list; elem != rpn_list + rpn_count; elem++)
	{
		if (elem->type == RPN_VALUE)
		{
			PUSH(elem->u.value);
		}
		else if (elem->type == RPN_VARIABLE)
		{
			switch (elem->u.index)
			{
				case 0:
					PUSH(arg0);
					break;
				case 1:
					PUSH(arg1);
					break;
				default:
					ERRORF("index out of range: %u", elem->u.index);
					PUSH(0.0f);
			}
		}
		else if (elem->type == RPN_BINARY_OP)
		{
			TOP(right);
			stk_idx--;	// valid index guaranteed by TOP
			TOP(left);
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
			TOP(left);
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

#define STL_TOP(var) if (stk.empty()) \
	{ \
		ERRORF("empty stack for type %u op %u", elem->type, elem->u.op); \
		stk.push(0.0f); \
	} \
	var = stk.top()


float CalcRPN2STACK(const std::vector<RPNElem> *rpn_list, float arg0, float arg1)
{
	std::stack<float> stk;
	float left, right;

	for (std::vector<RPNElem>::const_iterator elem = rpn_list->begin();
			elem != rpn_list->end();
			elem++)
	{
		if (elem->type == RPN_VALUE)
		{
			stk.push(elem->u.value);
		}
		else if (elem->type == RPN_VARIABLE)
		{
			switch (elem->u.index)
			{
				case 0:
					stk.push(arg0);
					break;
				case 1:
					stk.push(arg1);
					break;
				default:
					ERRORF("index out of range: %u", elem->u.index);
					stk.push(0.0f);
			}
		}
		else if (elem->type == RPN_BINARY_OP)
		{
			STL_TOP(right);
			stk.pop();
			STL_TOP(left);
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
					ERRORF("unknown binary op %u", elem->u.op);
			}
		}
		else  // RPN_UNARY_OP
		{
			STL_TOP(left);
			switch (elem->u.op)
			{
				case UNARY_OP_NEGATIVE:
					stk.top() = -left;
				default:
					ERRORF("unknown unary op %u", elem->u.op);
			}
		}
	}

	if (stk.size() != 1)
	{
		ERRORF("wrong stack size %d", stk.size());
		return 0.0f;
	}

	return stk.top();
}
