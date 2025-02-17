OBJECTS := main.o signalHandler.o funcs.o binOpOrder.o ipow.o

UFLAGS :=
CFLAGS :=
AFLAGS :=
LFLAGS :=

all: theYearGame
theYearGame: $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(UFLAGS) $(LFLAGS)
%.s: %.c *.h
	gcc -o $@ -S $< $(UFLAGS) $(CFLAGS)
%.o: %.s *.has
	gcc -o $@ -c $< $(UFLAGS) $(AFLAGS)

clean:
	rm *.o theYearGame