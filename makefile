# Makefile for the parsing program

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Target executable
TARGET = parsing

# Source files
SRCS = parsing.c injection.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)