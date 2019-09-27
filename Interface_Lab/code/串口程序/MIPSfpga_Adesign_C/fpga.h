/*
 * fpga.h
 *
 *  Created on: Dec 6, 2014
 *      Author: MIPS TECHNOLOGIES, INC
 */

#ifndef FPGA_H_
#define FPGA_H_

#define IO_LEDR        0xB0600000

#define BOARD_16_LEDS_ADDR     0xB0600000  //used by exception handlers
#define BOARD_16_SW_ADDR     0xB0600008  //used by exception handlers

#define READ_IO(addr)  (volatile unsigned int *)(addr)
#define WRITE_IO(addr) (volatile unsigned int *)( addr)

#define STACK_BASE_ADDR 0xbfc00900;

#endif /* FPGA_H_ */

