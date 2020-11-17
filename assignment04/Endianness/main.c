/*
 * If debugger set to simulator:
 * - target selected to be M3/M4 Big Endian    - program will return -1.
 * - target selected to be M3/M4 Little Endian - program will return 0.
 *
 * Determines any processor endianness by reading lower byte of a 32 bit value and identifying it's stored location in memory
*/

int main()
{
    int var = 0x12345678;
    char *varc = (char*)&var;
    if(*varc == 0x78)
    {
        // Little Endian - LSB byte is stored first (lower memory address)
        return 0;
    }
    else
    {
        // Big Endian - MSB byte is stored first (lower memory address)
        return -1;   
    }
}
