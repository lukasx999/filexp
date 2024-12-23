#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "./explorer.h"

#include <raylib.h>
#include <raymath.h>





static void set_window_title(const Explorer *exp) {
    const char *prefix = "Filexp - ";
    size_t bufsize = FILENAME_BUFSIZE + strlen(prefix);
    char buf[bufsize];
    snprintf(buf, bufsize, "%s%s", prefix, exp->cwd);
    SetWindowTitle(buf);
}



typedef struct {
    Font font;
    float window_width;
    float window_height;
    Color color_widget_bg;
} Ui;

Ui ui_new(int width, int height, const char *font_file) {
    Ui ui = {
        .font            = LoadFontEx(font_file, 100, NULL, 0),
        .window_height   = height,
        .window_width    = width,
        .color_widget_bg = (Color) { 30, 30, 30, 255 },
    };

    return ui;
}

void ui_destroy(Ui *ui) {
    UnloadFont(ui->font);
}




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

    const int width = 1920, height = 1080;

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(width, height, "Filexp");

    const char *font_file = "resources/Roboto-Light.ttf";
    Ui ui = ui_new(width, height, font_file);




    float padding         = 50.0f;
    float main_area_width = 1350.0f;
    float rounding        = 0.1f;
    float segments        = 10.0f;


    Rectangle area_main = {
        .x      = padding,
        .y      = padding,
        .width  = main_area_width,
        .height = ui.window_height - padding*2,
    };



    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            set_window_title(&exp);

            DrawRectangleRounded(area_main,  rounding, segments, ui.color_widget_bg);

            /*
            char buf[10] = { 0 };
            snprintf(buf, 10, "%lu files", exp.filenames.size);
            Vector2 position = { padding, padding };
            DrawTextEx(ui.font, buf, position, 50, 10, WHITE);
            */

            for (size_t i=0; i < exp.filenames.size; ++i) {

                char *filename = exp.filenames.items[i];

                Vector2 position = {
                    padding,
                    padding * i + padding,
                };

                DrawTextEx(ui.font, filename, position, 50, 10, WHITE);

            }

            if (IsKeyPressed(KEY_SPACE)) {
                exp_update_files(&exp);
            }

            if (IsKeyPressed(KEY_MINUS)) {
                assert(!"Go up one directory");
            }

            if (IsKeyPressed(KEY_ENTER)) {
                assert(!"Go into directory");
            }


        }
        EndDrawing();
    }


    ui_destroy(&ui);
    exp_destroy(&exp);
    CloseWindow();
    return EXIT_SUCCESS;
}
