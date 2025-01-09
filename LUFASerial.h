
#ifndef LUFASerial_h
#define LUFASerial_h


#include "Arduino.h"

class LUFASerial {
	private:
	public:
	 LUFASerial();
   void begin(long baud);
	 void print(const char* StringPtr);
   void print(long value);
   void printhex(int value);
   void write(int value);
	 void println(const char* StringPtr);
   void println(long value);
   void println(long value,int type);
};

#endif
