#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./ui.h"
#include "explorer.h"



Ui ui_new(Explorer *exp, int width, int height, const char *font_file, const char *title) {
    Ui ui = {
        .exp      = exp,
        .font     = { 0 },
        .height   = height,
        .width    = width,
        .padding          = 50.0f,
        .color_widget_bg  = (Color) { 30, 30, 30, 255 },
        .color_background = (Color) { 5, 5, 5, 255 },
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
            ui->padding,
            ui->padding * i + ui->padding,
        };

        DrawTextEx(ui->font, filename, position, 50, 10, WHITE);

    }

}




void ui_loop(Ui *ui) {

    float main_area_width = 1350.0f;


    Rectangle area_main = {
        .x      = ui->padding,
        .y      = ui->padding,
        .width  = main_area_width,
        .height = ui->height - ui->padding*2,
    };


    // NOTE: Setting dynamic window title messes with DWM

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(ui->color_background);


            DrawRectangleRounded(area_main, 0.1f, 10.0f, ui->color_widget_bg);

            render_filenames(ui);
            handle_inputs(ui);


        }
        EndDrawing();
    }
}
