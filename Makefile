OBJECTS := main.o interuptHandler.o funcs.o

UFLAGS :=
CFLAGS :=
AFLAGS :=
LFLAGS :=

all: theYearGame
theYearGame: $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(UFLAGS) $(LFLAGS)
%.s: %.c *.h
	gcc -o $@ -S $< $(UFLAGS) $(CFLAGS)
%.o: %.s
	gcc -o $@ -c $< $(UFLAGS) $(AFLAGS)
