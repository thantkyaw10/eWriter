#ifndef __eWriter_H
#define __eWriter_H

#include <stdio.h>
#include <stdlib.h>
#include "IT8951.h"
#include <dirent.h>

char * openFile (char * filename, char*str, int charnum);
void eprint(uint8_t *str);
char * getFile();
void listdoc();

#endif
