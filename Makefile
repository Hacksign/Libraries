OS := $(shell uname -s)
CUR_DIR := $(shell pwd)
SUBDIRS := \
	$(CUR_DIR)/UserAgent \
	$(CUR_DIR)/HtmlParser \
	$(CUR_DIR)/Encode/Json \
	$(CUR_DIR)/Encode/Md5

ifeq ($(OS), Linux)
include Makefile.linux
else
include Makefile.win32
endif
