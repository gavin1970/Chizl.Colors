using System.Diagnostics;

namespace CSharpConsole
{
    internal class Program
    {
        static readonly RgbColor rgbEmpty = new RgbColor { alpha = 0, red = 0, green = 0, blue = 0 };
        static readonly RgbColor rgbRed = new RgbColor { alpha = 255, red = 255, green = 0, blue = 0 };
        static readonly RgbColor rgbBlue = new RgbColor { alpha = 255, red = 0, green = 0, blue = 255 };
        static readonly RgbColor rgbYellow = new RgbColor { alpha = 255, red = 255, green = 255, blue = 0 };
        static readonly RgbColor rgbCyan = new RgbColor { alpha = 255, red = 0, green = 255, blue = 255 };
        static readonly RgbColor rgbAshRose = new RgbColor { alpha = 255, red = 181, green = 129, blue = 125 };
        static readonly RgbColor rgbBlack = new RgbColor { alpha = 255, red = 0, green = 0, blue = 0 };
        static readonly RgbColor rgbWhite = new RgbColor { alpha = 255, red = 255, green = 255, blue = 255 };

        static void Main(string[] args)
        {
            consoleColorPrintDemo();
            colorConversionDemo();

            // with color, use NULL instead for no color.
            anyKey("\n\nPress any key to exit...\n\n", rgbRed);
        }

        static void SetColors(RgbColor bg, RgbColor fg)
        {
            if (fg.alpha != 0 && bg.alpha != 0)
                ColorApi.SetColorsEx(bg, fg);
            else if (fg.alpha != 0)
                ColorApi.SetFgColorEx(fg);
            else if (bg.alpha != 0)
                ColorApi.SetBgColorEx(bg);
            else
                ColorApi.ResetColor();
        }

        static void colorConversionDemo()
        {
            showColorInfo(rgbCyan, rgbBlack, "Cyan - #00FFFF");
            showColorInfo(rgbAshRose, rgbWhite, "Ash Rose - #B5817D");

            anyKey("\n\nPress any key to continue...", rgbYellow);
        }

        static void showColorInfo(RgbColor clr, RgbColor textClr, string title)
        {
            WriteLine(clr, textClr, "--- Testing {0} Conversions ---", title);

            var hsv = ColorApi.RgbToHsv(clr);
            var hsl = ColorApi.RgbToHsl(clr);

            var ahex = ColorApi.RgbToRgbHex(clr, true);
            var hex = ColorApi.RgbToRgbHex(clr, false);

            ColorApi.SetColorsEx(clr, textClr);
            Console.WriteLine("'{0}' Color: (R:{1}, G:{2}, B:{3})", title, clr.red, clr.green, clr.blue);
            Console.WriteLine(" - HSL: H:{0:0.00}, S:{1:0.00}, L:{2:0.00}, Raw:{3:0.000000}", hsl.hue, hsl.saturation, hsl.lightness, hsl.raw_lightness);
            Console.WriteLine(" - HSV: H:{0:0.00}, S:{1:0.00}, V:{2:0.00}, Raw:{3:0.000000}", hsv.hue, hsv.saturation, hsv.value, hsv.raw_value);
            Console.WriteLine(" - HEX8: {0}", ahex);
            Console.WriteLine(" - HEX6: {0}", hex);
            ColorApi.ResetColor();

            var hsv_rt = ColorApi.HsvToRgb(hsv);
            var hsl_rt = ColorApi.HslToRgb(hsl);

            Console.WriteLine(" - HSL Roundtrip -> RGB: (R:{0}, G:{1}, B:{2})", hsl_rt.red, hsl_rt.green, hsl_rt.blue);
            Console.WriteLine(" - HSV Roundtrip -> RGB: (R:{0}, G:{1}, B:{2})", hsv_rt.red, hsv_rt.green, hsv_rt.blue);
        }

        static void consoleColorPrintDemo()
        {
            // Other ways to be done:
            //  SetBgColor(255, 0, 0);
            //  SetFgColor(255, 255, 0);
            //  SetColorsEx(rgbYellow, rgbRed);
            Write(rgbRed, rgbYellow, " Yellow on Red ");

            // This will have no color.
            Write(rgbEmpty, rgbEmpty, " - default color - ");

            // Also can be done:
            //  SetFgColor(0, 255, 255);
            //  SetFgColorEx(rgbCyan);
            WriteLine(rgbEmpty, rgbCyan, "Cyan text only.");

            // with color
            anyKey("\n\nPress any key to continue...", rgbYellow);
        }

        static void Write(RgbColor bg, RgbColor fg, string msg, params object[] args) 
            => printWithColor(bg, fg, string.Format(msg, args));

        static void WriteLine(RgbColor bg, RgbColor fg, string msg, params object[] args) 
            => printWithColor(bg, fg, string.Format($"{msg}\n", args));

        static void printWithColor(RgbColor bg, RgbColor fg, string msg)
        {
            if (string.IsNullOrWhiteSpace(msg))
                return;

            SetColors(bg, fg);
            Console.Write(msg);      // Use threadsafe, and insure not extra % was uncaught.
            ColorApi.ResetColor();   // resets foreground and background color to console default colors.
        }

        static void anyKey(string msg, RgbColor fg)
        {
            if (!string.IsNullOrWhiteSpace(msg))
            {
                WriteLine(rgbEmpty, fg, msg);
                Console.ReadKey(true);
            }
        }
    }
}
