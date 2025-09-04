
=====================================
Fixed-point numbers store numbers as integers internally, but we treat them as having a fractional part.

_fixed_point_num (the raw value) is this integer that holds both the whole and fractional part.

=====================================
Imagine a pizza

You cut every pizza into 256 slices (because we chose 8 fractional bits = 2^8 = 256).

Now, instead of saying “I ate 1.5 pizzas,” we only count slices.

Examples

1 pizza = 256 slices.

0.5 pizza = 128 slices.

1.5 pizzas = 256 + 128 = 384 slices.

The computer only stores the number of slices (an int).

If you want to know how many pizzas it really is, you divide by 256.

So:

Internal: 384 (slices)

External meaning: 384 ÷ 256 = 1.5 pizzas.

That’s fixed-point math:

Store as integer slices.

Interpret as pizzas (divide by 256).
======================================
EXAMPLE
======================================
Assume _fractional_bits = 8. That means you always shift left by 8 → multiply by 2 na 8ma = 256

Fixed a(5);
num = 5
_raw_num = 5 << 8 = 5 * 256 = 1280

Stored raw value = 1280
So internally it’s 1280, but it represents 5.0 in fixed-point.
=====================================
We store integers inside, but pretend they are fixed-point with 8 fractional bits.
That means:

1 unit = 2^8 = 256 raw steps.

So the raw integer is always real_value × 256.
======================================
2. Example with integer (5.0):
raw = 5.0 × 256 = 1280


Stored raw = 1280.
When you divide by 256 again, you get back 5.0.

3. Example with fraction (5.5):
raw = 5.5 × 256 = 1408


Stored raw = 1408.
When read back: 1408 / 256 = 5.5.
=======================================

4. Range of fractional part:

With 8 bits for the fraction:

Smallest step = 1/256 ≈ 0.0039.

So numbers are always multiples of 0.0039.

5. Answer to your question:

No, it’s not limited to 5.255.
You can go much higher, because the whole number part uses all the other bits of the int.

Example:

With 32-bit int and 8 fractional bits → 24 bits for the integer part.

Max value ≈ 2^24 - 1 + 255/256 ≈ 16,777,215.996.

So:

Fractional part: max is 255/256 = 0.996.

Whole part: can be very large.
 Fixed-point just splits the bits: 24 bits whole + 8 bits fraction (in this project).
 ================================
 8 bits → 2^8 = 256 possible values

They are numbered: 0, 1, 2, …, 255 → that’s 256 values in total

That’s where 255 comes from: the largest number you can represent in 8 bits.
each step = 1 / 256 ≈ 0.00390625.

If fraction bits = 8, the smallest fractional increment = 0.0039

Max fraction = 255 / 256 ≈ 0.996
==================================