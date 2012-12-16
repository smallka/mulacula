import grammar

if __name__ == "__main__":
	import sys
	variables = [ "a", "b", "c", ]
	tree = grammar.Parse(sys.argv[1], variables)
	print "------- dump ------"
	tree.Dump("")
	print "------- rpn ------"
	lst = []
	tree.Rpn(lst)
	for node in lst:
		print node

