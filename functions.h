#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define true 1
#define false 0

struct list
{
  char *name;
  struct books* b;
  struct list* next;
};

struct book
{
  char* autor;
  char* title;
  struct book* next;
};

struct books
{
  struct book* b;
  struct books* next;
};

char getFileData(char pattern,char *buf, FILE *f);
inline const char*  getOption(const char * name, const char * defaut,
								int argc, char ** argv);

#endif