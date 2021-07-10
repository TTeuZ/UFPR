//
// screen.c
//

#include <ncurses.h>

#include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
#include "screen.h"


void i2hex4(int n, char b[]);
void i2hex8(int n, char b[]);
void instr2txt(int i, char b[]);


// print active code segment
void prt_asm(WINDOW * w, int MI[],
	     ender currIP, ender oldIP, ender oldoldIP, ender nextIP) {
  int x, y;
  char instr[16] = { ' ' };
  
  x = ASM_X;
  y = ASM_Y;

  mvprintw((y-2), x, "Active_instruction");

  if ( currIP > 1 ) {
    mvprintw(y+0, x, " ");
    instr2txt( MI[oldoldIP], instr ); 
    mvprintw(y+0, x+1, instr);
  }

  if ( currIP > 0 ) {
    mvprintw(y+1, x, " ");
    instr2txt( MI[oldIP], instr ); 
    mvprintw(y+1, x+1, instr);
  }
  
  // attron(COLOR_PAIR(1));
  mvprintw(y+2, x, "=");
  instr2txt( MI[currIP], instr ); 
  mvprintw(y+2, x+1, instr);
  // attroff(COLOR_PAIR(1));

  mvprintw(y+3, x, " ");
  instr2txt( MI[nextIP+0], instr ); 
  mvprintw(y+3, x+1, instr);

  mvprintw(y+4, x, " ");
  instr2txt( MI[nextIP+1], instr ); 
  mvprintw(y+4, x+1, instr);

  mvprintw(y+5, x, " ");
  instr2txt( MI[nextIP+2], instr ); 
  mvprintw(y+5, x+1, instr);

} // prt_asm() ----------------------------------------------

void clr_asm(WINDOW * w) {
  int x, y, i;
  char instr[18];
  
  x = ASM_X;
  y = ASM_Y;

  for(i=0; i<16; i++)
    instr[i] = ' ';
  instr[i] = '\0';
  
  mvprintw(y+0, x+1, instr);
  mvprintw(y+1, x+1, instr);
} // clr_asm() ----------------------------------------------



// print stack memory aka program stack
void prt_stack(WINDOW * w, int M[], int ini) {
  int x, y, lin, col, l, c, i;
  char str[10];
  char addr[5];
  
  x = STK_X;
  y = STK_Y;

  mvprintw((y-2), x, "Program_stack");

  lin = 4;
  col = 8;
  i = ini;
  
  for (l = 0; l < lin; l++, y++) {
    x = CODE_X;
    i2hex4(i, addr);
    mvprintw(y, x, addr);
    x = x + 5;
    for (c = 0; c < col; c++, i++, x+=9) {
      i2hex8(M[i], str);
      mvprintw(y, x, str);
    }
  }
} //-----------------------------------------------------------------------



// print data memory aka program data
void prt_data(WINDOW * w, int M[], int ini) {
  int x, y, lin, col, l, c, i;
  char str[10];
  char addr[5];
  
  x = DATA_X;
  y = DATA_Y;

  mvprintw((y-2), x, "Data_memory");

  lin = 4;
  col = 8;
  i = ini;
  
  for (l = 0; l < lin; l++, y++) {
    x = CODE_X;
    i2hex4(i, addr);
    mvprintw(y, x, addr);
    x = x + 5;
    for (c = 0; c < col; c++, i++, x+=9) {
      i2hex8(M[i], str);
      mvprintw(y, x, str);
    }
  }
#ifdef DEBUG
    // printf("M[%d] = %s\n", i, str);
#endif
} //-----------------------------------------------------------------------



// print instruction memory aka program text
void prt_code(WINDOW * w, int MI[], int ini) {
  int x, y, lin, col, l, c, i;
  char str[10];
  char addr[5];
  
  x = CODE_X;
  y = CODE_Y;

  mvprintw((y-2), x, "Program_text");

  lin = 4;
  col = 8;
  i = ini;
  
  for (l = 0; l < lin; l++, y++) {
    x = CODE_X;
    i2hex4(i, addr);
    mvprintw(y, x, addr);
    x = x + 5;
    for (c = 0; c < col; c++, i++, x+=9) {
      i2hex8(MI[i], str);
      mvprintw(y, x, str);
    }
  }
#ifdef DEBUG
    // printf("MI[%d] = %s\n", i, str);
#endif
} //-----------------------------------------------------------------------




