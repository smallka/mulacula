# simple calculator with variables -- all in one file.
# -----------------------------------------------------------------------------

tokens = (
	'VARIABLE','NUMBER',
	'PLUS','MINUS','TIMES','DIVIDE',
	'LPAREN','RPAREN',
)

# Tokens

t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_VARIABLE = r'[a-zA-Z_][a-zA-Z0-9_.]*'

def t_NUMBER(t):
	r"""([0-9]*\.[0-9]+)|(\d+)"""
	t.value = float(t.value)
	return t

def t_error(t):
	print("Illegal character '%s'" % t.value[0])
	t.lexer.skip(1)

# Build the lexer
import ply.lex as lex
lex.lex()

# Parsing rules

import node

var2index = {}

precedence = (
	('left','PLUS','MINUS'),
	('left','TIMES','DIVIDE'),
	('right','NEGATIVE'),
	)


def p_expression_plus(t):
	'''expression : expression PLUS expression'''
	t[0] = node.BinaryOpNode(node.BINARY_OP_PLUS, t[1], t[3])

def p_expression_minus(t):
	'''expression : expression MINUS expression'''
	t[0] = node.BinaryOpNode(node.BINARY_OP_MINUS, t[1], t[3])

def p_expression_times(t):
	'''expression : expression TIMES expression'''
	t[0] = node.BinaryOpNode(node.BINARY_OP_TIMES, t[1], t[3])

def p_expression_divide(t):
	'''expression : expression DIVIDE expression'''
	t[0] = node.BinaryOpNode(node.BINARY_OP_DIVIDE, t[1], t[3])

def p_expression_uminus(t):
	'expression : MINUS expression %prec NEGATIVE'
	if t[2].node_type == node.NODE_VALUE:
		t[0] = node.ValueNode(-t[2].value)
	else:
		t[0] = node.UnaryOpNode(node.UNARY_OP_NEGATIVE, t[2])

def p_expression_group(t):
	'expression : LPAREN expression RPAREN'
	t[0] = t[2]

def p_expression_number(t):
	'expression : NUMBER'
	t[0] = node.ValueNode(t[1])

def p_expression_variable(t):
	'expression : VARIABLE'
	index = var2index.get(t[1])
	if index is None:
		msg = "Undefined variable '%s'" % t[1]
		print(msg)
		t[0] = node.ErrorNode(msg)
	else:
		t[0] = node.VariableNode(index)

def p_error(t):
	print("Syntax error at '%s'" % t.value)

import ply.yacc as yacc
yacc.yacc()

########

def Parse(formula, variables):
	global var2index
	var2index.clear()
	for i in xrange(len(variables)):
		var2index[variables[i]] = i

	return yacc.parse(formula)

