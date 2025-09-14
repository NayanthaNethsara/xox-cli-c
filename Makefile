# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRC = xox.c board.c filewrite.c gameplay.c

# Header files folder
INC = -I header

# Output executable
TARGET = xox.o

# Default target
all: $(TARGET)

# Compile and link
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(TARGET)

# Clean object files and executable
clean:
	rm -f $(TARGET)
