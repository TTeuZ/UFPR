//
// mico12.c
//

#include <errno.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "mico12.h"
#include "screen.h"

// prxIP : 2, escR : 1, selB : 1, fun : 3, selC : 2, escM : 1, fill : 22;
const cntrlType memCtrl[16] = {
  {0,1,0,iADD,0,0,0}, // add
  {0,1,0,iSUB,0,0,0}, // sub
  {0,1,0,iMUL,0,0,0}, // mul
  {0,1,0,iAND,0,0,0}, // and
  {0,1,0,iOR ,0,0,0}, // or
  {0,1,0,iXOR,0,0,0}, // xor
  {0,1,0,iSLT,0,0,0}, // slt
  {0,1,0,iNOT,0,0,0}, // not
  {0,1,1,iADD,0,0,0}, // addi
  {0,1,1,iADD,1,0,0}, // ld
  {0,0,1,iADD,0,1,0}, // st
  {0,0,0,0,   0,0,0}, // show
  {1,1,0,0,   2,0,0}, // jal
  {2,0,0,0,   0,0,0}, // jr
  {3,0,0,iSUB,0,0,0}, // beq
  {0,0,0,0,   0,0,0}  // halt
};

int  ULA(int fun, int A, int B);

int  readInput(char line[], int * error);
void read_file(char *fname, int MI[]);
void clear_R(int R[]);

int  MI[ROM_SZ] = { 0 };
int  M[RAM_SZ]  = { 0 };
int  R[16]      = { 0 };


