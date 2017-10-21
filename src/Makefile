
# Define some constants
# -------------------------------------- #
SHELL     = /bin/sh
COMPILER  = g++
FLAGS 	  = -std=c++11
PROGRAM   = titanic_analyzer
SRCS      = $(foreach d, ${CURDIR}, $(wildcard $(addprefix $(d)/*, .cpp)))
HEDS      = $(foreach d, ${CURDIR}, $(wildcard $(addprefix $(d)/*, .h)))
OBJS      = $(addsuffix .o, $(basename $(SRCS)))
LIB       = $(OBJS:.o=.d)
BUILD     = $(subst -g ,,$($(COMPILER) $(FLAGS)))
COMPILE   = $(COMPILER) $(FLAGS) -c
LINK   	  = $(COMPILER) $(FLAGS)
# -------------------------------------- #

# Define Rules
# -------------------------------------- #
.PHONY: all clean
.SUFFIXES:

all: $(PROGRAM)

%.d:%.cpp
	@$(BUILD) $< >> $@

objs:$(OBJS)

%.o:%.cpp
	$(COMPILE) $< -o $@


$(PROGRAM): $(OBJS)
	$(LINK) $(OBJS) -o $@
	
	@echo '# ------------------------------------------------------------------- #'
	@echo 'Project was built successfully!' 
	@echo '   - Please type (.\$@) to run the program'
	@echo '   - Or type (make clean) to clean up the project'
	@echo '# ------------------------------------------------------------------- #'	

clean:
	rm -f $(LIB) $(OBJS) $(PROGRAM) $(PROGRAM).exe
	@echo '# ------------------------------------------------------------------- #'
	@echo 'All code objects and executable files have been removed successfully!'
	@echo '# ------------------------------------------------------------------- #'
# -------------------------------------- #