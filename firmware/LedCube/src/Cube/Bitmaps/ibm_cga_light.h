//
// FACE_NAME "IBM CGA Light 8x8"
//
// 0-31,127 : Code page 437, cf. https://en.wikipedia.org/wiki/Code_page_437
// 32-126   : ASCII
// 160-255  : ISO-8859-1, cf. https://en.wikipedia.org/wiki/ISO/IEC_8859-1

const char ibm_cga_light[224][8] = {
    // ---------------------------  0-127 ---------------------------
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0000 (uni0000.dup1)
    {0x7e, 0x81, 0xa5, 0x81, 0xbd, 0x99, 0x81, 0x7e}, // 0001 (uni0001)
    {0x7e, 0xff, 0xdb, 0xff, 0xc3, 0xe7, 0xff, 0x7e}, // 0002 (uni0002)
    {0x6c, 0xfe, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00}, // 0003 (uni0003)
    {0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00}, // 0004 (uni0004)
    {0x38, 0x7c, 0x38, 0xfe, 0xfe, 0xd6, 0x10, 0x38}, // 0005 (uni0005)
    {0x10, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x10, 0x38}, // 0006 (uni0006)
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00}, // 0007 (uni0007)
    {0xff, 0xff, 0xe7, 0xc3, 0xc3, 0xe7, 0xff, 0xff}, // 0008 (uni0008)
    {0x00, 0x3c, 0x66, 0x42, 0x42, 0x66, 0x3c, 0x00}, // 0009 (uni0009)
    {0xff, 0xc3, 0x99, 0xbd, 0xbd, 0x99, 0xc3, 0xff}, // 000a (uni000A)
    {0x0f, 0x03, 0x05, 0x7d, 0x84, 0x84, 0x84, 0x78}, // 000b (uni000B)
    {0x3c, 0x42, 0x42, 0x42, 0x3c, 0x18, 0x7e, 0x18}, // 000c (uni000C)
    {0x3f, 0x21, 0x3f, 0x20, 0x20, 0x60, 0xe0, 0xc0}, // 000d (uni000D)
    {0x3f, 0x21, 0x3f, 0x21, 0x23, 0x67, 0xe6, 0xc0}, // 000e (uni000E)
    {0x18, 0xdb, 0x3c, 0xe7, 0xe7, 0x3c, 0xdb, 0x18}, // 000f (uni000F)
    {0x80, 0xe0, 0xf8, 0xfe, 0xf8, 0xe0, 0x80, 0x00}, // 0010 (uni0010)
    {0x02, 0x0e, 0x3e, 0xfe, 0x3e, 0x0e, 0x02, 0x00}, // 0011 (uni0011)
    {0x18, 0x3c, 0x7e, 0x18, 0x18, 0x7e, 0x3c, 0x18}, // 0012 (uni0012)
    {0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x24, 0x00}, // 0013 (uni0013)
    {0x7f, 0x92, 0x92, 0x72, 0x12, 0x12, 0x12, 0x00}, // 0014 (uni0014)
    {0x3e, 0x63, 0x38, 0x44, 0x44, 0x38, 0xcc, 0x78}, // 0015 (uni0015)
    {0x00, 0x00, 0x00, 0x00, 0x7e, 0x7e, 0x7e, 0x00}, // 0016 (uni0016)
    {0x18, 0x3c, 0x7e, 0x18, 0x7e, 0x3c, 0x18, 0xff}, // 0017 (uni0017)
    {0x10, 0x38, 0x7c, 0x54, 0x10, 0x10, 0x10, 0x00}, // 0018 (uni0018)
    {0x10, 0x10, 0x10, 0x54, 0x7c, 0x38, 0x10, 0x00}, // 0019 (uni0019)
    {0x00, 0x18, 0x0c, 0xfe, 0x0c, 0x18, 0x00, 0x00}, // 001a (uni001A)
    {0x00, 0x30, 0x60, 0xfe, 0x60, 0x30, 0x00, 0x00}, // 001b (uni001B)
    {0x00, 0x00, 0x40, 0x40, 0x40, 0x7e, 0x00, 0x00}, // 001c (uni001C)
    {0x00, 0x24, 0x66, 0xff, 0x66, 0x24, 0x00, 0x00}, // 001d (uni001D)
    {0x00, 0x10, 0x38, 0x7c, 0xfe, 0xfe, 0x00, 0x00}, // 001e (uni001E)
    {0x00, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00}, // 001f (uni001F)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0020 (space)
    {0x10, 0x38, 0x38, 0x10, 0x10, 0x00, 0x10, 0x00}, // 0021 (exclam)
    {0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0022 (quotedbl)
    {0x24, 0x24, 0x7e, 0x24, 0x7e, 0x24, 0x24, 0x00}, // 0023 (numbersign)
    {0x18, 0x3e, 0x40, 0x3c, 0x02, 0x7c, 0x18, 0x00}, // 0024 (dollar)
    {0x00, 0x62, 0x64, 0x08, 0x10, 0x26, 0x46, 0x00}, // 0025 (percent)
    {0x30, 0x48, 0x30, 0x56, 0x88, 0x88, 0x76, 0x00}, // 0026 (ampersand)
    {0x10, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0027 (quotesingle)
    {0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00}, // 0028 (parenleft)
    {0x20, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x00}, // 0029 (parenright)
    {0x00, 0x44, 0x38, 0xfe, 0x38, 0x44, 0x00, 0x00}, // 002a (asterisk)
    {0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00, 0x00}, // 002b (plus)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x20}, // 002c (comma)
    {0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00}, // 002d (hyphen)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00}, // 002e (period)
    {0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00}, // 002f (slash)
    {0x3c, 0x42, 0x46, 0x4a, 0x52, 0x62, 0x3c, 0x00}, // 0030 (zero)
    {0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c, 0x00}, // 0031 (one)
    {0x3c, 0x42, 0x02, 0x0c, 0x30, 0x42, 0x7e, 0x00}, // 0032 (two)
    {0x3c, 0x42, 0x02, 0x1c, 0x02, 0x42, 0x3c, 0x00}, // 0033 (three)
    {0x08, 0x18, 0x28, 0x48, 0xfe, 0x08, 0x1c, 0x00}, // 0034 (four)
    {0x7e, 0x40, 0x7c, 0x02, 0x02, 0x42, 0x3c, 0x00}, // 0035 (five)
    {0x1c, 0x20, 0x40, 0x7c, 0x42, 0x42, 0x3c, 0x00}, // 0036 (six)
    {0x7e, 0x42, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00}, // 0037 (seven)
    {0x3c, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x3c, 0x00}, // 0038 (eight)
    {0x3c, 0x42, 0x42, 0x3e, 0x02, 0x04, 0x38, 0x00}, // 0039 (nine)
    {0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x00}, // 003a (colon)
    {0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20}, // 003b (semicolon)
    {0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x00}, // 003c (less)
    {0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00}, // 003d (equal)
    {0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00}, // 003e (greater)
    {0x3c, 0x42, 0x02, 0x04, 0x08, 0x00, 0x08, 0x00}, // 003f (question)
    {0x3c, 0x42, 0x5e, 0x52, 0x5e, 0x40, 0x3c, 0x00}, // 0040 (at)
    {0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x00}, // 0041 (A)
    {0x7c, 0x22, 0x22, 0x3c, 0x22, 0x22, 0x7c, 0x00}, // 0042 (B)
    {0x1c, 0x22, 0x40, 0x40, 0x40, 0x22, 0x1c, 0x00}, // 0043 (C)
    {0x78, 0x24, 0x22, 0x22, 0x22, 0x24, 0x78, 0x00}, // 0044 (D)
    {0x7e, 0x22, 0x28, 0x38, 0x28, 0x22, 0x7e, 0x00}, // 0045 (E)
    {0x7e, 0x22, 0x28, 0x38, 0x28, 0x20, 0x70, 0x00}, // 0046 (F)
    {0x1c, 0x22, 0x40, 0x40, 0x4e, 0x22, 0x1e, 0x00}, // 0047 (G)
    {0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x00}, // 0048 (H)
    {0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00}, // 0049 (I)
    {0x0e, 0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00}, // 004a (J)
    {0x62, 0x24, 0x28, 0x30, 0x28, 0x24, 0x63, 0x00}, // 004b (K)
    {0x70, 0x20, 0x20, 0x20, 0x20, 0x22, 0x7e, 0x00}, // 004c (L)
    {0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x41, 0x00}, // 004d (M)
    {0x62, 0x52, 0x4a, 0x46, 0x42, 0x42, 0x42, 0x00}, // 004e (N)
    {0x18, 0x24, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00}, // 004f (O)
    {0x7c, 0x22, 0x22, 0x3c, 0x20, 0x20, 0x70, 0x00}, // 0050 (P)
    {0x3c, 0x42, 0x42, 0x42, 0x4a, 0x3c, 0x03, 0x00}, // 0051 (Q)
    {0x7c, 0x22, 0x22, 0x3c, 0x28, 0x24, 0x72, 0x00}, // 0052 (R)
    {0x3c, 0x42, 0x40, 0x3c, 0x02, 0x42, 0x3c, 0x00}, // 0053 (S)
    {0x7f, 0x49, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00}, // 0054 (T)
    {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 0055 (U)
    {0x41, 0x41, 0x41, 0x41, 0x22, 0x14, 0x08, 0x00}, // 0056 (V)
    {0x41, 0x41, 0x41, 0x49, 0x49, 0x49, 0x36, 0x00}, // 0057 (W)
    {0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, 0x00}, // 0058 (X)
    {0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x1c, 0x00}, // 0059 (Y)
    {0x7f, 0x42, 0x04, 0x08, 0x10, 0x21, 0x7f, 0x00}, // 005a (Z)
    {0x78, 0x40, 0x40, 0x40, 0x40, 0x40, 0x78, 0x00}, // 005b (bracketleft)
    {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00}, // 005c (backslash)
    {0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x78, 0x00}, // 005d (bracketright)
    {0x10, 0x28, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00}, // 005e (asciicircum)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff}, // 005f (underscore)
    {0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0060 (grave)
    {0x00, 0x00, 0x3c, 0x02, 0x3e, 0x42, 0x3f, 0x00}, // 0061 (a)
    {0x60, 0x20, 0x20, 0x2e, 0x31, 0x31, 0x2e, 0x00}, // 0062 (b)
    {0x00, 0x00, 0x3c, 0x42, 0x40, 0x42, 0x3c, 0x00}, // 0063 (c)
    {0x06, 0x02, 0x02, 0x3a, 0x46, 0x46, 0x3b, 0x00}, // 0064 (d)
    {0x00, 0x00, 0x3c, 0x42, 0x7e, 0x40, 0x3c, 0x00}, // 0065 (e)
    {0x0c, 0x12, 0x10, 0x38, 0x10, 0x10, 0x38, 0x00}, // 0066 (f)
    {0x00, 0x00, 0x3d, 0x42, 0x42, 0x3e, 0x02, 0x7c}, // 0067 (g)
    {0x60, 0x20, 0x2c, 0x32, 0x22, 0x22, 0x62, 0x00}, // 0068 (h)
    {0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00}, // 0069 (i)
    {0x02, 0x00, 0x06, 0x02, 0x02, 0x42, 0x42, 0x3c}, // 006a (j)
    {0x60, 0x20, 0x24, 0x28, 0x30, 0x28, 0x26, 0x00}, // 006b (k)
    {0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00}, // 006c (l)
    {0x00, 0x00, 0x76, 0x49, 0x49, 0x49, 0x49, 0x00}, // 006d (m)
    {0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x00}, // 006e (n)
    {0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 006f (o)
    {0x00, 0x00, 0x6c, 0x32, 0x32, 0x2c, 0x20, 0x70}, // 0070 (p)
    {0x00, 0x00, 0x36, 0x4c, 0x4c, 0x34, 0x04, 0x0e}, // 0071 (q)
    {0x00, 0x00, 0x6c, 0x32, 0x22, 0x20, 0x70, 0x00}, // 0072 (r)
    {0x00, 0x00, 0x3e, 0x40, 0x3c, 0x02, 0x7c, 0x00}, // 0073 (s)
    {0x10, 0x10, 0x7c, 0x10, 0x10, 0x12, 0x0c, 0x00}, // 0074 (t)
    {0x00, 0x00, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x00}, // 0075 (u)
    {0x00, 0x00, 0x41, 0x41, 0x22, 0x14, 0x08, 0x00}, // 0076 (v)
    {0x00, 0x00, 0x41, 0x49, 0x49, 0x49, 0x36, 0x00}, // 0077 (w)
    {0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00}, // 0078 (x)
    {0x00, 0x00, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x7c}, // 0079 (y)
    {0x00, 0x00, 0x7c, 0x08, 0x10, 0x20, 0x7c, 0x00}, // 007a (z)
    {0x0c, 0x10, 0x10, 0x60, 0x10, 0x10, 0x0c, 0x00}, // 007b (braceleft)
    {0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x10, 0x00}, // 007c (bar)
    {0x30, 0x08, 0x08, 0x06, 0x08, 0x08, 0x30, 0x00}, // 007d (braceright)
    {0x32, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 007e (asciitilde)
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x41, 0x7f, 0x00}, // 007f (uni007F)
    // ---------------------------  160-255 ---------------------------
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 00a0 (uni00A0)
    {0x00, 0x10, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00}, // 00a1 (exclamdown)
    {0x08, 0x08, 0x3e, 0x40, 0x40, 0x3e, 0x08, 0x08}, // 00a2 (cent)
    {0x18, 0x24, 0x20, 0x70, 0x20, 0x42, 0x7c, 0x00}, // 00a3 (sterling)
    {0x00, 0xc6, 0x38, 0x44, 0x44, 0x38, 0xc6, 0x00}, // 00a4 (currency)
    {0x44, 0x28, 0x7c, 0x10, 0x7c, 0x10, 0x10, 0x00}, // 00a5 (yen)
    {0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x10, 0x00}, // 00a6 (brokenbar)
    {0x3e, 0x63, 0x38, 0x44, 0x44, 0x38, 0xcc, 0x78}, // 00a7 (section)
    {0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 00a8 (dieresis)
    {0x7c, 0x82, 0x9a, 0xa2, 0xa2, 0x9a, 0x82, 0x7c}, // 00a9 (copyright)
    {0x3c, 0x44, 0x44, 0x3e, 0x00, 0x7e, 0x00, 0x00}, // 00aa (ordfeminine)
    {0x00, 0x12, 0x24, 0x48, 0x24, 0x12, 0x00, 0x00}, // 00ab (guillemotleft)
    {0x00, 0x00, 0x00, 0x7e, 0x02, 0x02, 0x00, 0x00}, // 00ac (logicalnot)
    {0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00}, // 00ad (uni00AD)
    {0x7c, 0x82, 0xb2, 0xaa, 0xb2, 0xaa, 0x82, 0x7c}, // 00ae (registered)
    {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 00af (macron)
    {0x30, 0x48, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00}, // 00b0 (degree)
    {0x10, 0x10, 0x7c, 0x10, 0x10, 0x00, 0x7c, 0x00}, // 00b1 (plusminus)
    {0x30, 0x48, 0x10, 0x20, 0x78, 0x00, 0x00, 0x00}, // 00b2 (uni00B2)
    {0x30, 0x48, 0x10, 0x48, 0x30, 0x00, 0x00, 0x00}, // 00b3 (uni00B3)
    {0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 00b4 (acute)
    {0x00, 0x44, 0x44, 0x44, 0x7a, 0x40, 0x40, 0x80}, // 00b5 (mu)
    {0x7f, 0x92, 0x92, 0x72, 0x12, 0x12, 0x12, 0x00}, // 00b6 (paragraph)
    {0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00}, // 00b7 (periodcentered)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x38}, // 00b8 (cedilla)
    {0x20, 0x60, 0x20, 0x20, 0x70, 0x00, 0x00, 0x00}, // 00b9 (uni00B9)
    {0x38, 0x44, 0x44, 0x38, 0x00, 0x7c, 0x00, 0x00}, // 00ba (ordmasculine)
    {0x00, 0x48, 0x24, 0x12, 0x24, 0x48, 0x00, 0x00}, // 00bb (guillemotright)
    {0x42, 0xc4, 0x4a, 0xf6, 0x2a, 0x5f, 0x82, 0x02}, // 00bc (onequarter)
    {0x42, 0xc4, 0x48, 0xf6, 0x29, 0x43, 0x8c, 0x1f}, // 00bd (onehalf)
    {0xc0, 0x22, 0xc4, 0x2a, 0xd6, 0x2a, 0x5f, 0x82}, // 00be (threequarters)
    {0x10, 0x00, 0x10, 0x20, 0x40, 0x42, 0x3c, 0x00}, // 00bf (questiondown)
    {0xc0, 0x18, 0x24, 0x42, 0x7e, 0x42, 0x42, 0x00}, // 00c0 (Agrave)
    {0x03, 0x18, 0x24, 0x42, 0x7e, 0x42, 0x42, 0x00}, // 00c1 (Aacute)
    {0x3c, 0x42, 0x18, 0x24, 0x42, 0x7e, 0x42, 0x00}, // 00c2 (Acircumflex)
    {0x7e, 0x00, 0x3c, 0x42, 0x7e, 0x42, 0x42, 0x00}, // 00c3 (Atilde)
    {0x42, 0x18, 0x24, 0x42, 0x7e, 0x42, 0x42, 0x00}, // 00c4 (Adieresis)
    {0x18, 0x18, 0x00, 0x3c, 0x42, 0x7e, 0x42, 0x00}, // 00c5 (Aring)
    {0x1f, 0x24, 0x44, 0x7f, 0x44, 0x44, 0x47, 0x00}, // 00c6 (AE)
    {0x3c, 0x42, 0x40, 0x42, 0x3c, 0x0c, 0x02, 0x3c}, // 00c7 (Ccedilla)
    {0x60, 0x00, 0x7c, 0x20, 0x38, 0x20, 0x7c, 0x00}, // 00c8 (Egrave)
    {0x0c, 0x00, 0x7c, 0x20, 0x38, 0x20, 0x7c, 0x00}, // 00c9 (Eacute)
    {0x7c, 0x82, 0x7c, 0x20, 0x38, 0x20, 0x7c, 0x00}, // 00ca (Ecircumflex)
    {0x44, 0x00, 0x7c, 0x20, 0x38, 0x20, 0x7c, 0x00}, // 00cb (Edieresis)
    {0x60, 0x00, 0x38, 0x10, 0x10, 0x10, 0x38, 0x00}, // 00cc (Igrave)
    {0x0c, 0x00, 0x38, 0x10, 0x10, 0x10, 0x38, 0x00}, // 00cd (Iacute)
    {0x7c, 0x82, 0x38, 0x10, 0x10, 0x10, 0x38, 0x00}, // 00ce (Icircumflex)
    {0x44, 0x00, 0x38, 0x10, 0x10, 0x10, 0x38, 0x00}, // 00cf (Idieresis)
    {0x78, 0x24, 0x22, 0x72, 0x22, 0x24, 0x78, 0x00}, // 00d0 (Eth)
    {0x34, 0x4c, 0x00, 0x62, 0x52, 0x4a, 0x46, 0x00}, // 00d1 (Ntilde)
    {0xc0, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00}, // 00d2 (Ograve)
    {0x03, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00}, // 00d3 (Oacute)
    {0x7c, 0x82, 0x38, 0x44, 0x82, 0x44, 0x38, 0x00}, // 00d4 (Ocircumflex)
    {0x7f, 0x00, 0x1c, 0x22, 0x41, 0x22, 0x1c, 0x00}, // 00d5 (Otilde)
    {0x42, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00}, // 00d6 (Odieresis)
    {0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00}, // 00d7 (multiply)
    {0x7c, 0x86, 0x8e, 0xba, 0xe2, 0xc2, 0x7c, 0x00}, // 00d8 (Oslash)
    {0x60, 0x00, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00d9 (Ugrave)
    {0x06, 0x00, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00da (Uacute)
    {0x3c, 0x42, 0x00, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00db (Ucircumflex)
    {0x42, 0x00, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00dc (Udieresis)
    {0x06, 0x00, 0x44, 0x28, 0x10, 0x10, 0x38, 0x00}, // 00dd (Yacute)
    {0x70, 0x20, 0x3c, 0x22, 0x3c, 0x20, 0x70, 0x00}, // 00de (Thorn)
    {0x38, 0x44, 0x44, 0x48, 0x44, 0x42, 0x4c, 0x00}, // 00df (germandbls)
    {0x30, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3e, 0x00}, // 00e0 (agrave)
    {0x0c, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3e, 0x00}, // 00e1 (aacute)
    {0x3c, 0x42, 0x38, 0x04, 0x3c, 0x44, 0x3e, 0x00}, // 00e2 (acircumflex)
    {0x7e, 0x00, 0x3c, 0x02, 0x3e, 0x42, 0x3f, 0x00}, // 00e3 (atilde)
    {0x42, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3e, 0x00}, // 00e4 (adieresis)
    {0x10, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3e, 0x00}, // 00e5 (aring)
    {0x00, 0x00, 0x33, 0x0c, 0x3f, 0x4c, 0x3b, 0x00}, // 00e6 (ae)
    {0x00, 0x00, 0x3c, 0x40, 0x40, 0x3c, 0x06, 0x1c}, // 00e7 (ccedilla)
    {0x30, 0x00, 0x3c, 0x42, 0x7e, 0x40, 0x3c, 0x00}, // 00e8 (egrave)
    {0x0c, 0x00, 0x3c, 0x42, 0x7e, 0x40, 0x3c, 0x00}, // 00e9 (eacute)
    {0x3c, 0x42, 0x3c, 0x42, 0x7e, 0x40, 0x3c, 0x00}, // 00ea (ecircumflex)
    {0x42, 0x00, 0x3c, 0x42, 0x7e, 0x40, 0x3c, 0x00}, // 00eb (edieresis)
    {0x30, 0x00, 0x18, 0x08, 0x08, 0x08, 0x1c, 0x00}, // 00ec (igrave)
    {0x0c, 0x00, 0x18, 0x08, 0x08, 0x08, 0x1c, 0x00}, // 00ed (iacute)
    {0x78, 0x84, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00}, // 00ee (icircumflex)
    {0x24, 0x00, 0x18, 0x08, 0x08, 0x08, 0x1c, 0x00}, // 00ef (idieresis)
    {0x08, 0x3e, 0x04, 0x3c, 0x44, 0x44, 0x38, 0x00}, // 00f0 (eth)
    {0x32, 0x4c, 0x00, 0x7c, 0x42, 0x42, 0x42, 0x00}, // 00f1 (ntilde)
    {0x20, 0x10, 0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00}, // 00f2 (ograve)
    {0x04, 0x08, 0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00}, // 00f3 (oacute)
    {0x18, 0x24, 0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00}, // 00f4 (ocircumflex)
    {0x00, 0x7e, 0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00}, // 00f5 (otilde)
    {0x00, 0x42, 0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00}, // 00f6 (odieresis)
    {0x18, 0x18, 0x00, 0x7e, 0x00, 0x18, 0x18, 0x00}, // 00f7 (divide)
    {0x00, 0x02, 0x7c, 0x8a, 0x92, 0xa2, 0x7c, 0x80}, // 00f8 (oslash)
    {0x20, 0x10, 0x00, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00f9 (ugrave)
    {0x00, 0x04, 0x08, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00fa (uacute)
    {0x18, 0x24, 0x00, 0x42, 0x42, 0x42, 0x3c, 0x00}, // 00fb (ucircumflex)
    {0x00, 0x44, 0x00, 0x44, 0x44, 0x44, 0x3e, 0x00}, // 00fc (udieresis)
    {0x00, 0x06, 0x00, 0x42, 0x42, 0x3e, 0x02, 0x3c}, // 00fd (yacute)
    {0x60, 0x20, 0x3c, 0x22, 0x22, 0x3c, 0x20, 0x70}, // 00fe (thorn)
    {0x00, 0x42, 0x00, 0x42, 0x42, 0x3e, 0x02, 0x3c}, // 00ff (ydieresis)
};
