#include "sorting.h"

void fileSort(char *destinationPath, char **newFileName, size_t *newFileNameSize, char **oldFileName, size_t *oldFileNameSize, char *mainFolderPath, struct dirent *entry)
{
  char *temp = NULL;
  
  *newFileNameSize = strlen(destinationPath) + strlen(entry->d_name) + 1; // +1 for the null terminator  
  temp = realloc(*newFileName, *newFileNameSize);
  if (temp == NULL)
  {
    free(*newFileName);
    printf("\nMemory allocation failed.");
    exit(1);
  }
  *newFileName = temp;
  temp = NULL;

  snprintf(*newFileName, *newFileNameSize, "%s%s", destinationPath, entry->d_name);

  *oldFileNameSize = strlen(mainFolderPath) + strlen(entry->d_name) + 1; // +1 for null terminator
  temp = realloc(*oldFileName, *oldFileNameSize);
  if (temp == NULL)
  {
    free(*oldFileName);
    printf("\nMemory allocation failed.");
    exit(1);
  }
  *oldFileName = temp;
  temp = NULL;

  snprintf(*oldFileName, *oldFileNameSize, "%s%s", mainFolderPath, entry->d_name);

  int result = rename(*oldFileName, *newFileName);
  if (result == 0)
  {
    printf("\n\e[1;32mMoved:\e[0m %s -> %s", *oldFileName, *newFileName); 
  }
  else
  {
    printf("\nFailed to move file.");
    exit(1);
  }
}

