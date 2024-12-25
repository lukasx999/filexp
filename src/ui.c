#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        .area_filenames   = { 0 },
        .padding          = 30.0f,
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

}



static void render_filenames(const Ui *ui) {

    for (size_t i=0; i < ui->exp->filenames.size; ++i) {

        char *filename = ui->exp->filenames.items[i];

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
