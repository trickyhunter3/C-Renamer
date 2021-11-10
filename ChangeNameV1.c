#include "includeAll.h"
#include "IsFilterFilename.c"
#include "GetHighestLengthStingInADirectory.c"

#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

void ChangeNameV1(char *argv[])
{
    //        argv[0]  argv[1]   argv[2]                            argv[3]
    //format --> .exe 1          "path1,path2,path3..."             0/1
    //                ^          ^                                   ^
    //              this         place where the files          Function to 
    //              Function     are to be renamed              GetNumbersOutOfString
    //                                                          (V2 is default -> 1)

    //for now only one function of GetNumber (V1) 11/9/2021

    if(!argv[2])
    {
        printf("Error: ChangeNameV1 - No Path Was Provided");
        return;
    }
    char *token = strtok(argv[2], "|");//Split paths into an array

    while( token != NULL ) 
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(token);

        if (d)
        {
            //make 2 copys of the current path for the new and old name;
            char *oldName = malloc(strlen(token) + strlen(token));
            char *newName = malloc(strlen(token) + 8);
            strcpy(oldName, token);
            strcpy(newName, token);

            printf("dir:%s\n", token);
            while ((dir = readdir(d)) != NULL)
            {
                //filter unwanted names
                if(IsFilterFilename(dir->d_name)) continue;
                
                //Get the number to be renamed into
                int numOfNums = CountNumbersInAString(dir->d_name);
                int number = GetNumberOutOfString(dir->d_name, numOfNums, false, false);
                
                // convert int to string
                char str[ENOUGH];//TODO: int nDigits = floor(log10(abs(the_integer))) + 1; 
                sprintf(str, "%d", number);
                strcat(str, ".txt");

                //add the files name to the current pWath
                strcat(oldName, (dir->d_name));
                strcat(newName, str);

                //rename the file
                int result = rename(oldName, newName);
                if(!result)
                    printf("%s --> %d\n",dir->d_name, number);
                else    
                    printf("Error: %s: %s\n", strerror(errno), dir->d_name);

                //reset the value to the current path
                strcpy(oldName, token);
                strcpy(newName, token);
            }
            //close directory
            closedir(d);
            
            //free memory (used malloc)
            free(oldName);
            free(newName);
        }
        else
        {
            printf("Error: %s: %s\n", strerror(errno), token);
        }


        token = strtok(NULL, "|");//get next value
    }

}