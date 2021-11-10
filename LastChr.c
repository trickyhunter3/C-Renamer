#include "includeAll.h"

char LastChr(char *c) 
{
    if(c == NULL || *c == '\0') return 0;
    return c[strlen(c)-1];
}