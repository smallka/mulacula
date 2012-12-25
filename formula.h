#ifndef __FORMULA_H__
#define __FORMULA_H__

#include <vector>

enum UNARY_OP_TYPE
{
	UNARY_OP_NEGATIVE = 1,
	UNARY_OP_COUNT,
};

enum BINARY_OP_TYPE
{
	BINARY_OP_PLUS = 1,
	BINARY_OP_MINUS,
	BINARY_OP_TIMES,
	BINARY_OP_DIVIDE,
	BINARY_OP_COUNT,
};

enum RPN_TYPE
{
	RPN_VALUE = 1,
	RPN_VARIABLE,
	RPN_UNARY_OP,
	RPN_BINARY_OP,
};

typedef struct RPNElem_t
{
	unsigned char type;
	union
	{
		float value;
		unsigned int index;
		unsigned char op;
	} u;
} RPNElem;

float CalcRPN2(RPNElem rpn_list[], int rpn_count, float arg0, float arg1);
float CalcRPN2VECTOR(const std::vector<RPNElem> *rpn_list, float arg0, float arg1);
float CalcRPN2STACK(const std::vector<RPNElem> *rpn_list, float arg0, float arg1);

#endif  // __FORMULA_H__
