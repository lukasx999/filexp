#ifndef _UI_H
#define _UI_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

#include <raylib.h>

#include "./explorer.h"



typedef struct {
    Explorer *exp;
    Font font;

    Rectangle area_filenames;
    ssize_t filenames_scroll; // signed for bounds checking

    float width;
    float height;
    float padding;

    float fontsize;
    float fontspacing;

    Color color_widget_bg;
    Color color_background;
} Ui;


extern Ui ui_new(Explorer *exp, int width, int height, const char *font_file, const char *title);
extern void ui_destroy(Ui *ui);
extern void ui_loop(Ui *ui);


#endif // _UI_H
