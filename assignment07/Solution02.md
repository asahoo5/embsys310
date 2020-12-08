a) Total ROM Memory (Code + Data) occupied = (376 + 82) = 458 bytes

b) Total RAM Memory occupied = 8196 bytes (Linker created 8192 bytes which is the stack size and the 4 byte uTickCounter global variable )

c) IAR initialization & startup library i.e. rt7M_tl.a take the most Read Only Memory (150 bytes), whereas (delay.o + main.o + startup_stm32l475xx.o) occupies 158 Code + 68 Data = 226 bytes.

d) CStack space (8192 bytes) took the most of RAM.

3. Usage of RAM can be optimized by limiting the Stack Size based on the Application requirement. In this particular case, we do not need 8196 bytes of memory to do the task - so it can be reduced.
