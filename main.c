#include "includeAll.h"
#include "includeFunctions.h"

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        int numbersCount = CountNumbersInAString(argv[1]);
        int num = GetNumberOutOfString(argv[1], numbersCount, false, false);
        printf("%d\n", num);
    }
    else
    {
        printf("Error: There Is No Arguments");
        return 1;
    }    
    return 0;
}