#!/usr/bin/env python3
import argparse
import json
import re
import struct
from pathlib import Path

def png_size(path: Path) -> tuple[int, int]:
    with path.open('rb') as f:
        sig = f.read(8)
        if sig != b"\x89PNG\r\n\x1a\n":
            raise ValueError(f"Not a PNG: {path}")
        length = struct.unpack('>I', f.read(4))[0]
        if f.read(4) != b'IHDR':
            raise ValueError(f"Missing IHDR: {path}")
        data = f.read(length)
        w, h = struct.unpack('>II', data[:8])
        return w, h

def load_coords(path: Path, width: int, height: int) -> dict[str, tuple[float, float]]:
    data = json.loads(path.read_text())
    if data.get('units') != 'percent':
        raise ValueError("coords json must use percent units")
    coords = {}
    for key, (xp, yp) in data['keys'].items():
        coords[key] = (xp / 100.0 * width, yp / 100.0 * height)
    return coords

def key_label_from_token(token: str) -> str | None:
    # Extract last KC_* token within wrappers like LT(3, KC_DOT)
    m = re.findall(r'(KC_[A-Z0-9_]+)', token)
    if not m:
        return None
    kc = m[-1]
    if kc.startswith('KC_') and len(kc) == 4:
        return kc[-1]
    mapping = {
        'KC_DOT': '.',
        'KC_COMM': ',',
        'KC_SCLN': ';',
        'KC_MINS': '-',
        'KC_EQL': '=',
        'KC_SLSH': '/',
        'KC_BSLS': '\\',
        'KC_QUOT': "'",
        'KC_GRV': '`',
        'KC_LBRC': '[',
        'KC_RBRC': ']',
        'KC_BSPC': 'BSPC',
        'KC_DEL': 'DEL',
        'KC_ENT': 'ENT',
        'KC_SPC': 'SPC',
        'KC_TAB': 'TAB',
    }
    if kc in mapping:
        return mapping[kc]
    if kc.startswith('KC_'):
        return kc[3:]
    return kc

def output_label(expr: str) -> str:
    expr = expr.strip()
    shift_map = {
        'KC_1': '!', 'KC_2': '@', 'KC_3': '#', 'KC_4': '$', 'KC_5': '%',
        'KC_6': '^', 'KC_7': '&', 'KC_8': '*', 'KC_9': '(', 'KC_0': ')',
        'KC_LBRC': '{', 'KC_RBRC': '}', 'KC_COMM': '<', 'KC_DOT': '>',
        'KC_SCLN': ':', 'KC_QUOT': '"', 'KC_MINS': '_', 'KC_EQL': '+',
        'KC_GRV': '~', 'KC_SLSH': '?', 'KC_BSLS': '|',
    }
    m = re.match(r'([A-Z]+)\(([^)]+)\)', expr)
    if m:
        mod, inner = m.group(1), m.group(2).strip()
        if mod == 'S':
            return shift_map.get(inner, f"Shift+{key_label_from_token(inner) or inner}")
        mod_label = {
            'A': 'Alt',
            'C': 'Ctrl',
            'G': 'Gui',
            'LGUI': 'Cmd',
            'RGUI': 'Cmd',
        }.get(mod, mod)
        key = key_label_from_token(inner) or inner
        return f"{mod_label}+{key}"
    if expr.startswith('TG('):
        return f"Toggle L{expr[3:-1]}"
    if expr == 'QK_CAPS_WORD_TOGGLE':
        return 'Caps Word'
    key = key_label_from_token(expr)
    return key or expr

