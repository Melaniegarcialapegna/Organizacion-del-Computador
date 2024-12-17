#include <stdint.h>
/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~(~x & ~y);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;

}
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  return (~x & ~y);
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int operacionOr  = ~(~x & ~y);
  int operacionAnd = (x&y);
  return (operacionOr & ~(operacionAnd));
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
    int pares = 0x55; 
    pares |= pares << 8;
    pares |= pares << 16;
    return pares;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    int preMask = 0xAA;
    int preMask2 = preMask<<8;
    int preMask3 = (preMask | preMask2) <<16;
    int finalMask = preMask | preMask2 | preMask3;
    int impares = x & finalMask;
    return !!impares;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int mBytes = m<<3;
  int nBytes = n<<3;
  int tramo1parte1 = x>>mBytes;
  int tramo1parte2 = tramo1parte1<<nBytes;
  int mask1 = 0xFF << nBytes; 

  int tramo2parte1 = x>>nBytes;
  int tramo2parte2 = tramo2parte1<<mBytes;
  int mask2 = 0xFF << mBytes;

  int maskRestantes = x & ~mask1 & ~mask2;
  
  return (maskRestantes) | (tramo1parte2 & mask1) | (tramo2parte2 & mask2);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    int negado = ~(n) + 1;
    int shift = 32 + negado;
    int shifted = (x << shift) >> shift;
    return !(x ^ shifted);
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  int preMask1 = 0xAA;
  int preMask2 = preMask1<<8;
  int preMask3 = (preMask1 | preMask2) << 16;
  return preMask1 | preMask2 | preMask3;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
    int dobleNegacion = !!x;
    int shifteado = (x>>31);
    return dobleNegacion | shifteado;
}
//3
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int signoX = x >> 31;
  int signoY = y >> 31;
  int suma = x + y;
  int signoSuma = suma >> 31;
  return !((signoX ^ signoSuma) & (signoY ^ signoSuma));
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {

  int negativoLow = ~lowbit + 1; 
  int resta = highbit + negativoLow; 
  int maskFiltro = 0x80<<16; 
  int filtro = ~(resta & maskFiltro);
  int mascaraFinal = filtro>>31;
  
  int todosUno = ~0x00;
  int maskLow = todosUno << lowbit;
  int maskHigh = todosUno << (highbit); 
  int maskHigh2 = maskHigh << 1;
  int maskHighNegada = ~maskHigh2;
  int resultado = maskLow & maskHighNegada;

  return (resultado & mascaraFinal);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int condicion = !!(x);
  int negacion = ~(condicion);
  int mask = negacion +1;

  int resultadoY =(mask & y);
  int resultadoZ =((~mask) & z);

  return resultadoY | resultadoZ;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int mask1;
    int mask2;
    int mask3;
    int mask4;
    int mask5;

    mask1 = 0x55 | (0x55 << 8);
    mask1 = mask1 | (mask1 << 16);
    mask2 = 0x33 | (0x33 << 8);
    mask2 = mask2 | (mask2 << 16);
    mask3 = 0x0F | (0x0F << 8);
    mask3 = mask3 | (mask3 << 16);
    mask4 = 0xFF | (0xFF << 16);
    mask5 = 0xFF | (0xFF << 8);

    x = (x & mask1) + ((x >> 1) & mask1);
    x = (x & mask2) + ((x >> 2) & mask2);
    x = (x & mask3) + ((x >> 4) & mask3);
    x = (x & mask4) + ((x >> 8) & mask4);
    x = (x & mask5) + ((x >> 16) & mask5);

    return x & 0xFF;
}
/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and & 
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
  int operacionOr  = ~(~x & ~y);
  int operacionAnd = (x&y);
  return ~(operacionOr & ~(operacionAnd));
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int nBytes = n<<3;
  int mask1 = ~(0xFF<<nBytes);
  int aplicarMascara = (x & mask1);

  int num = 0x0 + c;
  int soloC = (num<<nBytes);

  return (aplicarMascara | soloC);
}
//4
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
    int sum = x + y;
    int overflow_pos = ~(x >> 31) & ~(y >> 31) & (sum >> 31);
    int overflow_neg = (x >> 31) & (y >> 31) & ~(sum >> 31);
    int maxInt = ~(1 << 31);
    int minInt = 1 << 31;

    int result = (overflow_pos & maxInt) | (overflow_neg & minInt) | (~(overflow_pos | overflow_neg) & sum);

    return result;
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  int mask = 0x80<<24;
  int duplicado = x << 1;

  int hacerElOr = x ^ duplicado;
  int condicionVerSiOver = (hacerElOr & mask);

  //Aca vemos si es Tmax o Tmin
  int primerDigito = x & mask;
  int condicion = !!(primerDigito);
  int negarCondicion = ~(condicion);
  int operando= negarCondicion +1;
  int tipoOver = operando  ^(~(mask));

  //MOMENTO TERNARIO!! 🤓
  int condicionTernario = !!(condicionVerSiOver);
  int negacion = ~(condicionTernario);
  int maskTernario = negacion +1;

  int resultadoY =(maskTernario & tipoOver);
  int resultadoZ =((~maskTernario) & duplicado);

  return resultadoY | resultadoZ;
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  int menosX = ~x + 1;
  return ((x | menosX) >> 31) & 1;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  int todosUnos = ~0x0;
  int desplazada = todosUnos << n;
  int mask = ~(desplazada);

  int danLaVuelta = x & mask;
  int negado = ~(n) + 1;
  int desplazarVuelteros = danLaVuelta<<(32+negado);
  int rotarX = x>>n;
  int maskFinal = mask<<(32+negado); 
  int resultado =(desplazarVuelteros & maskFinal) | (rotarX & ~maskFinal);
  return resultado;
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  unsigned maskPrimero = 0x80<<24; 
  unsigned maskExp = 0xFF; 
  unsigned exp = uf>>23 & maskExp;
  unsigned primerBit = uf & maskPrimero;
  unsigned mascaraFrac = (0xFF>>1)<<16; 
  unsigned fraccion = uf & mascaraFrac;

  if(fraccion){
    if(exp == maskExp){
      return uf;
    }
  }

  if(primerBit){
    unsigned resultado = uf & ~maskPrimero;
    return resultado;
  }
  return uf;
}
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
    unsigned uf_exp = uf >> 23 & 0xFF;
    unsigned ug_exp = ug >> 23 & 0xFF;
    int unoEnPrimero = 0x1<<31;
    unsigned mascaraFrac = ~(~(0x0)<<23);
    unsigned uf_frac = uf & mascaraFrac;
    unsigned ug_frac = ug & mascaraFrac;

    if ((uf_exp == 0xFF && uf_frac != 0) || (ug_exp == 0xFF && ug_frac != 0)) {
        return 0;
    }

    if ((uf == 0 || uf == unoEnPrimero) && (ug == 0 || ug == unoEnPrimero)) {
        return 1;
    }

    return uf == ug;
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  unsigned mask;
  unsigned exponente = (uf >> 23)& 0xFF;
  unsigned mascaraFrac = ~(~(0x0)<<23);
  unsigned fraccion = uf & mascaraFrac;
  if(exponente == 0xFF && fraccion){
    return uf;
  }

  mask = (0x1 << 31);
  return uf ^ mask;
}

  /* 
  * floatIsLess - Compute f < g for floating point arguments f and g.
  *   Both the arguments are passed as unsigned int's, but
  *   they are to be interpreted as the bit-level representations of
  *   single-precision f
}loating point values.
  *   If either argument is NaN, return 0.
  *   +0 and -0 are considered equal.
  *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
  *   Max ops: 30
  *   Rating: 3
  */
