namespace CSharpConsole
{
    internal class Program
    {
        static readonly RgbColor rgbRed = new RgbColor { alpha = 255, red = 255, green = 0, blue = 0 };
        static readonly RgbColor rgbBlue = new RgbColor { alpha = 255, red = 0, green = 0, blue = 255 };
        static readonly RgbColor rgbYellow = new RgbColor { alpha = 255, red = 255, green = 255, blue = 0 };
        static readonly RgbColor rgbCyan = new RgbColor { alpha = 255, red = 0, green = 255, blue = 255 };
        static readonly RgbColor rgbAshRose = new RgbColor { alpha = 255, red = 181, green = 129, blue = 125 };
        static readonly RgbColor rgbBlack = new RgbColor { alpha = 255, red = 0, green = 0, blue = 0 };
        static readonly RgbColor rgbWhite = new RgbColor { alpha = 255, red = 255, green = 255, blue = 255 };

        static void Main(string[] args)
        {
            // 1. Convert to Hex
            string hexWithAlpha = ColorApi.RgbToRgbHex(rgbAshRose, true);
            string hexNoAlpha = ColorApi.RgbToRgbHex(rgbAshRose, false);

            // 2. Convert to Decimal
            int rgbDec = ColorApi.RgbToRgbDec(rgbAshRose);
            int argbDec = ColorApi.RgbToArgbDec(rgbAshRose);

            // 3. Convert to HSL/HSV
            HslSpace hsl = ColorApi.RgbToHsl(rgbAshRose);
            HsvSpace hsv = ColorApi.RgbToHsv(rgbAshRose);

            // 4. Convert back to RGB
            RgbColor rtHslColor = ColorApi.HslToRgb(hsl);
            RgbColor rtHsvColor = ColorApi.HsvToRgb(hsv);

            // 5. Lets show our results
            Console.WriteLine($"Hex (Alpha): {hexWithAlpha}, Dec: {argbDec}");      // e.g., #FF40E0D0
            Console.WriteLine($"Hex (No Alpha): {hexNoAlpha}, Dec: {rgbDec}\n");    // e.g., #40E0D0

            Console.WriteLine($"HSL: H={hsl.hue:F2}, S={hsl.saturation:F2}, L={hsl.lightness:F2}");
            Console.WriteLine($"HSV: H={hsv.hue:F2}, S={hsv.saturation:F2}, L={hsv.value:F2}\n");

            Console.WriteLine($"Roundtrip HSL->RGB: A={rtHslColor.alpha}, R={rtHslColor.red}, G={rtHslColor.green}, B={rtHslColor.blue}");
            Console.WriteLine($"Roundtrip HSV->RGB: A={rtHsvColor.alpha}, R={rtHsvColor.red}, G={rtHsvColor.green}, B={rtHsvColor.blue}\n");

            Console.ReadKey(true);
        }
    }
}
