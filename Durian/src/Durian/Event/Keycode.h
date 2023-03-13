#pragma once

#define DURIAN_SCANCODE_UNKNOWN 0

/**
 *  \name Usage page 0x07
 *
 *  These values are from usage page 0x07 (USB keyboard page).
 */
 /* @{ */

#define DURIAN_SCANCODE_A 4
#define DURIAN_SCANCODE_B 5
#define DURIAN_SCANCODE_C 6
#define DURIAN_SCANCODE_D 7
#define DURIAN_SCANCODE_E 8
#define DURIAN_SCANCODE_F 9
#define DURIAN_SCANCODE_G 10
#define DURIAN_SCANCODE_H 11
#define DURIAN_SCANCODE_I 12
#define DURIAN_SCANCODE_J 13
#define DURIAN_SCANCODE_K 14
#define DURIAN_SCANCODE_L 15
#define DURIAN_SCANCODE_M 16
#define DURIAN_SCANCODE_N 17
#define DURIAN_SCANCODE_O 18
#define DURIAN_SCANCODE_P 19
#define DURIAN_SCANCODE_Q 20
#define DURIAN_SCANCODE_R 21
#define DURIAN_SCANCODE_S 22
#define DURIAN_SCANCODE_T 23
#define DURIAN_SCANCODE_U 24
#define DURIAN_SCANCODE_V 25
#define DURIAN_SCANCODE_W 26
#define DURIAN_SCANCODE_X 27
#define DURIAN_SCANCODE_Y 28
#define DURIAN_SCANCODE_Z 29

#define DURIAN_SCANCODE_1 30
#define DURIAN_SCANCODE_2 31
#define DURIAN_SCANCODE_3 32
#define DURIAN_SCANCODE_4 33
#define DURIAN_SCANCODE_5 34
#define DURIAN_SCANCODE_6 35
#define DURIAN_SCANCODE_7 36
#define DURIAN_SCANCODE_8 37
#define DURIAN_SCANCODE_9 38
#define DURIAN_SCANCODE_0 39

#define DURIAN_SCANCODE_RETURN 40
#define DURIAN_SCANCODE_ESCAPE 41
#define DURIAN_SCANCODE_BACKSPACE 42
#define DURIAN_SCANCODE_TAB 43
#define DURIAN_SCANCODE_SPACE 44

#define DURIAN_SCANCODE_MINUS 45
#define DURIAN_SCANCODE_EQUALS 46
#define DURIAN_SCANCODE_LEFTBRACKET 47
#define DURIAN_SCANCODE_RIGHTBRACKET 48
#define DURIAN_SCANCODE_BACKSLASH 49 /**< Located at the lower left of the return
                                       *   key on ISO keyboards and at the right end
                                       *   of the QWERTY row on ANSI keyboards.
                                       *   Produces REVERSE SOLIDUS (backslash) and
                                       *   VERTICAL LINE in a US layout REVERSE
                                       *   SOLIDUS and VERTICAL LINE in a UK Mac
                                       *   layout NUMBER SIGN and TILDE in a UK
                                       *   Windows layout DOLLAR SIGN and POUND SIGN
                                       *   in a Swiss German layout NUMBER SIGN and
                                       *   APOSTROPHE in a German layout GRAVE
                                       *   ACCENT and POUND SIGN in a French Mac
                                       *   layout and ASTERISK and MICRO SIGN in a
                                       *   French Windows layout.
                                       */
#define DURIAN_SCANCODE_NONUSHASH 50 /**< ISO USB keyboards actually use this code
                              *   instead of 49 for the same key but all
                              *   OSes I've seen treat the two codes
                              *   identically. So as an implementor unless
                              *   your keyboard generates both of those
                              *   codes and your OS treats them differently
                              *   you should generate DURIAN_SCANCODE_BACKSLASH
                              *   instead of this code. As a user you
                              *   should not rely on this code because DURIAN
                              *   will never generate it with most (all?)
                              *   keyboards.
                              */
