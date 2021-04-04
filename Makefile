# Directory that contains this project
PROJECT_DIR = 3780-CTP
PROJECT = 3780-CTP

TESTLIBS = -lgtest -lgtest_main -lpthread
OBJS = SimpleHeader.o

CXX=g++
CXXVERSION= -std=c++11

BINARIES = server sender

testSH: $(OBJS) test_header.o
				$(CXX) -o $@ $(OBJS) $(TESTLIBS)

all: $(BINARIES)

server: $(OBJS) receiver.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) receiver.cpp

sender: $(OBJS) sender.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) sender.cpp

.PHONY: clean
clean:
		rm -f *.o $(BINARIES) *~ *.d

## include the generate dependency files
-include $(addsuffix .d, $(basename $(OBJS)))
