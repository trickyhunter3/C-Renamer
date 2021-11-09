#include "includeAll.h"

int CountNumbersInAString(char *fileName)
{
    char *p = fileName;
    int count = 0;
    while (*p) //count how much numbers in the name
    {
        if (isdigit(*p)) 
        {
            count++;
            strtol(p, &p, 10);//this moves the *p or something so the thing works
        }
        else 
            p++;
    }

    return count;
}