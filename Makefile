# Compiler and flags
CC = gcc
CFLAGS = -g

# Directories
OBJDIR = obj
SRCDIR = .
BINDIR = .

# Target and objects
TARGET = test.exe
OBJS = $(OBJDIR)/gluethread/glthread.o \
       $(OBJDIR)/graph.o \
       $(OBJDIR)/topologies.o \
       $(OBJDIR)/testapp.o

# Create object directories if they don't exist
$(shell mkdir -p $(OBJDIR)/gluethread)

# Pattern rule for object files
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -I. -Igluethread -c $< -o $@

# Pattern rule for gluethread objects
$(OBJDIR)/gluethread/%.o: gluethread/%.c
	$(CC) $(CFLAGS) -I. -Igluethread -c $< -o $@

# Final target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	echo '#!/bin/sh' > run.sh
	echo '/lib64/ld-linux-x86-64.so.2 ./test.exe "$$@"' >> run.sh
	chmod +x run.sh

# Clean up object files and executables
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/gluethread/*.o $(TARGET)
	rm -rf $(OBJDIR)

# Build all target
.PHONY: all
all: $(TARGET)