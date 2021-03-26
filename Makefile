CC := 6502-gcc
CA := ca65
LD := ld65
DEPS := lib/nes_registers.h lib/memory.h lib/rainbow.h lib/utils.h
ROOT_DIR := .
CFLAGS := -Os -Wall -Wextra -Werror -I $(ROOT_DIR)

all: \
	src/game.S \
	src/main.S \
	src/message_ws.S \
	src/message_tcp.S \
	src/message_udp_noloss.S \
	src/game.o \
	system/crt0.o \
	system/ines.o \
	src/main.o \
	src/message_ws.o \
	src/message_tcp.o \
	src/message_udp_noloss.o \
	chr/tiles.o \
	game_ws.nes \
	game_tcp.nes \
	game_udp_noloss.nes

clean:
	rm -f \
		src/game.S \
		src/main.S \
		src/message_ws.S \
		src/message_tcp.S \
		src/message_udp_noloss.S \
		src/game.o \
		system/crt0.o \
		system/ines.o \
		src/main.o \
		src/message_ws.o \
		src/message_tcp.o \
		src/message_udp_noloss.o \
		chr/tiles.o \
		game_ws.nes \
		game_ws.map \
		game_ws.dbg \
		game_tcp.nes \
		game_tcp.map \
		game_tcp.dbg

src/game.S: src/game.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/main.S: src/main.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/message_ws.S: src/message_ws.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/message_tcp.S: src/message_tcp.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/message_udp_noloss.S: src/message_udp_noloss.c $(DEPS)
	$(CC) $(CFLAGS) $< -S -o $@

src/game.o: src/game.S
	$(CA) $<

src/message_ws.o: src/message_ws.S
	$(CA) $<

src/message_tcp.o: src/message_tcp.S
	$(CA) $<

src/message_udp_noloss.o: src/message_udp_noloss.S
	$(CA) $<

system/crt0.o: system/crt0.S
	$(CA) $<

system/ines.o: system/ines.S
	$(CA) $<

src/main.o: src/main.S
	$(CA) $<

chr/tiles.o: chr/tiles.S chr/background.chr chr/sprite.chr
	$(CA) $<

game_ws.nes: system/ld65.cfg chr/tiles.o src/main.o system/ines.o system/crt0.o src/game.o src/message_ws.o
	$(LD) -o $@ \
	-C system/ld65.cfg \
	--dbgfile game_ws.dbg \
	--mapfile game_ws.map \
	src/game.o \
	src/message_ws.o \
	system/crt0.o \
	system/ines.o \
	src/main.o \
	chr/tiles.o \
	/home/sylvain/workspace/nes/n++/gcc-6502-bits/gcc-build/6502/libgcc/libgcc.a \
	/home/sylvain/workspace/nes/n++/gcc-6502-bits/libtinyc/libtinyc.a

game_tcp.nes: system/ld65.cfg chr/tiles.o src/main.o system/ines.o system/crt0.o src/game.o src/message_tcp.o
	$(LD) -o $@ \
	-C system/ld65.cfg \
	--dbgfile game_ws.dbg \
	--mapfile game_ws.map \
	src/game.o \
	src/message_tcp.o \
	system/crt0.o \
	system/ines.o \
	src/main.o \
	chr/tiles.o \
	/home/sylvain/workspace/nes/n++/gcc-6502-bits/gcc-build/6502/libgcc/libgcc.a \
	/home/sylvain/workspace/nes/n++/gcc-6502-bits/libtinyc/libtinyc.a

game_udp_noloss.nes: system/ld65.cfg chr/tiles.o src/main.o system/ines.o system/crt0.o src/game.o src/message_udp_noloss.o
	$(LD) -o $@ \
	-C system/ld65.cfg \
	--dbgfile game_ws.dbg \
	--mapfile game_ws.map \
	src/game.o \
	src/message_udp_noloss.o \
	system/crt0.o \
	system/ines.o \
	src/main.o \
	chr/tiles.o \
	/home/sylvain/workspace/nes/n++/gcc-6502-bits/gcc-build/6502/libgcc/libgcc.a \
	/home/sylvain/workspace/nes/n++/gcc-6502-bits/libtinyc/libtinyc.a
