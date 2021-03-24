CC := 6502-gcc
CA := /home/sylvain/workspace/nes/cc65/bin/ca65
LD := /home/sylvain/workspace/nes/cc65/bin/ld65
DEPS := lib/nes_registers.h lib/memory.h lib/rainbow.h lib/utils.h
ROOT_DIR := .
CFLAGS := -Os -Wall -Wextra -Werror -I $(ROOT_DIR)

all: src/game.S src/main.S src/game.o system/crt0.o system/ines.o src/main.o tiles.o game.nes

clean:
	rm src/game.S src/main.S src/game.o system/crt0.o system/ines.o src/main.o tiles.o game.nes game.map game.dbg

src/game.S: src/game.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/main.S: src/main.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/game.o: src/game.S
	$(CA) $<

system/crt0.o: system/crt0.S
	$(CA) $<

system/ines.o: system/ines.S
	$(CA) $<

src/main.o: src/main.S
	$(CA) $<

tiles.o: tiles.S background.chr sprite.chr
	$(CA) $<

game.nes: system/ld65.cfg tiles.o src/main.o system/ines.o system/crt0.o src/game.o
	$(LD) -o $@ -C system/ld65.cfg --dbgfile game.dbg --mapfile game.map src/game.o system/crt0.o system/ines.o src/main.o tiles.o /home/sylvain/workspace/nes/n++/gcc-6502-bits/gcc-build/6502/libgcc/libgcc.a /home/sylvain/workspace/nes/n++/gcc-6502-bits/libtinyc/libtinyc.a
