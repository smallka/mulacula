import grammar

if __name__ == "__main__":
	import sys
	attrs = {
		"p.level" : 1,
		"p.attack" : 2,
		"p.defence" : 3,
	}
	variables = [ "team_count", "level", ]
	tree = grammar.Parse(sys.argv[1], variables, attrs)
	print "------- dump ------"
	tree.Dump("")
	print "------- rpn ------"
	lst = []
	tree.GenRPN(lst)
	for node in lst:
		print node