#define DURIAN_SCANCODE_SEMICOLON 51
#define DURIAN_SCANCODE_APOSTROPHE 52
#define DURIAN_SCANCODE_GRAVE 53 /**< Located in the top left corner (on both ANSI
                                   *   and ISO keyboards). Produces GRAVE ACCENT and
                                   *   TILDE in a US Windows layout and in US and UK
                                   *   Mac layouts on ANSI keyboards GRAVE ACCENT
                                   *   and NOT SIGN in a UK Windows layout SECTION
                                   *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                                   *   layouts on ISO keyboards SECTION SIGN and
                                   *   DEGREE SIGN in a Swiss German layout (Mac:
                                   *   only on ISO keyboards) CIRCUMFLEX ACCENT and
                                   *   DEGREE SIGN in a German layout (Mac: only on
                                   *   ISO keyboards) SUPERSCRIPT TWO and TILDE in a
                                   *   French Windows layout COMMERCIAL AT and
                                   *   NUMBER SIGN in a French Mac layout on ISO
                                   *   keyboards and LESS-THAN SIGN and GREATER-THAN
                                   *   SIGN in a Swiss German German or French Mac
                                   *   layout on ANSI keyboards.
                                   */
#define DURIAN_SCANCODE_COMMA 54
#define DURIAN_SCANCODE_PERIOD 55
#define DURIAN_SCANCODE_SLASH 56

#define DURIAN_SCANCODE_CAPSLOCK 57

#define DURIAN_SCANCODE_F1 58
#define DURIAN_SCANCODE_F2 59
#define DURIAN_SCANCODE_F3 60
#define DURIAN_SCANCODE_F4 61
#define DURIAN_SCANCODE_F5 62
#define DURIAN_SCANCODE_F6 63
#define DURIAN_SCANCODE_F7 64
#define DURIAN_SCANCODE_F8 65
#define DURIAN_SCANCODE_F9 66
#define DURIAN_SCANCODE_F10 67
#define DURIAN_SCANCODE_F11 68
#define DURIAN_SCANCODE_F12 69

#define DURIAN_SCANCODE_PRINTSCREEN 70
#define DURIAN_SCANCODE_SCROLLLOCK 71
#define DURIAN_SCANCODE_PAUSE 72
#define DURIAN_SCANCODE_INSERT 73 /**< insert on PC help on some Mac keyboards (but
                                    does send code 73 not 117) */
#define DURIAN_SCANCODE_HOME 74
#define DURIAN_SCANCODE_PAGEUP 75
#define DURIAN_SCANCODE_DELETE 76
#define DURIAN_SCANCODE_END 77
#define DURIAN_SCANCODE_PAGEDOWN 78
#define DURIAN_SCANCODE_RIGHT 79
#define DURIAN_SCANCODE_LEFT 80
#define DURIAN_SCANCODE_DOWN 81
#define DURIAN_SCANCODE_UP 82

#define DURIAN_SCANCODE_NUMLOCKCLEAR 83 /**< num lock on PC clear on Mac keyboards
                                 */
#define DURIAN_SCANCODE_KP_DIVIDE 84
#define DURIAN_SCANCODE_KP_MULTIPLY 85
#define DURIAN_SCANCODE_KP_MINUS 86
#define DURIAN_SCANCODE_KP_PLUS 87
#define DURIAN_SCANCODE_KP_ENTER 88
#define DURIAN_SCANCODE_KP_1 89
#define DURIAN_SCANCODE_KP_2 90
#define DURIAN_SCANCODE_KP_3 91
#define DURIAN_SCANCODE_KP_4 92
#define DURIAN_SCANCODE_KP_5 93
#define DURIAN_SCANCODE_KP_6 94
#define DURIAN_SCANCODE_KP_7 95
#define DURIAN_SCANCODE_KP_8 96
#define DURIAN_SCANCODE_KP_9 97
#define DURIAN_SCANCODE_KP_0 98
#define DURIAN_SCANCODE_KP_PERIOD 99

