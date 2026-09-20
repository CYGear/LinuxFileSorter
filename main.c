#include "Main.h"

// Helper libs
#include "sorting.h"

// 1. Get file extension
// 2. Find directory to place file in 
// 3. Rename file, if files are in dif

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

  char *temp = NULL; // temp pointer for paths

  int opt;

  while ((opt = getopt(argc, argv, "hi:v:t:p:a:")) != -1) // -h = help -i = images path -v = videos path -t = three d/3d models -p = 3d print files -a = audios path
  {
    switch (opt)
    {
      case 'h':
        printf("Help:\n-h = help\n-i = images path\n-v = videos path\n-t = three d/3d models path\n-p = 3d print files path\n-a = audio path\n");
        return 0;
      case 'i':
        imagesPSize = strlen(optarg) + 1;
        temp = realloc(imagesPath, imagesPSize);
        if (temp == NULL)
        {
          printf("\nMemory allocation failed.");
          free(imagesPath);
          return 1;
        }
        imagesPath = temp;

        snprintf(imagesPath, imagesPSize, optarg);
      
        break;
      case 'v':
        videosPSize = strlen(optarg) + 1;
        temp = realloc(videosPath, videosPSize);
        if (temp == NULL)
        {
          printf("\nMemory allocation failed.");
          free(videosPath);
          return 1;
        }
        videosPath = temp;

        snprintf(videosPath, videosPSize, optarg);
        
        break;
      case 't':
        tdmPSize = strlen(optarg) + 1;
        temp = realloc(threeDModelsPath, tdmPSize);
        if (temp == NULL)
        {
          printf("\nMemory allocation failed.");
          free(threeDModelsPath);
          return 1;
        }
        threeDModelsPath = temp;

        snprintf(threeDModelsPath, tdmPSize, optarg);
        
        break;
      case 'p':
        tdpPSize = strlen(optarg) + 1;
        temp = realloc(threeDPrintsPath, tdpPSize);
        if (temp == NULL)
        {
          printf("\nMemory allocation failed.");
          free(threeDPrintsPath);
          return 1;
        }
        threeDPrintsPath = temp;

        snprintf(threeDPrintsPath, tdpPSize, optarg);
        
        break;
      case 'a':
        audiosPSize = strlen(optarg) + 1;
        temp = realloc(audiosPath, audiosPSize);
        if (temp == NULL)
        {
          printf("\nMemory allocation failed.");
          free(audiosPath);
          return 1;
        }
        audiosPath = temp;

        snprintf(audiosPath, audiosPSize, optarg);
        
        break;
      case '?':
        printf("Unkown option or missing argument.\n");
        return 0;
    }
  }

  size_t dFFPSize = strlen(getenv("HOME")) + 12; // length of home dir + /Downloads/ -- 11 + 1 for null terminator
  char *downloadsFolderPath = malloc(dFFPSize);

  snprintf(downloadsFolderPath, dFFPSize, "%s/Downloads/", getenv("HOME"));

  DIR *downloadsFolder = opendir(downloadsFolderPath);

  struct dirent *entry;
  while ((entry = readdir(downloadsFolder)) != NULL)
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
        imageSort(imagesPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, downloadsFolderPath, entry);           
      }
      else if (isVideo && strcmp(videosPath, "Not Used"))
      {
        videoSort(videosPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, downloadsFolderPath, entry);           
      }
      else if (isAudio && strcmp(audiosPath, "Not Used"))
      {
        audioSort(audiosPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, downloadsFolderPath, entry);           
      }
      else if (isThreeDModel && strcmp(threeDModelsPath, "Not Used"))
      {
        threeDModelSort(threeDModelsPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, downloadsFolderPath, entry);           
      }
      else if (isThreeDPrint && strcmp(threeDPrintsPath, "Not Used"))
      {
        threeDPrintSort(threeDPrintsPath, &newFileName, &newFileNameSize, &oldFileName, &oldFileNameSize, downloadsFolderPath, entry);           
      }

    }
  }

  closedir(downloadsFolder);

  free(downloadsFolderPath);

  free(imagesPath); 
  free(videosPath);
  free(threeDModelsPath);
  free(threeDPrintsPath);
  free(audiosPath);
  free(newFileName);
  free(oldFileName);

  return 0;
}
