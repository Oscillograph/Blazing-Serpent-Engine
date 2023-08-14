#ifndef BSE_KEYCODES_H
#define BSE_KEYCODES_H

#include <Core.h>

namespace BSE {
	enum class KeyCode : uint32_t {
		// ------------------------------------
		// 				KEYBOARD
		// ------------------------------------
		/* Printable keys */
		Space				= 32,
		Apostrophe			= 39,  /* ' */
		Comma				= 44,  /* , */
		Minus				= 45,  /* - */
		Period				= 46,  /* . */
		Slash              	= 47,  /* / */
		D0                 	= 48,
		D1                 	= 49,
		D2                 	= 50,
		D3                 	= 51,
		D4                 	= 52,
		D5                 	= 53,
		D6                 	= 54,
		D7                 	= 55,
		D8                 	= 56,
		D9                 	= 57,
		
		Semicolon          	= 59,  /* ; */
		Equal              	= 61,  /* = */

		A                  	= 65,
		B                  	= 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket       	= 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket      	= 93,  /* ] */
		GraveAccent       	= 96,  /* ` */
		World1            	= 161, /* non-US #1 */
		World2            	= 162, /* non-US #2 */
		
		/* Function keys */
		Esc             	= 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock          	= 280,
		ScrollLock        	= 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP_0                = 320,
		KP_1                = 321,
		KP_2                = 322,
		KP_3                = 323,
		KP_4                = 324,
		KP_5                = 325,
		KP_6                = 326,
		KP_7                = 327,
		KP_8                = 328,
		KP_9                = 329,
		KP_Decimal          = 330,
		KP_Divide           = 331,
		KP_Multiply         = 332,
		KP_Subtract         = 333,
		KP_Add              = 334,
		KP_Enter            = 335,
		KP_Equal            = 336,
		
		/* Shift, Control, Alt, Super and Menu*/
		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343, /* basically, Win key*/
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348,
		
		// ------------------------------------
		// 				MOUSE
		// ------------------------------------
		MouseButton1        = 0,
		MouseButton2      	= 1,
		MouseButton3        = 2,
		MouseButton4        = 3,
		MouseButton5        = 4,
		MouseButton6        = 5,
		MouseButton7        = 6,
		MouseButton8        = 7,
		MouseButtonLeft		= MouseButton1,
		MouseButtonRight	= MouseButton2,
		MouseButtonMiddle	= MouseButton3,
		MouseButtonLast		= MouseButton8,
		
		// ------------------------------------
		// 				JOYSTICK
		// ------------------------------------
		Joystick1           = 0,
		Joystick2           = 1,
		Joystick3           = 2,
		Joystick4           = 3,
		Joystick5           = 4,
		Joystick6           = 5,
		Joystick7           = 6,
		Joystick8           = 7,
		Joystick9           = 8,
		Joystick10          = 9,
		Joystick11          = 10,
		Joystick12          = 11,
		Joystick13          = 12,
		Joystick14          = 13,
		Joystick15          = 14,
		Joystick16          = 15,
		JoystickLast        = Joystick16,
		
		// ------------------------------------
		// 				GAMEPAD
		// ------------------------------------
		GamepadButtonA               	= 0,
		GamepadButtonB               	= 1,
		GamepadButtonX               	= 2,
		GamepadButtonY               	= 3,
		GamepadButtonLeftBumper      	= 4,
		GamepadButtonRightBumper     	= 5,
		GamepadButtonBack            	= 6,
		GamepadButtonStart           	= 7,
		GamepadButtonGuide           	= 8,
		GamepadButtonLeftThumb       	= 9,
		GamepadButtonRightThumb      	= 10,
		GamepadButtonDPadUp          	= 11,
		GamepadButtonDPadRight       	= 12,
		GamepadButtonDPadDown        	= 13,
		GamepadButtonDPadLeft        	= 14,
		GamepadButtonLast            	= GamepadButtonDPadLeft,
				
		GamepadButtonCross       	 	= GamepadButtonA,
		GamepadButtonCircle      	 	= GamepadButtonB,
		GamepadButtonSquare      	 	= GamepadButtonX,
		GamepadButtonTriangle    	 	= GamepadButtonY,

		GamepadButtonAxisLeftX       	= 0,
		GamepadButtonAxisLeftY       	= 1,
		GamepadButtonAxisRightX      	= 2,
		GamepadButtonAxisRightY      	= 3,
		GamepadButtonAxisLeftTrigger 	= 4,
		GamepadButtonAxisRightTrigger	= 5,
		GamepadButtonAxisLast        	= GamepadButtonAxisRightTrigger
	};
	
	// Stolen from glfw3.h
	
	// ------------------------------------
	// 				KEYBOARD
	// ------------------------------------
		/* The unknown key */
	#define BSE_KEY_UNKNOWN            -1
		