#define DURIAN_SCANCODE_NONUSBACKSLASH 100 /**< This is the additional key that ISO
                                              *   keyboards have over ANSI ones
                                              *   located between left shift and Y.
                                              *   Produces GRAVE ACCENT and TILDE in a
                                              *   US or UK Mac layout REVERSE SOLIDUS
                                              *   (backslash) and VERTICAL LINE in a
                                              *   US or UK Windows layout and
                                              *   LESS-THAN SIGN and GREATER-THAN SIGN
                                              *   in a Swiss German German or French
                                              *   layout. */
#define DURIAN_SCANCODE_APPLICATION 101 /**< windows contextual menu compose */
#define DURIAN_SCANCODE_POWER 102 /**< The USB document says this is a status flag
                                     *   not a physical key - but some Mac keyboards
                                     *   do have a power key. */
#define DURIAN_SCANCODE_KP_EQUALS 103
#define DURIAN_SCANCODE_F13 104
#define DURIAN_SCANCODE_F14 105
#define DURIAN_SCANCODE_F15 106
#define DURIAN_SCANCODE_F16 107
#define DURIAN_SCANCODE_F17 108
#define DURIAN_SCANCODE_F18 109
#define DURIAN_SCANCODE_F19 110
#define DURIAN_SCANCODE_F20 111
#define DURIAN_SCANCODE_F21 112
#define DURIAN_SCANCODE_F22 113
#define DURIAN_SCANCODE_F23 114
#define DURIAN_SCANCODE_F24 115
#define DURIAN_SCANCODE_EXECUTE 116
#define DURIAN_SCANCODE_HELP 117
#define DURIAN_SCANCODE_MENU 118
#define DURIAN_SCANCODE_SELECT 119
#define DURIAN_SCANCODE_STOP 120
#define DURIAN_SCANCODE_AGAIN 121   /**< redo */
#define DURIAN_SCANCODE_UNDO 122
#define DURIAN_SCANCODE_CUT 123
#define DURIAN_SCANCODE_COPY 124
#define DURIAN_SCANCODE_PASTE 125
#define DURIAN_SCANCODE_FIND 126
#define DURIAN_SCANCODE_MUTE 127
#define DURIAN_SCANCODE_VOLUMEUP 128
#define DURIAN_SCANCODE_VOLUMEDOWN 129
/* not sure whether there's a reason to enable these */
/*     DURIAN_SCANCODE_LOCKINGCAPSLOCK 130  */
/*     DURIAN_SCANCODE_LOCKINGNUMLOCK 131 */
/*     DURIAN_SCANCODE_LOCKINGSCROLLLOCK 132 */
#define DURIAN_SCANCODE_KP_COMMA 133
#define DURIAN_SCANCODE_KP_EQUALSAS400 134

#define DURIAN_SCANCODE_INTERNATIONAL1 135 /**< used on Asian keyboards see
                                        footnotes in USB doc */
#define DURIAN_SCANCODE_INTERNATIONAL2 136
#define DURIAN_SCANCODE_INTERNATIONAL3 137 /**< Yen */
#define DURIAN_SCANCODE_INTERNATIONAL4 138
#define DURIAN_SCANCODE_INTERNATIONAL5 139
#define DURIAN_SCANCODE_INTERNATIONAL6 140
#define DURIAN_SCANCODE_INTERNATIONAL7 141
#define DURIAN_SCANCODE_INTERNATIONAL8 142
#define DURIAN_SCANCODE_INTERNATIONAL9 143
#define DURIAN_SCANCODE_LANG1 144 /**< Hangul/English toggle */
#define DURIAN_SCANCODE_LANG2 145 /**< Hanja conversion */
#define DURIAN_SCANCODE_LANG3 146 /**< Katakana */
#define DURIAN_SCANCODE_LANG4 147 /**< Hiragana */
#define DURIAN_SCANCODE_LANG5 148 /**< Zenkaku/Hankaku */
#define DURIAN_SCANCODE_LANG6 149 /**< reserved */
#define DURIAN_SCANCODE_LANG7 150 /**< reserved */
#define DURIAN_SCANCODE_LANG8 151 /**< reserved */
#define DURIAN_SCANCODE_LANG9 152 /**< reserved */

