#include QMK_KEYBOARD_H

// FIRST PART TAP DACE
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
//  TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance declarations
enum {
    TD_SPC_ENT = 0,
    TD_NUM_CAD
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Space, twice for Enter
    [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
};

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
//void ql_reset(qk_tap_dance_state_t *state, void *user_data);
// End of Tap Dance declarations

// LAYOUT
enum layer_number {
  _QWERTY = 0,
  _NUMPAD = 1
  _CAD = 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| PLAY  |    |  DEL  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | CAPS | NUMP | / Space /       \Enter \  |BackSP| RGUI |QWERTY|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,   KC_DEL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        KC_LALT, KC_CAPS, TT(_NUMPAD), KC_SPC,  KC_ENT,  KC_BSPC, KC_RGUI, TO(_QWERTY)
),
/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |      |   /  |   *  |   -  |PRINTS| HOME |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |                    |      |   7  |   8  |   9  |   +  | P_UP |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |  UP  |      |      |-------.    ,-------|      |   4  |   5  |   6  |   =  | P_DN |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | LEFT | DOWN | RGHT |      |-------|    |-------|   0  |   1  |   2  |   3  |   .  | END  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | CAPS |QWERTY| / Space /       \Enter \  |BackSP| RGUI |QWERTY|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_NUMPAD] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       _______, KC_PSLS, KC_PAST, KC_PMNS, KC_PSCR, KC_HOME,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                      _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PGUP,
  _______, _______, _______, KC_UP,   _______, _______,                     _______, KC_P4,   KC_P5,   KC_P6,   KC_PEQL, KC_PGDN,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,  _______, _______,  KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_END,
                         _______, _______, TO(_QWERTY),  _______, _______,  _______, _______, KC_TRNS
),
/* CAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |      |   /  |   *  |   -  |PRINTS| HOME |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |                    |      |   7  |   8  |   9  |   +  | P_UP |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   +  |  UP  |   -  |   M  |-------.    ,-------|      |   4  |   5  |   6  |   =  | P_DN |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | LEFT | DOWN | RGHT |   C  |-------|    |-------|   0  |   1  |   2  |   3  |   .  | END  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | CAPS |QWERTY| / Space /       \Enter \  |BackSP| RGUI |QWERTY|
 *                   |      |      |      |/  Enter/         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_CAD] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        _______, KC_PSLS, KC_PAST, KC_PMNS, KC_PSCR, KC_HOME,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                        _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PGUP,
  _______, _______, KC_PPLS, KC_UP,   KC_PMNS, KC_M,                        _______, KC_P4,   KC_P5,   KC_P6,   KC_PEQL, KC_PGDN,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_C,     _______, _______,  KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_END,
                 _______, _______, TO(_QWERTY),  TD(TD_SPC_ENT),  _______,  _______, _______, KC_TRNS
)
};
// END OF LAYOUT

// SECOND PART TAP DANCE
// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NUMPAD)) {
                // If already set, then switch it off
                layer_off(_NUMPAD;
            } else {
                // If not already set, then switch the layer on
                layer_on(_NUMPAD);
            }
            break;
      //case TD_SINGLE_HOLD:
      //    layer_on(_NUMPAD);
      //    break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_CAD)) {
                // If already set, then switch it off
                layer_off(_CAD);
            } else {
                // If not already set, then switch the layer on
                layer_on(_CAD);
            }
            break;
        default:
            break;
    }
}

/* void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_MY_LAYER);
    }
    ql_tap_state.state = TD_NONE;
} */

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_NUM_CAD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, NULL, 275)
};
// END OF TAP DANCE

// START OF OLED
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return (rotation);
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case _CAD:
            oled_write_P(PSTR("CAD\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        //oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPSLOCK ") : PSTR("       "), false);
        //oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
        oled_write_P(PSTR("              Owner: vincuit\n\n"), false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status(); //Renders the current keyboard state (layer, lock, caps, scroll, etc.)
  } else {
    render_qmk_logo(); //Renders QMK logo
  }
  return false;
}
#endif
// END OF OLED

// START OF ENCODER
/* The encoder_update_user is a function.
 * It'll be called by QMK every time you turn the encoder.
 *
 * The index parameter tells you which encoder was turned. If you only have
 * one encoder, the index will always be zero.
 * 
 * The clockwise parameter tells you the direction of the encoder. It'll be
 * true when you turned the encoder clockwise, and false otherwise.
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
  /* With an if statement we can check which encoder was turned. */
  if (index == 0) { /* First encoder */
  /*  if (clockwise) {
    tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
  }*/
  if(IS_LAYER_ON(_NUMPAD)) { // on Numpad layer control volume
    if (clockwise){
      tap_code(KC_VOLU);
    } else{
      tap_code(KC_VOLD);
    }        
  } else { // on other layers emulate mouse scrollwheel
    if (clockwise){
      tap_code(KC_MS_WH_DOWN);
    } else{
      tap_code(KC_MS_WH_UP);
    }
  }
  return false;
}
// END OF ENCODER
