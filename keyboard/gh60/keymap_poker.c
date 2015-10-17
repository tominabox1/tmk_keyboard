#include "keymap_common.h"
#include "backlight.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: colemak 
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Caps  |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Backsp|  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '| Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Opt |Cmd  |       Space/Fn0        |Cmd   |Fn4 |Fn1  |
     * `-----------------------------------------------------------'
     */
    KEYMAP(ESC,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, CAPS,      \
           TAB,  Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN, LBRC,RBRC,BSLS,      \
           BSPC, A,   R,   S,   T,   D,   H,   N,   E,   I,   O,QUOT,ENT,            \
                      Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,RSFT,          \
           LCTL, LSFT,LALT,LGUI,           FN0,                     RGUI,FN2,FN1),

    /* 1: colemak 
     * ,-----------------------------------------------------------.
     * |`  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|  -|  =| Caps  |
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |    |   |   |PgUp|Up|PgDn|  |  |   |     |
     * |-----------------------------------------------------------|
     * |Del   |    |   |    |   |   |   |Left|Down|Right|  |  |    |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |   |   |   |   |   |          |
     * |-----------------------------------------------------------|
     * |Ctrl |Opt |Cmd  |       Space/Fn0        |Cmd   |Fn4 |Fn1  |
     * `-----------------------------------------------------------'
     */
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, MINS,EQL, CAPS,      \
           TAB,  NO,  NO,   NO,   FN3,   NO,  NO, PGUP,  UP,PGDN,    NO,NO,NO,NO,      \
           DEL, NO,   NO,   NO,   NO,   NO,   NO, LEFT,DOWN,RGHT, NO,NO,      NO,            \
                      NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,NO, NO,NO,          \
           LCTL, LSFT,LALT,LGUI,           FN0,                     FN4,FN2,FN1),

    /* 2: Gaming/QWERTY
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Caps  |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ |
     * |-----------------------------------------------------------|
     * |Backsp|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     
     * |-----------------------------------------------------------|
     * |Ctrl |Opt |Cmd  |       Space            |Cmd   |Opt |Fn1  |
     * `-----------------------------------------------------------'
     */
    KEYMAP(ESC,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0, MINS,EQL, CAPS,      \
           TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P, LBRC,RBRC,BSLS,      \
           BSPC, A,   S,   D,   F,  G,   H,   J,   K,   L,   SCLN,QUOT,ENT,            \
                      Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,          \
           LCTL, LSFT,LALT,LGUI,           SPC,                     RGUI,RALT,FN1),

    /* 3: Numpad
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Caps  |
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |   |   7|  8|  9|  +|   |  |   \ |
     * |-----------------------------------------------------------|
     * |Backsp|   |   |   |   |   |   |  4|  5|  6|  +|  '| Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |   |  1|  2|  3|  /|Shift     |     
     * |-----------------------------------------------------------|
     * |Ctrl |Opt |Cmd  |          0             |.     |Opt |Fn1  |
     * `-----------------------------------------------------------'
     */
    KEYMAP(ESC,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0, MINS,EQL, CAPS,      \
           TAB,  NO,   NO,  NO,  NO,   NO,   NO,   7,   8,   9,   PMNS, LBRC,RBRC,BSLS,      \
           BSPC, NO,   NO,   NO,   NO,  NO,   NO,   4,   5,   6,   PPLS,QUOT,ENT,            \
                      NO,   NO,   NO,   NO,   NO,   NO,   1,   2,3, SLSH,RSFT,          \
           LCTL, LSFT,LALT,LGUI,           FN6,                     DOT,FN2,FN1),

};

enum macro_id {
    AIDS,
    PRISM,
};


const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(1, KC_SPC),              // FN0
    [1] = ACTION_LAYER_MOMENTARY(2),                    // Activates directional layer
    [2] = ACTION_LAYER_TOGGLE(3),			   // Activates numpad layer
    [3] = ACTION_LAYER_MOMENTARY(1),			   // Same as FN0 but does not send space on tap
    [4] = ACTION_BACKLIGHT_STEP(),			   // FN5 toggles backlight
    [5] = ACTION_LAYER_TOGGLE(0),			   // Toggles back to Default Layer 0
    [6] = ACTION_LAYER_TAP_KEY(1, KC_0),                // FN0 or 0
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    //uint8_t tap_count = record->tap_count;

    switch (id) {
        case AIDS:
            return (event.pressed ?
                   MACRO(T(A), T(I), T(D), T(S), END ) :
                    MACRO( END ) );
      case PRISM:
            return (event.pressed ?
                   MACRO(T(SLSH), T(P), T(R), T(I), T(S), T(M), T(SPC), END ) :
                    MACRO( END ) );
     
    }
    return MACRO_NONE;
};
