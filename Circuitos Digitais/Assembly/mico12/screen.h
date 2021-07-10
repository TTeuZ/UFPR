//
// screen.h
//

#include <ncurses.h>

// #include <stdlib.h>
// #include <stdio.h>

#ifndef MICO12
  #include "mico12.h"
#endif

// header
#define HEAD_X 0
#define HEAD_Y 0

// dis-assembled code
#define ASM_X 0
#define ASM_Y 5

// instruction memory
#define CODE_X 0
#define CODE_Y 15

// data memory
#define DATA_X 0
#define DATA_Y 22

// stack in data memory
#define STK_X 0
#define STK_Y 29

// internal signals
#define STATE_X 24
#define STATE_Y 5

// register block
#define REGS_X 48
#define REGS_Y 5


// print header
void prt_head(WINDOW * w);


// print instruction memory aka program text
void prt_code(WINDOW * w, int MI[], int ini);


// print data memory aka program data
void prt_data(WINDOW * w, int M[], int ini);


// print stack memory aka program stack
void prt_stack(WINDOW * w, int M[], int ini);


// print processor state
void prt_state(WINDOW * w,
		      ender currIP, ender IP, int instr,
		      int A, int B, int C, int display);


// print register block
void prt_regs(WINDOW * w, int R[]);


// print active code segment
void prt_asm(WINDOW * w, int MI[],
	     ender currIP, ender oldIP, ender oldoldIP, ender nextIP);

// clear fst two lines of active code segment
void clr_asm(WINDOW * w);

