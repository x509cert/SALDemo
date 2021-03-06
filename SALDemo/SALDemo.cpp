// Simple demo for SAL using _Out_cap_() 
// mikehow@microsoft.com
// Info about SAL at:
// https://blogs.msdn.microsoft.com/michael_howard/2006/05/19/a-brief-introduction-to-the-standard-annotation-language-sal/
// https://cloudblogs.microsoft.com/microsoftsecure/2009/06/11/a-declspec-sal-to-attribute-sal-rosetta-stone/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SCRIPT
// Using VC++, compile at /W4 - you get no warnings. 
// Clearly, there's a memory corruption issue as the code allocates 32 bytes and creates 60 '!' characters in that buffer. Oops!
// Now change:
//      char *szBuff 
// to
//      _Out_cap_(cb) char *szBuff
// 
// Now recompile, you get two warnings, one is because of the memory corruption and the other is about a mismatch from malloc
// When malloc() fails it returns NULL, but char *szBuff cannot be NULL, otherwise the annotation would include _Opt (optional)
// So to fix these issues, change:
//      FillMemory(d, 60, '!');
// to
//      if (d) FillMemory(d, 32, '!');
// Voila :)


#include "stdafx.h"

void FillMemory(char *szBuff,
				size_t cb, 
				char c) {

	for (size_t i = 0; i < cb; i++)
		*szBuff++ = c;
}



int main()
{
	char *d = (char*)malloc(32);

	FillMemory(d, 60, '!');

	return 0;
}

