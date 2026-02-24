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

[StructLayout(LayoutKind.Sequential)]
internal struct XyzSpace
{
    public double x;
    public double y;
    public double z;
}

[StructLayout(LayoutKind.Sequential)]
public struct LabSpace
{
    public double l;
    public double a;
    public double b;
}

[StructLayout(LayoutKind.Sequential)]
public struct WhitePoint
{
    public double x;
    public double y;
    public double z;
}

public enum WhitePointType : int
{
    WPID_D65 = 0,
    WPID_D65_FULL = 1
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

    // --- Xyz / Lab Conversions ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern XyzSpace RgbToXyz(RgbColor rgb);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern LabSpace XyzToLabEx(XyzSpace xyz, WhitePointType wp);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern LabSpace XyzToLab(XyzSpace xyz);

    // --- Integer / Decimal Conversions ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern uint RgbToArgbDec(RgbColor rgb);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern uint RgbToRgbDec(RgbColor rgb);

    // --- Hex String Conversion (The special one!) ---

    //[DllImport(DllName, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    //[return: MarshalAs(UnmanagedType.LPStr)]
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    internal static extern nint RgbToRgbHex(RgbColor rgb, bool includeAlpha);

    // --- Set Console Colors by struct ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetColorsEx(RgbColor bg, RgbColor fg);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetFgColorEx(RgbColor fg);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetBgColorEx(RgbColor bg);

    // --- Set Console Colors by int/uint ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetFgColor(uint red, uint green, uint blue);
    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetBgColor(uint red, uint green, uint blue);

    // --- Reset Foreground and Background Colors ---

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void ChizlFree(IntPtr ptr);

    [DllImport(DllName)]
    public static extern void ResetColor();

    [DllImport(DllName)]
    public static extern void ClearBuffer();
}