int floatIsLess(unsigned uf, unsigned ug) {
    unsigned mask;
    unsigned signoF = uf >> 31;
    unsigned signoG = ug >> 31;
    unsigned expF = (uf>>23) & 0xFF;
    unsigned expG = (ug>>23) & 0xFF;
    
    unsigned mascaraFrac = ~(~(0x0)<<23); //
    unsigned fraccionF = uf & mascaraFrac;
    unsigned fraccionG = ug & mascaraFrac;

    if(((expF == 0xFF) && fraccionF)){
      return 0;
    }
    if(((expG == 0xFF) && fraccionG)){
      return 0;
    }

    mask = ~(0x1<<31);
    if( ( ((uf | ug) & mask) == 0x0) ){
      return 0;
    }

    // 0 , 1
    if(signoF > signoG){
      return 1;
    }
    if(signoG > signoF){
      return 0;
    }
    if (signoF && signoG){
        if(expG > expF){
          return 0;
        }
        if(expF > expG){
          return 1; 
        }
    
        if(fraccionF > fraccionG){
          return 1;
        }
    } 
    else{
        if(expG > expF){
          return 1;
        }
        if(expF > expG){
          return 0;
        }
    
        if(fraccionG > fraccionF){
          return 1;
        }
    } 
  return 0;
}

/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    unsigned M;
    int result;
    unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & ~(~(0x0)<<23);
    int E = exp - 127; 
    int unoEnPrimero = 0x1<<31;
    
    if (exp == 0xFF) {

        return unoEnPrimero;
    }

    if (E > 31) {
        return unoEnPrimero;
    }
    if (E < 0) {
        return 0;
    }

    M = frac | 0x1<<23;

    if (E > 23) {
        result = M << (E + (~23 + 1));
    } else {
        result = M >> (23 + (~E + 1));
    }

    if (sign) {
        result = ~result + 1;
    }

    return result;
}

/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int bias = 127;
  int exp = x + bias;

    if (exp <= 0) {
        return 0;
    }

    if (exp >= 255) {
        return 0xFF<<23;
    }

    return exp << 23;
}
