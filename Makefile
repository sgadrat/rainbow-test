CC := 6502-gcc
CA := /home/sylvain/workspace/nes/cc65/bin/ca65
LD := /home/sylvain/workspace/nes/cc65/bin/ld65
CFLAGS := -Os -Wall -Wextra -Werror
DEPS := nes_registers.h memory.h

all: game.S main.S game.o crt0.o ines.o main.o tiles.o game.nes

clean:
	rm game.S main.S game.o crt0.o ines.o main.o tiles.o game.nes game.map game.dbg

game.S: game.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

main.S: main.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

game.o: game.S
	$(CA) $<

crt0.o: crt0.S
	$(CA) $<

ines.o: ines.S
	$(CA) $<

main.o: main.S
	$(CA) $<

tiles.o: tiles.S
	$(CA) $<

game.nes: ld65.cfg tiles.o main.o ines.o crt0.o game.o 
	$(LD) -o $@ -C ld65.cfg --dbgfile game.dbg --mapfile game.map game.o crt0.o ines.o main.o tiles.o /home/sylvain/workspace/nes/n++/gcc-6502-bits/gcc-build/6502/libgcc/libgcc.a /home/sylvain/workspace/nes/n++/gcc-6502-bits/libtinyc/libtinyc.a
