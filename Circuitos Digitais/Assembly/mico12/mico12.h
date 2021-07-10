//
// mico12.h
//

#ifndef MICO12
  #define MICO12
#endif

#define GOOD TRUE
#define FAIL FALSE

typedef struct inst {
  unsigned int con : 16,
    rc : 4,
    rb : 4,
    ra : 4,
    opc : 4;
} instType;

typedef union instr {
  instType     f;        // structure bit fields
  unsigned int i;        // integer
} instrType;


typedef unsigned short ender;

#define ROM_SZ 64*1024

#define RAM_SZ 64*1024

typedef enum {iADD=0, iSUB, iMUL, iAND, iOR, iXOR, iSLT, iNOT,
	      iADDI, iLD, iST, iSHOW, iJAL, iJR, iBEQ, iHALT} opcode;

typedef struct cntrl {
  unsigned int prxIP : 2,
    escR : 1,    
    selB : 1,
    fun  : 3,
    selC : 2,
    escM : 1,
    fill : 22;
} cntrlType;

// max input-file line size
#define MAX_INP 128

void instr2str(instrType i, char * c[]);

instrType int2instr(int d);

void panic(char *msg, int error);
void panic_str(char * msg, char * error);
