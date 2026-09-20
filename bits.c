/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    /* 同号 = 符号位相同 且 "是否为 0" 相同（0 只与 0 同号） */
    return !((x >> 31) ^ (y >> 31)) & !(!x ^ !y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    /* 二分找最高位 1 的位置：每轮用比较结果决定是否右移，并把位移量累加进结果 */
    int r, s;
    r = (v > 0xFFFF) << 4;
    v >>= r;
    s = (v > 0xFF) << 3;
    v >>= s;
    r |= s;
    s = (v > 0xF) << 2;
    v >>= s;
    r |= s;
    s = (v > 0x3) << 1;
    v >>= s;
    r |= s;
    r |= (v >> 1);
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    /* t = 两字节之差（异或值），分别异或回两个位置即可完成交换；n == m 时 t == 0 */
    int sn = n << 3;
    int sm = m << 3;
    int t = ((x >> sn) ^ (x >> sm)) & 0xFF;
    return x ^ (t << sn) ^ (t << sm);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    /* 蝶形交换：先按 1 位交换，再 2 位、4 位、8 位、16 位 */
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    return (v >> 16) | (v << 16);
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    /* 算术右移后，把高 n 位强行清零 */
    int mask = ((1 << 31) >> n) << 1;
    return (x >> n) & ~mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    /* 二分：若最高 k 位全 1 则计数加 k 并左移 k 位，k = 16, 8, 4, 2, 1 */
    int c, n;
    n = !(~(x >> 16)) << 4;
    c = n;
    x = x << n;
    n = !(~(x >> 24)) << 3;
    c = c + n;
    x = x << n;
    n = !(~(x >> 28)) << 2;
    c = c + n;
    x = x << n;
    n = !(~(x >> 30)) << 1;
    c = c + n;
    x = x << n;
    n = !(~(x >> 31));
    c = c + n;
    x = x << n;
    /* 上面最多数到 31，剩下的最高位仍为 1 说明 32 位全是 1 */
    return c + ((x >> 31) & 1);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned a = x;
    unsigned e = 158; /* 127 + 31：规格化后隐含位在第 31 位时的阶码 */
    unsigned f, r, res;
    if (x == 0)
        return 0;
    if (x < 0) {
        sign = 0x80000000;
        a = -a;
    }
    /* 左移到最高位为 1，每左移一位阶码减 1 */
    while (!(a & 0x80000000)) {
        a = a << 1;
        e = e - 1;
    }
    f = (a >> 8) & 0x7FFFFF; /* 取隐含位之后的 23 位尾数 */
    r = a & 0xFF;            /* 被丢弃的 8 位，用于舍入 */
    res = sign | (e << 23) | f;
    /* 就近舍入、平局取偶；进位会自然传入阶码 */
    if ((r > 0x80) | ((r == 0x80) & (f & 1)))
        res = res + 1;
    return res;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    if (exp == 0xFF) /* NaN 原样返回，无穷乘 2 仍是无穷 */
        return uf;
    if (exp == 0) /* 非规格化：尾数左移一位，进位会自然变成阶码 1 */
        return sign | (frac << 1);
    exp = exp + 1;
    if (exp == 0xFF) /* 上溢为无穷，尾数必须清零 */
        return sign | 0x7F800000;
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned val;
    if (exp < 1023) /* |x| < 1，向零舍入得 0 */
        return 0;
    if (exp > 1054) /* |x| >= 2^32，必然越界（含 inf 与 NaN） */
        return 0x80000000;
    /* 补上隐含位，取最高 32 位有效数字：隐含 1 放在第 31 位 */
    val = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    val = val >> (1054 - exp); /* 右移即向零舍入 */
    if (sign) {
        if (val > 0x80000000)
            return 0x80000000;
        return -val;
    }
    if (val > 0x7FFFFFFF)
        return 0x80000000;
    return val;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) /* 超出最大规格化数，返回 +INF */
        return 0x7F800000;
    if (x < -149) /* 比最小非规格化数还小 */
        return 0;
    if (x < -126) /* 非规格化：尾数第 (x + 149) 位置 1 */
        return 1 << (x + 149);
    return (x + 127) << 23; /* 规格化：尾数为 0，只需填阶码 */
}
