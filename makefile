
CXX					=	g++
OFILE				= formal
override CXXFLAGS	=	-ggdb -w
override TARGETS	+= source.cpp

all: clean $(OFILE)
	./$(OFILE)

formal:
	$(CXX) $(CXXFLAGS) $(TARGETS) -o $@

clean:
	-@test "$(CXX)" == "clang++" && rm -rf *.dSYM
	-rm $(OFILE)
