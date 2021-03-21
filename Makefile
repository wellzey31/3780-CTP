# Directory that contains this project
PROJECT_DIR = 3780-CTP
PROJECT = 3780-CTP

TESTLIBS = -lgtest -lgtest_main -lpthread
OBJS = SimpleHeader.o test_header.o

CXX=g++
CXXVERSION= -std=c++11

BINARIES = receiver sender

testSH: $(OBJS)
				$(CXX) -o $@ $(OBJS) $(TESTLIBS)

all: $(BINARIES)

receiver: receiver.cpp SimpleHeader.h
	$(CXX) $(CXXFLAGS) -o receiver receiver.cpp

sender: sender.cpp SimpleHeader.h
	$(CXX) $(CXXFLAGS) -o sender sender.cpp

.PHONY: clean
clean:
		rm -f *.o $(BINARIES) *~ *.d

## include the generate dependency files
-include $(addsuffix .d, $(basename $(OBJS)))
