1. Inject 0x7FFFFFFF for the “counter” value in the variable window:

a) Value of Counter becomes -2147483648 in Local window (default format is Decimal - 32 bit signed value wraps around to it's max negative value)
b) Value of Counter becomes 0x80000000 in Registers window.
c) N and V flags are set to '1' in APSR register - indicates Negative term (counter++ resulted in negative bit i.e.[31]) and an overflow condition (post increment on counter resulted in exceeding the range allowed by the size of the bit field)

2. Writing all Fs (0XFFFFFFFF) in the Register value for “counter” then step thru the program once to increment “counter”:

a) Value becomes '0' and '0x0' in Locals window and Register window respectively.
b) N and V are set to '0' and '0' respectively in APSR register. CPU stores negative number in 2's complement form, 0xFFFFFFFF is 2'complement respresent of decimal -1 and incrementing -1 results in 0. So, neither negative flag nor overflow flag are set.

3. Change the “counter” variable type in your code to “unsigned int”.  Inject the values “0x7FFFFFFF” then step thru the program to increment the “counter” once:

a) After increment, 'counter' and 'local' window values are 2147483648 (decimal) and 0x80000000 respectively.
b) N and V flags are set to '1' in APSR register (Expecting something wrong with IAR register setting (same result with simulator & device debugging), ideally Negative flag shouldn't be set for unsigned numbers & ++(0x7FFFFFFF) result in (0x80000000), which is not an overflow condition for unsigned integer) )
   It is true if internal logic sets N bit is set to the two's complement sign bit of the result (bit 31) regardless of signed or unsigned term. But anyhow ovwerflow condition do not add up here.
   
4. Change the “counter” variable type in your code to “unsigned”. Inject the values “0xFFFFFFFF” then step thru the program to increment the “counter” once:

a) Value becomes '0' and '0x0' in Locals window and Register window respectively.
b) N and V are set to '0' and '0' respectively in APSR register. A result that cannot be represented by the resulting unsigned integer type is reduced modulo the number that is one greater than
   the largest value that can be represented by the resulting type (i.e. (0xffffffff + 0x1) % 0x100000000)

5. Move the “counter’ variable outside of main (at the top of the file):

a) Now the counter variable is in Global scope.
b) No, variable isn't visible in Locals view.
c) We can look at counter variable by adding it to the Live Watch view.
d) The address of the counter variable - 0x20000000.

6. Pointer program:

a) The value of the counter at the end of program is '4'.
b) Reason: pointer 'p_int' points to the address of gloabal variable 'counter'. Incrementing (*p_int) is seen as incrementing the value stored by p_int variable.

7. Running above pointer program in STM32L575 evaluation board:

a) Counter is stored at following memory location : 0x20000000.
b) Stored in RAM location.
c) Counter value is 4 at the end of the program.