// print processor state
void prt_state(WINDOW * w,
	       ender currIP, ender IP, int instr,
	       int A, int B, int C, int display) {
  int x, y;
  char str[10];
  
  x = STATE_X;
  y = STATE_Y;

  mvprintw((y-2), x, "Internal_state");
  
  mvprintw(y+0, x, "currIP = ");
  i2hex8(currIP, str);
  mvprintw(y+0, x+9, str);

  mvprintw(y+1, x, "instr  = ");
  i2hex8(instr, str);
  mvprintw(y+1, x+9, str);

  mvprintw(y+2, x, "A      = ");
  i2hex8(A, str);
  mvprintw(y+2, x+9, str);

  mvprintw(y+3, x, "beta   = ");
  i2hex8(B, str);
  mvprintw(y+3, x+9, str);

  mvprintw(y+4, x, "C      = ");
  i2hex8(C, str);
  mvprintw(y+4, x+9, str);

  mvprintw(y+5, x, "proxIP = ");
  i2hex8(IP, str);
  mvprintw(y+5, x+9, str);

  mvprintw(y+7, x, "print  = ");
  i2hex8(display, str);
  mvprintw(y+7, x+9, str);
} //-----------------------------------------------------------------


// print processor state
void prt_head(WINDOW * w) {
  int x, y;
  
  x = HEAD_X;
  y = HEAD_Y;

  mvprintw(y+0, x, "Mico v12");
  mvprintw(y+0, x+22,
	   "SPC = next, r = reload & clear R[], g = run,  q = quit");  
  mvprintw(y+1, x+22,
	   "c|d|s = scroll up code,data,stack, C|D|S - scroll down");  
  
} //-----------------------------------------------------------------




// print register block
void prt_regs(WINDOW *w, int R[]) {

  int r, x, y;
  char str[10];
  char reg[6] = "rX = ";
  char h;
  
  x = REGS_X;
  y = REGS_Y;

  mvprintw((y-2), x, "Registers");  // Move to (y, x) then print string

  for (r = 0; r < 8; r++, y++) {
#ifdef DEBUG
    // printf("R[%d] = %s\n", r, str);
#endif
    reg[1] = (char)(r+'0');
    mvprintw(y, x, reg);
    i2hex8(R[r], str);
    mvprintw(y, x+5, str);
  }

  x = REGS_X + 15;
  y = REGS_Y;
  for (r = 8 ; r < 16; r++, y++) {
    h = ( (r < 10) ? '0' : ('a'-10) );
    reg[1] = (char)(r+h);
    mvprintw(y, x, reg);
    i2hex8(R[r], str);
    mvprintw(y, x+5, str);
  }

} //-----------------------------------------------------------------


//
// disassemble instruction
//

#define i2a(m) ( ((m) < 10) ? ((m)+'0') : (((m & 0xf)+'a')-10) )

void scpy(char *fte, char *dst) {
  while( (*dst = *fte) != '\0' ) {
    dst++; fte++;
  }
  *dst = '\0';
} //-----------------------------------------------------------------

void scat(char *ini, char *fin) {
  while( *ini != '\0' ) {
    ini++;
  }
  while( (*ini = *fin) != '\0' ) {
    ini++; fin++;
  }
  *ini = '\0';
} //-----------------------------------------------------------------



