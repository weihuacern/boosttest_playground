TESTBINARYNAME := test
VECTORBINARYNAME := vector
UNIQUEPTRBINARYNAME := unique_ptr

all: test vector unique_ptr

## test: Build test binary
test:
	g++ -std=c++11 src/solution_test.cpp src/solution.cpp -o $(TESTBINARYNAME)

## vector: Build vector binary
vector:
	g++ -std=c++11 src/huawei_vector_test.cpp src/huawei_vector.cpp -o $(VECTORBINARYNAME)

## unique_ptr: Build unique_ptr binary
unique_ptr:
	g++ -std=c++11 src/huawei_unique_ptr_test.cpp -o $(UNIQUEPTRBINARYNAME)

## clean: Clean up
clean:
	rm -rf $(TESTBINARYNAME)
	rm -rf $(VECTORBINARYNAME)
	rm -rf $(UNIQUEPTRBINARYNAME)

## help: Obtain help related information
help: Makefile
	@sed -n 's/^##//p' $<
