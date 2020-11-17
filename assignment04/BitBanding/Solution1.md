a)b) No bit-band addressing available for writing to or reading from GPIO registers bits. Anyway for GPIO, the BSRR register provides the atomic read-modify-write facility through hardware.

     But Bit-Banding on RCC AHB2ENR register reduced Four step operation to Three steps i.e. logical OR operation for writing into register was not required. Writing into Bit Banding alias maps directly into the bit location of RCC_AHB2ENR register.
