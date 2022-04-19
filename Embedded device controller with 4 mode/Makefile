CC = arm-none-linux-gnueabi-gcc
CFLAGS = -pthread -static -Wall -c

SRCDIR = .
INCDIR = includes
TARGET = prog
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/environment.c $(SRCDIR)/shm.c $(SRCDIR)/device.c $(SRCDIR)/process/input_process.c $(SRCDIR)/process/main_process.c $(SRCDIR)/process/output_process.c $(SRCDIR)/module/counter_mode.c $(SRCDIR)/module/clock_mode.c $(SRCDIR)/module/texteditor_mode.c $(SRCDIR)/module/drawboard_mode.c

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(INCDIR)

$(TARGET): $(OBJECTS)
	$(CC) -pthread -static -o $@ $(OBJECTS) -I $(INCDIR)
	  rm -f $(OBJECTS)
clean:
	  rm -f $(OBJECTS) $(TARGET)
