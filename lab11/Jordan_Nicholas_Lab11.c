/*
 * CMPS 3600
 * Jordan Nicholas
 * Lab 11
 */

#include "Jordan_Nicholas_Lab11.h"

int main(int argc, char **argv)
{
    mode_t addPermissions = 0;
    mode_t removePermissions = 0;
    setPermissions(&addPermissions, &removePermissions, argc, argv);
    if (changePermissions(addPermissions, removePermissions, argc, argv))
        return 0;
    exit(1);    
}