int main(int argc, char *argv[]) {

  instrType instr;
  cntrlType ctrl_word;
  
  int opc, ra, rb, rc, cnst16, cnst32;
  int A, B, C, display;
  int beta, gamma, rho, iguais;

  int   prxIP, selC, selB, escR, escM, fun;
  ender IP, currIP, oldIP, oldoldIP;

  char inp_err_char[3];
  int  c, show_base_code, show_base_data, show_top_stack;
  int to_completion;
  
  WINDOW *w;

  show_base_code = show_base_data = 0; // display memory from zero
  show_top_stack = (RAM_SZ-32);        // dispaly stack from top
  
  initscr();
  clear();
  noecho();
  cbreak();  // Line buffering disabled. pass on everything
  
#if 0
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
#endif
  
  w = newwin(12,40,13,0);

  // read input file
  // fname = argv[1];
  read_file(argv[1], MI);
  
  to_completion = FALSE;
  display = 0;
  
  IP = currIP = oldIP = oldoldIP = 0;

  // interpret program instructions
  instr.i = MI[IP];
  opc     = instr.f.opc & 0xf;

  while ( (opc != iHALT) && (IP < ROM_SZ) ) {

#ifdef DEBUG
    // printf("MI[%d]=%08x  opc=%x\n", IP, (unsigned int)MI[IP], (opcode)opc);
#endif

    ra     = instr.f.ra;
    rb     = instr.f.rb;
    rc     = instr.f.rc;
    cnst16 = instr.f.con;

    ctrl_word = memCtrl[opc];
    prxIP = ctrl_word.prxIP;
    escR  = ctrl_word.escR;
    selB  = ctrl_word.selB;
    fun   = ctrl_word.fun;
    selC  = ctrl_word.selC;
    escM  = ctrl_word.escM;

    A = R[ra];
    B = R[rb];

    // sign extend
    cnst32 = ( ( cnst16>>15 & 1 ) != 0  ? 0xffff0000 | cnst16 : cnst16 );
    if ( selB != 0) {
      beta = cnst32;
    } else {
      beta = B;
    }
    
    gamma = ULA( fun, A, beta );
    iguais = (A == B);

    rho = M[ (ender)gamma ];

    switch (selC) {   // mux at register block input 
    case 0: C = gamma;  break;
    case 1: C = rho;    break;
    case 2: C = IP + 1; break;
    default: panic("selC undefined", selC);
    }

    oldoldIP = oldIP;
    oldIP = currIP;
    currIP = IP;
    switch (prxIP) {   // mux at Instruction Pointer input 
    case 0: IP = (ender)(IP + 1);  break;
    case 1: IP = (ender)cnst16;    break;
    case 2: IP = (ender)A;         break;
    case 3:
      if ( (opc == iBEQ) && (iguais == TRUE) ) {
	IP = (ender)cnst16;
      } else {
	IP = (ender)(IP + 1);
      };
      break;
    default: panic("proxIP undefined at address ", currIP);
    }

#ifdef DEBUG
    // printf("ooIP %d oIP %d currIP %d proxIP %d\n",oldoldIP,oldIP,currIP,IP);
    // printf("prxIP %d escR %d selB %d fun %d selC %d escM %d rc %d C %d\n", prxIP, escR, selB, fun, selC, escM, rc, C);
#endif
    
    if ( (escR != 0) && (rc != 0) ) {  // update register block
      R[rc] = C;
    }
    
    if ( escM != 0 ) {  // update memory
      M[ (ender)gamma ] = B;
    }

    if (opc == iSHOW) { // instruction display
      display = A;
      // printf("print A = %d 0x%x\n", A, (unsigned int)A);
    }

    // print active code segment
    prt_head(w);

    // print active code segment
    prt_asm(w, MI, currIP, oldIP, oldoldIP, IP);
    
    // print processor state
    prt_state(w, currIP, IP, instr.i, A, beta, C, display);

    // print register block
    prt_regs(w, R);
    
    // print instruction memory aka program text
    prt_code(w, MI, show_base_code);

    // print data memory aka program data
    prt_data(w, M, show_base_data);

    // print stack memory aka program stack
    prt_stack(w, M, show_top_stack);
    
    wrefresh(w);    // Print it on to the real screen


    if (to_completion == FALSE) {
      c = getch();    // Wait for user input

      switch((char)c) {
      case ' ':  // go to next instruction
	// fetch next instruction
	instr.i = MI[IP];
	opc     = instr.f.opc & 0xf;
	break; 
      case 'g':  // run to completion
	to_completion = TRUE;
	// fetch next instruction
	instr.i = MI[IP];
	opc     = instr.f.opc & 0xf;
	break; 
      case 'r':  // reload input file, clear registers
	read_file(argv[1], MI);
	IP = currIP = oldIP = oldoldIP = 0;
	clear_R(R);
	clr_asm(w);
	break;
      case 'q':  // force end of simulation
	opc = iHALT;
	delwin(w);
	endwin();
	break;
      case 'c':  // scroll up display of code memory
	if ( (show_base_code + 8) > ROM_SZ ) {
	  show_base_code = 0;
	} else {
	  show_base_code += 8;
	}
	break;
      case 'C':  // scroll DOWN display of code memory
	if ( (show_base_code - 8) < 0 ) {
	  show_base_code = 0;
	} else {
	  show_base_code -= 8;
	}
	break;
      case 'd':  // scroll up display of data memory
	if ( (show_base_data + 8) > RAM_SZ ) {
	  show_base_data = 0;
	} else {
	  show_base_data += 8;
	}
	break;
      case 'D':  // scroll DOWN display of data memory
	if ( (show_base_data - 8) < 0 ) {
	  show_base_data = 0;
	} else {
	  show_base_data -= 8;
	}
	break;
      case 'S':  // scroll UP display of stack memory
	if ( (show_top_stack + 8) > RAM_SZ ) {
	  show_top_stack = (RAM_SZ-32);
	} else {
	  show_top_stack += 8;
	}
	break;
      case 's':  // scroll down display of stack memory
	if ( (show_top_stack - 8) < 0 ) {
	  show_top_stack = (RAM_SZ-32);
	} else {
	  show_top_stack -= 8;
	}
	break;
      default:  // any other input
	inp_err_char[0] = c;
	inp_err_char[1] = '\n';      
	inp_err_char[2] = '\0';      
	panic_str("\n\n\n\tInvalid comand: ", inp_err_char);
	delwin(w);
	endwin();
      } // switch(c)
    } else { // if (to_completion)==TRUE
    	instr.i = MI[IP];
	opc     = instr.f.opc & 0xf;
    } // if (to_completion)

  } // while ( (opc != iHALT) && (IP < ROM_SZ) )

  if ( to_completion == TRUE ) {
      c = getch();    // Wait for user input then exit
  }
  
  delwin(w);
  endwin();

  exit(0);

} // main() ------------------------------------------------------------


