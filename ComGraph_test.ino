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

void sendInt32(int value)
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
    if (inByte == 9)
    {
      for (int i = 0; i < 1900; i++)
      {
        int m = millis();
        sendInt32(m);
        sendInt16(i);
      }
    }
    if (inByte == 10)
    {
      int m = millis();
      sendInt32(m);
      sendByte(counter);
      sendInt32(counter++);
      sendFloat(fcounter);
      fcounter += 0.1;
    }
  }
}