#include <assert.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "./ui.h"
#include "explorer.h"



Ui ui_new(
    Explorer *exp,
    int width,
    int height,
    const char *font_file,
    const char *title
) {

    Ui ui = {
        .exp              = exp,
        .font             = { 0 },

        .height           = height,
        .width            = width,

        .fontsize         = 50.0f,
        .fontspacing      = 1.5f,
        .padding          = 30.0f,

        .area_filenames   = { 0 },
        .filenames_scroll = 0,


        .color_widget_bg  = (Color) { 30, 30, 30, 255 },
        .color_background = (Color) { 5,  5,  5,  255 },
    };

    ui.area_filenames = (Rectangle) {
        .x      = ui.padding,
        .y      = ui.padding,
        .width  = 1350.0f,
        .height = ui.height - ui.padding*2,
    };

    // this initializes the OpenGL context, so dont put any raylib functions before this line
    InitWindow(ui.width, ui.height, title);
    SetTraceLogLevel(LOG_ERROR);
    ui.font = LoadFontEx(font_file, 100, NULL, 0);

    return ui;
}

void ui_destroy(Ui *ui) {
    UnloadFont(ui->font);
    CloseWindow();
}




static void handle_inputs(Ui *ui) {

    if (IsKeyPressed(KEY_SPACE)) {
        exp_update_files(ui->exp);
    }

    if (IsKeyPressed(KEY_MINUS)) {
        assert(!"Go up one directory");
    }

    if (IsKeyPressed(KEY_ENTER)) {
        assert(!"Go into directory");
    }


    ui->filenames_scroll -= GetMouseWheelMove();

    if (IsKeyPressed(KEY_DOWN))
        ui->filenames_scroll += 1;

    if (IsKeyPressed(KEY_UP))
        ui->filenames_scroll -= 1;

}



static void render_filenames(Ui *ui) {

    float available_area   = ui->area_filenames.height - ui->padding*2;
    size_t entries         = (size_t) available_area / ui->fontsize;
    ssize_t *scroll_offset = &ui->filenames_scroll;

    if (*scroll_offset < 0)
        *scroll_offset = 0;

    size_t max_scroll_offset = ui->exp->filenames.size - entries;
    if ((size_t) *scroll_offset > max_scroll_offset)
        *scroll_offset = max_scroll_offset;





    for (size_t i=0; i < entries; ++i) {

        char *filename = filenames_get(&ui->exp->filenames, i+*scroll_offset);

        if (filename == NULL)
            break;

        Vector2 position = {
            .x = ui->area_filenames.x + ui->padding,
            .y = (ui->area_filenames.y + ui->padding) + ui->fontsize * i,
        };

        DrawTextEx(
            ui->font,
            filename,
            position,
            ui->fontsize,
            ui->fontspacing,
            WHITE
        );

    }

}




void ui_loop(Ui *ui) {

    // NOTE: Setting dynamic window title messes with DWM

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(ui->color_background);

            DrawRectangleRounded(
                ui->area_filenames,
                0.1f,
                10.0f,
                ui->color_widget_bg
            );

            render_filenames(ui);
            handle_inputs(ui);

        }
        EndDrawing();
    }
}
