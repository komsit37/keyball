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
#ifdef KEYBALL_STATS_ENABLE
#include "print.h"
#endif

enum combo_events {
    EI_ALT_RIGHT,
    DW_LPAREN,
    TS_RPAREN,
    QF_ALT_DEL,
    HA_CTRL_A,
    AE_ALT_LEFT,
    FO_CAPS_WORD,
    XM_COPY,
    ZX_QMARK,
    XC_PASTE,
    MC_COMMA,
    WQ_LBRC,
    P_DOT_MINUS,
    CV_UNDERSCORE,
    YH_ALT_BSPC,
    KP_UNDERSCORE,
    LD_LCBR,
    RT_RCBR,
    BL_LABK,
    DOT_SCLN_COMMA,
    NR_RABK,
    SG_RBRC,
    ENT_SPC_TG1,
    SH_TG2,
    COMBO_COUNT
};

#ifdef KEYBALL_STATS_ENABLE
enum custom_keycodes {
    STATS_DUMP = SAFE_RANGE,
};
#    define STATS_DUMP_KEY STATS_DUMP
#else
#    define STATS_DUMP_KEY _______
#endif

const uint16_t PROGMEM ei_combo[]  = {RSFT_T(KC_E), RGUI_T(KC_I), COMBO_END};
const uint16_t PROGMEM dw_combo[]  = {LCTL_T(KC_D), LGUI_T(KC_W), COMBO_END};
const uint16_t PROGMEM ts_combo[]  = {LT(4, KC_T), LT(2, KC_S), COMBO_END};
const uint16_t PROGMEM qf_combo[]  = {KC_QUOT, RGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM ha_combo[]  = {LT(2, KC_H), LT(4, KC_A), COMBO_END};
const uint16_t PROGMEM ae_combo[]  = {LT(4, KC_A), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM fo_combo[]  = {RGUI_T(KC_F), RCTL_T(KC_O), COMBO_END};
const uint16_t PROGMEM xm_combo[]  = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM zx_combo[]  = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[]  = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM mc_combo[]  = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM wq_combo[]  = {LGUI_T(KC_W), KC_Q, COMBO_END};
const uint16_t PROGMEM cv_combo[]  = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM yh_combo[]  = {KC_Y, LT(2, KC_H), COMBO_END};
const uint16_t PROGMEM kp_combo[]  = {KC_K, KC_P, COMBO_END};
const uint16_t PROGMEM ld_combo[]  = {LALT_T(KC_L), LCTL_T(KC_D), COMBO_END};
const uint16_t PROGMEM rt_combo[]  = {LSFT_T(KC_R), LT(4, KC_T), COMBO_END};
const uint16_t PROGMEM bl_combo[]  = {KC_B, LALT_T(KC_L), COMBO_END};
const uint16_t PROGMEM p_dot_combo[] = {KC_P, LT(3, KC_DOT), COMBO_END};
const uint16_t PROGMEM dot_scln_combo[] = {LT(3, KC_DOT), KC_SCLN, COMBO_END};
const uint16_t PROGMEM nr_combo[]  = {LGUI_T(KC_N), LSFT_T(KC_R), COMBO_END};
const uint16_t PROGMEM sg_combo[]  = {LT(2, KC_S), KC_G, COMBO_END};
const uint16_t PROGMEM ent_spc_combo[] = {LT(1, KC_ENT), LT(1, KC_SPC), COMBO_END};
const uint16_t PROGMEM sh_combo[]  = {KC_SLSH, KC_ENT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [EI_ALT_RIGHT] = COMBO(ei_combo, A(KC_RGHT)),
    [DW_LPAREN]   = COMBO(dw_combo, S(KC_9)),
    [TS_RPAREN]   = COMBO(ts_combo, S(KC_0)),
    [QF_ALT_DEL]  = COMBO(qf_combo, A(KC_DEL)),
    [HA_CTRL_A]   = COMBO(ha_combo, C(KC_A)),
    [AE_ALT_LEFT] = COMBO(ae_combo, A(KC_LEFT)),
    [FO_CAPS_WORD]= COMBO(fo_combo, QK_CAPS_WORD_TOGGLE),
    [XM_COPY]     = COMBO(xm_combo, LGUI(KC_C)),
    [ZX_QMARK]    = COMBO(zx_combo, S(KC_SLSH)),
    [XC_PASTE]    = COMBO(xc_combo, LGUI(KC_V)),
    [MC_COMMA]    = COMBO(mc_combo, KC_COMM),
    [WQ_LBRC]     = COMBO(wq_combo, KC_LBRC),
    [CV_UNDERSCORE]= COMBO(cv_combo, KC_GRV),
    [YH_ALT_BSPC] = COMBO(yh_combo, A(KC_BSPC)),
    [P_DOT_MINUS] = COMBO(p_dot_combo, KC_MINS),
    [KP_UNDERSCORE] = COMBO(kp_combo, S(KC_MINS)),
    [LD_LCBR]     = COMBO(ld_combo, S(KC_LBRC)),
    [RT_RCBR]     = COMBO(rt_combo, S(KC_RBRC)),
    [BL_LABK]     = COMBO(bl_combo, S(KC_COMM)),
    [DOT_SCLN_COMMA] = COMBO(dot_scln_combo, KC_COMM),
    [NR_RABK]     = COMBO(nr_combo, S(KC_DOT)),
    [SG_RBRC]     = COMBO(sg_combo, KC_RBRC),
    [ENT_SPC_TG1] = COMBO(ent_spc_combo, TG(1)),
    [SH_TG2]      = COMBO(sh_combo, TG(5)),
};

#ifdef KEYBALL_STATS_ENABLE
typedef struct {
    uint32_t presses;
    uint32_t taps;
    uint32_t holds;
    uint32_t interrupted;
    uint32_t tap_time_total;
    uint32_t hold_time_total;
    uint16_t press_timer;
    bool     pressed;
} dual_role_stat_t;

enum tracked_dual_role {
    TR_L,
    TR_D,
    TR_W,
    TR_F,
    TR_O,
    TR_U,
    TR_N,
    TR_R,
    TR_E,
    TR_I,
    TR_T,
    TR_S,
    TR_H,
    TR_A,
    TR_COUNT
};

static const uint16_t tracked_keycodes[TR_COUNT] = {
    LALT_T(KC_L),
    LCTL_T(KC_D),
    LGUI_T(KC_W),
    RGUI_T(KC_F),
    RCTL_T(KC_O),
    RALT_T(KC_U),
    LGUI_T(KC_N),
    LSFT_T(KC_R),
    RSFT_T(KC_E),
    RGUI_T(KC_I),
    LT(4, KC_T),
    LT(2, KC_S),
    LT(2, KC_H),
    LT(4, KC_A),
};

static dual_role_stat_t dual_role_stats[TR_COUNT];
static uint32_t         combo_triggers[COMBO_COUNT];

static int8_t tracked_index_from_keycode(uint16_t keycode) {
    for (uint8_t i = 0; i < TR_COUNT; i++) {
        if (tracked_keycodes[i] == keycode) {
            return i;
        }
    }
    return -1;
}

static void dump_dual_role_stats(void) {
    uprintf("\nKBST\n");
    for (uint8_t i = 0; i < TR_COUNT; i++) {
        dual_role_stat_t *s       = &dual_role_stats[i];
        uint32_t          tap_avg = s->taps ? (s->tap_time_total / s->taps) : 0;
        uint32_t          hold_avg = s->holds ? (s->hold_time_total / s->holds) : 0;
        uint32_t          tap_pct  = s->presses ? ((s->taps * 100U) / s->presses) : 0;
        uprintf("K%u,%lu,%lu,%lu,%lu,%lu,%lu,%lu\n", i, s->presses, s->taps, s->holds, s->interrupted, tap_avg, hold_avg, tap_pct);
    }
    for (uint8_t i = 0; i < COMBO_COUNT; i++) {
        uprintf("C%u,%lu\n", i, combo_triggers[i]);
    }
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed && combo_index < COMBO_COUNT) {
        combo_triggers[combo_index]++;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == STATS_DUMP && record->event.pressed) {
        dump_dual_role_stats();
        return false;
    }

    int8_t tracked = tracked_index_from_keycode(keycode);
    if (tracked < 0) {
        return true;
    }

    dual_role_stat_t *s = &dual_role_stats[tracked];
    if (record->event.pressed) {
        s->presses++;
        s->pressed     = true;
        s->press_timer = timer_read();
        return true;
    }

    if (s->pressed) {
        uint16_t elapsed = timer_elapsed(s->press_timer);
        if (elapsed == 0) {
            elapsed = 1;
        }
        if (record->tap.count > 0) {
            s->taps++;
            s->tap_time_total += elapsed;
        } else {
            s->holds++;
            s->hold_time_total += elapsed;
        }
        if (record->tap.interrupted) {
            s->interrupted++;
        }
        s->pressed = false;
    }

    return true;
}
#endif

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    // Finger-based tuning: index/middle tap faster, ring/pinky need slightly longer.
    const uint16_t INDEX_TERM  = 138; // S/H/W/F
    const uint16_t MIDDLE_TERM = 145; // D/O/T/A
    const uint16_t RING_TERM   = 152; // L/U/R/E
    const uint16_t PINKY_TERM  = 160; // N/I

    switch (keycode) {
        // Pinky
        case LGUI_T(KC_N):
        case RGUI_T(KC_I):
            return PINKY_TERM;

        // Ring
        case LALT_T(KC_L):
        case RALT_T(KC_U):
        case LSFT_T(KC_R):
            return RING_TERM;
        case RSFT_T(KC_E):
            return RING_TERM + 8;

        // Middle
        case LCTL_T(KC_D):
            return MIDDLE_TERM;
        case RCTL_T(KC_O):
            return MIDDLE_TERM + 8;
        case LT(4, KC_T):
        case LT(4, KC_A):
            return MIDDLE_TERM;

        // Index
        case LGUI_T(KC_W):
        case RGUI_T(KC_F):
        case LT(2, KC_S):
        case LT(2, KC_H):
            return INDEX_TERM;
    }

    return TAPPING_TERM;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_UP   , KC_B          , LALT_T(KC_L)  , LCTL_T(KC_D)  , LGUI_T(KC_W)  , KC_Q     ,                                    KC_QUOT       , RGUI_T(KC_F)  , RCTL_T(KC_O)  , RALT_T(KC_U)  , KC_J     , KC_LBRC  ,
    LSFT_T(KC_DOWN), LGUI_T(KC_N)  , LSFT_T(KC_R)  , LT(4,KC_T)    , LT(2,KC_S)    , KC_G     ,                                    KC_Y          , LT(2,KC_H)    , LT(4,KC_A)    , RSFT_T(KC_E) , RGUI_T(KC_I) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_RBRC) ,
    LGUI(KC_GRV), KC_Z     , KC_X          , KC_M          , KC_C          , KC_V     ,                                    KC_K          , KC_P          , LT(3,KC_DOT)  , KC_SCLN  , KC_SLSH  , KC_ENT   ,
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
              STATS_DUMP_KEY, _______      , _______      , _______      , _______      ,                  KC_DEL       , KC_ENT       , KC_NO         , KC_NO    , AML_TO
  ),

  [4] = LAYOUT_universal(
    KC_Q      , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_B) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_L) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_D) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_W) , MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_Q) ,                                  _______      , S(KC_7)     , S(KC_8)     , S(KC_BSLS) , _______  , _______  ,
    KC_A      , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       ,                                  _______      , S(KC_4)     , S(KC_5)     , S(KC_6)     , S(KC_SCLN) , _______  ,
    RGB_RMOD , RGB_HUD    , RGB_SAD    , RGB_VAD    , _______    , _______    ,                                  _______      , S(KC_1)     , S(KC_2)     , S(KC_3)     , _______    , _______  ,
              QK_BOOT  , _______    , KC_TAB     , KC_SPC     , _______    ,                  _______      , _______    , KC_NO         , KC_NO    , TO(0)
  ),

  // Excel / spreadsheet layer
  [5] = LAYOUT_universal(
    KC_ESC      , LGUI(KC_Z) , LGUI(KC_Y) , LGUI(KC_C) , LGUI(KC_V) , LGUI(KC_S) ,                                 S(KC_EQL) , KC_7     , KC_8    , KC_9    , S(KC_8)  , KC_MINS  ,
    KC_TAB      , LSFT(KC_TAB), KC_F2      , KC_UP      , KC_ENT     , KC_HOME    ,                                 KC_MINS   , KC_4     , KC_5    , KC_6    , KC_EQL   , KC_MINS  ,
    KC_DEL      , LGUI(KC_D) , KC_LEFT    , KC_DOWN    , KC_RGHT    , KC_END     ,                                 KC_0      , KC_1     , KC_2    , KC_3    , KC_SLSH  , KC_DOT   ,
                  KC_PGUP     , KC_PGDN    , KC_LSFT    , TO(0)      , KC_SPC     ,                  KC_COMM   , KC_DOT   , KC_BSPC      , KC_ENT  , TO(0)
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
