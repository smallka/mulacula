#ifndef __FORMULA_H__
#define __FORMULA_H__

#include <vector>

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

float CalcRPN(const std::vector<float>& vars, const std::vector<RPNElem>& elems);

#endif  // __FORMULA_H__
