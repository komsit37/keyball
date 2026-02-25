#!/usr/bin/env python3
import re
from pathlib import Path

def key_label_from_token(token: str) -> str | None:
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
        'KC_ESC': 'ESC',
        'KC_LEFT': 'LEFT',
        'KC_RGHT': 'RGHT',
        'KC_UP': 'UP',
        'KC_DOWN': 'DOWN',
        'KC_NO': '----',
        'KC_HOME': 'HOME',
        'KC_END': 'END',
        'KC_PGUP': 'PGUP',
        'KC_PGDN': 'PGDN',
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

def split_top_level(s: str) -> list[str]:
    out = []
    buf = []
    depth = 0
    for ch in s:
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        if ch == ',' and depth == 0:
            item = ''.join(buf).strip()
            if item:
                out.append(item)
            buf = []
            continue
        buf.append(ch)
    tail = ''.join(buf).strip()
    if tail:
        out.append(tail)
    return out

def extract_layout_block(text: str) -> str:
    start = text.find('[0] = LAYOUT_universal(')
    if start == -1:
        raise SystemExit('Layer 0 LAYOUT_universal not found')
    start = text.find('LAYOUT_universal(', start)
    start = text.find('(', start) + 1
    depth = 1
    i = start
    while i < len(text) and depth > 0:
        ch = text[i]
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        i += 1
    if depth != 0:
        raise SystemExit('Unbalanced parentheses while parsing layout')
    return text[start:i-1]

def parse_layer0_tokens(text: str) -> list[str]:
    body = extract_layout_block(text)
    return split_top_level(body)

def parse_combo_defs(text: str) -> dict[str, list[str]]:
    combo_defs = {}
    for name, body in re.findall(r'const uint16_t PROGMEM (\w+)\[\]\s*=\s*\{([^}]+)\};', text):
        tokens = [t for t in split_top_level(body) if t and t != 'COMBO_END']
        combo_defs[name] = tokens
    return combo_defs

def parse_combo_entries(text: str):
    entries = []
    for m in re.finditer(r'\[(\w+)\]\s*=\s*COMBO\(', text):
        combo_id = m.group(1)
        start = m.end()
        depth = 1
        i = start
        while i < len(text) and depth > 0:
            ch = text[i]
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
            i += 1
        args = text[start:i-1]
        parts = split_top_level(args)
        if len(parts) >= 2:
            entries.append({
                'id': combo_id,
                'combo_name': parts[0].strip(),
                'output': parts[1].strip(),
            })
    return entries

def fmt_row(keys: list[str], width: int = 4) -> str:
    return ' '.join(f"[{k:>{width}}]" for k in keys)

def fmt_combo_row(keys: list[str], width: int = 10) -> str:
    return ' '.join(f"[{k:>{width}}]" for k in keys)

def normalize_token(token: str) -> str:
    return re.sub(r'\s+', '', token)

def trunc(text: str, width: int) -> str:
    if len(text) <= width:
        return text
    return text[:width-1] + '~'

def render_row(left: list[list[str]], right: list[list[str]], width: int) -> None:
    left_border = "+" + "+".join(["-" * width for _ in left]) + "+"
    right_border = "+" + "+".join(["-" * width for _ in right]) + "+"
    gap = "  "
    max_lines = max(max(len(lines) for lines in left), max(len(lines) for lines in right))
    print(left_border + gap + right_border)
    for i in range(max_lines):
        left_line = []
        right_line = []
        for lines in left:
            content = lines[i] if i < len(lines) else ""
            left_line.append(content.center(width))
        for lines in right:
            content = lines[i] if i < len(lines) else ""
            right_line.append(content.center(width))
        print("|" + "|".join(left_line) + "|" + gap + "|" + "|".join(right_line) + "|")
    print(left_border + gap + right_border)

def main():
    keymap_path = Path('qmk_firmware/keyboards/keyball/keyball44/keymaps/via/keymap.c')
    text = keymap_path.read_text()

    tokens = parse_layer0_tokens(text)
    counts = [12, 12, 12, 10]
    if sum(counts) != len(tokens):
        raise SystemExit(f'Unexpected key count: {len(tokens)}')

    labels = [key_label_from_token(t) or t for t in tokens]

    rows = []
    idx = 0
    for c in counts:
        rows.append(labels[idx:idx+c])
        idx += c

    combo_defs = parse_combo_defs(text)
    combos = parse_combo_entries(text)

    token_positions = {}
    for i, token in enumerate(tokens):
        token_positions.setdefault(normalize_token(token), []).append(i)
    combo_lines = [[] for _ in tokens]
    for combo in combos:
        keys = combo_defs.get(combo['combo_name'], [])
        key_labels = [key_label_from_token(k) for k in keys]
        if None in key_labels or len(key_labels) != 2:
            continue
        if len(keys) != 2:
            continue
        t1 = normalize_token(keys[0])
        t2 = normalize_token(keys[1])
        if t1 not in token_positions or t2 not in token_positions:
            continue
        p1 = token_positions[t1][0]
        p2 = token_positions[t2][0]
        out = output_label(combo['output'])
        left, right = (p1, p2) if p1 <= p2 else (p2, p1)
        pair = f"{labels[left]}+{labels[right]}"
        combo_lines[left].append((pair, out))

    print('Layer 0 (LAYOUT_universal)')
    for r, row in enumerate(rows):
        if r < 3:
            left, right = row[:6], row[6:]
        else:
            left, right = row[:5], row[5:]
            left = [left[0], left[1], "----", left[2], left[3], left[4]]
            right = [right[0], right[1], "----", "----", right[4], "----"]
        print(fmt_row(left) + '  ||  ' + fmt_row(right))

    print('\nCombo Layout (per key, pair then output)')
    width = 10
    combo_rows = []
    idx = 0
    for c in counts:
        combo_rows.append(list(range(idx, idx + c)))
        idx += c

    for r, row in enumerate(combo_rows):
        cell_lines = []
        for pos in row:
            pairs = combo_lines[pos]
            lines = []
            for pair, out in pairs:
                lines.append(trunc(pair, width))
                lines.append(trunc(out, width))
            if not lines:
                lines = [""]
            cell_lines.append(lines)

        if r < 3:
            left, right = cell_lines[:6], cell_lines[6:]
        else:
            left, right = cell_lines[:5], cell_lines[5:]
            left = [left[0], left[1], ["----"], left[2], left[3], left[4]]
            right = [right[0], right[1], ["----"], ["----"], right[4], ["----"]]
        render_row(left, right, width)

    print('\nCombos')
    for combo in combos:
        keys = combo_defs.get(combo['combo_name'], [])
        key_labels = [key_label_from_token(k) for k in keys]
        if None in key_labels or len(key_labels) != 2:
            continue
        out = output_label(combo['output'])
        print(f"- {key_labels[0]}+{key_labels[1]} -> {out}")

if __name__ == '__main__':
    main()
