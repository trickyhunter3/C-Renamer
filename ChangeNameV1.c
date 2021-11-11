#include "includeAll.h"
#include "IsFilterFilename.c"
#include "GetHighestLengthStingInADirectory.c"
#include "GetFileNameExt.c"
#include "LastChr.c"

#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

void ChangeNameV1(char *argv[])
{
    //        argv[0]  argv[1]   argv[2]                           argv[3]                argv[4]                       argv[5]
    //format --> .exe 0          "path1,path2,path3..."          is the number first?      is the number last?           0/1
    //                ^          ^                                  1-yes            1-yes                              ^   
    //              this         place where the files              0-no             0-no                            Function to 
    //              Function     are to be renamed                                                                  GetNumbersOutOfString
    //                                                                                                              (V2 is default -> 1)

    //for now only one function of GetNumber (V1) 11/9/2021

    if(!argv[2])
    {
        printf("example: .exe 0 \"Path1|Path2\" 0/1 0/1 0/1\n");
        printf("first 0/1 is The version of GetNumberOutOfString\n");
        printf("second 0/1 is returning the first number found in GetNumberOutOfString\n");
        printf("third 0/1 is returning the last number found in GetNumberOutOfString\n");
        return;
    }
    char *token = strtok(argv[2], "|");//Split paths into an array

    bool isLastNoIntialize = true;
    char *isFirst;
    char *isLast;

    if(!argv[3])
    {
        isFirst = "0";
    }
    else
    {
        isFirst = argv[3];

        if(!argv[4])
            isLast = "0";
        else 
            isLast = argv[4];
        isLastNoIntialize = false;
    }

    if(isLastNoIntialize)
    {
        isLast = "0";
    }

    while( token != NULL ) 
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(token);

        if (d)
        {
            char *currentPath = NULL, *oldName, *newName;
            if(LastChr(token) != '\\')
            {
                //if the last letter not a '\\'
                currentPath = malloc(strlen(token) + 2);//'\0' and '\\' i need to add so 2
                strcpy(currentPath, token);
                strcat(currentPath, "\\");

                //make 2 copys of the current path for the new and old name;
                oldName = malloc(strlen(currentPath) + GetHighestLengthStingInADirectory(d, currentPath) + 1);//allocate enough memory
                newName = malloc(strlen(currentPath) + 13);//max 12 characters total so 8 numbers left (for the newName)
                strcpy(oldName, currentPath);
                strcpy(newName, currentPath);
            }
            else
            {
                //make 2 copys of the current path for the new and old name;
                oldName = malloc(strlen(token) + GetHighestLengthStingInADirectory(d, token) + 1);//allocate enough memory
                newName = malloc(strlen(token) + 13);//max 12 characters total so 8 numbers left (for the newName)
                strcpy(oldName, token);
                strcpy(newName, token);
            }

            printf("dir: %s\n", token);
            while ((dir = readdir(d)) != NULL)
            {
                //filter unwanted names
                if(IsFilterFilename(dir->d_name)) continue;
                
                //Get the number to be renamed into
                int numOfNums = CountNumbersInAString(dir->d_name);
                int number = GetNumberOutOfString(dir->d_name, numOfNums, isFirst, isLast);
                
                // convert int to string
                char str[ENOUGH];
                sprintf(str, "%d", number);
                strcat(str, ".");
                strcat(str, GetFileNameExt(dir->d_name));

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
                if(currentPath != NULL)
                {
                    strcpy(oldName, currentPath);
                    strcpy(newName, currentPath);
                }
                else
                {
                    strcpy(oldName, token);
                    strcpy(newName, token);
                }
            }
            //close directory
            closedir(d);
            
            //free memory (used malloc)
            free(currentPath);
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