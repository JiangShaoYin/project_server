INC_DIR:= ./include/
SRCS:=$(wildcard ./src/*.cc) $(wildcard ./src/*.cpp)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) 
EXE:=./server.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXE)
