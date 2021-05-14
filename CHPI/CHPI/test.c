// unsigned char string[] = "hello world titititititititititi";

char *string __attribute__ ((section(".rodata")))= {"hello world titititititititititi"};

int count;

int test (void)
{
  for (count=0; count<12; count++)
    string[count] = 'a' + (unsigned char) count;
  return (0);
}
