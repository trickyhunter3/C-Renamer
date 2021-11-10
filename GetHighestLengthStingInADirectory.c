#include "includeAll.h"

int GetHighestLengthStingInADirectory(DIR *d, char *path)
{
    int max = 1;

    struct dirent *dir;
    d = opendir(path);
    while ((dir = readdir(d)) != NULL)
    {
        //small filter
        if(dir->d_name == "desktop.ini" || dir->d_name == "icon.ico") continue;

        if(dir->d_namlen > max)
            max = dir->d_namlen;
    }

    return max;
}