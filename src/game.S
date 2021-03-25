	.feature at_in_identifiers
	.feature dollar_in_identifiers
	.autoimport +
	.p02
	.importzp _sp0, _sp1, _fp0, _fp1
	.importzp _r0, _r1, _r2, _r3, _r4, _r5, _r6, _r7
	.importzp _s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7
	.importzp _e0, _e1, _e2, _e3, _e4, _e5, _e6, _e7
	.importzp _e8, _e9, _e10, _e11, _e12, _e13, _e14, _e15
	.importzp _e16, _e17, _e18, _e19, _e20, _e21, _e22, _e23
	.importzp _e24, _e25, _e26, _e27, _e28, _e29, _e30, _e31
	.importzp _tmp0, _tmp1
	.importzp _sa, _sx, _sy
	.segment "CODE"
esp_send_cmd:
; frame size 0, pretend size 0, outgoing size 0
	lda _r1
	sta _r3
	lda _r0
	sta _r2
	ldy #$00
	lda (_r2),y
	sta _r1
	sta $5000
	ldy #$01
L@2:
	lda (_r2),y
	sta $5000
	tya
	clc
	adc #$01
	cpy _r1
	bne L@3
	rts
L@3:
	tay
	jmp L@2
	.export game_init
game_init:
; frame size 0, pretend size 0, outgoing size 0
	lda #$80
	sta $0200
	lda #$01
	sta $0201
	lda #$00
	sta $0202
	sta $0203
	lda $2002
	lda #$3f
	sta $2006
	lda #$00
	sta $2006
	lda #<(palettes$1525)
	sta _r0
	lda #>(palettes$1525)
	sta _r1
	lda #$20
L@5:
	sta _sa
	ldy #$00
	lda (_r0),y
	tax
	lda _sa
	stx $2007
	clc
	adc #$ff
	inc _r0
	bne L@7
	inc _r1
L@7:
	cmp #$00
	bne L@5
	sta ready_state
	lda #$01
	sta $5001
	lda #<(cmd_get_status$1530)
	sta _r0
	lda #>(cmd_get_status$1530)
	sta _r1
	jsr esp_send_cmd
	rts
	.export game_tick
game_tick:
; frame size 0, pretend size 0, outgoing size 0
	lda ready_state
	cmp #$02
	beq L@9
	lda $5001
	sec
	sbc #$00
	bvc L@24
	eor #$80	; negate top bit
L@24:
	bmi L@10
	lda #$00
	sta ready_msg
L@8:
	rts
L@10:
;# 149 "./lib/rainbow.h" 1
	lda $5000
	nop
	lda $5000
	sta ready_msg
	ldy #$00
L@12:
	sty _r0
	cmp _r0
	bne L@13
	lda ready_msg
	beq L@8
	lda ready_msg+1
	beq L@14
	cmp #$02
	bne L@8
	lda ready_msg+2
	cmp #$03
	bne L@16
	lda #$02
	sta ready_state
	jmp L@8
L@13:
	iny
	ldx $5000
	php
	sta _tmp0
	txa
	sta ready_msg,y
	lda _tmp0
	plp
	jmp L@12
L@14:
	lda #<(cmd_restore_settings$1521)
	sta _r0
	lda #>(cmd_restore_settings$1521)
	sta _r1
	jsr esp_send_cmd
	jsr msg_set_protocol
	lda #<(cmd_connect$1522)
	sta _r0
	lda #>(cmd_connect$1522)
	sta _r1
	jsr esp_send_cmd
	lda #$01
	sta ready_state
L@16:
	lda #<(cmd_get_wifi_status$1533)
	sta _r0
	lda #>(cmd_get_wifi_status$1533)
	sta _r1
	jsr esp_send_cmd
	jmp L@8
L@9:
	jsr msg_get_message
	lda _r0
	cmp #$01
	beq L@17
	cmp #$02
	bne L@8
	lda #$8c
	sta $0204
	lda #$01
	sta $0205
	lda #$00
	sta $0206
	lda last_msg_value
	sta $0207
L@20:
	jmp L@20
L@17:
	inc $0203
	jmp L@8
	.segment "RODATA"
cmd_connect$1522:
	.byte	$01
	.byte	$13
cmd_restore_settings$1521:
	.byte	$01
	.byte	$12
cmd_get_wifi_status$1533:
	.byte	$01
	.byte	$06
cmd_get_status$1530:
	.byte	$01
	.byte	$00
palettes$1525:
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$0f
	.byte	$00
	.byte	$10
	.byte	$20
	.byte	$0f
	.byte	$20
	.byte	$20
	.byte	$20
	.byte	$0f
	.byte	$20
	.byte	$20
	.byte	$20
	.byte	$0f
	.byte	$20
	.byte	$20
	.byte	$20
	.export WIFI_READY
WIFI_READY:
	.byte	$02
	.export ESP_READY
ESP_READY:
	.byte	$01
	.export NOT_READY
NOT_READY:
.res 1,$00
	.segment "BSS"
	.global ready_state
ready_state:
	.res 1
	.global last_msg_value
last_msg_value:
	.res 1
	.global ready_msg
ready_msg:
	.res 3
