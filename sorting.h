#ifndef SORTING_H
#define SORTING_H

#include "Main.h"

void fileSort(char *destinationPath, char **newFileName, size_t *newFileNameSize, char **oldFileName, size_t *oldFileNameSize, char *mainFolderPath, struct dirent *entry);

#endif
