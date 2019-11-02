include Makefile.in

all: libams562proj1.a prog

prog: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp libams562proj1.a
	./prog

libams562proj1.a:
	$(MAKE) -C srcs

.PHONY: clean prog

clean:
	cd srcs; make clean
	rm -f libams562proj1.a prog
