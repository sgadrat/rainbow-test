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
	.export nmi
nmi:
; frame size 0, pretend size 0, outgoing size 0
	lda #$00
	sta $2003
	lda #$02
	sta $4014
	lda $2002
	lda #$00
	sta $2005
	sta $2005
	rts
	.export irq
irq:
; frame size 0, pretend size 0, outgoing size 0
	rts
	.export main
main:
; frame size 0, pretend size 0, outgoing size 0
	lda #$00
	sta $2000
	sta $2001
	sta $4010
L@4:
	lda $2002
	sec
	sbc #$00
	bvc L@15
	eor #$80	; negate top bit
L@15:
	bpl L@4
	lda #$00
L@5:
	sta _r0
	ldx #$00
	stx _r3
	tax
	sta _r2
	clc
	lda _r3
	adc #$02
	sta _r3
	lda #$ff
	ldy #$00
	sta (_r2),y
	lda _r0
	inx
	cmp #$ff
	bne L@9
L@6:
	lda $2002
	sec
	sbc #$00
	bvc L@14
	eor #$80	; negate top bit
L@14:
	bpl L@6
	jsr game_init
	lda #$90
	sta $2000
	lda #$1e
	sta $2001
L@8:
	jsr game_tick
L@7:
	lda $2002
	sec
	sbc #$00
	bvc L@13
	eor #$80	; negate top bit
L@13:
	bpl L@7
	jmp L@8
L@9:
	txa
	jmp L@5
