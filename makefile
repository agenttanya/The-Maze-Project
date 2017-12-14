CXX = g++
CXXFLAGS = -g -std=c++11 $(shell fltk-config --cxxflags)
LDFLAGS = $(shell fltk-config --use-images --ldflags)

.SUFFIXES: .cpp .o

GRAPHLIB = GUI.o Graph.o Window.o
GRAPHINC = GUI.h Graph.h Point.h Simple_window.h Window.h fltk.h Vector_ref.h

TARGETS = test.exe test_move.exe test_automove.exe test_keyboard.exe test_vector_ref.exe

default: all

.PHONY: all clean

all: $(TARGETS)

.PRECIOUS: %.o

%.exe: %.cpp $(GRAPHLIB) $(GRAPHINC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(GRAPHLIB) $(LDFLAGS)

%.o: %.cpp $(GRAPHINC)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGETS) $(GRAPHLIB) *.dSYM

