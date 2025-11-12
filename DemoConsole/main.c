#include <conio.h>      // _getch
#include <stdio.h>      // printf
#include <windows.h>    // FlushConsoleInputBuffer, GetStdHandle, STD_INPUT_HANDLE
#include "main.h"

const RgbColor rgbRed = { 255, 255, 0, 0 };
const RgbColor rgbBlue = { 255, 0, 0, 255 };
const RgbColor rgbYellow = { 255, 255, 255, 0 };
const RgbColor rgbCyan = { 255, 0, 255, 255 };
const RgbColor rgbAshRose = { 255, 181, 129, 125 };
const RgbColor rgbBlack = { 255, 0, 0, 0 };
const RgbColor rgbWhite = { 255, 255, 255, 255 };

static void colorConversionDemo();
static void consoleColorPrintDemo();
static void printWithColor(const RgbColor* bg, const RgbColor* fg, const char* msg);
static void showColorInfo(RgbColor clr, RgbColor textClr, char* title);
static void anyKey(const char* msg, const RgbColor* fg);
static void formatString(char* buffer, size_t size, const char* fmt, ...);
static void formatStringV(char* buffer, size_t size, const char* fmt, va_list args);
static void SetColors(const RgbColor* bg, const RgbColor* fg);
static void WriteLine(const RgbColor* bg, const RgbColor* fg, const char* msg, ...);
static void Write(const RgbColor* bg, const RgbColor* fg, const char* msg, ...);

int main(void)
{
    consoleColorPrintDemo();
    colorConversionDemo();

    // with color, use NULL instead for no color.
    anyKey("\n\nPress any key to exit...\n\n", &rgbRed);
    return 0;
}

static void SetColors(const RgbColor* bg, const RgbColor* fg) {
    if (fg != NULL && bg != NULL) SetColorsEx(*bg, *fg);
    else if (fg != NULL) SetFgColorEx(*fg);
    else if (bg != NULL) SetBgColorEx(*bg);
    else ResetColor();
}

static void colorConversionDemo()
{
    showColorInfo(rgbCyan, rgbBlack, "Cyan - #00FFFF");
    showColorInfo(rgbAshRose, rgbWhite, "Ash Rose - #B5817D");

    anyKey("\n\nPress any key to continue...", &rgbYellow);
}

static void showColorInfo(RgbColor clr, RgbColor textClr, char* title) {
    WriteLine(&clr, &textClr, "--- Testing %s Conversions ---", title);

    HsvSpace hsv = RgbToHsv(clr);
    HslSpace hsl = RgbToHsl(clr);

    char* ahex = RgbToRgbHex(clr, 1);
    char* hex = RgbToRgbHex(clr, 0);

    SetColorsEx(clr, textClr);
    printf("'%s' Color: (R:%u, G:%u, B:%u)\n", title, clr.red, clr.green, clr.blue);
    printf(" - HSL: H:%.2f, S:%.2f, L:%.2f, Raw:%f\n", hsl.hue, hsl.saturation, hsl.lightness, hsl.raw_lightness);
    printf(" - HSV: H:%.2f, S:%.2f, V:%.2f, Raw:%f\n", hsv.hue, hsv.saturation, hsv.value, hsv.raw_value);
    printf(" - HEX8: %s\n", ahex);
    printf(" - HEX6: %s\n", hex);
    ResetColor();

    RgbColor hsv_rt = HsvToRgb(hsv);
    RgbColor hsl_rt = HslToRgb(hsl);

    printf(" - HSL Roundtrip -> RGB: (R:%u, G:%u, B:%u)\n", hsl_rt.red, hsl_rt.green, hsl_rt.blue);
    printf(" - HSV Roundtrip -> RGB: (R:%u, G:%u, B:%u)\n", hsv_rt.red, hsv_rt.green, hsv_rt.blue);
}

static void consoleColorPrintDemo() {
    // Other ways to be done:
    //  SetBgColor(255, 0, 0);
    //  SetFgColor(255, 255, 0);
    //  SetColorsEx(rgbYellow, rgbRed);
    Write(&rgbRed, &rgbYellow, " Yellow on Red ");

    // This will have no color.
    Write(NULL, NULL, " - default color - ");

    // Also can be done:
    //  SetFgColor(0, 255, 255);
    //  SetFgColorEx(rgbCyan);
    WriteLine(NULL, &rgbCyan, "Cyan text only.");

    // with color
    anyKey("\n\nPress any key to continue...", &rgbYellow);
}

static void Write(const RgbColor* bg, const RgbColor* fg, const char* msg, ...) {
    if (msg == NULL)
        return;

    char buffer[256] = { 0 };
    size_t len = sizeof(buffer);

    va_list args;
    va_start(args, msg);
    formatStringV(buffer, len, msg, args);
    va_end(args);

    printWithColor(bg, fg, buffer);
}

static void WriteLine(const RgbColor* bg, const RgbColor* fg, const char* msg, ...) {
    if (msg == NULL)
        return;

    char buffer[256] = { 0 };
    size_t len = sizeof(buffer);

    va_list args;
    va_start(args, msg);
    formatStringV(buffer, len, msg, args);
    va_end(args);

    printWithColor(bg, fg, buffer);
    printf("\n");
}

static void printWithColor(const RgbColor* bg, const RgbColor* fg, const char* msg) {
    if (msg == NULL)
        return;

    SetColors(bg, fg);
    printf_s("%s", msg);    // Use threadsafe, and insure not extra % was uncaught.
    ResetColor();           // resets foreground and background color to console default colors.
}

static void formatStringV(char* buffer, size_t size, const char* fmt, va_list args) {
    vsnprintf(buffer, size, fmt, args);
}

static void formatString(char* buffer, size_t size, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    formatStringV(buffer, size, fmt, args);
    va_end(args);
}

static void anyKey(const char* msg, const RgbColor* fg) {
    // Clear buffer.  
    // If this wasn't used, previous buffered input could 
    // force _getch() to continue without prompt.
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    if (msg != NULL)
        WriteLine(NULL, fg, msg);

    int c = _getch();
}