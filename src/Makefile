CXX=g++
CXXFLAGS=-ansi -Wall -g
LD=g++
AR=ar cqs
LDFLAGS=
RM = /bin/rm -Rf
LIB_PREFIX=../lib/
GENETIKLIB=libGenetiK.a

MKDIR=mkdir -p

SRC_PREFIX=./
OBJ_PREFIX=../obj/src/

SRCS=$(SRC_PREFIX)EvolutionaryAlgorithm.cpp\
	$(SRC_PREFIX)Population.cpp\
	$(SRC_PREFIX)SelectionMethod.cpp\
	$(SRC_PREFIX)RankingSelection.cpp\
	$(SRC_PREFIX)StopCriterionMaxIteration.cpp\
	$(SRC_PREFIX)Individual.cpp\
	$(SRC_PREFIX)RouletteWheel.cpp\
	$(SRC_PREFIX)TournamentSelection.cpp\
	$(SRC_PREFIX)IndividualFactory.cpp\
	$(SRC_PREFIX)StopCriterion.cpp\
	$(SRC_PREFIX)ga/Individual.cpp\
	$(SRC_PREFIX)ga/IndividualFactory.cpp\
	$(SRC_PREFIX)gp/Gene.cpp\
	$(SRC_PREFIX)gp/Individual.cpp\
	$(SRC_PREFIX)gp/IndividualFactory.cpp\
	$(SRC_PREFIX)gp/st/Gene.cpp\
	$(SRC_PREFIX)gp/st/Individual.cpp\
	$(SRC_PREFIX)gp/st/IndividualFactory.cpp\
	$(SRC_PREFIX)util/Exception.cpp\
	$(SRC_PREFIX)util/IllegalStateException.cpp\
	$(SRC_PREFIX)util/Log.cpp\
	$(SRC_PREFIX)util/Random.cpp\
	$(SRC_PREFIX)util/Variant.cpp

OBJS_NOPREFIX=$(SRCS:.cpp=.o)
OBJS=$(subst $(SRC_PREFIX),$(OBJ_PREFIX),$(OBJS_NOPREFIX))

.PHONY: all clean dep

all: $(LIB_PREFIX)$(GENETIKLIB)

$(LIB_PREFIX)$(GENETIKLIB): $(LIB_PREFIX) $(OBJ_PREFIX) $(OBJS) 
	$(AR) $(LIB_PREFIX)$(GENETIKLIB) $(OBJS)

$(LIB_PREFIX):
	$(MKDIR) $(LIB_PREFIX)

$(OBJ_PREFIX):
	$(MKDIR) $(OBJ_PREFIX)
	$(MKDIR) $(OBJ_PREFIX)util
	$(MKDIR) $(OBJ_PREFIX)ga
	$(MKDIR) $(OBJ_PREFIX)gp
	$(MKDIR) $(OBJ_PREFIX)gp/st

$(OBJ_PREFIX)%.o: $(SRC_PREFIX)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	$(RM) $(OBJ_PREFIX)
	$(RM) $(LIB_PREFIX)

dep: $(SRCS)
	sh ../scripts/makedepend.sh $(OBJ_PREFIX) $(subst $(SRC_PREFIX),,$(SRCS)) > depend

include depend




