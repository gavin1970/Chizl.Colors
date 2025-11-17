using System.Diagnostics;
using System.Text;

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
        static readonly RgbColor rgbConsoleBlack = new RgbColor { alpha = 255, red = 12, green = 12, blue = 12 };

        static void Main(string[] args)
        {
            consoleColorPrintDemo();
            colorConversionDemo();
            
            // with color, use NULL instead for no color.
            anyKey("Press any key to exit...", rgbRed);
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
            showColorInfo(rgbCyan, rgbBlack, "Cyan");
            Console.WriteLine();
            showColorInfo(rgbAshRose, rgbWhite, "Ash Rose");
            Console.WriteLine();
            showColorInfo(rgbBlue, rgbWhite, "Blue");
            Console.WriteLine();

            anyKey("Press any key to continue...", rgbYellow);
        }

        static void showColorInfo(RgbColor clr, RgbColor textClr, string title)
        {
            var pad = " ";
            var sb = new StringBuilder();

            var hsv = ColorApi.RgbToHsv(clr);
            var hsl = ColorApi.RgbToHsl(clr);

            var ahex = ColorApi.RgbToRgbHex(clr, true);
            var hex = ColorApi.RgbToRgbHex(clr, false);

            var aDec = ColorApi.RgbToRgbDec(clr);
            var dec = ColorApi.RgbToArgbDec(clr);

            var hsv_rev = ColorApi.HsvToRgb(hsv);
            var hsl_rev = ColorApi.HslToRgb(hsl);

            sb.AppendLine($"{pad} --- Testing {title} - {hex} Conversions ---\n");

            sb.AppendLine($"{pad}'{title}' Color: (R:{clr.red}, G:{clr.green}, B:{clr.blue})");
            sb.AppendLine($"{pad} - HSV: H:{hsv.hue:0.00}, S:{hsv.saturation:0.00}, V:{hsv.value:0.00}, Raw:{hsv.raw_value:0.000000}");
            sb.AppendLine($"{pad} - HSL: H:{hsl.hue:0.00}, S:{hsl.saturation:0.00}, L:{hsl.lightness:0.00}, Raw:{hsl.raw_lightness:0.000000}\n");

            sb.AppendLine($"{pad} - HEX8: {ahex}, Dec: {aDec}");
            sb.AppendLine($"{pad} - HEX6: {hex},   Dec: {dec}\n");

            sb.AppendLine($"{pad} - HSV Roundtrip -> RGB: (R:{hsv_rev.red}, G:{hsv_rev.green}, B:{hsv_rev.blue})");
            sb.AppendLine($"{pad} - HSL Roundtrip -> RGB: (R:{hsl_rev.red}, G:{hsl_rev.green}, B:{hsl_rev.blue})\n");

            WriteLines(clr, textClr, sb.ToString().Replace("\r", "").Split('\n'), 55);
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
            WriteLine(rgbEmpty, rgbCyan, "Cyan text only.\n\n");

            // with color
            anyKey("Press any key to continue...", rgbYellow);
        }

        static void Write(RgbColor bg, RgbColor fg, string msg, params object[] args) 
            => printWithColor(bg, fg, string.Format(msg, args));

        static void WriteLine(RgbColor bg, RgbColor fg, string msg, params object[] args)
            => printWithColor(bg, fg, string.Format($"{msg}\n", args));

        static int WriteLines(RgbColor bg, RgbColor fg, string[] msgs, int minWidth=0)
        {
            var maxLen = 0;
            foreach (var msg in msgs)
                maxLen = Math.Max(maxLen, msg.Length);

            maxLen++;   // add space to end            
            if (maxLen < minWidth)
                maxLen = minWidth;

            foreach (var msg in msgs)
            {
                var newMsg = msg + new string(' ', maxLen - msg.Length);
                printWithColor(bg, fg, string.Format($"{newMsg}\n"));
            }

            return maxLen;
        }

        static void printWithColor(RgbColor bg, RgbColor fg, string msg)
        {
            if (string.IsNullOrEmpty(msg))
                return;

            SetColors(bg, fg);
            Console.Write(msg);      // Use threadsafe, and insure not extra % was uncaught.
            ColorApi.ResetColor();   // resets foreground and background color to console default colors.
        }

        static void anyKey(string msg, RgbColor fg)
        {
            if (!string.IsNullOrWhiteSpace(msg))
            {
                var curLoc = new int[] { Console.CursorLeft, Console.CursorTop };
                WriteLine(rgbEmpty, fg, msg);

                Console.ReadKey(true);
                //set cursor back to start of message.
                Console.CursorTop = curLoc[1];
                Console.CursorLeft = curLoc[0];
                //write message, but in black, overwriting and keeping CrLf that might exists.
                WriteLine(rgbEmpty, rgbConsoleBlack, msg);
                //set cursor back to start of message.
                Console.CursorTop = curLoc[1];
                Console.CursorLeft = curLoc[0];
            }
        }
    }
}
