#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "./explorer.h"





Filenames filenames_new(void) {

    Filenames s = {
        .capacity = 5,
        .size     = 0,
        .items    = NULL,
    };

    s.items = malloc(s.capacity * sizeof(char*));

    for (size_t i=0; i < s.capacity; ++i) {
        s.items[i] = malloc(FILENAME_BUFSIZE * sizeof(char));
        memset(s.items[i], 0, FILENAME_BUFSIZE);
    }

    return s;
}

void filenames_destroy(Filenames *f) {
    for (size_t i=0; i < f->capacity; ++i) {
        free(f->items[i]);
    }
    free(f->items);
    f->items = NULL;
}

void filenames_append(Filenames *f, const char *str) {

    if (f->size == f->capacity) {
        f->capacity *= 2;
        f->items = realloc(f->items, f->capacity * sizeof(char*));

        for (size_t i = f->capacity / 2; i < f->capacity; ++i) {
            f->items[i] = malloc(FILENAME_BUFSIZE * sizeof(char));
            memset(f->items[i], 0, FILENAME_BUFSIZE);
        }
    }

    strncpy(f->items[f->size++], str, FILENAME_BUFSIZE-1); // -1 to preserve nullbyte

}

void filenames_clear(Filenames *f) {
    filenames_destroy(f);
    *f = filenames_new();
}

char* filenames_get(const Filenames *f, size_t index) {
    return (index >= f->size)
    ? NULL
    : f->items[index];
}





int exp_new(Explorer *exp, const char *dirpath) {

    Explorer e = {
        .cwd       = { 0 },
        .filenames = filenames_new(),
    };

    strncpy(e.cwd, dirpath, FILENAME_BUFSIZE-1);

    int err = exp_update_files(&e);
    if (err != 0)
        return 1;

    *exp = e;
    return 0;

}

void exp_destroy(Explorer *exp) {
    filenames_destroy(&exp->filenames);
}


static int sort_alphabetical(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}


int exp_update_files(Explorer *exp) {
    filenames_clear(&exp->filenames);

    DIR *dir = opendir(exp->cwd);

    if (dir == NULL)
        return 1;

    struct dirent *directory = NULL;
    while ((directory = readdir(dir)) != NULL) {
        char *name = directory->d_name;
        if (!strncmp(name, "..", 256) || !strncmp(name, ".", 256))
            continue;
        filenames_append(&exp->filenames, name);
    }

    qsort(
        exp->filenames.items,
        exp->filenames.size,
        sizeof(char*),
        sort_alphabetical
    );

    closedir(dir);
    return 0;

}
