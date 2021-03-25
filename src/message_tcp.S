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
	.export msg_set_protocol
msg_set_protocol:
; frame size 0, pretend size 0, outgoing size 0
	lda #$02
	sta $5000
	lda #$0e
	sta $5000
	lda #$02
	sta $5000
	lda #$00
	sta msg_ptr
	sta msg_ptr+1
	sta msg
	rts
	.export msg_get_message
msg_get_message:
; frame size 0, pretend size 0, outgoing size 0
	lda msg_ptr
	beq :+
	jmp L@3
	:
	lda msg_ptr+1
	beq :+
	jmp L@3
	:
	lda $5001
	sec
	sbc #$00
	bvc L@15
	eor #$80	; negate top bit
L@15:
	bmi L@4
	lda #$00
	sta msg
L@18:
	sta _r0
L@2:
	rts
L@4:
;# 149 "./lib/rainbow.h" 1
	lda $5000
	nop
	lda $5000
	sta msg
	ldy #$00
L@6:
	sty _r0
	cmp _r0
	bne L@7
	lda msg
	sta _r0
	beq L@2
	lda #$09
	sta $5000
	lda #$03
	sta $5000
	lda #$72
	sta $5000
	lda #$65
	sta $5000
	lda #$63
	sta $5000
	lda #$76
	sta $5000
	lda #$20
	sta $5000
	lda msg
	sta $5000
	ldx #$01
	lda msg+1
	sta $5000
	ldy msg+2
	sty $5000
	cpx msg
	bcc L@8
L@9:
	lda #$02
	jmp L@18
L@7:
	iny
	ldx $5000
	php
	sta _tmp0
	txa
	sta msg,y
	lda _tmp0
	plp
	jmp L@6
L@8:
	cmp #$08
	bne L@9
	lda #$02
	sta msg_ptr
	lda #$00
	sta msg_ptr+1
L@3:
	lda msg_ptr
	sta _r0
	lda msg_ptr+1
	sta _r1
	lda #<(msg)
	sta _r2
	lda #>(msg)
	clc
	adc _r1
	sta _r3
	ldy _r0
	lda (_r2),y
	sta last_msg_value
	cmp $0203
	bne L@9
	inc _r0
	bne L@17
	inc _r1
L@17:
	lda _r0
	sta msg_ptr
	lda _r1
	sta msg_ptr+1
	lda #$00
	sta _r3
	lda msg
	sta _r2
	lda _r1
	cmp _r3
	bcc L@10
	bne L@16
	lda _r2
	cmp _r0
	bcs L@10
L@16:
	lda #$00
	sta msg_ptr
	sta msg_ptr+1
L@10:
	lda #$01
	jmp L@18
	.segment "BSS"
	.global msg_ptr
msg_ptr:
	.res 2
	.global msg
msg:
	.res 257