#define DURIAN_SCANCODE_ALTERASE 153 /**< Erase-Eaze */
#define DURIAN_SCANCODE_SYSREQ 154
#define DURIAN_SCANCODE_CANCEL 155
#define DURIAN_SCANCODE_CLEAR 156
#define DURIAN_SCANCODE_PRIOR 157
#define DURIAN_SCANCODE_RETURN2 158
#define DURIAN_SCANCODE_SEPARATOR 159
#define DURIAN_SCANCODE_OUT 160
#define DURIAN_SCANCODE_OPER 161
#define DURIAN_SCANCODE_CLEARAGAIN 162
#define DURIAN_SCANCODE_CRSEL 163
#define DURIAN_SCANCODE_EXSEL 164

#define DURIAN_SCANCODE_KP_00 176
#define DURIAN_SCANCODE_KP_000 177
#define DURIAN_SCANCODE_THOUSANDSSEPARATOR 178
#define DURIAN_SCANCODE_DECIMALSEPARATOR 179
#define DURIAN_SCANCODE_CURRENCYUNIT 180
#define DURIAN_SCANCODE_CURRENCYSUBUNIT 181
#define DURIAN_SCANCODE_KP_LEFTPAREN 182
#define DURIAN_SCANCODE_KP_RIGHTPAREN 183
#define DURIAN_SCANCODE_KP_LEFTBRACE 184
#define DURIAN_SCANCODE_KP_RIGHTBRACE 185
#define DURIAN_SCANCODE_KP_TAB 186
#define DURIAN_SCANCODE_KP_BACKSPACE 187
#define DURIAN_SCANCODE_KP_A 188
#define DURIAN_SCANCODE_KP_B 189
#define DURIAN_SCANCODE_KP_C 190
#define DURIAN_SCANCODE_KP_D 191
#define DURIAN_SCANCODE_KP_E 192
#define DURIAN_SCANCODE_KP_F 193
#define DURIAN_SCANCODE_KP_XOR 194
#define DURIAN_SCANCODE_KP_POWER 195
#define DURIAN_SCANCODE_KP_PERCENT 196
#define DURIAN_SCANCODE_KP_LESS 197
#define DURIAN_SCANCODE_KP_GREATER 198
#define DURIAN_SCANCODE_KP_AMPERSAND 199
#define DURIAN_SCANCODE_KP_DBLAMPERSAND 200
#define DURIAN_SCANCODE_KP_VERTICALBAR 201
#define DURIAN_SCANCODE_KP_DBLVERTICALBAR 202
#define DURIAN_SCANCODE_KP_COLON 203
#define DURIAN_SCANCODE_KP_HASH 204
#define DURIAN_SCANCODE_KP_SPACE 205
#define DURIAN_SCANCODE_KP_AT 206
#define DURIAN_SCANCODE_KP_EXCLAM 207
#define DURIAN_SCANCODE_KP_MEMSTORE 208
#define DURIAN_SCANCODE_KP_MEMRECALL 209
#define DURIAN_SCANCODE_KP_MEMCLEAR 210
#define DURIAN_SCANCODE_KP_MEMADD 211
#define DURIAN_SCANCODE_KP_MEMSUBTRACT 212
#define DURIAN_SCANCODE_KP_MEMMULTIPLY 213
#define DURIAN_SCANCODE_KP_MEMDIVIDE 214
#define DURIAN_SCANCODE_KP_PLUSMINUS 215
#define DURIAN_SCANCODE_KP_CLEAR 216
#define DURIAN_SCANCODE_KP_CLEARENTRY 217
#define DURIAN_SCANCODE_KP_BINARY 218
#define DURIAN_SCANCODE_KP_OCTAL 219
#define DURIAN_SCANCODE_KP_DECIMAL 220
#define DURIAN_SCANCODE_KP_HEXADECIMAL 221

#define DURIAN_SCANCODE_LCTRL 224
#define DURIAN_SCANCODE_LSHIFT 225
#define DURIAN_SCANCODE_LALT 226 /**< alt option */
#define DURIAN_SCANCODE_LGUI 227 /**< windows command (apple) meta */
#define DURIAN_SCANCODE_RCTRL 228
#define DURIAN_SCANCODE_RSHIFT 229
#define DURIAN_SCANCODE_RALT 230 /**< alt gr option */
#define DURIAN_SCANCODE_RGUI 231 /**< windows command (apple) meta */

