# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright © 2024      GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
#                       Matthias Kretz <m.kretz@gsi.de>

STRESS=7
TORTURE=0
CXXFLAGS:=-O2 -std=c++20 -Wall -D STRESS=$(STRESS) -ftime-report
suf:=$(STRESS)

ifneq ($(TORTURE),0)
CXXFLAGS+=-D TORTURE
suf:=$(suf)_tortured
endif

all: stress_fast_$(suf).o stress_$(suf).o

stress_fast_$(suf).o: stress.cpp Makefile
	$(CXX) $(CXXFLAGS) -D GO_FAST=1 -o $@ -c $<

stress_$(suf).o: stress.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ -c $<

help:
	@echo stress.o

clean:
	rm stress_*.o
