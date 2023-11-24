void setup()
{
  Serial.begin(115200);
  while (!Serial) { }
}

void sendByte(int value)
{
  Serial.write(value);
}

void sendInt16(int value)
{
  sendByte(value);
  sendByte(value >> 8);
}

void sendInt24(int32_t value)
{
  sendByte(value);
  sendByte(value >> 8);
  sendByte(value >> 16);
}

void sendInt32(int32_t value)
{
  sendInt16(value);
  sendInt16(value >> 16);
}

void sendFloat(float fvalue)
{
  char* p;
  p = (char*)&fvalue;
  for (int i = 0; i < 4; i++)
  {
    sendByte(p[i]);
  }
}

int counter = 0;
float fcounter = 0.0;

void loop()
{
  if (Serial.available() > 0)
  {
    int inByte = Serial.read();
    if (inByte == 8)
    {
      for (int i = 0; i < 128; i++) // 768 bytes
      {
        int m = millis();
        sendInt32(m);
        sendInt16(i);
      }
    }
    if (inByte == 9)
    {
      for (int i = 0; i < 1900; i++) // 11400 bytes
      {
        int m = millis();
        sendInt32(m);
        sendInt16(i);
      }
    }
    if (inByte == 10) // 12 bytes
    {
      int m = millis();
      sendInt32(m);
      sendByte(counter);
      sendInt24(counter++);
      sendFloat(fcounter);
      fcounter += 0.1;
    }
    if (inByte == 11) // 60 bytes
    {      
      for (int i = 0; i < 5; i++)
      {
        int m = millis();
        sendInt32(m);
        sendByte(counter);
        sendInt24(counter++);
        sendFloat(fcounter);
        fcounter += 0.1;
      }
    }
    if (inByte == 12) // 1 byte
    {
      sendByte(counter++);
    }
    if (inByte == 13) 
    {
      sendByte(129);
      sendByte(129);
      sendInt16(48123);//Uint16
      sendInt16(-20123);//Int16
      sendInt24(9123456);//UInt24
      sendInt24(-6123456);//Int24
      sendInt32(3123456789);//Uint32
      sendInt32(-1512345678);//Int32
      sendFloat(123.148);
      sendFloat(-123.148);
    }
  }
}