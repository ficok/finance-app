# Define the compiler and its flags
CC = gcc
CFLAGS = -Wall -Wextra -arch arm64

# List of source files and corresponding object files
SRCS = ./library/adding_funds.c ./library/spending_funds.c ./library/reserving.c ./library/loading.c ./library/logging.c ./library/reserving_functions.c ./library/utilities.c app.c
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = finance-app

# Default target (the first target in the file is the default)
all: $(TARGET)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean up object files and the executable
clean:
	rm -f $(OBJS)
