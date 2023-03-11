#include QMK_KEYBOARD_H

// Layers
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _SYS 3
#define _WASD 4
#define _COLEMAK_DH 5

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SYS MO(_SYS)
#define WASD MO(_WASD)

#define MCTL_EX MT(MOD_LCTL, KC_ESC)
#define LALT_BK LALT_T(KC_BSPC)

#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)

const uint16_t PROGMEM backspace[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM del_word[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM enter[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM semicolon[] = {KC_L, KC_QUOT, COMBO_END};
const uint16_t PROGMEM cap_word_combo[] = {KC_Z, KC_SLSH, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(backspace, KC_BSPC),
    COMBO(del_word, LCTL(KC_BSPC)),
    COMBO(enter, KC_ENT),
    COMBO(semicolon, KC_SCLN),
    COMBO(cap_word_combo, CW_TOGG)
};

// Disabled Auto-shift on Gaming layer
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
      case _WASD:
          autoshift_disable();
          break;
      default:
          autoshift_enable();
          break;
      }
  return state;
}

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
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_QUOT,KC_SCLN,
        MCTL_EX, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH, KC_EQL,
                        KC_LGUI,KC_RBRC,                                                        KC_BSLS, KC_GRV,
                                        KC_GRV   , LT(LOWER, KC_SPC),             LT(0, KC_ENT), LT(RAISE, KC_BSPC) ,
                                        KC_LGUI,LALT_BK,                        KC_LSFT,XXXXXXX,
                                        XXXXXXX,TG(_WASD),                        TG(_COLEMAK_DH),XXXXXXX
    ),    

    [_WASD] = LAYOUT_5x6(
        KC_ESC , KC_ESC, KC_2  , KC_3  , KC_3  , KC_T  ,                      TG(_WASD),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_BSPC,
        KC_TAB , KC_1  , KC_Q  , KC_W  , KC_E  , KC_R  ,                        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        KC_G   ,KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  ,                        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        KC_B   ,KC_LCTL,KC_Z   , KC_X  , KC_C  , KC_V  ,                        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                        KC_N  , KC_M  ,                                                         XXXXXXX, XXXXXXX,
                                         KC_ENT  , KC_SPC,                         XXXXXXX,XXXXXXX,
                                         KC_Y  ,KC_LALT,                        XXXXXXX,XXXXXXX,
                                        XXXXXXX,TG(_WASD),                        XXXXXXX,XXXXXXX
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                   KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN ,    QK_BOOT,
        XXXXXXX,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        XXXXXXX,KC_TAB, OSM_CTL, OSM_ALT, OSM_GUI, KC_MINS,                KC_EQL, KC_LPRN, KC_RPRN,  KC_LBRC, KC_RBRC, XXXXXXX,
        XXXXXXX,C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B),               KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS, KC_SLSH, XXXXXXX,
                        XXXXXXX,XXXXXXX,                                                        XXXXXXX, XXXXXXX,
                                                KC_GRV,KC_SPC,              KC_ENT,SYS,
                                                XXXXXXX,KC_BSPC,            XXXXXXX,XXXXXXX,
                                                XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX

    ),

    [_RAISE] = LAYOUT_5x6(
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,XXXXXXX,KC_BTN2,KC_MS_UP,KC_BTN1,XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
        XXXXXXX,XXXXXXX,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,XXXXXXX,             KC_LEFT, KC_DOWN,KC_UP,KC_RIGHT,S(KC_F10),XXXXXXX,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                       LSA(KC_LEFT),A(KC_LEFT),A(KC_RGHT), LSA(KC_RGHT),XXXXXXX,XXXXXXX,
                        XXXXXXX,KC_MUTE,                                                        KC_VOLD ,KC_VOLU,
                                                  XXXXXXX, SYS,            XXXXXXX,KC_TRNS,
                                                  XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX,
                                                  XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX
    ),


    [_SYS] = LAYOUT_5x6(
       QK_BOOT,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                        TG(_WASD),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
       XXXXXXX,KC_F12,KC_F7,KC_F8,KC_F9,KC_VOLU,                        XXXXXXX,KC_BTN4,KC_WH_U,KC_BTN5,KC_PSCR,XXXXXXX,
       XXXXXXX,KC_F11,KC_F4,KC_F5,KC_F6,KC_VOLD,                        XXXXXXX,KC_BTN1,KC_BTN3,KC_BTN2,XXXXXXX,XXXXXXX,
       XXXXXXX,KC_F10,KC_F1,KC_F2,KC_F3,KC_MUTE,                        XXXXXXX,KC_WH_L,KC_WH_D,KC_WH_R,XXXXXXX,XXXXXXX,
                       XXXXXXX,XXXXXXX,                                                        XXXXXXX, XXXXXXX,
                                             XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX,
                                             XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX,
                                             XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX
    ),

    [_COLEMAK_DH] = LAYOUT_5x6(
  /* COLEMAK_DH
   * .-----------------------------------------.                                  .-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  Bsp |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |                                  |   J  |   L  |   U  |   Y  |   ;  |  \   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Del  |   A  |R /CTL|S /ALT|T /CMD|   G  |                                  |   M  |N /CMD|E /ALT|I /CTL|   O  |  '   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Shft |   Z  |   X  |   C  |   D  |   V  |                                  |   K  |   H  |   ,  |   .  |   /  | Shft |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    / RAISE /---------------.    .---------------\ LOWER \    |      |      |
   *               |      |      |   /       / Space / Enter /      \ Enter \ Space \       \   |      |      |
   *               '-------------'  '-------/ Shift / Shift /        \ Shift \ Shift \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /   =   / Home  /            \  End  \   -   \
   *                                     /   +   /       /              \       \   _   \
   *                                    '---------------'                '---------------'
   */
   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
   KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                                     KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSLS,
   KC_DEL , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   ,                                     KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     KC_LBRC,KC_RBRC,                                                        KC_BSLS, KC_GRV,
                                        KC_BSPC , KC_SPC,             KC_ENT, KC_BSPC,
                                        KC_LGUI,LALT_BK,               KC_LSFT,XXXXXXX,
                                        XXXXXXX,XXXXXXX,            TG(_COLEMAK_DH),XXXXXXX
   ),
};
