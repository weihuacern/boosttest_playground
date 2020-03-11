TESTBINARYNAME := test

all: test

## test: Build test binary
test:
	g++ -std=c++11 src/solution_test.cpp src/solution.cpp -o $(TESTBINARYNAME)

## clean: Clean up
clean:
	rm -rf $(TESTBINARYNAME)

## help: Obtain help related information
help: Makefile
	@sed -n 's/^##//p' $<
