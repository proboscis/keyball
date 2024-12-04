/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

enum combo_events {
  SEND_WH,
};


const uint16_t PROGMEM yw_is_wh[] = {KC_Y, KC_W, COMBO_END};
const uint16_t PROGMEM jg_is_z[] = {KC_J, KC_G, COMBO_END};
const uint16_t PROGMEM gp_is_qu[] = {KC_G, KC_P, COMBO_END};
combo_t key_combos[] = {
    [SEND_WH] = COMBO_ACTION(yw_is_wh),
    COMBO(jg_is_z, KC_Z), 
    COMBO(gp_is_qu, KC_Q)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SEND_WH:
      if (pressed) {
        SEND_STRING("WH");
      }
      break;
  }
}


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
      KC_J     , KC_Z     , KC_G     , KC_Q           , KC_M      ,                 KC_P        , KC_V     , KC_SCLN  , KC_COLN  , KC_DOT   ,
      KC_R     , KC_S     , KC_N     , KC_D           , KC_B      ,                 KC_COMM     , KC_I     , KC_A     , KC_E     , KC_H     ,
      KC_X     , KC_F     , KC_L     , KC_C           , KC_K      ,                 KC_MINS     , KC_T     , KC_U     , KC_O     , KC_W     ,
      KC_LCTL  , KC_LGUI  , KC_LALT  , LSFT_T(KC_LNG2), KC_T      , LT(3,KC_LNG1) , LT(1,KC_SPC),KC_BSPC   ,LSFT_T(KC_LNG2),KC_RALT,KC_RGUI,KC_RSFT
    ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// enum custom_keycodes {
//   KC_MY_BTN1 = KEYBALL_SAFE_RANGE;
//   KC_MY_BTN2;
//   KC_MY_BTN3;
//   KC_MY_BTN4;
//   KC_MY_BTN5;
// };



// bool process_record_user(uint16_t keycode, keyrecord_t * record){
//   switch(keycode){
//     case KC_MY_BTN1:
//     case KC_MY_BTN2:
//     case KC_MY_BTN3:
//     case KC_MY_BTN4:
//     case KC_MY_BTN5:
//   }
// }
