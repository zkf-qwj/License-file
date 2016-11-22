FLEXLM_INST_ROOT=./flexNet
FLEXLM_INC_DIR=$(FLEXLM_INST_ROOT)/include
FLEXLM_LIB_DIR=$(FLEXLM_INST_ROOT)/lib

LIBEV_LIB=libev-4.15/lib 

FLEXLM_LIB_FLAGS=$(FLEXLM_LIB_DIR)/lm_new.o -L$(FLEXLM_LIB_DIR) -llmgr -lcrvs -lnoact -llmgr_dongle_stub -lsb
all: 
	g++  -g  retest.cpp   -o all  $(FLEXLM_LIB_FLAGS)  -ldl -lrt  -L. -llicense   -lev -L$(LIBEV_LIB) -lpthread
clean:
	rm all 
