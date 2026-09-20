#include "sorting.h"

void imageSort(char *imagesPath, char **newFileName, size_t *newFileNameSize, char **oldFileName, size_t *oldFileNameSize, char *downloadsFolderPath, struct dirent *entry)
{
  char *temp = NULL;

  if (strchr(imagesPath, '/') != NULL)
  {
    if (*(strrchr(imagesPath, '/') + 1) == '\0')
    {
      *newFileNameSize = strlen(imagesPath) + strlen(entry->d_name) + 1; // +1 for the null terminator  
      temp = realloc(*newFileName, *newFileNameSize);
      if (temp == NULL)
      {
        free(*newFileName);
        printf("\nMemory allocation failed.");
        exit(1);
      }
      *newFileName = temp;
      temp = NULL;

      snprintf(*newFileName, *newFileNameSize, "%s%s", imagesPath, entry->d_name);
    }
    else 
    {
      *newFileNameSize = strlen(imagesPath) + strlen(entry->d_name) + 2; // +2 for null terminator AND the extra / 
      temp = realloc(*newFileName, *newFileNameSize);
      if (temp == NULL)
      {
        free(*newFileName);
        printf("\nMemory allocation failed.");
        exit(1);
      }
      *newFileName = temp;
      temp = NULL;

      snprintf(*newFileName, *newFileNameSize, "%s/%s", imagesPath, entry->d_name);
    }
  }
  else 
  {
    printf("\nALL PATHS MUST HAVE ATLEAST 1 '/' CHARACTER.");
    exit(1);
  } 

  *oldFileNameSize = strlen(downloadsFolderPath) + strlen(entry->d_name) + 1; // +1 for null terminator
  temp = realloc(*oldFileName, *oldFileNameSize);
  if (temp == NULL)
  {
    free(*oldFileName);
    printf("\nMemory allocation failed.");
    exit(1);
  }
  *oldFileName = temp;
  temp = NULL;

  snprintf(*oldFileName, *oldFileNameSize, "%s%s", downloadsFolderPath, entry->d_name);

  int result = rename(*oldFileName, *newFileName);
  if (result == 0)
  {
    printf("%s -> %s\n", *newFileName, entry->d_name); 
  }
  else
  {
    printf("\nFailed to move file.");
    exit(1);
  }
}