def parse_combos(keymap_text: str):
    combo_defs = {}
    for name, body in re.findall(r'const uint16_t PROGMEM (\w+)_combo\[\]\s*=\s*\{([^}]+)\};', keymap_text):
        tokens = [t.strip() for t in body.split(',') if t.strip() and t.strip() != 'COMBO_END']
        combo_defs[name] = tokens

    combos = []
    for combo_id, combo_name, output in re.findall(r'\[(\w+)\]\s*=\s*COMBO\((\w+),\s*([^\)]+)\)', keymap_text):
        keys = combo_defs.get(combo_name, [])
        combos.append({
            'id': combo_id,
            'name': combo_name,
            'keys': keys,
            'output': output.strip(),
        })
    return combos

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--keymap', default='qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c')
    ap.add_argument('--coords', default='assets/keyball_layout_coords.json')
    ap.add_argument('--image', default='assets/keyball_layout.png')
    ap.add_argument('--out', default='combo_cheatsheet.html')
    args = ap.parse_args()

    keymap_path = Path(args.keymap)
    coords_path = Path(args.coords)
    image_path = Path(args.image)
    out_path = Path(args.out)

    width, height = png_size(image_path)
    coords = load_coords(coords_path, width, height)

    text = keymap_path.read_text()
    combos = parse_combos(text)

    placed = []
    unplaced = []
    for combo in combos:
        key_labels = [key_label_from_token(k) for k in combo['keys']]
        if None in key_labels:
            unplaced.append((combo, key_labels))
            continue
        if len(key_labels) != 2:
            unplaced.append((combo, key_labels))
            continue
        k1, k2 = key_labels
        if k1 not in coords or k2 not in coords:
            unplaced.append((combo, key_labels))
            continue
        placed.append({
            'keys': (k1, k2),
            'output': output_label(combo['output']),
        })

    svg_lines = []
    svg_labels = []
    for i, combo in enumerate(placed):
        (k1, k2) = combo['keys']
        (x1, y1) = coords[k1]
        (x2, y2) = coords[k2]
        mx, my = (x1 + x2) / 2.0, (y1 + y2) / 2.0
        label = f"{k1}+{k2} → {combo['output']}"
        svg_lines.append(f'<line x1="{x1:.1f}" y1="{y1:.1f}" x2="{x2:.1f}" y2="{y2:.1f}" class="combo-line" />')
        svg_labels.append(
            f'<g class="combo-label" transform="translate({mx:.1f},{my:.1f})">'
            f'<rect x="-70" y="-12" width="140" height="24" rx="10" ry="10" />'
            f'<text text-anchor="middle" dominant-baseline="middle">{label}</text>'
            f'</g>'
        )

    unplaced_list = "\n".join([
        f"<li>{' + '.join([k for k in keys if k])} → {output_label(c['output'])}</li>"
        for c, keys in unplaced
    ])
    if not unplaced_list:
        unplaced_list = "<li>None</li>"

    html = f"""<!doctype html>
<html lang=\"en\">
<head>
<meta charset=\"utf-8\" />
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />
<title>Keyball44 Combo Cheat Sheet</title>
<style>
:root {{
  --bg: #f6f6f6;
  --ink: #1b1b1b;
  --accent: #3b82f6;
  --label-bg: rgba(59, 130, 246, 0.14);
}}
body {{
  margin: 0;
  font-family: "IBM Plex Sans", "Segoe UI", sans-serif;
  background: var(--bg);
  color: var(--ink);
}}
.wrapper {{
  max-width: {width}px;
  margin: 24px auto 40px;
  padding: 0 16px;
}}
.stage {{
  position: relative;
  width: {width}px;
  height: {height}px;
  margin: 0 auto;
  box-shadow: 0 18px 50px rgba(0,0,0,0.12);
  border-radius: 18px;
  overflow: hidden;
  background: #fff;
}}
.stage img {{
  width: 100%;
  height: 100%;
  display: block;
}}
.stage svg {{
  position: absolute;
  inset: 0;
}}
.combo-line {{
  stroke: var(--accent);
  stroke-width: 3;
  stroke-linecap: round;
  opacity: 0.8;
}}
.combo-label rect {{
  fill: var(--label-bg);
  stroke: var(--accent);
  stroke-width: 1.5;
}}
.combo-label text {{
  font-size: 12px;
  font-weight: 600;
  fill: var(--ink);
}}
.list {{
  margin: 20px 0 0;
  font-size: 14px;
}}
.list h2 {{
  margin: 0 0 8px;
  font-size: 16px;
}}
.list ul {{
  margin: 0;
  padding-left: 18px;
}}
</style>
</head>
<body>
  <div class=\"wrapper\">
    <div class=\"stage\">
      <img src=\"{image_path.as_posix()}\" alt=\"Keyball44 layout\" />
      <svg viewBox=\"0 0 {width} {height}\" preserveAspectRatio=\"none\">
        {'\n        '.join(svg_lines)}
        {'\n        '.join(svg_labels)}
      </svg>
    </div>
    <div class=\"list\">
      <h2>Unplaced combos (missing key coords)</h2>
      <ul>
        {unplaced_list}
      </ul>
    </div>
  </div>
</body>
</html>
"""

    out_path.write_text(html)
    print(f"Wrote {out_path}")

if __name__ == '__main__':
    main()
