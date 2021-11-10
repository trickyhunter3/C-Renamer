#include "includeAll.h"
#include "includeFunctions.h"

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        switch (atoi(argv[1]))
        {
        case Desc:
            Description();
            break;
        case ChangeV1:
            ChangeNameV1(argv);
            break;
        }
    }
    else
    {
        printf("Error: There Are No Arguments\n");
        Description();
        return 1;
    }    
    return 0;
}