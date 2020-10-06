#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  
   struct stat stats;
   if(stat(path, &stats) == 0){
	return S_ISDIR(stats.st_mode);
   }
   else{return false;}
}

void process_path(const char*);

void process_directory(const char* path) {
  
   DIR *dr = opendir(path);
   struct dirent *entry;
   chdir(path);

   while((entry = readdir(dr)) != NULL){
   if(entry->d_name == "."||entry->d_name == ".."){
   num_dirs++;
   }
   }

   chdir("..");
   closedir(dr);
}

void process_file(const char* path) {
  
   DIR *dr = opendir(path);
   struct dirent *entry;
   while((entry = readdir(dr)) != NULL){
   if(entry->d_type == DT_REG){
   num_regular++;
   }
   }
   closedir(dr);
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
