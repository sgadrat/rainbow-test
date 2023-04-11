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

	.export RAINBOW_WIFI_RX, RAINBOW_WIFI_TX

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

	RAINBOW_PRG_BANKING_MODE = $4100

	RAINBOW_PRG_ROM_BANKING_1_HI = $4108
	RAINBOW_PRG_ROM_BANKING_2_HI = $4109
	RAINBOW_PRG_ROM_BANKING_3_HI = $410a
	RAINBOW_PRG_ROM_BANKING_4_HI = $410b
	RAINBOW_PRG_ROM_BANKING_5_HI = $410c
	RAINBOW_PRG_ROM_BANKING_6_HI = $410d
	RAINBOW_PRG_ROM_BANKING_7_HI = $410e
	RAINBOW_PRG_ROM_BANKING_8_HI = $410f
	RAINBOW_PRG_ROM_BANKING_1_LO = $4118
	RAINBOW_PRG_ROM_BANKING_2_LO = $4119
	RAINBOW_PRG_ROM_BANKING_3_LO = $411a
	RAINBOW_PRG_ROM_BANKING_4_LO = $411b
	RAINBOW_PRG_ROM_BANKING_5_LO = $411c
	RAINBOW_PRG_ROM_BANKING_6_LO = $411d
	RAINBOW_PRG_ROM_BANKING_7_LO = $411e
	RAINBOW_PRG_ROM_BANKING_8_LO = $411f

	RAINBOW_PRG_RAM_BANKING_1_HI = $4106
	RAINBOW_PRG_RAM_BANKING_2_HI = $4107
	RAINBOW_PRG_RAM_BANKING_1_LO = $4116
	RAINBOW_PRG_RAM_BANKING_2_LO = $4117

	RAINBOW_FPGA_RAM_BANKING = $4115

	RAINBOW_CHR_CONTROL = $4120

	RAINBOW_EXT_BG_BANK_HI = $4121

	RAINBOW_NAMETABLES_BANK_1 = $4126
	RAINBOW_NAMETABLES_BANK_2 = $4127
	RAINBOW_NAMETABLES_BANK_3 = $4128
	RAINBOW_NAMETABLES_BANK_4 = $4129

	RAINBOW_NAMETBALES_CTRL_1 = $412a
	RAINBOW_NAMETBALES_CTRL_2 = $412b
	RAINBOW_NAMETBALES_CTRL_3 = $412c
	RAINBOW_NAMETBALES_CTRL_4 = $412d

	RAINBOW_CHR_BANKING_1_HI = $4130
	RAINBOW_CHR_BANKING_2_HI = $4131
	RAINBOW_CHR_BANKING_3_HI = $4132
	RAINBOW_CHR_BANKING_4_HI = $4133
	RAINBOW_CHR_BANKING_5_HI = $4134
	RAINBOW_CHR_BANKING_6_HI = $4135
	RAINBOW_CHR_BANKING_7_HI = $4136
	RAINBOW_CHR_BANKING_8_HI = $4137
	RAINBOW_CHR_BANKING_9_HI = $4138
	RAINBOW_CHR_BANKING_10_HI = $4139
	RAINBOW_CHR_BANKING_11_HI = $413a
	RAINBOW_CHR_BANKING_12_HI = $413b
	RAINBOW_CHR_BANKING_13_HI = $413c
	RAINBOW_CHR_BANKING_14_HI = $413d
	RAINBOW_CHR_BANKING_15_HI = $413e
	RAINBOW_CHR_BANKING_16_HI = $413f
	RAINBOW_CHR_BANKING_1_LO = $4140
	RAINBOW_CHR_BANKING_2_LO = $4141
	RAINBOW_CHR_BANKING_3_LO = $4142
	RAINBOW_CHR_BANKING_4_LO = $4143
	RAINBOW_CHR_BANKING_5_LO = $4144
	RAINBOW_CHR_BANKING_6_LO = $4145
	RAINBOW_CHR_BANKING_7_LO = $4146
	RAINBOW_CHR_BANKING_8_LO = $4147
	RAINBOW_CHR_BANKING_9_LO = $4148
	RAINBOW_CHR_BANKING_10_LO = $4149
	RAINBOW_CHR_BANKING_11_LO = $414a
	RAINBOW_CHR_BANKING_12_LO = $414b
	RAINBOW_CHR_BANKING_13_LO = $414c
	RAINBOW_CHR_BANKING_14_LO = $414d
	RAINBOW_CHR_BANKING_15_LO = $414e
	RAINBOW_CHR_BANKING_16_LO = $414f

	RAINBOW_SCANLINE_IRQ_LATCH = $4150
	RAINBOW_SCANLINE_IRQ_CONTROL = $4151
	RAINBOW_SCANLINE_IRQ_OFFSET = $4152

	RAINBOW_CPU_CYCLES_IRQ_COUNTER_LO = $4158
	RAINBOW_CPU_CYCLES_IRQ_COUNTER_HI = $4159
	RAINBOW_CPU_CYCLES_IRQ_CONTROL = $415a
	RAINBOW_CPU_CYCLES_IRQ_ACK = $415b

	RAINBOW_MAPPER_VERSION = $4160

	RAINBOW_MULTIPLY_A = $4161
	RAINBOW_MULTIPLY_B = $4162

	RAINBOW_PULSE_CHANNEL_1_CONTROL = $41a0
	RAINBOW_PULSE_CHANNEL_1_FREQ_LOW = $41a1
	RAINBOW_PULSE_CHANNEL_1_FREQ_HIGH = $41a2
	RAINBOW_PULSE_CHANNEL_2_CONTROL = $41a3
	RAINBOW_PULSE_CHANNEL_2_FREQ_LOW = $41a4
	RAINBOW_PULSE_CHANNEL_2_FREQ_HIGH = $41a5
	RAINBOW_SAW_CHANNEL_ACCUMULATOR = $41a6
	RAINBOW_SAW_CHANNEL_FREQ_LOW = $41a7
	RAINBOW_SAW_CHANNEL_FREQ_HIGH = $41a8

	RAINBOW_AUDIO_OUTPUT_CONTROL = $41a9

	RAINBOW_WIFI_CONF = $4170
	RAINBOW_WIFI_RX = $4171
	RAINBOW_WIFI_TX = $4172
	RAINBOW_WIFI_RX_DEST = $4173
	RAINBOW_WIFI_TX_SOURCE = $4174

	; Aliases
	RAINBOW_PRG_BANK_8000_MODE_1_HI = RAINBOW_PRG_ROM_BANKING_1_HI
	RAINBOW_PRG_BANK_8000_MODE_1_LO = RAINBOW_PRG_ROM_BANKING_1_LO
	RAINBOW_PRG_BANK_C000_MODE_1_HI = RAINBOW_PRG_ROM_BANKING_5_HI
	RAINBOW_PRG_BANK_C000_MODE_1_LO = RAINBOW_PRG_ROM_BANKING_5_LO

	; Set PRG ROM banking
	lda #%01111111 ; CUUUUUUU - PRG-ROM, last bank
	sta RAINBOW_PRG_BANK_C000_MODE_1_HI
	lda #%11111111 ; LLLLLLLL - last bank
	sta RAINBOW_PRG_BANK_C000_MODE_1_LO
	lda #%00000001 ; A....OOO - PRG-RAM 8K, PRG-ROM 16K+16K
	sta RAINBOW_PRG_BANKING_MODE

	;; Set CHR-RAM
	;lda #%01000000 ; CCE..BBB - CHR-RAM, Disable Sprite extension, 8K CHR banking
	;sta RAINBOW_CHR_CONTROL

	; Set CHR-ROM
	lda #%00000000 ; CCE..BBB - CHR-ROM, Disable Sprite extension, 8K CHR banking
	sta RAINBOW_CHR_CONTROL

	; Select CHR bank
	lda #0
	sta RAINBOW_CHR_BANKING_1_HI
	sta RAINBOW_CHR_BANKING_1_LO

	; Set Horizontal mirroring
	; Nothing, reset values are fine

	; Select non-conflicting FPGA RAM
	lda #0 ; FPGA-RAM bank 0 to be mapped at CPU address $5000 to $5fff (TX/RX buffers are in the last 2K of FPGA-RAM)
	sta RAINBOW_FPGA_RAM_BANKING

	; Place TX/RX buffers
	lda #%00000000 ; Buffer at $4800
	sta RAINBOW_WIFI_RX_DEST
	lda #%00000001 ; Buffer at $4900
	sta RAINBOW_WIFI_TX_SOURCE

	; Disable sound extension
	lda #%00000000 ; E...FFFF - disable, (don't care of frequency) ; useless - the value in A is already good
	sta RAINBOW_PULSE_CHANNEL_1_FREQ_HIGH
	sta RAINBOW_PULSE_CHANNEL_2_FREQ_HIGH
	sta RAINBOW_SAW_CHANNEL_FREQ_HIGH

	; Enable ESP
	lda #%00000001 ; ......IE - disable IRQ, enable ESP
	sta RAINBOW_WIFI_CONF

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
