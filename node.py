UNARY_OP_NEGATIVE = 1

BINARY_OP_PLUS = 1
BINARY_OP_MINUS = 2
BINARY_OP_TIMES = 3
BINARY_OP_DIVIDE = 4

RPN_VALUE = 1
RPN_VARIABLE = 2
RPN_UNARY_OP = 3
RPN_BINARY_OP = 4
RPN_ATTR = 5

class Node(object):
	def __init__(self):
		pass

	def GenRPN(self, lst):
		raise NotImplementedError("Subclasses should implement this!")

	def __repr__(self):
		raise NotImplementedError("Subclasses should implement this!")

	def Dump(self, indent):
		print indent + str(self)

class ErrorNode(Node):
	def __init__(self, msg):
		super(ErrorNode, self).__init__()
		self.msg = msg

	def __repr__(self):
		return "[ERROR] " + self.msg

class ValueNode(Node):
	def __init__(self, value):
		super(ValueNode, self).__init__()
		self.value = value

	def GenRPN(self, lst):
		lst.append([ RPN_VALUE, self.value, ])

	def __repr__(self):
		return "[value] %f" % self.value

class VariableNode(Node):
	def __init__(self, index):
		super(VariableNode, self).__init__()
		self.index = index

	def GenRPN(self, lst):
		lst.append([ RPN_VARIABLE, self.index, ])

	def __repr__(self):
		return "[variable] %u" % self.index

class UnaryOpNode(Node):
	def __init__(self, op, value):
		super(UnaryOpNode, self).__init__()
		self.op = op
		self.value = value

	def GenRPN(self, lst):
		self.value.GenRPN(lst)
		lst.append([ RPN_UNARY_OP, self.op, ])

	def __repr__(self):
		return "[op] %u" % self.op

	def Dump(self, indent):
		super(UnaryOpNode, self).Dump(indent)
		self.value.Dump("  " + indent)

class BinaryOpNode(Node):
	def __init__(self, op, left, right):
		super(BinaryOpNode, self).__init__()
		self.op = op
		self.left = left
		self.right = right

	def GenRPN(self, lst):
		self.left.GenRPN(lst)
		self.right.GenRPN(lst)
		lst.append([ RPN_BINARY_OP, self.op, ])

	def __repr__(self):
		return "[op] %u" % self.op

	def Dump(self, indent):
		super(BinaryOpNode, self).Dump(indent)
		self.left.Dump("  " + indent)
		self.right.Dump("  " + indent)

class AttrNode(Node):
	def __init__(self, index):
		super(AttrNode, self).__init__()
		self.index = index

	def GenRPN(self, lst):
		lst.append([ RPN_ATTR, self.index, ])

	def __repr__(self):
		return "[attr] %u" % self.index
