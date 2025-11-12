using System.Runtime.InteropServices;


[StructLayout(LayoutKind.Sequential)]
internal struct RgbColor
{
    public byte alpha;
    public byte red;
    public byte green;
    public byte blue;
}

[StructLayout(LayoutKind.Sequential)]
internal struct HsvSpace
{
    public double hue;
    public double saturation;
    public double value;
    public double raw_value;
}

[StructLayout(LayoutKind.Sequential)]
internal struct HslSpace
{
    public double hue;
    public double saturation;
    public double lightness;
    public double raw_lightness;
}

internal static class ColorApi
{
    private const string DllName = "chizl.colors.dll";

    static ColorApi()
    {
        if (!File.Exists(DllName))
            throw new Exception($"Missing file: {DllName}");
    }

    // --- HSV Conversions ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern HsvSpace RgbToHsv(RgbColor rgb);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern RgbColor HsvToRgb(HsvSpace hsv);

    // --- HSL Conversions ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern HslSpace RgbToHsl(RgbColor rgb);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern RgbColor HslToRgb(HslSpace hsl);

    // --- Integer / Decimal Conversions ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int RgbToRgbDec(RgbColor clr);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int RgbToArgbDec(RgbColor clr);

    // --- Hex String Conversion (The special one!) ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    [return: MarshalAs(UnmanagedType.LPStr)]
    public static extern string RgbToRgbHex(RgbColor clr, bool includeAlpha);



    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetColorsEx(RgbColor bg, RgbColor fg);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetFgColorEx(RgbColor fg);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetBgColorEx(RgbColor bg);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetFgColor(uint red, uint green, uint blue);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetBgColor(uint red, uint green, uint blue);
    [DllImport(DllName)]
    public static extern void ResetColor();
}