#define DURIAN_SCANCODE_MODE 257    /**< I'm not sure if this is really not covered
                                       *   by any of the above but since there's a
                                       *   special KMOD_MODE for it I'm adding it here
                                       */
                                       
                                       /* @} *//* Usage page 0x07 */

/**
 *  \name Usage page 0x0C
 *
 *  These values are mapped from usage page 0x0C (USB consumer page).
 */
 /* @{ */

#define DURIAN_SCANCODE_AUDIONEXT 258
#define DURIAN_SCANCODE_AUDIOPREV 259
#define DURIAN_SCANCODE_AUDIOSTOP 260
#define DURIAN_SCANCODE_AUDIOPLAY 261
#define DURIAN_SCANCODE_AUDIOMUTE 262
#define DURIAN_SCANCODE_MEDIASELECT 263
#define DURIAN_SCANCODE_WWW 264
#define DURIAN_SCANCODE_MAIL 265
#define DURIAN_SCANCODE_CALCULATOR 266
#define DURIAN_SCANCODE_COMPUTER 267
#define DURIAN_SCANCODE_AC_SEARCH 268
#define DURIAN_SCANCODE_AC_HOME 269
#define DURIAN_SCANCODE_AC_BACK 270
#define DURIAN_SCANCODE_AC_FORWARD 271
#define DURIAN_SCANCODE_AC_STOP 272
#define DURIAN_SCANCODE_AC_REFRESH 273
#define DURIAN_SCANCODE_AC_BOOKMARKS 274

/* @} *//* Usage page 0x0C */

/**
 *  \name Walther keys
 *
 *  These are values that Christian Walther added (for mac keyboard?).
 */
 /* @{ */

#define DURIAN_SCANCODE_BRIGHTNESSDOWN 275
#define DURIAN_SCANCODE_BRIGHTNESSUP 276
#define DURIAN_SCANCODE_DISPLAYSWITCH 277 /**< display mirroring/dual display
                                       switch video mode switch */
#define DURIAN_SCANCODE_KBDILLUMTOGGLE 278
#define DURIAN_SCANCODE_KBDILLUMDOWN 279
#define DURIAN_SCANCODE_KBDILLUMUP 280
#define DURIAN_SCANCODE_EJECT 281
#define DURIAN_SCANCODE_SLEEP 282

#define DURIAN_SCANCODE_APP1 283
#define DURIAN_SCANCODE_APP2 284

/* @} *//* Walther keys */

/**
 *  \name Usage page 0x0C (additional media keys)
 *
 *  These values are mapped from usage page 0x0C (USB consumer page).
 */
 /* @{ */

#define DURIAN_SCANCODE_AUDIOREWIND 285
#define DURIAN_SCANCODE_AUDIOFASTFORWARD 286

/* @} *//* Usage page 0x0C (additional media keys) */

/**
 *  \name Mobile keys
 *
 *  These are values that are often used on mobile phones.
 */
 /* @{ */

#define DURIAN_SCANCODE_SOFTLEFT 287 /**< Usually situated below the display on phones and
                                  used as a multi-function feature key for selecting
                                  a software defined function shown on the bottom left
                                  of the display. */
#define DURIAN_SCANCODE_SOFTRIGHT 288 /**< Usually situated below the display on phones and
                                   used as a multi-function feature key for selecting
                                   a software defined function shown on the bottom right
                                   of the display. */
#define DURIAN_SCANCODE_CALL 289 /**< Used for accepting phone calls. */
#define DURIAN_SCANCODE_ENDCALL 290 /**< Used for rejecting phone calls. */

/* @} *//* Mobile keys */

/* Add any other keys here. */

#define DURIAN_NUM_SCANCODES 512 /**< not a key just marks the number of scancodes
                             for array bounds */

#define DURIAN_BUTTON_LEFT     1
#define DURIAN_BUTTON_MIDDLE   2
#define DURIAN_BUTTON_RIGHT    3