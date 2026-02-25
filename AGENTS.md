# Agent Runtime Notes

Purpose: session-resume context for QMK Keyball44 tuning tasks.

## Startup Rule
At the beginning of each new helper session:
1. Read `qmk_helper_skills.md`.
2. Read this file (`agent.md`).
3. Verify current firmware files still match documented assumptions:
   - `qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c`
   - `qmk_firmware/keyboards/keyball/keyball44/keymaps/via/config.h`
   - `qmk_firmware/keyboards/keyball/keyball44/keymaps/via/rules.mk`

## Required Maintenance
After every meaningful change, update:
1. `qmk_helper_skills.md`
   - Current behavior
   - Build profile (telemetry on/off)
   - Any mapping/tuning deltas
   - Known issues and fixes
2. `agent.md`
   - Append a one-line entry to Task Log
   - Append/update Knowledge section if new reusable insight appears

## Task Log
- 2026-02-20: Added Keyball44 combo set and updated layer toggles (`TG(1)`, `TG(5)`).
- 2026-02-20: Added Excel-focused layer 5 while preserving left-arrow and right-number muscle memory positions.
- 2026-02-20: Tuned home-row/layer behavior (`CHORDAL_HOLD`, no `PERMISSIVE_HOLD`, per-key tapping terms).
- 2026-02-20: Implemented telemetry stats dump (`STATS_DUMP`) and `qmk console` output for tuning.
- 2026-02-20: Reduced flash pressure (LTO, telemetry string compression, `OLED_ENABLE = no` in telemetry profile).
- 2026-02-20: Patched `keyball.c` for non-OLED build compatibility.
- 2026-02-24: Set combo `C+M` to comma; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Set paste combo to `X+C`; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Added combos `P+.` -> `-`, `K+P` -> `_`, `.+;` -> `,`; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Set combo `C+V` to backtick; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Added bracket/paren combos and repurposed `N+R`, `S+G`; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Set combo `E+I` to Alt+Delete; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Set combo `E+I` to Alt+Backspace and added `U+J` -> Alt+Delete; files: qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c, qmk_helper_skills.md
- 2026-02-24: Added combo cheat sheet generator and output; files: bin/gen_combo_cheatsheet.py, assets/keyball_layout_coords.json, combo_cheatsheet.html, qmk_helper_skills.md

## Knowledge Base
- Combo/layer conflicts are likely when layer-tap keys participate in combos; `COMBO_MUST_TAP_PER_COMBO` avoids hold-trigger collisions.
- `COMBO_ONLY_FROM_LAYER 0` keeps combo detection stable across toggled layers.
- Telemetry is best treated as a temporary build profile due to flash limits.
- For this repo, `qmk console` is the practical replacement for missing `hid_listen`.
- Keyball library may require OLED guards when building with `OLED_ENABLE = no`.

## Quick Commands
```bash
cd /Users/pkomsit/code/c/qmk
make SKIP_GIT=yes keyball/keyball44:via
qmk flash -kb keyball/keyball44 -km via
qmk console
```

## Update Template (append to Task Log)
`- YYYY-MM-DD: <change summary>; files: <path1>, <path2>`
