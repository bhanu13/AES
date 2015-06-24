EXENAME = AES
OBJS = main.o AES.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp AES.h
	$(CXX) $(CXXFLAGS) main.cpp

AES.o : AES.h AES.cpp tables.h
	$(CXX) $(CXXFLAGS) AES.cpp

clean :
	-rm -f *.o $(EXENAME)