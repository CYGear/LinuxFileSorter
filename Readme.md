### This file sorter ONLY works on LINUX 

# Installation/Setup
  Source Build:

      git clone https://github.com/CYGear/LinuxFileSorter ~/LinuxFileSorter
      cd ~/LinuxFileSorter
      cmake -B build
      cmake --build build
      
      sudo mv build/linuxfilesorter /usr/local/bin 

      # optional - delete ~/LinuxFileSorter
      rm -rf ~/LinuxFileSorter

  Install Pre-built:
      
     

# Usage 
    linuxfilesorter -flag

# Flags  
    -h = help
    -m = path to folder to sort
    -i = path to Images folder
    -v = path to Videos folder
    -t = path to 3D Models folder
    -p = path to 3D Prints folder
    -a = path to Audio folder

Only use flags for types of files you want to sort

    EX: LinuxFileSorter -m ~/PATH_TO_FOLDER_TO_SORT -i ~/PATH_TO_IMAGES -a ~/PATH_TO_AUDIOS 
    
    This only sorts images and audio files into their corresponding folders

