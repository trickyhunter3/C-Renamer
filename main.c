#include "includeAll.h"
#include "includeFunctions.h"

int main(int argc, char *argv[])
{
    if(argv[1])
    {
        char *name;
        switch (atoi(argv[1]))
        {
        case ChangeV1:
            ChangeNameV1(argv);
            break;
        default:
            Description();
        }
    }
    else
    {
        Description();
        return 1;
    }    
    return 0;
}