; Note: this file is derived from crt0.S present in the 6502-gcc project,
;       maybe it can be ported there one day.
        .feature at_in_identifiers

        .importzp _sp0, _sp1, _fp0, _fp1
        .importzp _r0, _r1, _r2, _r3, _r4, _r5, _r6, _r7
        .importzp _s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7
        .importzp _tmp0, _tmp1

	.import main
	.import nmi
	.import irq
	.import __DATA_RUN__
	.import __DATA_LOAD__
	.import __DATA_SIZE__

	.segment "VECTORS"
	.word _nmi
	.word __STARTUP_LOAD__
	.word irq

	.segment "STARTUP"
	sei        ; disable IRQs
	ldx #$40
	cld        ; disable decimal mode
	stx $4017  ; disable APU frame IRQ
	ldx #$FF
	txs        ; Set up stack

	.segment "STARTUP"
	__STACKTOP__ = $07ff
	__BSS_RUN__ = $0200
	__BSS_SIZE__ = $600

	__STARTUP_LOAD__:
	lda #38 ;
	sta 1   ; Why?
	lda #<__STACKTOP__
	sta _sp0
	lda #>__STACKTOP__
	sta _sp1
	; Clear BSS.
	lda #<__BSS_RUN__
	sta _r0
	lda #>__BSS_RUN__
	sta _r1
	lda #<__BSS_SIZE__
	sta _r2
	ldx #>__BSS_SIZE__
	stx _r3
	ora _r3
	beq nobss
	.scope
	ldy #0
loop:
	lda #0
	sta (_r0),y
	inc _r0
	bne :+
	inc _r1
:	dec _r2
	lda _r2
	cmp #255
	bne :+
	dec _r3
:	ora _r3
	bne loop
	.endscope
nobss:

	lda #<__DATA_LOAD__
	sta _r0
	lda #>__DATA_LOAD__
	sta _r1
	lda #<__DATA_RUN__
	sta _r2
	lda #>__DATA_RUN__
	sta _r3
	lda #<__DATA_SIZE__
	sta _r4
	ldx #>__DATA_SIZE__
	stx _r5
	ora _r5
	beq nodata

	lda _r0
	cmp _r2
	bne outerloop
	lda _r1
	cmp _r3
	beq nodata

outerloop:
	lda _r5
	beq lastpage

	ldy #0
copypage:
	lda (_r0),y
	sta (_r2),y
	iny
	bne copypage
	inc _r1
	inc _r3
	dec _r5
	jmp outerloop
lastpage:
	ldy #0
lastbit:
	lda (_r0),y
	sta (_r2),y
	iny
	cpy _r4
	bne lastbit
nodata:

rainbow_init:
	RAINBOW_PRG_BANKING_1 = $5002
	RAINBOW_PRG_BANKING_2 = $5003
	RAINBOW_PRG_BANKING_3 = $5004
	RAINBOW_WRAM_BANKING = $5005
	RAINBOW_CONFIGURATION = $5006
	RAINBOW_CHR_BANKING_1 = $5400
	RAINBOW_CHR_BANKING_2 = $5401
	RAINBOW_CHR_BANKING_3 = $5402
	RAINBOW_CHR_BANKING_4 = $5403
	RAINBOW_CHR_BANKING_5 = $5404
	RAINBOW_CHR_BANKING_6 = $5405
	RAINBOW_CHR_BANKING_7 = $5406
	RAINBOW_CHR_BANKING_8 = $5407
	RAINBOW_PULSE_CHANNEL_1_CONTROL = $5800
	RAINBOW_PULSE_CHANNEL_1_FREQ_LOW = $5801
	RAINBOW_PULSE_CHANNEL_1_FREQ_HIGH = $5802
	RAINBOW_PULSE_CHANNEL_2_CONTROL = $5803
	RAINBOW_PULSE_CHANNEL_2_FREQ_LOW = $5804
	RAINBOW_PULSE_CHANNEL_2_FREQ_HIGH = $5805
	RAINBOW_SAW_CHANNEL_FREQ_LOW = $5c01
	RAINBOW_SAW_CHANNEL_FREQ_HIGH = $5c02
	RAINBOW_MAPPER_VERSION = $5c03
	RAINBOW_IRQ_LATCH = $5c04
	RAINBOW_IRQ_RELOAD = $5c05
	RAINBOW_IRQ_DISABLE = $5c06
	RAINBOW_IRQ_ENABLE = $5c07

	; Configure rainbow mapper
	lda #%00010110 ; ssmmrccp - horizontal mirroring, CHR-ROM, 8k CHR window, 16k+8k+8k PRG banking
	sta RAINBOW_CONFIGURATION

	; Select the PRG bank just before the last for the variable 8k window (emulating 16k variable + 16k fixed banking)
	lda #%00111110 ; c.BBBBbb - PRG-ROM, befor the last bank
	sta RAINBOW_PRG_BANKING_3

	; Select the first CHR-BANK
	lda #%00000000 ; BBBBBBBB - first bank
	sta RAINBOW_CHR_BANKING_1

	; Disable scanline IRQ
	sta RAINBOW_IRQ_DISABLE

	; Disable sound extension
	;lda #%00000000 ; E...FFFF - disable, (don't care of frequency) ; useless - the value in A is already good
	sta RAINBOW_PULSE_CHANNEL_1_FREQ_HIGH
	sta RAINBOW_PULSE_CHANNEL_2_FREQ_HIGH
	sta RAINBOW_SAW_CHANNEL_FREQ_HIGH

call_program:
	lda #0
	sta _r0
	sta _r1
	sta _r2
	sta _r3
	jsr main
	; Retrieve exit code
	lda _r0

	; No exit possible on the NES, reboot
	jmp __STARTUP_LOAD__

_nmi:
	; Save CPU registers
	php
	pha
	txa
	pha
	tya
	pha

	; Call external implementation
	jsr nmi

	; Restore CPU registers
	pla
	tay
	pla
	tax
	pla
	plp

	rti
