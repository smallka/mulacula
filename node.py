OP_UMINUS = 1
OP_PLUS = 2
OP_MINUS = 3
OP_TIMES = 4
OP_DIVIDE = 5

class Node(object):
	def __init__(self):
		pass

	def Rpn(self, lst):
		lst.append(self)

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

	def __repr__(self):
		return "[value] %d" % self.value

class VariableNode(Node):
	def __init__(self, index):
		super(VariableNode, self).__init__()
		self.index = index

	def __repr__(self):
		return "[variable] %u" % self.index

class UnaryOpNode(Node):
	def __init__(self, op, value):
		super(UnaryOpNode, self).__init__()
		self.op = op
		self.value = value

	def Rpn(self, lst):
		self.value.Rpn(lst)
		super(UnaryOpNode, self).Rpn(lst)

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

	def Rpn(self, lst):
		self.left.Rpn(lst)
		self.right.Rpn(lst)
		super(BinaryOpNode, self).Rpn(lst)

	def __repr__(self):
		return "[op] %u" % self.op

	def Dump(self, indent):
		super(BinaryOpNode, self).Dump(indent)
		self.left.Dump("  " + indent)
		self.right.Dump("  " + indent)

