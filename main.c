#include "Main.h"

// Helper libs
#include "sorting.h"

// 1. Get file extension
// 2. Find directory to place file in 
// 3. Rename file, if files are in dif

bool is_valid_directory(char *path)
{
  struct stat path_stat;
  
  if (stat(path, &path_stat) != 0)
  {
    return false;
  }

  return S_ISDIR(path_stat.st_mode);
}

void pathValidation(char *path, size_t *pathToChangeSize, char **pathToChange)
{
  char *temp = NULL;

  if ((path != NULL && strlen(path) > 0) && is_valid_directory(path))
  {
    if (path[(strlen(path) - 1)] == '/')
    {
      *pathToChangeSize = strlen(path) + 1; // length of path + null terminator
      temp = realloc(*pathToChange, *pathToChangeSize);
      if (temp == NULL)
      {
        printf("\nMemory allocation failed.");
        free(*pathToChange);
        exit(1);
      }
      *pathToChange = temp;
    
      snprintf(*pathToChange, *pathToChangeSize, path);
    }
    else
    {
      *pathToChangeSize = strlen(path) + 2; // length of path + / + null terminator
      temp = realloc(*pathToChange, *pathToChangeSize);
      if (temp == NULL)
      {
        printf("\nMemory allocation failed.");
        free(*pathToChange);
        exit(1);
      }
      *pathToChange = temp;

      snprintf(*pathToChange, *pathToChangeSize, "%s/", path);
    }
  }
  else 
  {
    printf("\nPlease enter valid path.");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  size_t newFileNameSize = 1024;
  char *newFileName = malloc(newFileNameSize);
  if (newFileName == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }
  size_t oldFileNameSize = 1024;
  char *oldFileName = malloc(oldFileNameSize);
  if (newFileName == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }

  // MAIN DIR 
  size_t mainFolderPSize = 1024;
  char *mainFolderPath = malloc(mainFolderPSize);
  if (mainFolderPath == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }

  size_t imagesPSize = 1024; 
  char *imagesPath = malloc(imagesPSize);
  if (imagesPath == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }
  strcpy(imagesPath, "Not Used");

  size_t videosPSize = 1024; 
  char *videosPath = malloc(videosPSize);
  if (videosPath == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }
  strcpy(videosPath, "Not Used");

  size_t tdmPSize = 1024; 
  char *threeDModelsPath = malloc(tdmPSize);
  if (threeDModelsPath == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }
  strcpy(threeDModelsPath, "Not Used");

  size_t tdpPSize = 1024; 
  char *threeDPrintsPath = malloc(tdpPSize);
  if (threeDPrintsPath == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }
  strcpy(threeDPrintsPath, "Not Used");

  size_t audiosPSize = 1024; 
  char *audiosPath = malloc(audiosPSize);
  if (audiosPath == NULL)
  {
    printf("\nMemory allocation failed.");
    return 1;
  }
  strcpy(audiosPath, "Not Used");

  int opt;

  while ((opt = getopt(argc, argv, "hm:i:v:t:p:a:")) != -1) // -h = help -m = main path to sort -i = images path -v = videos path -t = three d/3d models -p = 3d print files -a = audios path
  {
    switch (opt)
    {
      case 'h':
        printf("\e[0;33mHelp:\n-h = help\n-m = main path to sort \n-i = images path\n-v = videos path\n-t = three d/3d models path\n-p = 3d print files path\n-a = audio path\e[0m\n");
        return 0;
      case 'm':
        pathValidation(optarg, &mainFolderPSize, &mainFolderPath);
        break;
      case 'i':
        pathValidation(optarg, &imagesPSize, &imagesPath);  
        break;
      case 'v':
        pathValidation(optarg, &videosPSize, &videosPath);
        break;
      case 't':
        pathValidation(optarg, &tdmPSize, &threeDModelsPath);        
        break;
      case 'p':
        pathValidation(optarg, &tdpPSize, &threeDPrintsPath);        
        break;
      case 'a':
        pathValidation(optarg, &audiosPSize, &audiosPath);
        break;
      case '?':
        printf("\e[0;31mUnkown option or missing argument.\e[0m\n");
        return 0;
    }
  }

  DIR *mainFolder = opendir(mainFolderPath);

  struct dirent *entry;
  while ((entry = readdir(mainFolder)) != NULL)
  {
    if (strrchr(entry->d_name, '.') != NULL)
    {
      char *extension = strrchr(entry->d_name, '.');
    
      if (!(extension && extension != entry->d_name))
      {
        continue;
      }

      bool isImage = (!(strcmp(extension, ".png")) || !(strcmp(extension, ".jpeg")) || !(strcmp(extension, ".jpg")) || !(strcmp(extension, ".webp")) || !(strcmp(extension, ".gif")) || !(strcmp(extension, ".bmp")) || !(strcmp(extension, ".tif")) || !(strcmp(extension, ".svg")) || !(strcmp(extension, ".ico")) || !(strcmp(extension, ".avif")) || !(strcmp(extension, ".heic")) || !(strcmp(extension, ".heif")) || !(strcmp(extension, ".jxl")));
      bool isVideo = (!(strcmp(extension, ".mp4")) || !(strcmp(extension, ".mkv")) || !(strcmp(extension, ".mov")) || !(strcmp(extension, ".avi")) || !(strcmp(extension, ".webm")) || !(strcmp(extension, ".wmv")) || !(strcmp(extension, ".flv")) || !(strcmp(extension, ".m4v")) || !(strcmp(extension, ".mpg")) || !(strcmp(extension, ".mpeg")) || !(strcmp(extension, ".3gp")) || !(strcmp(extension, ".3g2")) || !(strcmp(extension, ".ts")) || !(strcmp(extension, ".mts")) || !(strcmp(extension, ".m2ts")) || !(strcmp(extension, ".vob")) || !(strcmp(extension, ".ogv")));
      bool isAudio = (!(strcmp(extension, ".mp3")) || !(strcmp(extension, ".wav")) || !(strcmp(extension, ".flac")) || !(strcmp(extension, ".aac")) || !(strcmp(extension, ".ogg")) || !(strcmp(extension, ".oga")) || !(strcmp(extension, ".opus")) || !(strcmp(extension, ".m4a")) || !(strcmp(extension, ".wma")) || !(strcmp(extension, ".aiff")) || !(strcmp(extension, ".aif")) || !(strcmp(extension, ".alac")) || !(strcmp(extension, ".amr")) || !(strcmp(extension, ".mid")) || !(strcmp(extension, ".midi")));
      bool isThreeDModel = (!(strcmp(extension, ".obj")) || !(strcmp(extension, ".fbx")) || !(strcmp(extension, ".stl")) || !(strcmp(extension, ".gltf")) || !(strcmp(extension, ".glb")) || !(strcmp(extension, ".dae")) || !(strcmp(extension, ".3ds")) || !(strcmp(extension, ".blend")) || !(strcmp(extension, ".ply")) || !(strcmp(extension, ".abc")) || !(strcmp(extension, ".usd")) || !(strcmp(extension, ".usda")) || !(strcmp(extension, ".usdc")) || !(strcmp(extension, ".usdz")));
      bool isThreeDPrint = (!(strcmp(extension, ".step")) || !(strcmp(extension, ".stp")) || !(strcmp(extension, ".iges")) || !(strcmp(extension, ".igs")) || !(strcmp(extension, ".3mf")) || !(strcmp(extension, ".fcstd")));

      if (isImage && strcmp(imagesPath, "Not Used"))
      {
        fileSort(imagesPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, mainFolderPath, entry);           
      }
      else if (isVideo && strcmp(videosPath, "Not Used"))
      {
        fileSort(videosPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, mainFolderPath, entry);           
      }
      else if (isAudio && strcmp(audiosPath, "Not Used"))
      {
        fileSort(audiosPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, mainFolderPath, entry);           
      }
      else if (isThreeDModel && strcmp(threeDModelsPath, "Not Used"))
      {
        fileSort(threeDModelsPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, mainFolderPath, entry);           
      }
      else if (isThreeDPrint && strcmp(threeDPrintsPath, "Not Used"))
      {
        fileSort(threeDPrintsPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, mainFolderPath, entry);           
      }

    }
  }

  printf("\n\n\e[1;93mFILES SORTED\e[0m\n");

  closedir(mainFolder);
  free(mainFolderPath);

  free(imagesPath); 
  free(videosPath);
  free(threeDModelsPath);
  free(threeDPrintsPath);
  free(audiosPath);
  free(newFileName);
  free(oldFileName);

  return 0;
}
