CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

OBJS = puzzle.o solver.o combinations.o

TASK8_OBJS = task8.o $(OBJS)
TARGET = task8.exe

TEST_OBJS = tests.o $(OBJS)
TEST_TARGET = tests.exe

all: $(TARGET)

$(TARGET): $(TASK8_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TASK8_OBJS)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

task8.o: task8.cpp puzzle.h solver.h combinations.h
	$(CXX) $(CXXFLAGS) -c task8.cpp

tests.o: tests.cpp puzzle.h solver.h combinations.h
	$(CXX) $(CXXFLAGS) -c tests.cpp

puzzle.o: puzzle.cpp puzzle.h combinations.h
	$(CXX) $(CXXFLAGS) -c puzzle.cpp

solver.o: solver.cpp solver.h puzzle.h combinations.h
	$(CXX) $(CXXFLAGS) -c solver.cpp

combinations.o: combinations.cpp combinations.h
	$(CXX) $(CXXFLAGS) -c combinations.cpp

clean:
	rm -f $(OBJS) $(TASK8_OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
