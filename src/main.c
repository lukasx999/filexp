#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "./explorer.h"
#include "./ui.h"

#include <raylib.h>
#include <raymath.h>




int main(int argc, char **argv) {

    if (argc > 2) {
        fprintf(stderr, "Incorrect usage!\n");
        fprintf(stderr, "Usage: %s <directory?>\n", argv[0]);
        exit(1);
    }

    const char *dirpath = (argc == 2) ? argv[1] : ".";

    Explorer exp = { 0 };
    int err = exp_new(&exp, dirpath);
    if (err != 0) {
        fprintf(stderr, "Failed to open directory\n");
        exit(1);
    }


    Ui ui = ui_new(&exp, 1920, 1080, "resources/Roboto-Light.ttf", "Filexp");

    ui_loop(&ui);

    ui_destroy(&ui);
    exp_destroy(&exp);

    return EXIT_SUCCESS;
}
