CXX=g++
CXXFLAGS=-ansi -Wall -g
LD=g++
AR=ar cqs
LDFLAGS=
RM=/bin/rm -Rf
MAKE=make
BIN_PREFIX=../bin/
EXAMPLE=example

MKDIR=mkdir -p

LINK_LIBRARIES=../lib/libGenetiK.a
OBJ_PREFIX=../obj/example/
SRC_PREFIX=./

SRCS=$(SRC_PREFIX)GeneticAlgorithm.cpp\
	$(SRC_PREFIX)GeneticProgramming.cpp\
	$(SRC_PREFIX)genetik.cpp\
	$(SRC_PREFIX)StronglyTypedGeneticProgramming.cpp

OBJS_NOPREFIX=$(SRCS:.cpp=.o)
OBJS=$(subst $(SRC_PREFIX),$(OBJ_PREFIX),$(OBJS_NOPREFIX))

.PHONY: all clean dep

all: $(BIN_PREFIX)$(EXAMPLE)

$(BIN_PREFIX)$(EXAMPLE): $(LINK_LIBRARIES) $(BIN_PREFIX) $(OBJ_PREFIX) $(OBJS) 
	$(LD) $(LDFLAGS) -o $(BIN_PREFIX)$(EXAMPLE) $(OBJS) $(LINK_LIBRARIES) 

$(LINK_LIBRARIES):
	cd ../src && $(MAKE)

$(BIN_PREFIX):
	$(MKDIR) $(BIN_PREFIX)

$(OBJ_PREFIX):
	$(MKDIR) $(OBJ_PREFIX)

$(OBJ_PREFIX)%.o: $(SRC_PREFIX)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	$(RM) $(OBJ_PREFIX)
	$(RM) $(BIN_PREFIX)

dep: $(SRCS)
	sh ../scripts/makedepend.sh $(OBJ_PREFIX) $(subst $(SRC_PREFIX),,$(SRCS)) > depend

include depend




