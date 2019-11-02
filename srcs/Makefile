include ../Makefile.in

SRCS = coo.cpp csr.cpp vec.cpp
OBJS = $(SRCS:.cpp=.o)

../libams562proj1.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANDLIB) $@

clean:
	rm -f $(OBJS)

%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
