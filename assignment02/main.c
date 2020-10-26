unsigned int counter = 0x0;

int main()
{
  /*
  //int counter = 0;
  counter ++;
  counter ++;
  counter ++;
  counter ++;
  counter ++;
  counter ++;
  counter ++;*/
  
  unsigned int *p_int = (unsigned int *)0x20000000;
  ++(*p_int);
  ++(*p_int);
  ++(*p_int);
  counter ++;

  return 0;
}
