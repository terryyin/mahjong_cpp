PRODUCT := mahjong
CPPUTEST_HOME := cpputest
CPPUTEST_USE_REAL_GTEST=Y
CPPUTEST_USE_REAL_GMOCK=Y
GMOCK_HOME=gmock-1.6.0

EVALUATOR = mahjong_evaluator
EVALUATOR_LIB = $(EVALUATOR)/lib/lib$(EVALUATOR).a
LD_LIBRARIES += -lpthread
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
  
-include $(CPPUTEST_HOME)/build/MakefileWorker.mk

$(EVALUATOR_LIB) :
	make -C $(EVALUATOR)
	
.PHONY: all product dependency
product : $(PRODUCT)
	
$(PRODUCT): $(PRDUCT_MAIN_OBJ) $(TARGET_LIB) $(EVALUATOR_LIB) $(CPPUTEST_LIB)
	@echo 'Building target: $@'
	$(CC) -o $@ -g $^ $(LD_LIBRARIES)
	@echo 'Running the game. Go to your browser to play at http://localhst:8888'

dependency:$(GMOCK_HOME).zip master.zip
	cd $(GMOCK_HOME) && ./configure && make && cd ..
	export GMOCK_HOME=../../$(GMOCK_HOME)	&& cd cpputest/lib && ../configure --enable-gmock && make
$(GMOCK_HOME).zip:
	wget https://googlemock.googlecode.com/files/$(GMOCK_HOME).zip
	unzip $(GMOCK_HOME).zip
master.zip:
	wget https://github.com/cpputest/cpputest/archive/master.zip
	unzip master.zip
	mv cpputest-master cpputest
