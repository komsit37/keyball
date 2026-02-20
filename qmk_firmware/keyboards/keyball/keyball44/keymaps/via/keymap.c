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
    EI_ALT_BSPC,
    HA_CTRL_A,
    AE_CAPS_WORD,
    XM_COPY,
    MC_PASTE,
    CV_UNDERSCORE,
    YH_MINUS,
    ENT_SPC_TG1,
    SH_TG2,
    COMBO_COUNT
};

const uint16_t PROGMEM ei_combo[]  = {RSFT_T(KC_E), RGUI_T(KC_I), COMBO_END};
const uint16_t PROGMEM ha_combo[]  = {LT(2, KC_H), LT(4, KC_A), COMBO_END};
const uint16_t PROGMEM ae_combo[]  = {LT(4, KC_A), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM xm_combo[]  = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM mc_combo[]  = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[]  = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM yh_combo[]  = {KC_Y, LT(2, KC_H), COMBO_END};
const uint16_t PROGMEM ent_spc_combo[] = {LT(1, KC_ENT), LT(1, KC_SPC), COMBO_END};
const uint16_t PROGMEM sh_combo[]  = {LT(2, KC_S), LT(2, KC_H), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [EI_ALT_BSPC] = COMBO(ei_combo, A(KC_BSPC)),
    [HA_CTRL_A]   = COMBO(ha_combo, C(KC_A)),
    [AE_CAPS_WORD]= COMBO(ae_combo, QK_CAPS_WORD_TOGGLE),
    [XM_COPY]     = COMBO(xm_combo, C(KC_C)),
    [MC_PASTE]    = COMBO(mc_combo, C(KC_V)),
    [CV_UNDERSCORE]= COMBO(cv_combo, S(KC_MINS)),
    [YH_MINUS]    = COMBO(yh_combo, KC_MINS),
    [ENT_SPC_TG1] = COMBO(ent_spc_combo, TG(1)),
    [SH_TG2]      = COMBO(sh_combo, TG(2)),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_UP   , KC_B          , LALT_T(KC_L)  , LCTL_T(KC_D)  , LGUI_T(KC_W)  , KC_Q     ,                                    KC_QUOT       , RGUI_T(KC_F)  , RCTL_T(KC_O)  , RALT_T(KC_U)  , KC_J     , KC_LBRC  ,
    LSFT_T(KC_DOWN), LGUI_T(KC_N)  , LSFT_T(KC_R)  , LT(4,KC_T)    , LT(2,KC_S)    , KC_G     ,                                    KC_Y          , LT(2,KC_H)    , LT(4,KC_A)    , RSFT_T(KC_E) , RGUI_T(KC_I) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_RBRC) ,
    LGUI_T(KC_GRV), KC_Z          , KC_X          , KC_M          , KC_C          , KC_V     ,                                    KC_K          , KC_P          , LT(3,KC_DOT)  , KC_SCLN  , KC_SLSH  , KC_ENT   ,
              KC_LEFT      , KC_RGHT       , LT(3,KC_TAB)   , LT(1,KC_ENT)   , LSFT_T(KC_ESC) ,                  LT(2,KC_BSPC), LT(1,KC_SPC) , KC_NO        , KC_NO    , QK_CAPS_WORD_TOGGLE
  ),

  [1] = LAYOUT_universal(
    _______ , _______      , _______       , _______       , _______       , _______       ,                                  RGUI(KC_GRV)   , _______       , RCTL_T(S(KC_9)), RALT_T(S(KC_9)), RCTL_T(KC_UP) , KC_HOME  ,
    _______ , _______      , LSFT_T(KC_GRV), KC_UP         , KC_ESC        , KC_HOME       ,                                  RGUI_T(KC_LBRC), KC_BTN1       , KC_UP         , RSFT_T(KC_BTN2), RGUI_T(KC_HOME), _______  ,
    _______ , KC_LALT      , KC_LEFT       , KC_DOWN       , KC_RGHT       , KC_END        ,                                  S(KC_1)        , KC_LEFT       , KC_DOWN       , KC_RGHT       , RALT_T(KC_END) , KC_END   ,
              _______      , _______       , _______       , _______       , KC_DEL        ,                  _______        , _______       , KC_NO         , KC_NO   , KC_RCTL
  ),

  [2] = LAYOUT_universal(
    _______ , S(KC_COMM) , S(KC_LBRC), S(KC_9)    , KC_LBRC      , S(KC_GRV) ,                                  S(KC_EQL)   , KC_7          , RCTL_T(KC_8) , RALT_T(KC_9) , S(KC_8)    , S(KC_MINS) ,
    _______ , S(KC_DOT)  , S(KC_RBRC), S(KC_0)    , KC_RBRC      , S(KC_BSLS),                                  KC_MINS     , KC_4          , KC_5         , RSFT_T(KC_6) , KC_EQL     , KC_MINS    ,
    _______ , S(KC_SLSH) , KC_BSLS   , S(KC_MINS) , KC_COMM      , KC_GRV    ,                                  KC_0        , KC_1          , KC_2         , KC_3         , KC_SLSH    , RSFT_T(KC_DOT),
              _______ , _______     , KC_BSPC    , _______      , _______   ,                  KC_COMM    , KC_DOT     , KC_NO         , KC_NO    , KC_COMM
  ),

  [3] = LAYOUT_universal(
    _______ , KC_F1        , KC_F2        , KC_F3        , KC_F4        , KC_F5        ,                                  KC_F6        , KC_F7        , KC_F8        , KC_F9        , KC_F10       , _______  ,
    _______ , KC_GRV       , LSFT_T(KC_P) , KC_P         , KC_QUOT      , KC_BSLS      ,                                  KC_VOLU      , KC_VOLD      , KC_QUOT      , KC_LBRC      , KC_RBRC      , _______  ,
    _______ , LGUI_T(KC_Z) , _______      , QK_MACRO_0   , QK_MACRO_1   , _______      ,                                  CPI_I100     , CPI_D100     , SCRL_DVD     , SCRL_DVI     , SCRL_DVD     , SCRL_DVI ,
              _______ , _______      , _______      , _______      , _______      ,                  KC_DEL       , KC_ENT       , KC_NO         , KC_NO    , AML_TO
  ),

  [4] = LAYOUT_universal(
    KC_Q      , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_B) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_L) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_D) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_W) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_Q) ,                                  _______      , S(KC_7)     , S(KC_8)     , S(KC_BSLS) , _______  , _______  ,
    KC_A      , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       ,                                  _______      , S(KC_4)     , S(KC_5)     , S(KC_6)     , S(KC_SCLN) , _______  ,
    RGB_RMOD , RGB_HUD    , RGB_SAD    , RGB_VAD    , _______    , _______    ,                                  _______      , S(KC_1)     , S(KC_2)     , S(KC_3)     , _______    , _______  ,
              QK_BOOT  , _______    , KC_TAB     , KC_SPC     , _______    ,                  _______      , _______    , KC_NO         , KC_NO    , TO(0)
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
