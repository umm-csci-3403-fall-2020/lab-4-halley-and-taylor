#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
   
   bool isDir;
   struct stat stats;
   if(stat(path, &stats) == 0){
	isDir = S_ISDIR(stats.st_mode);
	return isDir;
   }
   else{return false;}
}

void process_path(const char*);

void process_directory(const char* path) {
  
  num_dirs++;
  DIR *newDir;
  struct dirent *stuff;

  if((newDir = opendir(path)) == NULL){
  	printf("ERROR");
	exit(0);
  }
  chdir(path);

  
 while(stuff = readdir(newDir)){
  	if(strcmp(stuff->d_name,".") != 0 && strcmp(stuff->d_name,"..") != 0){
		process_path(stuff->d_name);
	}
  }

  chdir("..");
  closedir(newDir);
}

void process_file(const char* path) {
   num_regular++;
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
