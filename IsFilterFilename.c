#include "includeAll.h"

bool IsFilterFilename(char *Filename)
{
    if(!strcmp(Filename, ".")) return true;
    if(!strcmp(Filename, "..")) return true;
    if(!strcmp(Filename, "desktop.ini")) return true;
    if(!strcmp(Filename, "icon.ico")) return true;

    return false;
}