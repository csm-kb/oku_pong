#include <engine/Input.h>

std::array<bool,InputKey::SIZE> Input::isKeyDown {false};
std::unordered_set<InputKey> Input::isKeyDownEdge {};
std::unordered_set<InputKey> Input::isKeyUpEdge{};

std::unordered_map<SDL_Keycode, InputKey> Input::_sdlInputMap {
	{SDL_SCANCODE_UNKNOWN, K_UNKNOWN},
	{SDL_SCANCODE_A, K_A},
	{SDL_SCANCODE_B, K_B},
	{SDL_SCANCODE_C, K_C},
	{SDL_SCANCODE_D, K_D},
	{SDL_SCANCODE_E, K_E},
	{SDL_SCANCODE_F, K_F},
	{SDL_SCANCODE_G, K_G},
	{SDL_SCANCODE_H, K_H},
	{SDL_SCANCODE_I, K_I},
	{SDL_SCANCODE_J, K_J},
	{SDL_SCANCODE_K, K_K},
	{SDL_SCANCODE_L, K_L},
	{SDL_SCANCODE_M, K_M},
	{SDL_SCANCODE_N, K_N},
	{SDL_SCANCODE_O, K_O},
	{SDL_SCANCODE_P, K_P},
	{SDL_SCANCODE_Q, K_Q},
	{SDL_SCANCODE_R, K_R},
	{SDL_SCANCODE_S, K_S},
	{SDL_SCANCODE_T, K_T},
	{SDL_SCANCODE_U, K_U},
	{SDL_SCANCODE_V, K_V},
	{SDL_SCANCODE_W, K_W},
	{SDL_SCANCODE_X, K_X},
	{SDL_SCANCODE_Y, K_Y},
	{SDL_SCANCODE_Z, K_Z},
	{SDL_SCANCODE_1, K_1},
	{SDL_SCANCODE_2, K_2},
	{SDL_SCANCODE_3, K_3},
	{SDL_SCANCODE_4, K_4},
	{SDL_SCANCODE_5, K_5},
	{SDL_SCANCODE_6, K_6},
	{SDL_SCANCODE_7, K_7},
	{SDL_SCANCODE_8, K_8},
	{SDL_SCANCODE_9, K_9},
	{SDL_SCANCODE_0, K_0},
	{SDL_SCANCODE_RETURN, K_RETURN},
	{SDL_SCANCODE_ESCAPE, K_ESCAPE},
	{SDL_SCANCODE_BACKSPACE, K_BACKSPACE},
	{SDL_SCANCODE_TAB, K_TAB},
	{SDL_SCANCODE_SPACE, K_SPACE},
	{SDL_SCANCODE_MINUS, K_MINUS},
	{SDL_SCANCODE_EQUALS, K_EQUALS},
	{SDL_SCANCODE_LEFTBRACKET, K_LEFTBRACKET},
	{SDL_SCANCODE_RIGHTBRACKET, K_RIGHTBRACKET},
	{SDL_SCANCODE_BACKSLASH, K_BACKSLASH},
	{SDL_SCANCODE_NONUSHASH, K_NONUSHASH},
	{SDL_SCANCODE_SEMICOLON, K_SEMICOLON},
	{SDL_SCANCODE_APOSTROPHE, K_APOSTROPHE},
	{SDL_SCANCODE_GRAVE, K_GRAVE},
	{SDL_SCANCODE_COMMA, K_COMMA},
	{SDL_SCANCODE_PERIOD, K_PERIOD},
	{SDL_SCANCODE_SLASH, K_SLASH},
	{SDL_SCANCODE_CAPSLOCK, K_CAPSLOCK},
	{SDL_SCANCODE_F1, K_F1},
	{SDL_SCANCODE_F2, K_F2},
	{SDL_SCANCODE_F3, K_F3},
	{SDL_SCANCODE_F4, K_F4},
	{SDL_SCANCODE_F5, K_F5},
	{SDL_SCANCODE_F6, K_F6},
	{SDL_SCANCODE_F7, K_F7},
	{SDL_SCANCODE_F8, K_F8},
	{SDL_SCANCODE_F9, K_F9},
	{SDL_SCANCODE_F10, K_F10},
	{SDL_SCANCODE_F11, K_F11},
	{SDL_SCANCODE_F12, K_F12},
	{SDL_SCANCODE_PRINTSCREEN, K_PRINTSCREEN},
	{SDL_SCANCODE_SCROLLLOCK, K_SCROLLLOCK},
	{SDL_SCANCODE_PAUSE, K_PAUSE},
	{SDL_SCANCODE_INSERT, K_INSERT},
	{SDL_SCANCODE_HOME, K_HOME},
	{SDL_SCANCODE_PAGEUP, K_PAGEUP},
	{SDL_SCANCODE_DELETE, K_DELETE},
	{SDL_SCANCODE_END, K_END},
	{SDL_SCANCODE_PAGEDOWN, K_PAGEDOWN},
	{SDL_SCANCODE_RIGHT, K_RIGHT},
	{SDL_SCANCODE_LEFT, K_LEFT},
	{SDL_SCANCODE_DOWN, K_DOWN},
	{SDL_SCANCODE_UP, K_UP},
	{SDL_SCANCODE_NUMLOCKCLEAR, K_NUMLOCKCLEAR},
	{SDL_SCANCODE_KP_DIVIDE, K_KP_DIVIDE},
	{SDL_SCANCODE_KP_MULTIPLY, K_KP_MULTIPLY},
	{SDL_SCANCODE_KP_MINUS, K_KP_MINUS},
	{SDL_SCANCODE_KP_PLUS, K_KP_PLUS},
	{SDL_SCANCODE_KP_ENTER, K_KP_ENTER},
	{SDL_SCANCODE_KP_1, K_KP_1},
	{SDL_SCANCODE_KP_2, K_KP_2},
	{SDL_SCANCODE_KP_3, K_KP_3},
	{SDL_SCANCODE_KP_4, K_KP_4},
	{SDL_SCANCODE_KP_5, K_KP_5},
	{SDL_SCANCODE_KP_6, K_KP_6},
	{SDL_SCANCODE_KP_7, K_KP_7},
	{SDL_SCANCODE_KP_8, K_KP_8},
	{SDL_SCANCODE_KP_9, K_KP_9},
	{SDL_SCANCODE_KP_0, K_KP_0},
	{SDL_SCANCODE_KP_PERIOD, K_KP_PERIOD},
	{SDL_SCANCODE_NONUSBACKSLASH, K_NONUSBACKSLASH},
	{SDL_SCANCODE_APPLICATION, K_APPLICATION},
	{SDL_SCANCODE_POWER, K_POWER},
	{SDL_SCANCODE_KP_EQUALS, K_KP_EQUALS},
	{SDL_SCANCODE_F13, K_F13},
	{SDL_SCANCODE_F14, K_F14},
	{SDL_SCANCODE_F15, K_F15},
	{SDL_SCANCODE_F16, K_F16},
	{SDL_SCANCODE_F17, K_F17},
	{SDL_SCANCODE_F18, K_F18},
	{SDL_SCANCODE_F19, K_F19},
	{SDL_SCANCODE_F20, K_F20},
	{SDL_SCANCODE_F21, K_F21},
	{SDL_SCANCODE_F22, K_F22},
	{SDL_SCANCODE_F23, K_F23},
	{SDL_SCANCODE_F24, K_F24},
	{SDL_SCANCODE_EXECUTE, K_EXECUTE},
	{SDL_SCANCODE_HELP, K_HELP},
	{SDL_SCANCODE_MENU, K_MENU},
	{SDL_SCANCODE_SELECT, K_SELECT},
	{SDL_SCANCODE_STOP, K_STOP},
	{SDL_SCANCODE_AGAIN, K_AGAIN},
	{SDL_SCANCODE_UNDO, K_UNDO},
	{SDL_SCANCODE_CUT, K_CUT},
	{SDL_SCANCODE_COPY, K_COPY},
	{SDL_SCANCODE_PASTE, K_PASTE},
	{SDL_SCANCODE_FIND, K_FIND},
	{SDL_SCANCODE_MUTE, K_MUTE},
	{SDL_SCANCODE_VOLUMEUP, K_VOLUMEUP},
	{SDL_SCANCODE_VOLUMEDOWN, K_VOLUMEDOWN},
	{SDL_SCANCODE_KP_COMMA, K_KP_COMMA},
	{SDL_SCANCODE_KP_EQUALSAS400, K_KP_EQUALSAS400},
	{SDL_SCANCODE_INTERNATIONAL1, K_INTERNATIONAL1},
	{SDL_SCANCODE_INTERNATIONAL2, K_INTERNATIONAL2},
	{SDL_SCANCODE_INTERNATIONAL3, K_INTERNATIONAL3},
	{SDL_SCANCODE_INTERNATIONAL4, K_INTERNATIONAL4},
	{SDL_SCANCODE_INTERNATIONAL5, K_INTERNATIONAL5},
	{SDL_SCANCODE_INTERNATIONAL6, K_INTERNATIONAL6},
	{SDL_SCANCODE_INTERNATIONAL7, K_INTERNATIONAL7},
	{SDL_SCANCODE_INTERNATIONAL8, K_INTERNATIONAL8},
	{SDL_SCANCODE_INTERNATIONAL9, K_INTERNATIONAL9},
	{SDL_SCANCODE_LANG1, K_LANG1},
	{SDL_SCANCODE_LANG2, K_LANG2},
	{SDL_SCANCODE_LANG3, K_LANG3},
	{SDL_SCANCODE_LANG4, K_LANG4},
	{SDL_SCANCODE_LANG5, K_LANG5},
	{SDL_SCANCODE_LANG6, K_LANG6},
	{SDL_SCANCODE_LANG7, K_LANG7},
	{SDL_SCANCODE_LANG8, K_LANG8},
	{SDL_SCANCODE_LANG9, K_LANG9},
	{SDL_SCANCODE_ALTERASE, K_ALTERASE},
	{SDL_SCANCODE_SYSREQ, K_SYSREQ},
	{SDL_SCANCODE_CANCEL, K_CANCEL},
	{SDL_SCANCODE_CLEAR, K_CLEAR},
	{SDL_SCANCODE_PRIOR, K_PRIOR},
	{SDL_SCANCODE_RETURN2, K_RETURN2},
	{SDL_SCANCODE_SEPARATOR, K_SEPARATOR},
	{SDL_SCANCODE_OUT, K_OUT},
	{SDL_SCANCODE_OPER, K_OPER},
	{SDL_SCANCODE_CLEARAGAIN, K_CLEARAGAIN},
	{SDL_SCANCODE_CRSEL, K_CRSEL},
	{SDL_SCANCODE_EXSEL, K_EXSEL},
	{SDL_SCANCODE_KP_00, K_KP_00},
	{SDL_SCANCODE_KP_000, K_KP_000},
	{SDL_SCANCODE_THOUSANDSSEPARATOR, K_THOUSANDSSEPARATOR},
	{SDL_SCANCODE_DECIMALSEPARATOR, K_DECIMALSEPARATOR},
	{SDL_SCANCODE_CURRENCYUNIT, K_CURRENCYUNIT},
	{SDL_SCANCODE_CURRENCYSUBUNIT, K_CURRENCYSUBUNIT},
	{SDL_SCANCODE_KP_LEFTPAREN, K_KP_LEFTPAREN},
	{SDL_SCANCODE_KP_RIGHTPAREN, K_KP_RIGHTPAREN},
	{SDL_SCANCODE_KP_LEFTBRACE, K_KP_LEFTBRACE},
	{SDL_SCANCODE_KP_RIGHTBRACE, K_KP_RIGHTBRACE},
	{SDL_SCANCODE_KP_TAB, K_KP_TAB},
	{SDL_SCANCODE_KP_BACKSPACE, K_KP_BACKSPACE},
	{SDL_SCANCODE_KP_A, K_KP_A},
	{SDL_SCANCODE_KP_B, K_KP_B},
	{SDL_SCANCODE_KP_C, K_KP_C},
	{SDL_SCANCODE_KP_D, K_KP_D},
	{SDL_SCANCODE_KP_E, K_KP_E},
	{SDL_SCANCODE_KP_F, K_KP_F},
	{SDL_SCANCODE_KP_XOR, K_KP_XOR},
	{SDL_SCANCODE_KP_POWER, K_KP_POWER},
	{SDL_SCANCODE_KP_PERCENT, K_KP_PERCENT},
	{SDL_SCANCODE_KP_LESS, K_KP_LESS},
	{SDL_SCANCODE_KP_GREATER, K_KP_GREATER},
	{SDL_SCANCODE_KP_AMPERSAND, K_KP_AMPERSAND},
	{SDL_SCANCODE_KP_DBLAMPERSAND, K_KP_DBLAMPERSAND},
	{SDL_SCANCODE_KP_VERTICALBAR, K_KP_VERTICALBAR},
	{SDL_SCANCODE_KP_DBLVERTICALBAR, K_KP_DBLVERTICALBAR},
	{SDL_SCANCODE_KP_COLON, K_KP_COLON},
	{SDL_SCANCODE_KP_HASH, K_KP_HASH},
	{SDL_SCANCODE_KP_SPACE, K_KP_SPACE},
	{SDL_SCANCODE_KP_AT, K_KP_AT},
	{SDL_SCANCODE_KP_EXCLAM, K_KP_EXCLAM},
	{SDL_SCANCODE_KP_MEMSTORE, K_KP_MEMSTORE},
	{SDL_SCANCODE_KP_MEMRECALL, K_KP_MEMRECALL},
	{SDL_SCANCODE_KP_MEMCLEAR, K_KP_MEMCLEAR},
	{SDL_SCANCODE_KP_MEMADD, K_KP_MEMADD},
	{SDL_SCANCODE_KP_MEMSUBTRACT, K_KP_MEMSUBTRACT},
	{SDL_SCANCODE_KP_MEMMULTIPLY, K_KP_MEMMULTIPLY},
	{SDL_SCANCODE_KP_MEMDIVIDE, K_KP_MEMDIVIDE},
	{SDL_SCANCODE_KP_PLUSMINUS, K_KP_PLUSMINUS},
	{SDL_SCANCODE_KP_CLEAR, K_KP_CLEAR},
	{SDL_SCANCODE_KP_CLEARENTRY, K_KP_CLEARENTRY},
	{SDL_SCANCODE_KP_BINARY, K_KP_BINARY},
	{SDL_SCANCODE_KP_OCTAL, K_KP_OCTAL},
	{SDL_SCANCODE_KP_DECIMAL, K_KP_DECIMAL},
	{SDL_SCANCODE_KP_HEXADECIMAL, K_KP_HEXADECIMAL},
	{SDL_SCANCODE_LCTRL, K_LCTRL},
	{SDL_SCANCODE_LSHIFT, K_LSHIFT},
	{SDL_SCANCODE_LALT, K_LALT},
	{SDL_SCANCODE_LGUI, K_LGUI},
	{SDL_SCANCODE_RCTRL, K_RCTRL},
	{SDL_SCANCODE_RSHIFT, K_RSHIFT},
	{SDL_SCANCODE_RALT, K_RALT},
	{SDL_SCANCODE_RGUI, K_RGUI},
	{SDL_SCANCODE_MODE, K_MODE},
	{SDL_SCANCODE_AUDIONEXT, K_AUDIONEXT},
	{SDL_SCANCODE_AUDIOPREV, K_AUDIOPREV},
	{SDL_SCANCODE_AUDIOSTOP, K_AUDIOSTOP},
	{SDL_SCANCODE_AUDIOPLAY, K_AUDIOPLAY},
	{SDL_SCANCODE_AUDIOMUTE, K_AUDIOMUTE},
	{SDL_SCANCODE_MEDIASELECT, K_MEDIASELECT},
	{SDL_SCANCODE_WWW, K_WWW},
	{SDL_SCANCODE_MAIL, K_MAIL},
	{SDL_SCANCODE_CALCULATOR, K_CALCULATOR},
	{SDL_SCANCODE_COMPUTER, K_COMPUTER},
	{SDL_SCANCODE_AC_SEARCH, K_AC_SEARCH},
	{SDL_SCANCODE_AC_HOME, K_AC_HOME},
	{SDL_SCANCODE_AC_BACK, K_AC_BACK},
	{SDL_SCANCODE_AC_FORWARD, K_AC_FORWARD},
	{SDL_SCANCODE_AC_STOP, K_AC_STOP},
	{SDL_SCANCODE_AC_REFRESH, K_AC_REFRESH},
	{SDL_SCANCODE_AC_BOOKMARKS, K_AC_BOOKMARKS},
	{SDL_SCANCODE_BRIGHTNESSDOWN, K_BRIGHTNESSDOWN},
	{SDL_SCANCODE_BRIGHTNESSUP, K_BRIGHTNESSUP},
	{SDL_SCANCODE_DISPLAYSWITCH, K_DISPLAYSWITCH},
	{SDL_SCANCODE_KBDILLUMTOGGLE, K_KBDILLUMTOGGLE},
	{SDL_SCANCODE_KBDILLUMDOWN, K_KBDILLUMDOWN},
	{SDL_SCANCODE_KBDILLUMUP, K_KBDILLUMUP},
	{SDL_SCANCODE_EJECT, K_EJECT},
	{SDL_SCANCODE_SLEEP, K_SLEEP},
	{SDL_SCANCODE_APP1, K_APP1},
	{SDL_SCANCODE_APP2, K_APP2},
	{SDL_SCANCODE_AUDIOREWIND, K_AUDIOREWIND},
	{SDL_SCANCODE_AUDIOFASTFORWARD, K_AUDIOFASTFORWARD}
};

void Input::EndGameLoop()
{
	isKeyDownEdge.clear();
	isKeyUpEdge.clear();
}

void Input::SetKeyDown(SDL_Keycode key)
{
	if (_sdlInputMap.find(key) == _sdlInputMap.end())
		return;
	const auto ikey = _sdlInputMap.at(key);
	if (isKeyDown[ikey])
		return;

	isKeyDownEdge.insert(ikey);
	isKeyDown[ikey] = true;
}

void Input::SetKeyUp(SDL_Keycode key)
{
	if (_sdlInputMap.find(key) == _sdlInputMap.end())
		return;
	const auto ikey = _sdlInputMap.at(key);
	if (!isKeyDown[ikey])
		return;

	isKeyDown[ikey] = false;
	isKeyUpEdge.insert(ikey);
}

bool Input::GetKeyDown(InputKey key)
{
	return isKeyDown[key];
}

bool Input::GetKeyPressed(InputKey key)
{
	return isKeyDownEdge.find(key) != isKeyDownEdge.end();
}

bool Input::GetKeyReleased(InputKey key)
{
	return isKeyUpEdge.find(key) != isKeyUpEdge.end();
}

