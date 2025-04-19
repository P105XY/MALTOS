#include "MaltConsole.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <xpsprint.h>
#include <print>

extern "C" int _outp(unsigned short, int);

void OutPortByte(ushort port, uchar value)
{
	_outp(port, value);
}

