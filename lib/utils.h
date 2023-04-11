#pragma once
#include <stdint.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static uint8_t u16_lsb(uint16_t val) {
	return ((int)val) & 0x00ff;
}

static uint8_t u16_msb(uint16_t val) {
	return (((int)val) >> 8) & 0x00ff;
}

static uint8_t i16_lsb(int16_t val) {
	return ((int)val) & 0x00ff;
}

static uint8_t i16_msb(int16_t val) {
	return (((int)val) >> 8) & 0x00ff;
}

static uint8_t u32_byte0(uint32_t val) {
	return val & 0x000000ff;
}

static uint8_t u32_byte1(uint32_t val) {
	return (val & 0x0000ff00) >> 8;
}

static uint8_t u32_byte2(uint32_t val) {
	return (val & 0x00ff0000) >> 16;
}

static uint8_t u32_byte3(uint32_t val) {
	return (val & 0xff000000) >> 24;
}

static uint32_t u32(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3) {
	return ((uint32_t)(byte3) << 24) + ((uint32_t)(byte2) << 16) + ((uint32_t)(byte1) << 8) + (uint32_t)(byte0);
}

static uint16_t u16(uint8_t lsb, uint8_t msb) {
	return ((uint16_t)msb) * 256 + lsb;
}

static int16_t i16(uint8_t lsb, uint8_t msb) {
	return -(0x10000 - u16(lsb, msb));
}

static uint8_t ptr_lsb(void const* ptr) {
	return u16_lsb((uint16_t)ptr);
}

static uint8_t ptr_msb(void const* ptr) {
	return u16_msb((uint16_t)ptr);
}

static uint8_t const* ptr(uint8_t lsb, uint8_t msb) {
	return (uint8_t const*)((((uint16_t)(msb)) << 8) + lsb);
}

static int16_t min(int16_t a, int16_t b) {
	return a < b ? a : b;
}

static int16_t max(int16_t a, int16_t b) {
	return a > b ? a : b;
}

/** strnlen working on 8bit values */
static uint8_t strnlen8(char const* s, uint8_t maxlen) {
	uint8_t len = 0;
	while (len < maxlen && s[len] != 0) {
		++len;
	}
	return len;
}

#define CONST_HUNDREDS(val) ((((val) % 1000) / 100))
#define CONST_TENS(val) ((((val) % 100) / 10))
#define CONST_UNITS(val) ((val) % 10)

#pragma GCC diagnostic pop
