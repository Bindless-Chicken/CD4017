cmake_minimum_required( VERSION 2.8 )

set( AVR_MCU attiny2313a )

include( avr.cmake )

project( CD4017 )

add_avr_executable( CD4017 CD4017/main.cpp )