# Directory that contains this project
PROJECT_DIR = 3780-CTP
PROJECT = 3780-CTP

CXX=g++
CXXVERSION= -std=c++11

BINARIES = receiver sender

all: $(BINARIES)

receiver: receiver.cpp
	$(CXX) $(CXXFLAGS) -o receiver receiver.cpp

sender: sender.cpp
	$(CXX) $(CXXFLAGS) -o sender sender.cpp

.PHONY: clean
clean:
		rm -f *.o $(BINARIES)
