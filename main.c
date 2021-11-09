#include "includeAll.h"
#include "includeFunctions.h"

int main(int argc, char *argv[])
{
    int numbersCount = CountNumbersInAString(argv[1]);
    int *nums = GetNumberOutOfString(argv[1], numbersCount);
    for(int i = 0; i < numbersCount; i++)
    {
        printf("%d\n", *(nums + i));
    }
    
    return 0;
}