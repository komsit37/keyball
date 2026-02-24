# QMK Helper Skills (Keyball44 VIA)

Last updated: 2026-02-20
Scope: `/Users/pkomsit/code/c/keyball`

## Current Firmware Profile
- Keymap: `qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c`
- Config: `qmk_firmware/keyboards/keyball/keyball44/keymaps/via/config.h`
- Rules: `qmk_firmware/keyboards/keyball/keyball44/keymaps/via/rules.mk`
- Dynamic layers: `6` (layers `0..5`)
- Telemetry build currently enabled:
  - `#define KEYBALL_STATS_ENABLE`
  - `CONSOLE_ENABLE = yes`
  - `OLED_ENABLE = no` (disabled to fit flash during telemetry)

## Home Row / Layer Tuning (Current)
- `CHORDAL_HOLD` enabled.
- `PERMISSIVE_HOLD` disabled.
- `TAPPING_TERM = 170` with `TAPPING_TERM_PER_KEY`.
- Finger-based per-key tuning in `get_tapping_term()`:
  - Pinky: `N/I = 160`
  - Ring: `L/U/R = 152`, `E = 160`
  - Middle: `D/T/A = 145`, `O = 153`
  - Index: `S/H/W/F = 138`
- Why:
  - Reduce accidental mod/layer holds in rolling text.
  - Preserve intentional hold behavior for shortcuts and layer-taps.

## Combo Strategy (Current)
- `COMBO_ENABLE = yes`
- `COMBO_ALLOW_ACTION_KEYS`
- `COMBO_ONLY_FROM_LAYER 0`
- `COMBO_MUST_TAP_PER_COMBO`
- Trigger updates:
  - `/, Enter -> TG(5)` (Excel layer toggle)
  - `Enter + Space -> TG(1)`
- Useful active combos (as implemented in keymap):
  - `E+I -> Alt+Backspace`
  - `H+A -> Ctrl+A`
  - `A+E -> Caps Word Toggle`
  - `X+M -> Cmd+C`
  - `X+C -> Cmd+V`
  - `M+C -> ,`
  - `C+V -> \``
  - `Y+H -> Alt+Left`
  - `P+. -> -`
  - `K+P -> _`
  - `N+R -> Alt+Delete`
  - `S+G -> Alt+Right`
  - `.+; -> ,`

## Excel Layer (Layer 5)
- Added for number-heavy spreadsheet workflows.
- Kept right-hand number cluster aligned with layer 2 positions.
- Kept left-hand arrow positions aligned with layer 1 positions.
- Added spreadsheet shortcuts (`Undo/Redo/Copy/Paste/Save`, `F2`, tab navigation, etc.).

## Telemetry / Statistics
- Implemented in `keymap.c` behind `KEYBALL_STATS_ENABLE`.
- Dump key mapped to:
  - Layer 3, row 3, col 0 (`STATS_DUMP`).
- Output via `qmk console`, format:
  - `KBST`
  - `Kx,presses,taps,holds,interrupted,tap_avg_ms,hold_avg_ms,tap_pct`
  - `Cx,count` for combo triggers
- Key index map:
  - `K0=L`, `K1=D`, `K2=W`, `K3=F`, `K4=O`, `K5=U`, `K6=N`, `K7=R`, `K8=E`, `K9=I`, `K10=T`, `K11=S`, `K12=H`, `K13=A`
- Reliability fix applied:
  - Clamp elapsed to at least `1ms` to avoid `0ms` averages.

## Known Build Constraints / Fixes
- Flash size was exceeded when telemetry + OLED were both enabled.
- Mitigations used:
  - `LTO_ENABLE = yes`
  - telemetry output string compression
  - `OLED_ENABLE = no` for telemetry profile
- Patched library for non-OLED compile:
  - `qmk_firmware/keyboards/keyball/lib/keyball/keyball.c`
  - Guarded OLED-only symbols/usages so build succeeds with `OLED_ENABLE = no`.

## Build / Flash Commands
```bash
cd /Users/pkomsit/code/c/qmk
make SKIP_GIT=yes keyball/keyball44:via
qmk flash -kb keyball/keyball44 -km via
```

## Tuning Loop
1. Flash telemetry profile.
2. Run `qmk console`.
3. Type real workload (include known failure patterns).
4. Trigger dump key.
5. Adjust per-key tapping terms by small deltas (`±5..10ms`).
6. Rebuild/flash and repeat.

## Next Tuning Priorities
- Watch `O` and `E` accidental hold rates after recent +8ms adjustments.
- Validate layer-tap comfort for `S/H/T/A` with real spreadsheet + prose typing.
- If flash pressure returns, keep telemetry as temporary profile only.
