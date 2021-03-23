# Directory that contains this project
PROJECT_DIR = 3780-CTP
PROJECT = 3780-CTP

TESTLIBS = -lgtest -lgtest_main -lpthread
OBJS = SimpleHeader.o

CXX=g++
CXXVERSION= -std=c++11

BINARIES = receiver sender testSH

testSH: $(OBJS) test_header.o
				$(CXX) -o $@ $(OBJS) $(TESTLIBS)

all: $(BINARIES)

receiver: receiver.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o receiver receiver.cpp

sender: sender.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o sender sender.cpp

.PHONY: clean
clean:
		rm -f *.o $(BINARIES) *~ *.d

## include the generate dependency files
-include $(addsuffix .d, $(basename $(OBJS)))