int ULA(int fun, int A, int B) {
  int C;

  switch (fun % 16) {
  case iADD: C = A + B; break;
  case iSUB: C = A - B; break;
  case iMUL: C = A * B; break;
  case iAND: C = A & B; break;
  case iOR:  C = A | B; break;
  case iXOR: C = A ^ B; break;
  case iSLT: C = (A < B); break;
  case iNOT: C = ~A; break;
  default: panic("ALU function undefined", fun);
  }
#ifdef DEBUG
  // printf("fun=%1x A=%08x B=%08x C=%08x\n", fun, (unsigned int)A, (unsigned int)B, (unsigned int)C);
#endif

  return(C);
} // ULA() ---------------------------------------------------------------


// return GOOD if read 8 hexadecimal chars
// return FAIL otherwise
int readInput(char line[], int *error) {

  int c, d, k, old_i, i;

  d = i = 0;
  *error = GOOD;
  
  // skip white space

  // check if line empty, then discard input and return FAIL
  if ( line[i] == '\n' ) {
    *error = FAIL;
    return( 0 );
  }

  // skip over blanks on the left
  while ( (line[i] == ' ') || (line[i] == '\t' ) ) {
    i = i + 1;
    if ( i >= MAX_INP )
      panic("input line too long", i);
  }
  
  // check if comment, then discard input and return FAIL
  if ( line[i] == '#' ) {
    *error = FAIL;
    return( 0 );
  }
    
  old_i = i;
  for ( k=0; k < 7; k++ ) {
    c = (line[i] <= '9') ? (line[i] - '0') : ((line[i] - 'a')+10);
    d = d | c;
    d = d<<4;
    i = i + 1;
#ifdef DEBUG
    // printf("line[%d] = %x\n", i, (unsigned int)c);
#endif
  }
  c = (line[i] <= '9') ? (line[i] - '0') : ((line[i] - 'a')+10);
  d = d | c;
  i = i + 1;
#ifdef DEBUG
  // printf("line[%d] = %x\n", i, (unsigned int)c);
#endif
  
#ifdef DEBUG
  // printf("i=%d line %s  d %x\n", i, line, (unsigned int)d);
#endif
  
  if ( (old_i + 8) != i )
    panic_str("input line with less than 8 bytes", line);
  
  return( d );

} // readInput() ------------------------------------------------------



void read_file(char *fname, int MI[]) {
  int IP, c, k, d;
  int error = GOOD;
  char line[MAX_INP];

  FILE *fptr;
  
  if ((fptr = fopen(fname, "r")) == NULL) {
    panic_str("Error opening file", fname);
  }

  IP = 0;
  c  = 0;

  while ( c != EOF ) {
  
    k = 0;
    while ( (c = fgetc(fptr)) != '\n' && (c != EOF) ) {
      line[k] = (char)c;
      k += 1;
    }
    line[k] = '\0';
    
    if ( c != EOF) {
      // parse input and write instruction to ROM
      d = readInput(line, &error);

      if ( error != FAIL ) { // read a good instruction?  if not, skip
	MI[IP] = d;
	IP = IP + 1;
      }
      
    } // if (c != EOF)
  
  } // while (c != EOF)
  
  fclose(fptr);

#ifdef DEBUG
  // if ( c == EOF ) exit(0);
#endif

} // read_file() --------------------------------------------------------


void clear_R(int R[]) {
  int i;

  for (i=0; i<16; i++)
    R[i]=0;
} // clear_R() ----------------------------------------------------------


void panic(char *msg, int error) {
  fprintf(stderr,
	  "\n\n\t%s value %d %x\n\n", msg, error, (unsigned int)error);
  endwin();
  exit(1);
} // panic() ------------------------------------------------------------


void panic_str(char *msg, char *error) {
  fprintf(stderr,
	  "\n\n\t%s %s\n\n", msg, error);
  endwin();
  exit(1);
} // panic_str() --------------------------------------------------------