		/* Printable keys */
	#define BSE_KEY_SPACE              32
	#define BSE_KEY_APOSTROPHE         39  /* ' */
	#define BSE_KEY_COMMA              44  /* , */
	#define BSE_KEY_MINUS              45  /* - */
	#define BSE_KEY_PERIOD             46  /* . */
	#define BSE_KEY_SLASH              47  /* / */
	#define BSE_KEY_0                  48
	#define BSE_KEY_1                  49
	#define BSE_KEY_2                  50
	#define BSE_KEY_3                  51
	#define BSE_KEY_4                  52
	#define BSE_KEY_5                  53
	#define BSE_KEY_6                  54
	#define BSE_KEY_7                  55
	#define BSE_KEY_8                  56
	#define BSE_KEY_9                  57
	#define BSE_KEY_SEMICOLON          59  /* ; */
	#define BSE_KEY_EQUAL              61  /* = */
	#define BSE_KEY_A                  65
	#define BSE_KEY_B                  66
	#define BSE_KEY_C                  67
	#define BSE_KEY_D                  68
	#define BSE_KEY_E                  69
	#define BSE_KEY_F                  70
	#define BSE_KEY_G                  71
	#define BSE_KEY_H                  72
	#define BSE_KEY_I                  73
	#define BSE_KEY_J                  74
	#define BSE_KEY_K                  75
	#define BSE_KEY_L                  76
	#define BSE_KEY_M                  77
	#define BSE_KEY_N                  78
	#define BSE_KEY_O                  79
	#define BSE_KEY_P                  80
	#define BSE_KEY_Q                  81
	#define BSE_KEY_R                  82
	#define BSE_KEY_S                  83
	#define BSE_KEY_T                  84
	#define BSE_KEY_U                  85
	#define BSE_KEY_V                  86
	#define BSE_KEY_W                  87
	#define BSE_KEY_X                  88
	#define BSE_KEY_Y                  89
	#define BSE_KEY_Z                  90
	#define BSE_KEY_LEFT_BRACKET       91  /* [ */
	#define BSE_KEY_BACKSLASH          92  /* \ */
	#define BSE_KEY_RIGHT_BRACKET      93  /* ] */
	#define BSE_KEY_GRAVE_ACCENT       96  /* ` */
	#define BSE_KEY_WORLD_1            161 /* non-US #1 */
	#define BSE_KEY_WORLD_2            162 /* non-US #2 */
		
		/* Function keys */
	#define BSE_KEY_ESCAPE             256
	#define BSE_KEY_ENTER              257
	#define BSE_KEY_TAB                258
	#define BSE_KEY_BACKSPACE          259
	#define BSE_KEY_INSERT             260
	#define BSE_KEY_DELETE             261
	#define BSE_KEY_RIGHT              262
	#define BSE_KEY_LEFT               263
	#define BSE_KEY_DOWN               264
	#define BSE_KEY_UP                 265
	#define BSE_KEY_PAGE_UP            266
	#define BSE_KEY_PAGE_DOWN          267
	#define BSE_KEY_HOME               268
	#define BSE_KEY_END                269
	#define BSE_KEY_CAPS_LOCK          280
	#define BSE_KEY_SCROLL_LOCK        281
	#define BSE_KEY_NUM_LOCK           282
	#define BSE_KEY_PRINT_SCREEN       283
	#define BSE_KEY_PAUSE              284
	#define BSE_KEY_F1                 290
	#define BSE_KEY_F2                 291
	#define BSE_KEY_F3                 292
	#define BSE_KEY_F4                 293
	#define BSE_KEY_F5                 294
	#define BSE_KEY_F6                 295
	#define BSE_KEY_F7                 296
	#define BSE_KEY_F8                 297
	#define BSE_KEY_F9                 298
	#define BSE_KEY_F10                299
	#define BSE_KEY_F11                300
	#define BSE_KEY_F12                301
	#define BSE_KEY_F13                302
	#define BSE_KEY_F14                303
	#define BSE_KEY_F15                304
	#define BSE_KEY_F16                305
	#define BSE_KEY_F17                306
	#define BSE_KEY_F18                307
	#define BSE_KEY_F19                308
	#define BSE_KEY_F20                309
	#define BSE_KEY_F21                310
	#define BSE_KEY_F22                311
	#define BSE_KEY_F23                312
	#define BSE_KEY_F24                313
	#define BSE_KEY_F25                314
	#define BSE_KEY_KP_0               320
	#define BSE_KEY_KP_1               321
	#define BSE_KEY_KP_2               322
	#define BSE_KEY_KP_3               323
	#define BSE_KEY_KP_4               324
	#define BSE_KEY_KP_5               325
	#define BSE_KEY_KP_6               326
	#define BSE_KEY_KP_7               327
	#define BSE_KEY_KP_8               328
	#define BSE_KEY_KP_9               329
	#define BSE_KEY_KP_DECIMAL         330
	#define BSE_KEY_KP_DIVIDE          331
	#define BSE_KEY_KP_MULTIPLY        332
	#define BSE_KEY_KP_SUBTRACT        333
	#define BSE_KEY_KP_ADD             334
	#define BSE_KEY_KP_ENTER           335
	#define BSE_KEY_KP_EQUAL           336
	#define BSE_KEY_LEFT_SHIFT         340
	#define BSE_KEY_LEFT_CONTROL       341
	#define BSE_KEY_LEFT_ALT           342
	#define BSE_KEY_LEFT_SUPER         343 /* basically, Win key*/
	#define BSE_KEY_RIGHT_SHIFT        344
	#define BSE_KEY_RIGHT_CONTROL      345
	#define BSE_KEY_RIGHT_ALT          346
	#define BSE_KEY_RIGHT_SUPER        347
	#define BSE_KEY_MENU               348
	
