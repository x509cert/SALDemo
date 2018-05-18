Using VC++, compile at /W4 - you get no warnings.

Clearly, there's a memory corruption issue as the code allocates 32 bytes and creates 60 '!' characters in that buffer. Oops!

Now change:
      char *szBuff 
 to
      _Out_cap_(cb) char *szBuff
 
Now recompile. You get two warnings, one is because of the memory corruption and the other is about a mismatch from malloc.
When malloc() fails it returns NULL, but char *szBuff cannot be NULL, otherwise the annotation would include _Opt (optional)

The compiler knows that malloc() can return null because of its SAL annotation in corecrt_malloc.h:

_Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
_ACRTIMP _CRTALLOCATOR _CRT_JIT_INTRINSIC _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void* __cdecl malloc(
    _In_ _CRT_GUARDOVERFLOW size_t _Size
    );

Note the use of _Ret_maybenull_

So to fix these issues, change:
      FillMemory(d, 60, '!');
 to
      if (d) FillMemory(d, 32, '!');

Voila :)
