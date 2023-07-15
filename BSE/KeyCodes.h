#ifndef BSE_KEYCODES_H
#define BSE_KEYCODES_H

#include <Core.h>

namespace BSE {
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
