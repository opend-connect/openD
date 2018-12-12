#ifdef __cplusplus
extern "C"
{
#endif

unsigned char asciiToHex(unsigned char data) {
  if (data > '9') {
    data += 9;
  }
  return (data &= 0x0F);
}

#ifdef __cplusplus
}
#endif
