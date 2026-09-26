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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int part1 = (x >> (src << 3)) & 0xFF;
  int part2 = ~(0xFF << (dst << 3)) & x;
  return (part1 << (dst << 3)) | part2;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int temp = ~(((~0 << 31) >> n ) << 1);
  return temp & (x >> n);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0F | (0x0F << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int zeros = ~x;
  int remaining = zeros & (zeros + ~0);
  return remaining & (~remaining + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int shift = n & 31;
  int right = x >> shift;
  int mask = ~(((~0 << 31) >> shift) << 1);
  int left = x << ((~shift + 1) & 31);
  return (right & mask) | left;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int remain = ((1 << n) + ~0) & x;
  int half = 1 << (n + ~0);
  int equal = !(remain ^ half);
  int smaller = (remain + ~half + 1) >> 31 & 1;
  int add = (!smaller & !equal) | (equal & (x >> n) & 1);
  return ((x >> n) + add) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int sign1 = (x >> 31) & 1;
  int sign2 = (y >> 31) & 1;
  int bigger = ((sign1 ^ sign2) & ~sign1) | (~(sign1 ^ sign2) & ((~x + y) >> 31 & 1));
  int flag1 = x & 1;
  int flag2 = y & 1;
  return (x >> 1) + (y >> 1) + (flag1 & flag2) + (bigger & (flag1 ^ flag2));
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int xa = x + ~a + 1;
  int bx = b + ~x + 1;
  int xb = x + ~b + 1;
  int ax = a + ~x + 1;
  int lessXa = (xa ^ ((x ^ a) & (x ^ xa))) >> 31 & 1;
  int lessBx = (bx ^ ((b ^ x) & (b ^ bx))) >> 31 & 1;
  int lessXb = (xb ^ ((x ^ b) & (x ^ xb))) >> 31 & 1;
  int lessAx = (ax ^ ((a ^ x) & (a ^ ax))) >> 31 & 1;
  return (!lessXa & !lessBx) | (!lessXb & !lessAx);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int temp1 = x << 1;
  int temp2 = x << 2;
  int ans = temp2 + x;
  int sign = x >> 31;
  int overflow = !!(((x >> 31) ^ (temp1 >> 31)) |
                    ((x >> 31) ^ (temp2 >> 31)) |
                    ((x >> 31) ^ (ans >> 31)));
  int min = 1 << 31;
  int max = ~min;
  int limit = (sign & min) | (~sign & max);
  int mask = ~overflow + 1;
  return (~mask & ans) | (mask & limit);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int q = (x >> 2) + (y >> 2) + (z >> 2);
  int r = (x & 3) + (y & 3) + (z & 3);
  int unit = 1 << 29;
  q = q + (r >> 2);
  int maxq = unit + ~0;
  int delta = q + ~maxq + 1;
  int positive = !((delta + ~0) >> 31);
  int negative = (q + unit) >> 31 & 1;
  return positive | (~negative + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned product;
  unsigned rounded;
  if (exp == 0xFFu)
    return uf;
  if (exp == 0u) {
    product = frac * 3u;
    rounded = product >> 1;
    if ((product & 1u) && (rounded & 1u))
      rounded++;
    if (rounded >= 0x800000u)
      return sign | 0x00800000u | (rounded - 0x800000u);
    return sign | rounded;
  }
  product = (0x800000u | frac) * 3u;
  if (product < 0x02000000u) {
    rounded = product >> 1;
    if ((product & 1u) && (rounded & 1u))
      rounded++;
    if (rounded == 0x01000000u) {
      exp++;
      frac = 0u;
    } else {
      frac = rounded & 0x7FFFFFu;
    }
  } else {
    unsigned remainder;
    rounded = product >> 2;
    remainder = product & 3u;
    if (remainder > 2u || (remainder == 2u && (rounded & 1u)))
      rounded++;
    exp++;
    frac = rounded & 0x7FFFFFu;
  }
  if (exp >= 0xFFu)
    return sign | 0x7F800000u;
  return sign | (exp << 23) | frac;

}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned significand;
  unsigned rounded;
  unsigned remainder;
  unsigned half;
  unsigned shift;
  unsigned temp;
  unsigned bit;
  unsigned resultExp;
  if (exp == 0xFFu || exp >= 150u)
    return uf;
  if (exp < 126u || (exp == 126u && frac == 0u))
    return sign;
  if (exp == 126u)
    return sign | 0x3F800000u;
  significand = 0x800000u | frac;
  shift = 150u - exp;
  rounded = significand >> shift;
  remainder = significand & ((1u << shift) - 1u);
  half = 1u << (shift - 1u);
  if (remainder > half || (remainder == half && (rounded & 1u)))
    rounded++;
  if (rounded == 0u)
    return sign;
  temp = rounded;
  bit = 0u;
  while (temp > 1u) {
    temp >>= 1;
    bit++;
  }
  resultExp = bit + 127u;
  return sign | (resultExp << 23) | ((rounded << (23u - bit)) & 0x7FFFFFu);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0u;
  unsigned magnitude = x;
  unsigned temp;
  unsigned significand;
  unsigned remainder;
  unsigned half;
  unsigned shift;
  unsigned exp;
  int msb = 0;
  if (x == 0)
    return 0u;
  if (x < 0) {
    sign = 0x80000000u;
    magnitude = ~magnitude + 1u;
  }
  temp = magnitude;
  while (temp > 1u) {
    temp >>= 1;
    msb++;
  }
  exp = msb + 127u;
  if (msb <= 23)
    significand = magnitude << (23 - msb);
  else {
    shift = msb - 23;
    significand = magnitude >> shift;
    remainder = magnitude & ((1u << shift) - 1u);
    half = 1u << (shift - 1u);
    if (remainder > half || (remainder == half && (significand & 1u)))
      significand++;
    if (significand == 0x01000000u) {
      significand >>= 1;
      exp++;
    }
  }
  return sign | (exp << 23) | (significand & 0x7FFFFFu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask4 = 0x0F | (0x0F << 8);
  mask4 = mask4 | (mask4 << 16);
  int mask2 = mask4 ^ (mask4 << 2);
  int mask1 = mask2 ^ (mask2 << 1);
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x + (x >> 4)) & mask4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask = 0xFF | (0xFF << 8);
  x = ((x >> 16) & mask) | (x << 16);
  mask = mask ^ (mask << 8);
  x = ((x >> 8) & mask) | ((x & mask) << 8);
  mask = mask ^ (mask << 4);
  x = ((x >> 4) & mask) | ((x & mask) << 4);
  mask = mask ^ (mask << 2);
  x = ((x >> 2) & mask) | ((x & mask) << 2);
  mask = mask ^ (mask << 1);
  x = ((x >> 1) & mask) | ((x & mask) << 1);
  return x;
}
