TESTBINARYNAME := test
VECTORBINARYNAME := vector

all: test vector

## test: Build test binary
test:
	g++ -std=c++11 src/solution_test.cpp src/solution.cpp -o $(TESTBINARYNAME)

## vector: Build vector binary
vector:
	g++ -std=c++11 src/huawei_vector_test.cpp src/huawei_vector.cpp -o $(VECTORBINARYNAME)

## clean: Clean up
clean:
	rm -rf $(TESTBINARYNAME)
	rm -rf $(VECTORBINARYNAME)

## help: Obtain help related information
help: Makefile
	@sed -n 's/^##//p' $<
