Transform =
{
    Translation =
    {
        x = 0,
        y = 0,
        z = 0
    },
    Scale =
    {
        x = 1,
        y = 1,
        z = 1
    },
    Rotation =
    {
        x = 0,
        y = 0,
        z = 0
    }
}

Durian =
{
    Keycode =
    {
        -- I copied all of this from the Durian source by hand and now I want to fucking die
        DURIAN_SCANCODE_UNKNOWN = 0,
        DURIAN_SCANCODE_A = 4.0,
        DURIAN_SCANCODE_B = 5,
        DURIAN_SCANCODE_C = 6,
        DURIAN_SCANCODE_D = 7,
        DURIAN_SCANCODE_E = 8,
        DURIAN_SCANCODE_F = 9,
        DURIAN_SCANCODE_G = 10,
        DURIAN_SCANCODE_H = 11,
        DURIAN_SCANCODE_I = 12,
        DURIAN_SCANCODE_J = 13,
        DURIAN_SCANCODE_K = 14,
        DURIAN_SCANCODE_L = 15,
        DURIAN_SCANCODE_M = 16,
        DURIAN_SCANCODE_N = 17,
        DURIAN_SCANCODE_O = 18,
        DURIAN_SCANCODE_P = 19,
        DURIAN_SCANCODE_Q = 20,
        DURIAN_SCANCODE_R = 21,
        DURIAN_SCANCODE_S = 22,
        DURIAN_SCANCODE_T = 23,
        DURIAN_SCANCODE_U = 24,
        DURIAN_SCANCODE_V = 25,
        DURIAN_SCANCODE_W = 26,
        DURIAN_SCANCODE_X = 27,
        DURIAN_SCANCODE_Y = 28,
        DURIAN_SCANCODE_Z = 29,
        DURIAN_SCANCODE_1 = 30,
        DURIAN_SCANCODE_2 = 31,
        DURIAN_SCANCODE_3 = 32,
        DURIAN_SCANCODE_4 = 33,
        DURIAN_SCANCODE_5 = 34,
        DURIAN_SCANCODE_6 = 35,
        DURIAN_SCANCODE_7 = 36,
        DURIAN_SCANCODE_8 = 37,
        DURIAN_SCANCODE_9 = 38,
        DURIAN_SCANCODE_0 = 39,
        DURIAN_SCANCODE_RETURN = 40,
        DURIAN_SCANCODE_ESCAPE = 41,
        DURIAN_SCANCODE_BACKSPACE = 42,
        DURIAN_SCANCODE_TAB = 43,
        DURIAN_SCANCODE_SPACE = 44,
        DURIAN_SCANCODE_MINUS = 45,
        DURIAN_SCANCODE_EQUALS = 46,
        DURIAN_SCANCODE_LEFTBRACKET = 47,
        DURIAN_SCANCODE_RIGHTBRACKET = 48,
        DURIAN_SCANCODE_BACKSLASH = 49 ,
        DURIAN_SCANCODE_NONUSHASH = 50,
        DURIAN_SCANCODE_SEMICOLON = 51,
        DURIAN_SCANCODE_APOSTROPHE = 52,
        DURIAN_SCANCODE_GRAVE = 53,
        DURIAN_SCANCODE_COMMA = 54,
        DURIAN_SCANCODE_PERIOD = 55,
        DURIAN_SCANCODE_SLASH = 56,
        DURIAN_SCANCODE_CAPSLOCK = 57,
        DURIAN_SCANCODE_F1 = 58,
        DURIAN_SCANCODE_F2 = 59,
        DURIAN_SCANCODE_F3 = 60,
        DURIAN_SCANCODE_F4 = 61,
        DURIAN_SCANCODE_F5 = 62,
        DURIAN_SCANCODE_F6 = 63,
        DURIAN_SCANCODE_F7 = 64,
        DURIAN_SCANCODE_F8 = 65,
        DURIAN_SCANCODE_F9 = 66,
        DURIAN_SCANCODE_F10 = 67,
        DURIAN_SCANCODE_F11 = 68,
        DURIAN_SCANCODE_F12 = 69,
        DURIAN_SCANCODE_PRINTSCREEN = 70,
        DURIAN_SCANCODE_SCROLLLOCK = 71,
        DURIAN_SCANCODE_PAUSE = 72,
        DURIAN_SCANCODE_INSERT = 73,
        DURIAN_SCANCODE_HOME = 74,
        DURIAN_SCANCODE_PAGEUP = 75,
        DURIAN_SCANCODE_DELETE = 76,
        DURIAN_SCANCODE_END = 77,
        DURIAN_SCANCODE_PAGEDOWN = 78,
        DURIAN_SCANCODE_RIGHT = 79,
        DURIAN_SCANCODE_LEFT = 80,
        DURIAN_SCANCODE_DOWN = 81,
        DURIAN_SCANCODE_UP = 82,
        DURIAN_SCANCODE_NUMLOCKCLEAR = 83,
        DURIAN_SCANCODE_KP_DIVIDE = 84,
        DURIAN_SCANCODE_KP_MULTIPLY = 85,
        DURIAN_SCANCODE_KP_MINUS = 86,
        DURIAN_SCANCODE_KP_PLUS = 87,
        DURIAN_SCANCODE_KP_ENTER = 88,
        DURIAN_SCANCODE_KP_1 = 89,
        DURIAN_SCANCODE_KP_2 = 90,
        DURIAN_SCANCODE_KP_3 = 91,
        DURIAN_SCANCODE_KP_4 = 92,
        DURIAN_SCANCODE_KP_5 = 93,
        DURIAN_SCANCODE_KP_6 = 94,
        DURIAN_SCANCODE_KP_7 = 95,
        DURIAN_SCANCODE_KP_8 = 96,
        DURIAN_SCANCODE_KP_9 = 97,
        DURIAN_SCANCODE_KP_0 = 98,
        DURIAN_SCANCODE_KP_PERIOD = 99,
        DURIAN_SCANCODE_NONUSBACKSLASH = 100,
        DURIAN_SCANCODE_APPLICATION = 101,
        DURIAN_SCANCODE_POWER = 102,
        DURIAN_SCANCODE_KP_EQUALS = 103,
        DURIAN_SCANCODE_F13 = 104,
        DURIAN_SCANCODE_F14 = 105,
        DURIAN_SCANCODE_F15 = 106,
        DURIAN_SCANCODE_F16 = 107,
        DURIAN_SCANCODE_F17 = 108,
        DURIAN_SCANCODE_F18 = 109,
        DURIAN_SCANCODE_F19 = 110,
        DURIAN_SCANCODE_F20 = 111,
        DURIAN_SCANCODE_F21 = 112,
        DURIAN_SCANCODE_F22 = 113,
        DURIAN_SCANCODE_F23 = 114,
        DURIAN_SCANCODE_F24 = 115,
        DURIAN_SCANCODE_EXECUTE = 116,
        DURIAN_SCANCODE_HELP = 117,
        DURIAN_SCANCODE_MENU = 118,
        DURIAN_SCANCODE_SELECT = 119,
        DURIAN_SCANCODE_STOP = 120,
        DURIAN_SCANCODE_AGAIN = 121 ,
        DURIAN_SCANCODE_UNDO = 122,
        DURIAN_SCANCODE_CUT = 123,
        DURIAN_SCANCODE_COPY = 124,
        DURIAN_SCANCODE_PASTE = 125,
        DURIAN_SCANCODE_FIND = 126,
        DURIAN_SCANCODE_MUTE = 127,
        DURIAN_SCANCODE_VOLUMEUP = 128,
        DURIAN_SCANCODE_VOLUMEDOWN = 129,
        DURIAN_SCANCODE_INTERNATIONAL1 = 135,
        DURIAN_SCANCODE_INTERNATIONAL2 = 136,
        DURIAN_SCANCODE_INTERNATIONAL3 = 137,
        DURIAN_SCANCODE_INTERNATIONAL4 = 138,
        DURIAN_SCANCODE_INTERNATIONAL5 = 139,
        DURIAN_SCANCODE_INTERNATIONAL6 = 140,
        DURIAN_SCANCODE_INTERNATIONAL7 = 141,
        DURIAN_SCANCODE_INTERNATIONAL8 = 142,
        DURIAN_SCANCODE_INTERNATIONAL9 = 143,
        DURIAN_SCANCODE_LANG1 = 144,
        DURIAN_SCANCODE_LANG2 = 145,
        DURIAN_SCANCODE_LANG3 = 146,
        DURIAN_SCANCODE_LANG4 = 147,
        DURIAN_SCANCODE_LANG5 = 148,
        DURIAN_SCANCODE_LANG6 = 149,
        DURIAN_SCANCODE_LANG7 = 150,
        DURIAN_SCANCODE_LANG8 = 151,
        DURIAN_SCANCODE_LANG9 = 152,
        DURIAN_SCANCODE_ALTERASE = 153,
        DURIAN_SCANCODE_SYSREQ = 154,
        DURIAN_SCANCODE_CANCEL = 155,
        DURIAN_SCANCODE_CLEAR = 156,
        DURIAN_SCANCODE_PRIOR = 157,
        DURIAN_SCANCODE_RETURN2 = 158,
        DURIAN_SCANCODE_SEPARATOR = 159,
        DURIAN_SCANCODE_OUT = 160,
        DURIAN_SCANCODE_OPER = 161,
        DURIAN_SCANCODE_CLEARAGAIN = 162,
        DURIAN_SCANCODE_CRSEL = 163,
        DURIAN_SCANCODE_EXSEL = 164,
        DURIAN_SCANCODE_KP_00 = 176,
        DURIAN_SCANCODE_KP_000 = 177,
        DURIAN_SCANCODE_THOUSANDSSEPARATOR = 178,
        DURIAN_SCANCODE_DECIMALSEPARATOR = 179,
        DURIAN_SCANCODE_CURRENCYUNIT = 180,
        DURIAN_SCANCODE_CURRENCYSUBUNIT = 181,
        DURIAN_SCANCODE_KP_LEFTPAREN = 182,
        DURIAN_SCANCODE_KP_RIGHTPAREN = 183,
        DURIAN_SCANCODE_KP_LEFTBRACE = 184,
        DURIAN_SCANCODE_KP_RIGHTBRACE = 185,
        DURIAN_SCANCODE_KP_TAB = 186,
        DURIAN_SCANCODE_KP_BACKSPACE = 187,
        DURIAN_SCANCODE_KP_A = 188,
        DURIAN_SCANCODE_KP_B = 189,
        DURIAN_SCANCODE_KP_C = 190,
        DURIAN_SCANCODE_KP_D = 191,
        DURIAN_SCANCODE_KP_E = 192,
        DURIAN_SCANCODE_KP_F = 193,
        DURIAN_SCANCODE_KP_XOR = 194,
        DURIAN_SCANCODE_KP_POWER = 195,
        DURIAN_SCANCODE_KP_PERCENT = 196,
        DURIAN_SCANCODE_KP_LESS = 197,
        DURIAN_SCANCODE_KP_GREATER = 198,
        DURIAN_SCANCODE_KP_AMPERSAND = 199,
        DURIAN_SCANCODE_KP_DBLAMPERSAND = 200,
        DURIAN_SCANCODE_KP_VERTICALBAR = 201,
        DURIAN_SCANCODE_KP_DBLVERTICALBAR = 202,
        DURIAN_SCANCODE_KP_COLON = 203,
        DURIAN_SCANCODE_KP_HASH = 204,
        DURIAN_SCANCODE_KP_SPACE = 205,
        DURIAN_SCANCODE_KP_AT = 206,
        DURIAN_SCANCODE_KP_EXCLAM = 207,
        DURIAN_SCANCODE_KP_MEMSTORE = 208,
        DURIAN_SCANCODE_KP_MEMRECALL = 209,
        DURIAN_SCANCODE_KP_MEMCLEAR = 210,
        DURIAN_SCANCODE_KP_MEMADD = 211,
        DURIAN_SCANCODE_KP_MEMSUBTRACT = 212,
        DURIAN_SCANCODE_KP_MEMMULTIPLY = 213,
        DURIAN_SCANCODE_KP_MEMDIVIDE = 214,
        DURIAN_SCANCODE_KP_PLUSMINUS = 215,
        DURIAN_SCANCODE_KP_CLEAR = 216,
        DURIAN_SCANCODE_KP_CLEARENTRY = 217,
        DURIAN_SCANCODE_KP_BINARY = 218,
        DURIAN_SCANCODE_KP_OCTAL = 219,
        DURIAN_SCANCODE_KP_DECIMAL = 220,
        DURIAN_SCANCODE_KP_HEXADECIMAL = 221,
        DURIAN_SCANCODE_LCTRL = 224,
        DURIAN_SCANCODE_LSHIFT = 225,
        DURIAN_SCANCODE_LALT = 226,
        DURIAN_SCANCODE_LGUI = 227,
        DURIAN_SCANCODE_RCTRL = 228,
        DURIAN_SCANCODE_RSHIFT = 229,
        DURIAN_SCANCODE_RALT = 230,
        DURIAN_SCANCODE_RGUI = 231,
        DURIAN_SCANCODE_MODE = 257,
        DURIAN_SCANCODE_AUDIONEXT = 258,
        DURIAN_SCANCODE_AUDIOPREV = 259,
        DURIAN_SCANCODE_AUDIOSTOP = 260,
        DURIAN_SCANCODE_AUDIOPLAY = 261,
        DURIAN_SCANCODE_AUDIOMUTE = 262,
        DURIAN_SCANCODE_MEDIASELECT = 263,
        DURIAN_SCANCODE_WWW = 264,
        DURIAN_SCANCODE_MAIL = 265,
        DURIAN_SCANCODE_CALCULATOR = 266,
        DURIAN_SCANCODE_COMPUTER = 267,
        DURIAN_SCANCODE_AC_SEARCH = 268,
        DURIAN_SCANCODE_AC_HOME = 269,
        DURIAN_SCANCODE_AC_BACK = 270,
        DURIAN_SCANCODE_AC_FORWARD = 271,
        DURIAN_SCANCODE_AC_STOP = 272,
        DURIAN_SCANCODE_AC_REFRESH = 273,
        DURIAN_SCANCODE_AC_BOOKMARKS = 274,
        DURIAN_SCANCODE_BRIGHTNESSDOWN = 275,
        DURIAN_SCANCODE_BRIGHTNESSUP = 276,
        DURIAN_SCANCODE_DISPLAYSWITCH = 277 ,
        DURIAN_SCANCODE_KBDILLUMTOGGLE = 278,
        DURIAN_SCANCODE_KBDILLUMDOWN = 279,
        DURIAN_SCANCODE_KBDILLUMUP = 280,
        DURIAN_SCANCODE_EJECT = 281,
        DURIAN_SCANCODE_SLEEP = 282,
        DURIAN_SCANCODE_APP1 = 283,
        DURIAN_SCANCODE_APP2 = 284,
        DURIAN_SCANCODE_AUDIOREWIND = 285,
        DURIAN_SCANCODE_AUDIOFASTFORWARD = 286,
        DURIAN_SCANCODE_SOFTLEFT = 287,
        DURIAN_SCANCODE_SOFTRIGHT = 288,
        DURIAN_SCANCODE_CALL = 289,
        DURIAN_SCANCODE_ENDCALL = 290,
        DURIAN_NUM_SCANCODES = 512
    }
}