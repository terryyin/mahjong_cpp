PRODUCT := mahjong
CPPUTEST_HOME := cpputest
CPPUTEST_USE_REAL_GTEST=Y
CPPUTEST_USE_REAL_GMOCK=Y
GMOCK_HOME=gmock

EVALUATOR = mahjong_evaluator
EVALUATOR_LIB = $(EVALUATOR)/lib/lib$(EVALUATOR).a
#CPPUTEST_WARNINGFLAGS :=  -Wall
#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = $(PRODUCT)

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

SRC_DIRS = \
	src/htmlGame\
	src/httpServer\
	src/mahjongCore

TEST_SRC_DIRS = \
	tst\
	tst/mahjongCore

INCLUDE_DIRS =\
  .\
  include\
  tst\
  $(SRC_DIRS)\
  $(EVALUATOR)/include\
  $(CPPUTEST_HOME)/include
  
PRDUCT_MAIN_OBJ = src/main.o
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

$(CPPUTEST_LIB) :
	cd $(GMOCK_HOME);./configure;make
	make -C cpputest all extensions CPPUTEST_USE_REAL_GMOCK=$(CPPUTEST_USE_REAL_GMOCK) GMOCK_HOME=../$(GMOCK_HOME)
	
$(EVALUATOR_LIB) :
	make -C $(EVALUATOR)
	
.PHONY: product
product : $(PRODUCT)
	./$(PRODUCT)
	
$(PRODUCT): $(PRDUCT_MAIN_OBJ) $(TARGET_LIB) $(EVALUATOR_LIB) $(CPPUTEST_LIB)
	@echo 'Building target: $@'
	$(CC) -o $@ -g $^ $(LD_LIBRARIES)
	@echo 'Running the game. Go to your browser to play at http://localhst:8888'
