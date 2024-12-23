#ifndef _EXPLORER_H
#define _EXPLORER_H

#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>


#define FILENAME_BUFSIZE 256


typedef struct {
    size_t size;
    size_t capacity;
    char **items;
} Filenames;

extern Filenames filenames_new(void);
extern void filenames_destroy(Filenames *f);
extern void filenames_append(Filenames *f, const char *str);
extern void filenames_clear(Filenames *f);




typedef struct {
    char cwd[FILENAME_BUFSIZE];
    Filenames filenames;
} Explorer;

extern int exp_new(Explorer *exp, const char *dirpath);
extern int exp_update_files(Explorer *exp);
extern void exp_destroy(Explorer *exp);





#endif // _EXPLORER_H
