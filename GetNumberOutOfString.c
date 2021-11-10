#include "includeAll.h"

int GetNumberOutOfString(char *filename, int numOfNums, bool isFirst, bool isLast)
{
    if(!numOfNums)
        return -1;//no number found
    
    char *p = filename;
    int i = 0;
    int arr[numOfNums];
    
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

    if(isFirst)
        return arr[0];//first number
    if(isLast)
        return arr[numOfNums - 1];//last number

    bool currentNumberTaken = false;
    int converted = 0;
    int number_holder = -1;
    for(int i = 0; i < numOfNums; i++)
    {
        if(arr[i] == 0)
            number_holder = 0;
        switch (arr[i])//filter numbers
        {
            case 480:
            case 640:
            case 720:
            case 1080:
            case 1280:
            case 1920:
            case 2010:
            case 2160:
            case 3840:
            if (number_holder)
            {
                number_holder = arr[i];
                currentNumberTaken = true;
            }
            break;
        }
        if(!currentNumberTaken)
        {
            converted = arr[i]; 
            currentNumberTaken = false;
        }
    }

    if (converted + number_holder == number_holder)
        return number_holder; 
        //converted + num = num that means that the season or resolution filter worked but was not necessary
    return converted;
}