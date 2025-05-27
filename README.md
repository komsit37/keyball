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
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
```
Add layer 4 in keymap.c
 
## Enable CAP words
rules.mk
```scala
CAPS_WORD_ENABLE = yes
```

## Settings for homerow mods
recommended here https://getreuer.info/posts/keyboards/faqs/index.html#home-row-mods-are-hard-to-use
config.h
```c
#define TAPPING_TERM 200
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD
```


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
