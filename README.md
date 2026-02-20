# My Keyball Custom

created: 2025-04-03
# Instructions

## Setup
follow https://github.com/Yowkees/keyball/blob/main/qmk_firmware/keyboards/keyball/readme.md
- need to dowload and build avrdude 7.3 manually (8.0 in brew is not compatible)

## Build
```bash
make SKIP_GIT=yes keyball/keyball44:via
```

## Flash
```bash
qmk flash -kb keyball/keyball44 -km via
```
double press reset button to detect

# Custom
## Disable RGB
to free up ROM space
rules.mk
```scala
RGBLIGHT_ENABLE = no
```

## Increase layer
config.h
```c
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
```
Add layer 5 in keymap.c
 
## Enable CAP words
rules.mk
```scala
CAPS_WORD_ENABLE = yes
```

## Settings for homerow mods
recommended here https://getreuer.info/posts/keyboards/faqs/index.html#home-row-mods-are-hard-to-use
config.h
```c
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY
#define CHORDAL_HOLD
```
keymap.c
```c
// Finger-based tapping terms
// pinky: N/I = 160
// ring: L/U/R = 152, E = 160
// middle: D/T/A = 145, O = 153
// index: S/H/W/F = 138
```

## Update 2026-02-20
Keymap refresh for current daily usage and combo-heavy text navigation/editing.
- Layer 0: shift-hold moved from `;` to `E`.
- Layer 2: symbol row adjusted (`@/#` changed to `2/3` on the base positions).
- Layer 1-4: synced to current cheat sheet (navigation, symbols, function/media, RGB/boot).
- Combos enabled with `COMBO_ALLOW_ACTION_KEYS`, `COMBO_ONLY_FROM_LAYER 0`, and `COMBO_MUST_TAP_PER_COMBO` in `config.h`, plus `COMBO_ENABLE = yes` in `rules.mk`.
- Telemetry build is currently enabled with `#define KEYBALL_STATS_ENABLE` in `config.h` and `CONSOLE_ENABLE = yes` in `rules.mk`.
- OLED is disabled in telemetry profile (`OLED_ENABLE = no`) to fit firmware size.
- Stats dump key: layer 3, row 3 col 0 (`STATS_DUMP`).
- Telemetry tracks per-key tap/hold/interrupted counts and average tap/hold ms for: `L D W F O U N R E I T S H A`, plus combo trigger counts.
- Read stats with `qmk console` after pressing dump key.
- Active combos:
  - `E+I` -> `Alt+Backspace`
  - `H+A` -> `Ctrl+A`
  - `A+E` -> `Caps Word Toggle`
  - `X+M` -> `Cmd+C`
  - `M+C` -> `Cmd+V`
  - `C+V` -> `_`
  - `Y+H` -> `Alt+Left`
  - `K+P` -> `-`
  - `N+R` -> `Alt+Delete`
  - `S+G` -> `Alt+Right`
  - `.+;` -> `:`
  - `Enter+Space` -> `TG(1)`
  - `/+Enter` -> `TG(5)` (Excel layer)

## Tuning Workflow
Use this loop to tune tapping terms and hold behavior.
1. Build and flash telemetry profile:
```bash
make SKIP_GIT=yes keyball/keyball44:via
qmk flash -kb keyball/keyball44 -km via
```
2. Open console:
```bash
qmk console
```
3. Type real text and shortcuts for 5-15 minutes, including known failure patterns.
4. Press stats dump key (layer 3, row 3 col 0).
5. Capture `KBST` output lines:
   - `Kx,presses,taps,holds,interrupted,tap_avg_ms,hold_avg_ms,tap_pct`
   - `Cx,count`
6. Tune rules:
   - If accidental holds are high on a key, increase its tapping term by 5-10 ms.
   - If intentional holds feel hard, decrease by 5-10 ms.
   - Prioritize high-frequency keys first (`presses` large).
7. Rebuild, flash, and repeat until error patterns stabilize.

------------------------------------------------------------------------------------------------

# Original README

# Keyball Series

![Keyball61](./keyball61/doc/rev1/images/kb61_001.jpg)

Keyball series is keyboard family which have 100% track ball.

Keyboards in the family are:

* Available
    * Keyball39: split + 39 keys + a track ball
    * Keyball44: split + 44 keys + a track ball
    * Keyball61: split + 61 keys + a track ball
* Unavailable
    * Keyball46 (first one!)
    * One47

## Where to Buy

|Keyboard   |Yushakobo / 遊舎工房                       |Shirogane Lab / 白金ラボ                                   |
|-----------|-------------------------------------------|-----------------------------------------------------------|
|Keyball39  |<https://shop.yushakobo.jp/products/5357>  |<https://shirogane-lab.net/items/64b8f8693ee3fd0045280190> |
|Keyball44  |<https://shop.yushakobo.jp/products/8337>  |<https://shirogane-lab.net/items/64b7a006eb6dbe00346cd0c5> |
|Keyball61  |<https://shop.yushakobo.jp/products/5358>  |<https://shirogane-lab.net/items/64b8ed191435c1002bc4cd30> |

## Build Guide

*   Keyball39:
    [English/英語](/keyball39/doc/rev1/buildguide_en.md),
    [日本語/Japanese (ピンヘッダ版)](./keyball39/doc/rev1/buildguide_jp.md),
    [日本語/Japanese (コンスルー版)](./keyball39/doc/rev1/buildguide_jp_conth.md)
*   Keyball44: ~~English/英語~~ (Sorry, unavailable),
    [日本語/Japanese (ピンヘッダ版)](./keyball44/doc/rev1/buildguide_jp.md),
    [日本語/Japanese (コンスルー版)](./keyball44/doc/rev1/buildguide_jp_conth.md)
*   Keyball46:
    [English/英語](./keyball46/doc/rev1/buildguide_en.md),
    [日本語/Japanese](./keyball46/doc/rev1/buildguide_jp.md)
*   Keyball61:
    [English/英語](./keyball61/doc/rev1/buildguide_en.md),
    [日本語/Japanese (ピンヘッダ版)](./keyball61/doc/rev1/buildguide_jp.md),
    [日本語/Japanese (コンスルー版)](./keyball61/doc/rev1/buildguide_jp_conth.md)

## Firmware

See [document for firmware source code](./qmk_firmware/keyboards/keyball/readme.md).

### Pre-compiled Firmwares

(TO BE DOCUMENTED)
