#include "includeAll.h"


int *GetNumberOutOfString(char *fileName, int numOfNums)
{
    char *p = fileName;
    int i = 0;

    while (*p)//get all the numbers in an array
    {
        if (isdigit(*p)) 
        {
            int val = strtol(p, &p, 10);
            arr[i] = val;
            i++;
        }
        else p++;
    }

    int converted = 0;
    int number_holder = -1;
    for(int i = 0; i < numOfNums; i++)
    {
        switch (arr[i])
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 480:
            case 640:
            case 720:
            case 1080:
            case 1280:
            case 1920:
            case 2010:
            case 2160:
            case 3840:
            if (number_holder != 0)
            {
                number_holder = arr[i];
            }
            break;
        }
    }
    return arr;
}