void instr2txt(int instr, char b[]) {

  char *i;
  char cnst[5]  = { '\0' };
  char inst[20] = { '\0' };
  char oper[12] = { '\0' };
  #define FILL(ini) {int n; for(n=(ini);n<11;n++){oper[n]=' ';};oper[11]='\0';}
  
  i2hex4( (instr & 0xffff), cnst );

  switch ( (instr>>28) & 0xf ) {
  case  iADD:  i = "add  " ; break;
  case  iSUB:  i = "sub  " ; break;
  case  iMUL:  i = "mul  " ; break;
  case  iAND:  i = "and  " ; break;
  case  iOR:   i = "or   " ; break;
  case  iXOR:  i = "xor  " ; break;
  case  iSLT:  i = "slt  " ; break;
  case  iNOT:  i = "not  " ; break;
  case  iADDI: i = "addi " ; break;
  case  iLD:   i = "ld   " ; break;
  case  iST:   i = "st   " ; break;
  case  iSHOW: i = "show " ; break;
  case  iJAL:
    if ( ((instr>>16) & 0xf) == 0) {
      i = "j    ";  // writes to r0
    } else {
      i = "jal  ";
    }
    break;
  case  iJR:   i = "jr   " ; break;
  case  iBEQ:  i = "beq  " ; break;
  case  iHALT: i = "halt " ; break;
  default: panic("opcode undefined", instr);
  }

  scpy(i, inst);

  
#ifdef DEBUG
  // printf("opc = %s\n", inst);
#endif
  
  switch ( (instr>>28) & 0xf ) {
  case  iADD: // ALU
  case  iSUB:
  case  iMUL:
  case  iAND:
  case  iOR:
  case  iXOR:
  case  iSLT:
    oper[0] = 'r';
    oper[1] =  i2a((instr>>16) & 0xf);
    oper[2] = ',';
    oper[3] = 'r';
    oper[4] = i2a((instr>>24) & 0xf); 
    oper[5] = ',';
    oper[6] = 'r';
    oper[7] = i2a((instr>>20) & 0xf); 
    FILL(8);
    break;
  case  iNOT: // not
    oper[0] = 'r';
    oper[1] = i2a((instr>>16) & 0xf); 
    oper[2] = ',';
    oper[3] = 'r';
    oper[4] = i2a((instr>>24) & 0xf); 
    FILL(5);
    break;
  case  iADDI: // addi
    oper[0] = 'r';
    oper[1] = i2a((instr>>16) & 0xf); 
    oper[2] = ',';
    oper[3] = 'r';
    oper[4] = i2a((instr>>24) & 0xf); 
    oper[5] = ',';
    scpy(cnst, &(oper[6]));
    oper[10] = ' ';
    oper[11] = '\0';
    break;
  case  iLD: // ld
    oper[0] = 'r';
    oper[1] = i2a((instr>>16) & 0xf); 
    oper[2] = ',';
    scpy(cnst, &(oper[3]));
    oper[7] = '(';
    oper[8] = 'r';
    oper[9] = i2a((instr>>24) & 0xf); 
    oper[10] = ')';
    oper[11] = '\0';
    break;
  case iST: // st
    scpy(cnst, &(oper[0]));
    oper[4] = '(';
    oper[5] = 'r';
    oper[6] = i2a((instr>>24) & 0xf); 
    oper[7] = ')';
    oper[8] = ',';
    oper[9] = 'r';
    oper[10] = i2a((instr>>20) & 0xf); 
    oper[11] = '\0';
    break;
  case iSHOW: // show
    oper[0] = 'r';
    oper[1] = i2a((instr>>24) & 0xf); 
    FILL(2);
    break;
  case iJAL: // jal
    if ( ((instr>>16) & 0xf) == 0) { // jump, writes to r0
      scpy(cnst, &(oper[0]));
      FILL(4);
    } else { // jump-and-link, writes link to register
      oper[0] = 'r';
      oper[1] = i2a((instr>>16) & 0xf); 
      oper[2] = ',';
      scpy(cnst, &(oper[3]));
      FILL(7);
    }
    break;
  case iJR: // jr
    oper[0] = 'r';
    oper[1] = i2a((instr>>24) & 0xf); 
    FILL(2);
    break;
  case iBEQ: // beq
    oper[0] = 'r';
    oper[1] = i2a((instr>>24) & 0xf); 
    oper[2] = ',';
    oper[3] = 'r';
    oper[4] = i2a((instr>>20) & 0xf); 
    oper[5] = ',';
    scpy(cnst, &(oper[6]));
    oper[10] = ' ';
    oper[11] = '\0';
    break;
  case iHALT: // halt
    FILL(0);
    break;
  default: panic("opcode undefined", instr);
  }
#ifdef DEBUG
  // printf("oper = %s\n", oper);
#endif

  // if ALU instruction does nothing (writes to r0), show as NOP
  if ( (((instr>>28) & 0xf) <= iNOT) && (((instr>>16) & 0xf) == 0) ) {
    scpy("nop  ", inst);
    FILL(0);
  }
  
  scat(inst, oper);
  scpy(inst, b);

} //-----------------------------------------------------------------
	       

// convert integer to a 8 char string
void i2hex8(int n, char *b) {
  int k, d, sh;
  
  sh = 28;
  for ( k=0; k < 8; k++, sh = sh-4 ) {
    d = (n>>sh) & 0xf;
    b[k] = (d > 9) ? (d + ('a' - 10)) : (d + '0');
#ifdef DEBUG
    // printf("b[%d] = %x\n", k, (unsigned int)b[k]);
#endif
  }
  b[8] = '\0';
#ifdef DEBUG
  // printf("b = %s\n", b);
#endif

} //-----------------------------------------------------------------


// convert integer to a 4 char string
void i2hex4(int n, char *b) {
  int k, d, sh;
  
  sh = 12;
  for ( k=0; k < 4; k++, sh = sh-4 ) {
    d = (n>>sh) & 0xf;
    b[k] = (d > 9) ? (d + ('a'-10)) : (d + '0');
#ifdef DEBUG
    // printf("b[%d] = %x\n", k, (unsigned int)b[k]);
#endif
  }
  b[4] = '\0';
#ifdef DEBUG
  // printf("b = %s\n", b);
#endif

} //-----------------------------------------------------------------

