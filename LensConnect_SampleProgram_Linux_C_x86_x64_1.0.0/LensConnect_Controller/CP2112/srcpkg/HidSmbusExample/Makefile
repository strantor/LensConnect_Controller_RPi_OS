###########################################
# Simple Makefile for SLABHIDtoSMBus
# example application
#
# Tupham
# Silicon Labs
# 07-22-2022
###########################################

all: hidSMBusExample

OUT      ?= build/

CC       ?= gcc
CFLAGS   ?= -Wall -g -no-pie -Wl,-rpath=/usr/local/lib

CXX      ?= g++
CXXFLAGS ?= -Wall -g -no-pie -Wl,-rpath=/usr/local/lib

COBJS     = 
CPPOBJS   = main.o mainwindow.o Utilities.o
OBJS      = $(COBJS) $(CPPOBJS)
LDFLAGS  ?= -L/usr/local/lib
LIBS     ?= -lslabhidtosmbus -lslabhiddevice -lpthread -lusb-1.0
INCLUDES ?=


hidSMBusExample: $(OBJS) 
	mkdir -p $(OUT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $(OUT)hidSMBusExample
	
$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJS) $(OUT)hidSMBusExample
	rm -rf $(OUT)

.PHONY: clean