	// ------------------------------------
	// 				MOUSE
	// ------------------------------------
	#define BSE_MOUSE_BUTTON_1         0
	#define BSE_MOUSE_BUTTON_2         1
	#define BSE_MOUSE_BUTTON_3         2
	#define BSE_MOUSE_BUTTON_4         3
	#define BSE_MOUSE_BUTTON_5         4
	#define BSE_MOUSE_BUTTON_6         5
	#define BSE_MOUSE_BUTTON_7         6
	#define BSE_MOUSE_BUTTON_8         7
	#define BSE_MOUSE_BUTTON_LAST      BSE_MOUSE_BUTTON_8
	#define BSE_MOUSE_BUTTON_LEFT      BSE_MOUSE_BUTTON_1
	#define BSE_MOUSE_BUTTON_RIGHT     BSE_MOUSE_BUTTON_2
	#define BSE_MOUSE_BUTTON_MIDDLE    BSE_MOUSE_BUTTON_3
	
	// ------------------------------------
	// 				JOYSTICK
	// ------------------------------------
	#define BSE_JOYSTICK_1             0
	#define BSE_JOYSTICK_2             1
	#define BSE_JOYSTICK_3             2
	#define BSE_JOYSTICK_4             3
	#define BSE_JOYSTICK_5             4
	#define BSE_JOYSTICK_6             5
	#define BSE_JOYSTICK_7             6
	#define BSE_JOYSTICK_8             7
	#define BSE_JOYSTICK_9             8
	#define BSE_JOYSTICK_10            9
	#define BSE_JOYSTICK_11            10
	#define BSE_JOYSTICK_12            11
	#define BSE_JOYSTICK_13            12
	#define BSE_JOYSTICK_14            13
	#define BSE_JOYSTICK_15            14
	#define BSE_JOYSTICK_16            15
	#define BSE_JOYSTICK_LAST          BSE_JOYSTICK_16
	
	// ------------------------------------
	// 				GAMEPAD
	// ------------------------------------
	#define BSE_GAMEPAD_BUTTON_A               0
	#define BSE_GAMEPAD_BUTTON_B               1
	#define BSE_GAMEPAD_BUTTON_X               2
	#define BSE_GAMEPAD_BUTTON_Y               3
	#define BSE_GAMEPAD_BUTTON_LEFT_BUMPER     4
	#define BSE_GAMEPAD_BUTTON_RIGHT_BUMPER    5
	#define BSE_GAMEPAD_BUTTON_BACK            6
	#define BSE_GAMEPAD_BUTTON_START           7
	#define BSE_GAMEPAD_BUTTON_GUIDE           8
	#define BSE_GAMEPAD_BUTTON_LEFT_THUMB      9
	#define BSE_GAMEPAD_BUTTON_RIGHT_THUMB     10
	#define BSE_GAMEPAD_BUTTON_DPAD_UP         11
	#define BSE_GAMEPAD_BUTTON_DPAD_RIGHT      12
	#define BSE_GAMEPAD_BUTTON_DPAD_DOWN       13
	#define BSE_GAMEPAD_BUTTON_DPAD_LEFT       14
	#define BSE_GAMEPAD_BUTTON_LAST            BSE_GAMEPAD_BUTTON_DPAD_LEFT
		
	#define BSE_GAMEPAD_BUTTON_CROSS       BSE_GAMEPAD_BUTTON_A
	#define BSE_GAMEPAD_BUTTON_CIRCLE      BSE_GAMEPAD_BUTTON_B
	#define BSE_GAMEPAD_BUTTON_SQUARE      BSE_GAMEPAD_BUTTON_X
	#define BSE_GAMEPAD_BUTTON_TRIANGLE    BSE_GAMEPAD_BUTTON_Y

	#define BSE_GAMEPAD_AXIS_LEFT_X        0
	#define BSE_GAMEPAD_AXIS_LEFT_Y        1
	#define BSE_GAMEPAD_AXIS_RIGHT_X       2
	#define BSE_GAMEPAD_AXIS_RIGHT_Y       3
	#define BSE_GAMEPAD_AXIS_LEFT_TRIGGER  4
	#define BSE_GAMEPAD_AXIS_RIGHT_TRIGGER 5
	#define BSE_GAMEPAD_AXIS_LAST          BSE_GAMEPAD_AXIS_RIGHT_TRIGGER
}

#endif
