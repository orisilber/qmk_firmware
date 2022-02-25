BOOTLOADER = caterina
MCU = atmega32u4

# Saves a bunch of memory
EXTRAFLAGS += -flto
CONSOLE_ENABLE = no
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
COMBO_ENABLE = yes
WPM_ENABLE = no
RGBLIGHT_ENABLE = no        # Keyboard RGB underglow
RGB_MATRIX_ENABLE = no      # Disable RGB
LEADER_ENABLE = no
COMMAND_ENABLE = no         # Commands for debug and configuration
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
SLEEP_LED_ENABLE = no 

MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
UNICODE_ENABLE = yes        # Unicode
SPLIT_KEYBOARD = yes        # Use shared split_common code
TAP_DANCE_ENABLE = no

# SRC += oneshot.c
SRC += swapper.c