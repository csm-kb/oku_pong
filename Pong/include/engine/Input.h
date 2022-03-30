#ifndef Input_H
#define Input_H

#include <SDL.h>

#include <array>
#include <unordered_map>
#include <unordered_set>

/**
 * \brief Enum representing all of the standard keyboard key codes and some special ones.
 */
enum InputKey
{
    K_UNKNOWN,
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_RETURN,
	K_ESCAPE,
	K_BACKSPACE,
	K_TAB,
	K_SPACE,
	K_MINUS,
	K_EQUALS,
	K_LEFTBRACKET,
	K_RIGHTBRACKET,
	K_BACKSLASH,
    K_NONUSHASH,
    K_SEMICOLON,
    K_APOSTROPHE,
    K_GRAVE,
    K_COMMA,
    K_PERIOD,
    K_SLASH,
    K_CAPSLOCK,
    K_F1,
    K_F2,
    K_F3,
    K_F4,
    K_F5,
    K_F6,
    K_F7,
    K_F8,
    K_F9,
    K_F10,
    K_F11,
    K_F12,
    K_PRINTSCREEN,
    K_SCROLLLOCK,
    K_PAUSE,
    K_INSERT,
    K_HOME,
    K_PAGEUP,
    K_DELETE,
    K_END,
    K_PAGEDOWN,
    K_RIGHT,
    K_LEFT,
    K_DOWN,
    K_UP,
    K_NUMLOCKCLEAR,
    K_KP_DIVIDE,
    K_KP_MULTIPLY,
    K_KP_MINUS,
    K_KP_PLUS,
    K_KP_ENTER,
    K_KP_1,
    K_KP_2,
    K_KP_3,
    K_KP_4,
    K_KP_5,
    K_KP_6,
    K_KP_7,
    K_KP_8,
    K_KP_9,
    K_KP_0,
    K_KP_PERIOD,
    K_NONUSBACKSLASH,
    K_APPLICATION,
    K_POWER,
    K_KP_EQUALS,
    K_F13,
    K_F14,
    K_F15,
    K_F16,
    K_F17,
    K_F18,
    K_F19,
    K_F20,
    K_F21,
    K_F22,
    K_F23,
    K_F24,
    K_EXECUTE,
    K_HELP,
    K_MENU,
    K_SELECT,
    K_STOP,
    K_AGAIN,
    K_UNDO,
    K_CUT,
    K_COPY,
    K_PASTE,
    K_FIND,
    K_MUTE,
    K_VOLUMEUP,
    K_VOLUMEDOWN,
    K_KP_COMMA,
    K_KP_EQUALSAS400,
    K_INTERNATIONAL1,
    K_INTERNATIONAL2,
    K_INTERNATIONAL3,
    K_INTERNATIONAL4,
    K_INTERNATIONAL5,
    K_INTERNATIONAL6,
    K_INTERNATIONAL7,
    K_INTERNATIONAL8,
    K_INTERNATIONAL9,
    K_LANG1,
    K_LANG2,
    K_LANG3,
    K_LANG4,
    K_LANG5,
    K_LANG6,
    K_LANG7,
    K_LANG8,
    K_LANG9,
    K_ALTERASE,
    K_SYSREQ,
    K_CANCEL,
    K_CLEAR,
    K_PRIOR,
    K_RETURN2,
    K_SEPARATOR,
    K_OUT,
    K_OPER,
    K_CLEARAGAIN,
    K_CRSEL,
    K_EXSEL,
    K_KP_00,
    K_KP_000,
    K_THOUSANDSSEPARATOR,
    K_DECIMALSEPARATOR,
    K_CURRENCYUNIT,
    K_CURRENCYSUBUNIT,
    K_KP_LEFTPAREN,
    K_KP_RIGHTPAREN,
    K_KP_LEFTBRACE,
    K_KP_RIGHTBRACE,
    K_KP_TAB,
    K_KP_BACKSPACE,
    K_KP_A,
    K_KP_B,
    K_KP_C,
    K_KP_D,
    K_KP_E,
    K_KP_F,
    K_KP_XOR,
    K_KP_POWER,
    K_KP_PERCENT,
    K_KP_LESS,
    K_KP_GREATER,
    K_KP_AMPERSAND,
    K_KP_DBLAMPERSAND,
    K_KP_VERTICALBAR,
    K_KP_DBLVERTICALBAR,
    K_KP_COLON,
    K_KP_HASH,
    K_KP_SPACE,
    K_KP_AT,
    K_KP_EXCLAM,
    K_KP_MEMSTORE,
    K_KP_MEMRECALL,
    K_KP_MEMCLEAR,
    K_KP_MEMADD,
    K_KP_MEMSUBTRACT,
    K_KP_MEMMULTIPLY,
    K_KP_MEMDIVIDE,
    K_KP_PLUSMINUS,
    K_KP_CLEAR,
    K_KP_CLEARENTRY,
    K_KP_BINARY,
    K_KP_OCTAL,
    K_KP_DECIMAL,
    K_KP_HEXADECIMAL,
    K_LCTRL,
    K_LSHIFT,
    K_LALT,
    K_LGUI,
    K_RCTRL,
    K_RSHIFT,
    K_RALT,
    K_RGUI,
    K_MODE,
    K_AUDIONEXT,
    K_AUDIOPREV,
    K_AUDIOSTOP,
    K_AUDIOPLAY,
    K_AUDIOMUTE,
    K_MEDIASELECT,
    K_WWW,
    K_MAIL,
    K_CALCULATOR,
    K_COMPUTER,
    K_AC_SEARCH,
    K_AC_HOME,
    K_AC_BACK,
    K_AC_FORWARD,
    K_AC_STOP,
    K_AC_REFRESH,
    K_AC_BOOKMARKS,
    K_BRIGHTNESSDOWN,
    K_BRIGHTNESSUP,
    K_DISPLAYSWITCH,
    K_KBDILLUMTOGGLE,
    K_KBDILLUMDOWN,
    K_KBDILLUMUP,
    K_EJECT,
    K_SLEEP,
    K_APP1,
    K_APP2,
    K_AUDIOREWIND,
    K_AUDIOFASTFORWARD,
	SIZE
};

class Input
{
public:
	/**
	 * \brief Sets the corresponding InputKey to be down and pressed this frame.
	 * \param key The corresponding SDL keycode obtained from the window framework.
	 */
	static void SetKeyDown(SDL_Keycode key);
	/**
	 * \brief Sets the corresponding InputKey to be up and released this frame.
	 * \param key The corresponding SDL keycode obtained from the window framework.
	 */
	static void SetKeyUp(SDL_Keycode key);
	/**
	 * \brief Used by Input to clear edge states (pressed/released).
	 */
	static void EndGameLoop();

	/**
	 * \brief Returns whether or not the key is currently held down.
	 * \param key The value corresponding to the desired input key.
	 */
	static bool GetKeyDown(InputKey key);
	/**
	 * \brief Returns whether or not the key was pressed this frame.
	 * \param key The value corresponding to the desired input key.
	 */
	static bool GetKeyPressed(InputKey key);
	/**
	 * \brief Returns whether or not the key was released this frame.
	 * \param key The value corresponding to the desired input key.
	 */
	static bool GetKeyReleased(InputKey key);

private:
	static std::unordered_map<SDL_Keycode, InputKey> _sdlInputMap;

	static std::array<bool,InputKey::SIZE> isKeyDown;
	static std::unordered_set<InputKey> isKeyDownEdge;
	static std::unordered_set<InputKey> isKeyUpEdge;
};

#endif//Input_H