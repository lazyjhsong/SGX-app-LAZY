# Make clean
MAKE := make
ROOT_SRC_DIR := /home/jhsong/work/sgx/SGX-app-LAZY
SUB_DIRS := $(ROOT_SRC_DIR)/simple \
	$(ROOT_SRC_DIR)/simple_rdtscp \
	$(ROOT_SRC_DIR)/Template_C_LAZY \
	$(ROOT_SRC_DIR)/hot-calls

.PHONY : all clean

all: clean

clean: 
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done
