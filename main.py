import grammar

if __name__ == "__main__":
	import sys
	variables = [ "a", "t", "s.level", ]
	tree = grammar.Parse(sys.argv[1], variables)
	print "------- dump ------"
	tree.Dump("")
	print "------- rpn ------"
	lst = []
	tree.Rpn(lst)
	for node in lst:
		print node

