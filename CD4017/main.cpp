// Pin Mapping
#define CLOCK PB0
#define PIN_0 PB1
#define PIN_1 PB2
#define PIN_2 PB3
#define PIN_3 PB4
#define PIN_4 PB5
#define PIN_5 PB6
#define PIN_6 PB7
#define PIN_7 PD0
#define PIN_8 PD1
#define PIN_9 PD2
#define PIN_CARRY PD3

#ifndef UNIT_TEST
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#else

#include <cstdint>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

uint8_t DDRA, DDRB, DDRD, PORTB, PCMSK, GIMSK, PORTD;

#define ISR(X) void X()
#define _delay_ms(X) void(X)

#endif // !UNIT_TEST


uint16_t counter = 0x01;

#ifdef UNIT_TEST
int function_main(void)
#else
int main(void)
#endif // !
{
	DDRA = 0x00;
	DDRB = 0xFE;
	DDRD = 0x07;

	PORTB = counter << 1;

	//PCMSK |= _BV(PCINT0);
	//GIMSK |= _BV(PCIE0);
	//sei();


 //   while (1) 
 //   {
 //   }
	return 0;
}

ISR(PCINT0_vect){
	counter <<= 1;
	if (counter == 0x400)
	{
		counter = 0x01;
	}
	PORTB = (uint8_t)counter<<1;
	PORTD = (uint8_t)(counter>>7);
	_delay_ms(10);
}

#ifdef UNIT_TEST

TEST_CASE("Check the chip initialization", "[function_main]") {
	function_main();
	CHECK(DDRB == 0xFE);
	CHECK(DDRD == 0x07);

	CHECK(PORTB == 0x02);
}

TEST_CASE("Test shifting", "[PCINT0_vect]") {
	PCINT0_vect();
	CHECK(PORTB == 0x04);
	PCINT0_vect();
	CHECK(PORTB == 0x08);
	PCINT0_vect();
	CHECK(PORTB == 0x10);
	PCINT0_vect();
	CHECK(PORTB == 0x20);
	PCINT0_vect();
	CHECK(PORTB == 0x40);
	PCINT0_vect();
	CHECK(PORTB == 0x80);
	PCINT0_vect();
	CHECK(PORTD == 0x01);
	PCINT0_vect();
	CHECK(PORTD == 0x02);
	PCINT0_vect();
	CHECK(PORTD == 0x04);
	PCINT0_vect();
	INFO(counter);
	CHECK(PORTB == 0x02);
}
#endif // UNIT_TEST