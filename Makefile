CUR_DIR = $(shell pwd)
LIB = $(CUR_DIR)/lib
MAKE := make
MKDIR := mkdir -p
SUBDIRS := \
	$(CUR_DIR)/UserAgent \
	$(CUR_DIR)/Encode/Json \
	$(CUR_DIR)/HtmlParser

.PHONY : all clean

all : libs

libs :
	@$(MKDIR) $(LIB)
	@for f in $(SUBDIRS); do cd $${f} && $(MAKE) OUTPUT_DIR=$(LIB); done

clean :
	@for f in $(SUBDIRS); do cd $${f} && $(MAKE) clean; done
	rm -rf lib/*
