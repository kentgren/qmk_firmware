// Start normal Keymap File
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum ferris_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _SYS
};

const uint16_t PROGMEM backspace[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM del_word[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM enter[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM semicolon[] = {KC_L, KC_QUOT, COMBO_END};
const uint16_t PROGMEM cap_word_combo[] = {KC_Z, KC_SLSH, COMBO_END};
const uint16_t PROGMEM escape[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
	COMBO(backspace, KC_BSPC),
  COMBO(del_word, LALT(KC_BSPC)),
  COMBO(enter, KC_ENT),
  COMBO(semicolon, KC_SCLN),
  COMBO(cap_word_combo, CW_TOGG),
  COMBO(escape, KC_ESC)
};

#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)

// Custom Tap/Hold Behavior
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,KC_ENT):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_ENT)); // Intercept hold function to send Shift-Enter
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
    }
    return true;
}


// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* QWERTY */
    KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
    KC_A,         KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,  KC_K,    KC_L,   KC_QUOT,
    KC_Z,  	      KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH,
                                LT(1, KC_GRV),  KC_SPC,    LT(0, KC_ENT), LT(2, KC_BSPC)
  ),

  [_LOWER] = LAYOUT( /* [> LOWER <] */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TAB, OSM_CTL, OSM_ALT, OSM_GUI, KC_MINS,          KC_EQL, KC_LPRN, KC_RPRN,   KC_LBRC, KC_RBRC,
    G(KC_Z), G(KC_X), G(KC_C), G(KC_V), G(KC_B),         KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS, KC_SLSH,
                                    KC_TRNS, KC_TRNS, KC_TRNS, LT(3, KC_BSPC)  
  ),

  [_RAISE] = LAYOUT( /* [> RAISE <] */
    KC_NO,   KC_BTN2,KC_MS_UP,KC_BTN1,  KC_NO,            LSA(KC_LEFT),A(KC_LEFT),A(KC_RGHT),LSA(KC_RGHT),KC_NO,
    KC_NO,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT, KC_NO,       KC_LEFT     ,KC_DOWN   ,KC_UP     ,KC_RGHT ,S(KC_F10),
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_HOME     ,KC_PGDN   ,KC_PGUP   ,KC_END, KC_NO,
                                    LT(3, KC_GRV), KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_SYS] = LAYOUT( /* [> SYS <] */
    KC_SLEP,XXXXXXX,KC_BRID,KC_BRIU,KC_VOLU,           KC_F12,KC_F7,KC_F8,KC_F9, XXXXXXX,
    OSM_SFT,OSM_CTL,OSM_ALT,OSM_GUI,KC_VOLD,           KC_F11,KC_F4,KC_F5,KC_F6, XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_MUTE,           KC_F10,KC_F1,KC_F2,KC_F3, XXXXXXX,
                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};