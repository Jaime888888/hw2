# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++11

# Executable name
EXEC = amazon

# Source files
SRCS = amazon.cpp mydatastore.cpp product.cpp user.cpp util.cpp \
       db_parser.cpp product_parser.cpp book.cpp clothing.cpp movie.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the program
all: $(EXEC)

# Link the object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(EXEC) $(OBJS)
