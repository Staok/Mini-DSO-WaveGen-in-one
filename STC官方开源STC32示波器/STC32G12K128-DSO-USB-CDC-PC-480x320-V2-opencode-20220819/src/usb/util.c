#include "stc.h"
#include "util.h"

DWORD reverse4(DWORD d)
{   
    DWORD ret;
    
    ((BYTE *)&ret)[0] = ((BYTE *)&d)[3];
    ((BYTE *)&ret)[1] = ((BYTE *)&d)[2];
    ((BYTE *)&ret)[2] = ((BYTE *)&d)[1];
    ((BYTE *)&ret)[3] = ((BYTE *)&d)[0];

    return ret;
}
   
WORD reverse2(WORD w)
{
    WORD ret;
    
    ((BYTE *)&ret)[0] = ((BYTE *)&w)[1];
    ((BYTE *)&ret)[1] = ((BYTE *)&w)[0];

    return ret;
}
