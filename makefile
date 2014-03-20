
EXE = assignment2.exe

CC = g++
CFLAGS = -std=c++11
DBUG_FLAGS = -g -ggdb

DEPSDIR = ../dependencies
GLMINCLUDS = $(DEPSDIR)/glm/glm

INCLUDES = -I$(GLMINCLUDS)

LIBS = -lGL -lglut -lGLU

SRCSDIR = src

SRCS = $(shell cd $(SRCSDIR); find . -name "*.cpp")

OBJSDIR = obj
OBJS = $(SRCS:%.cpp=%.o)
OBJS_WITH_DIRa = $(OBJS:./%.o=$(OBJSDIR)/%.o)
OBJS_WITH_DIR_TEST = $(filter-out %$(EXE).o,$(OBJS_WITH_DIRa))
OBJS_WITH_DIR_EXE  = $(filter-out %test.o, $(OBJS_WITH_DIRa))
RELEASEDIR = $(OBJSDIR)/Release
DEBUGDIR = $(OBJSDIR)/Debug
BINDIR = bin

release: make-obj-dirs $(OBJS_WITH_DIR_EXE)
	$(CC) $(CFLAGS) $(DBUG_FLAGS) -o $(EXE) $(OBJS_WITH_DIR_EXE) $(LIBS)
	mkdir -p $(BINDIR)
	mv $(EXE) $(BINDIR)

make-obj-dirs:
	mkdir -p $(OBJSDIR)
	mkdir -p $(OBJSDIR)/scene

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	g++ $(CFLAGS) $(DBUG_FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJSDIR)
	rm -rf $(BINDIR)

run:
	./$(BINDIR)/$(EXE) $(args)

debug:
	ddd $(BINDIR)/$(EXE)
