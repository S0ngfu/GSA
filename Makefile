# Project: GSA
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = src/Benchmark.o src/GSA.o src/MyAlgorithm.o src/Problem.o src/SetUpParams.o src/Solution.o
LINKOBJ  = src/Benchmark.o src/GSA.o src/MyAlgorithm.o src/Problem.o src/SetUpParams.o src/Solution.o
LIBS     = -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/lib" -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/x86_64-w64-mingw32/lib" -static-libstdc++ -static-libgcc
INCS     = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/lib/gcc/x86_64-w64-mingw32/6.2.1/include"
CXXINCS  = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/gcc-6-win64/lib/gcc/x86_64-w64-mingw32/6.2.1/include"
BIN      = GSA.exe
CXXFLAGS = $(CXXINCS) 
CFLAGS   = $(INCS) 
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

src/Benchmark.o: src/Benchmark.cpp
	$(CPP) -c src/Benchmark.cpp -o src/Benchmark.o $(CXXFLAGS)

src/GSA.o: src/GSA.cpp
	$(CPP) -c src/GSA.cpp -o src/GSA.o $(CXXFLAGS)

src/MyAlgorithm.o: src/MyAlgorithm.cpp
	$(CPP) -c src/MyAlgorithm.cpp -o src/MyAlgorithm.o $(CXXFLAGS)

src/Problem.o: src/Problem.cpp
	$(CPP) -c src/Problem.cpp -o src/Problem.o $(CXXFLAGS)

src/SetUpParams.o: src/SetUpParams.cpp
	$(CPP) -c src/SetUpParams.cpp -o src/SetUpParams.o $(CXXFLAGS)

src/Solution.o: src/Solution.cpp
	$(CPP) -c src/Solution.cpp -o src/Solution.o $(CXXFLAGS)
