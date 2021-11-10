#include "includeAll.h"

#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

bool IsFilterFilename(char *Filename)
{
    if(!strcmp(Filename, ".")) return true;
    if(!strcmp(Filename, "..")) return true;
    if(!strcmp(Filename, "desktop.ini")) return true;
    if(!strcmp(Filename, "icon.ico")) return true;

    return false;
}

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
            printf("%s:\n", token);
            while ((dir = readdir(d)) != NULL)
            {
                if(IsFilterFilename(dir->d_name)) continue;
                
                int numOfNums = CountNumbersInAString(dir->d_name);
                int number = GetNumberOutOfString(dir->d_name, numOfNums, false, false);
                
                char str[ENOUGH];
                sprintf(str, "%d", number);// convert int to string
                strcat(str, ".txt");

                char *oldName = token;
                char *newName = token;

                strcat(oldName, dir->d_name);
                strcat(newName, str);

                //printf("OldName-%s\nNewName-%s\n", oldName, newName);
                int result = rename(oldName, newName);
                if(!result)
                    printf("%s --> %d\n",dir->d_name, number);
                else    
                    printf("Error: %s: %s\n", strerror(errno), dir->d_name);
            }
            closedir(d);
        }
        else
        {
            printf("Error: %s: %s\n", strerror(errno), token);
        }


        token = strtok(NULL, "|");//get next value
    }

}