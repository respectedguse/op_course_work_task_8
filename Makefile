CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

OBJS = task8.o puzzle.o solver.o combinations.o
TARGET = task8.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

task8.o: task8.cpp puzzle.h solver.h combinations.h
	$(CXX) $(CXXFLAGS) -c task8.cpp

puzzle.o: puzzle.cpp puzzle.h
	$(CXX) $(CXXFLAGS) -c puzzle.cpp

solver.o: solver.cpp solver.h puzzle.h combinations.h
	$(CXX) $(CXXFLAGS) -c solver.cpp

combinations.o: combinations.cpp combinations.h
	$(CXX) $(CXXFLAGS) -c combinations.cpp

clean:
	rm -f $(OBJS) $(TARGET)