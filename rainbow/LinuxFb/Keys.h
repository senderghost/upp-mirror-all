#ifndef _LinuxFb_Keys_h_
#define _LinuxFb_Keys_h_

//translation of linux keycodes from MEDIUMRAM to ultimate
//thanks goes to svgalib

K_BACK       = SCANCODE_BACKSPACE + K_DELTA,
K_BACKSPACE  = SCANCODE_BACKSPACE + K_DELTA,

K_TAB        = 9, //SCANCODE_TAB

K_SPACE      = 32, //SCANCODE_SPACE

K_RETURN     = 13, //SCANCODE_ENTER
K_ENTER      = K_RETURN,

K_SHIFT_KEY  = SCANCODE_LEFTSHIFT + K_DELTA,
K_CTRL_KEY   = SCANCODE_LEFTCONTROL + K_DELTA,
K_ALT_KEY    = SCANCODE_LEFTALT + K_DELTA,
K_CAPSLOCK   = SCANCODE_CAPSLOCK + K_DELTA,
K_ESCAPE     = SCANCODE_ESCAPE + K_DELTA,
K_PRIOR      = SCANCODE_PAGEUP + K_DELTA,
K_PAGEUP     = SCANCODE_PAGEUP + K_DELTA,
K_NEXT       = SCANCODE_PAGEDOWN + K_DELTA,
K_PAGEDOWN   = SCANCODE_PAGEDOWN + K_DELTA,
K_END        = SCANCODE_END + K_DELTA,
K_HOME       = SCANCODE_HOME + K_DELTA,
K_LEFT       = SCANCODE_CURSORBLOCKLEFT + K_DELTA,
K_UP         = SCANCODE_CURSORBLOCKUP + K_DELTA,
K_RIGHT      = SCANCODE_CURSORBLOCKRIGHT + K_DELTA,
K_DOWN       = SCANCODE_CURSORBLOCKDOWN + K_DELTA,
K_INSERT     = SCANCODE_INSERT + K_DELTA,
K_DELETE     = SCANCODE_REMOVE + K_DELTA,

K_NUMPAD0    = SCANCODE_KEYPAD0 + K_DELTA,
K_NUMPAD1    = SCANCODE_KEYPAD1 + K_DELTA,
K_NUMPAD2    = SCANCODE_KEYPAD2 + K_DELTA,
K_NUMPAD3    = SCANCODE_KEYPAD3 + K_DELTA,
K_NUMPAD4    = SCANCODE_KEYPAD4 + K_DELTA,
K_NUMPAD5    = SCANCODE_KEYPAD5 + K_DELTA,
K_NUMPAD6    = SCANCODE_KEYPAD6 + K_DELTA,
K_NUMPAD7    = SCANCODE_KEYPAD7 + K_DELTA,
K_NUMPAD8    = SCANCODE_KEYPAD8 + K_DELTA,
K_NUMPAD9    = SCANCODE_KEYPAD9 + K_DELTA,
K_MULTIPLY   = SCANCODE_KEYPADMULTIPLY + K_DELTA,
K_ADD        = SCANCODE_KEYPADPLUS + K_DELTA,
K_SEPARATOR  = SCANCODE_KEYPADPERIOD + K_DELTA,
K_SUBTRACT   = SCANCODE_KEYPADMINUS + K_DELTA,
K_DECIMAL    = SCANCODE_KEYPADPERIOD + K_DELTA,
K_DIVIDE     = SCANCODE_KEYPADDIVIDE + K_DELTA,
K_SCROLL     = SCANCODE_SCROLLLOCK + K_DELTA,

K_F1         = SCANCODE_F1 + K_DELTA,
K_F2         = SCANCODE_F2 + K_DELTA,
K_F3         = SCANCODE_F3 + K_DELTA,
K_F4         = SCANCODE_F4 + K_DELTA,
K_F5         = SCANCODE_F5 + K_DELTA,
K_F6         = SCANCODE_F6 + K_DELTA,
K_F7         = SCANCODE_F7 + K_DELTA,
K_F8         = SCANCODE_F8 + K_DELTA,
K_F9         = SCANCODE_F9 + K_DELTA,
K_F10        = SCANCODE_F10 + K_DELTA,
K_F11        = SCANCODE_F11 + K_DELTA,
K_F12        = SCANCODE_F12 + K_DELTA,

K_A          = SCANCODE_A + K_DELTA,
K_B          = SCANCODE_B + K_DELTA,
K_C          = SCANCODE_C + K_DELTA,
K_D          = SCANCODE_D + K_DELTA,
K_E          = SCANCODE_E + K_DELTA,
K_F          = SCANCODE_F + K_DELTA,
K_G          = SCANCODE_G + K_DELTA,
K_H          = SCANCODE_H + K_DELTA,
K_I          = SCANCODE_I + K_DELTA,
K_J          = SCANCODE_J + K_DELTA,
K_K          = SCANCODE_K + K_DELTA,
K_L          = SCANCODE_L + K_DELTA,
K_M          = SCANCODE_M + K_DELTA,
K_N          = SCANCODE_N + K_DELTA,
K_O          = SCANCODE_O + K_DELTA,
K_P          = SCANCODE_P + K_DELTA,
K_Q          = SCANCODE_Q + K_DELTA,
K_R          = SCANCODE_R + K_DELTA,
K_S          = SCANCODE_S + K_DELTA,
K_T          = SCANCODE_T + K_DELTA,
K_U          = SCANCODE_U + K_DELTA,
K_V          = SCANCODE_V + K_DELTA,
K_W          = SCANCODE_W + K_DELTA,
K_X          = SCANCODE_X + K_DELTA,
K_Y          = SCANCODE_Y + K_DELTA,
K_Z          = SCANCODE_Z + K_DELTA,
K_0          = SCANCODE_0 + K_DELTA,
K_1          = SCANCODE_1 + K_DELTA,
K_2          = SCANCODE_2 + K_DELTA,
K_3          = SCANCODE_3 + K_DELTA,
K_4          = SCANCODE_4 + K_DELTA,
K_5          = SCANCODE_5 + K_DELTA,
K_6          = SCANCODE_6 + K_DELTA,
K_7          = SCANCODE_7 + K_DELTA,
K_8          = SCANCODE_8 + K_DELTA,
K_9          = SCANCODE_9 + K_DELTA,

K_CTRL_LBRACKET  = K_CTRL|219|K_DELTA,
K_CTRL_RBRACKET  = K_CTRL|221|K_DELTA,
K_CTRL_MINUS     = K_CTRL|0xbd|K_DELTA,
K_CTRL_GRAVE     = K_CTRL|0xc0|K_DELTA,
K_CTRL_SLASH     = K_CTRL|0xbf|K_DELTA,
K_CTRL_BACKSLASH = K_CTRL|0xdc|K_DELTA,
K_CTRL_COMMA     = K_CTRL|0xbc|K_DELTA,
K_CTRL_PERIOD    = K_CTRL|0xbe|K_DELTA,
K_CTRL_SEMICOLON = K_CTRL|0xbe|K_DELTA,
K_CTRL_EQUAL     = K_CTRL|0xbb|K_DELTA,
K_CTRL_APOSTROPHE= K_CTRL|0xde|K_DELTA,

K_BREAK      = SCANCODE_BREAK + K_DELTA, //SCANCODE_BREAK_ALTERNATIVE

#endif
