#!/bin/bash

fceux_bin=~/workspace/nes/fceux/build/src/fceux
socketsrv_bin=~/workspace/socketsrv/socketsrv.py

t='udp_noloss'

if [ $t == 'udp_noloss' ]; then
	# Test: Connect udp_noloss ROM to a server sending UDP packets slowly
	# Expected result: White square moves slowly, error square does not appear
	(while true; do for i in {0..255}; do echo sendb udp 0 $(printf %02x $i); sleep 1; done; done) | "$socketsrv_bin" --batch &
	socketsrv_pid=$!
	RAINBOW_SERVER_ADDR=127.0.0.1 RAINBOW_SERVER_PORT=1234 "$fceux_bin" game_udp_noloss.nes
	kill $socketsrv_pid
fi
