CFLAGS=-Wall -Wextra -O2
TARGET=backsh
SRC=backsh.c
OBJ=$(SRC:.c=.o)
PREFIX?=/usr/local
MANDIR=$(PREFIX)/share/man/man1
MANPAGE=backsh.1

.PHONY: all clean install uninstall

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Install the executable
install: $(TARGET)
	install -d $(PREFIX)/bin
	install -m 755 $(TARGET) $(PREFIX)/bin/$(TARGET)
	install -d $(MANDIR)
	install -m 644 $(MANPAGE) $(MANDIR)/$(MANPAGE)

# Uninstall the executable
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
	rm -f $(MANDIR)/$(MANPAGE)

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)
