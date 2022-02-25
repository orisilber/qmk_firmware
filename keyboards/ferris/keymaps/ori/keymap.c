#include QMK_KEYBOARD_H

// #include "oneshot.h"
#include "swapper.h"

#define LMOD MO(_LMOD)
#define RMOD MO(_RMOD)
#define TG_MOUS TG(_MOUS)

// Left-hand home row mods
#define HOME_A LSFT_T(KC_A)
#define HOME_S LCTL_T(KC_S)
#define HOME_D LALT_T(KC_D)
#define HOME_F LGUI_T(KC_F)

// Right-hand home row mods
#define HOME_J RGUI_T(KC_J)
#define HOME_K LALT_T(KC_K)
#define HOME_L RCTL_T(KC_L)
#define HOME_SCLN RSFT_T(KC_SCLN)

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    // OS_SHFT = SAFE_RANGE,
    // OS_CTRL,
    // OS_ALT,
    // OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

enum ferris_layers {
  _BASE,
  _LMOD,
  _RMOD,
  _SYST,
  _MOUS,
};

enum ferris_chords {
  CHORD_ENTER,
  CHORD_TAB,
  CHORD_CAPS
};

const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM xcv_combo[] = {KC_X, KC_C ,KC_V, COMBO_END};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Base Layer */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y, KC_U,   KC_I,    KC_O,   KC_P,
    HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,            KC_H, HOME_J, HOME_K,  HOME_L, HOME_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N, KC_M,   KC_COMM, KC_DOT, KC_SLSH,
                                     LMOD, KC_SPC, KC_BSPC, RMOD
  ),

  [_LMOD] = LAYOUT( /* Left Mods */
    KC_ESC,  KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_7, KC_8, KC_9, KC_GRV,
    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,         XXXXXXX, KC_4, KC_5, KC_6, KC_QUOT,
    KC_F2,   KC_F3,   KC_F5,   KC_F11,  KC_F12,          XXXXXXX, KC_1, KC_2, KC_3, KC_0,
                                    _______, _______, _______, _______  
  ),

  [_RMOD] = LAYOUT( /* Right Mods */
    KC_EXLM, KC_EQL,  KC_LPRN, KC_RPRN, KC_AMPR,         XXXXXXX, KC_MINS, KC_PPLS, KC_PAST, KC_BSLS,
    KC_AT,   KC_HASH, KC_LBRC, KC_RBRC, KC_PIPE,         XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
    KC_DLR,  KC_PERC, KC_LCBR, KC_RCBR, KC_CIRC,         XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH,
                                   _______, _______, _______, _______  
  ),
  
  [_SYST] = LAYOUT( /* [> System Commands <] */
    KC_HOME, KC_END,  KC_UP,   KC_END,  KC_PGUP,         SW_WIN,  XXXXXXX, XXXXXXX, XXXXXXX, TG_MOUS,
    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,         SW_LANG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
    KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _______, _______, _______, _______  
  ),

  [_MOUS] = LAYOUT( /* [> Mouse <] */
    TG_MOUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_BTN1, KC_MS_U, KC_TRNS, KC_WH_U,
    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,         XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
    XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX,         XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, TG_MOUS,
                                    TG_MOUS, _______, _______, TG_MOUS  
  )
};

// Combos defenitions
combo_t key_combos[COMBO_COUNT] = {
  [CHORD_ENTER] = COMBO(op_combo, KC_ENT),
  [CHORD_TAB] = COMBO(qw_combo, KC_TAB),
  [CHORD_CAPS] = COMBO(xcv_combo, KC_CAPS)
};


// ONE SHOT CONFIGS
// bool is_oneshot_cancel_key(uint16_t keycode) {
//     switch (keycode) {
//     case LMOD:
//     case RMOD:
//     case TG_MOUS:
//         return true;
//     default:
//         return false;
//     }
// }

// bool is_oneshot_ignored_key(uint16_t keycode) {
//     switch (keycode) {
//       case LMOD:
//       case RMOD:
//       case KC_LSFT:
//       case OS_SHFT:
//       case OS_CTRL:
//       case OS_ALT:
//       case OS_CMD:
//         return true;
//     default:
//         return false;
//     }
// }

bool sw_win_active = false;
bool sw_lang_active = false;

// oneshot_state os_shft_state = os_up_unqueued;
// oneshot_state os_ctrl_state = os_up_unqueued;
// oneshot_state os_alt_state = os_up_unqueued;
// oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    // update_oneshot(
    //     &os_shft_state, KC_LSFT, OS_SHFT,
    //     keycode, record
    // );
    // update_oneshot(
    //     &os_ctrl_state, KC_LCTL, OS_CTRL,
    //     keycode, record
    // );
    // update_oneshot(
    //     &os_alt_state, KC_LALT, OS_ALT,
    //     keycode, record
    // );
    // update_oneshot(
    //     &os_cmd_state, KC_LCMD, OS_CMD,
    //     keycode, record
    // );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LMOD, _RMOD, _SYST);
}