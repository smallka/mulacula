
all:
	g++ formula.cpp -o formula

lint:
	python ../cpplint.py --filter=-whitespace,-whitespace/braces,-build/header_guard,-legal/copyright formula.*

clean:
	rm formula

