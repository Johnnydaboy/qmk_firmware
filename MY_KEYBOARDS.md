# My Keyboards Quick Reference

## Boards I Own

| Board | QMK Path | Keymap |
|-------|----------|--------|
| CannonKeys DB60 Hotswap | `cannonkeys/db60/hotswap` | `meme` |
| 1upkeyboards PI60 RGB | `1upkeyboards/pi60_rgb` | `repeat` |

## Quick Flash Commands

```bash
# DB60 Hotswap
qmk flash -kb cannonkeys/db60/hotswap -km meme

# PI60 RGB
qmk flash -kb 1upkeyboards/pi60_rgb -km repeat
```

## Aliases (in ~/.bashrc)

```bash
flash-db60    # Flash DB60 Hotswap
flash-pi60    # Flash PI60 RGB
compile-db60  # Compile DB60 only
compile-pi60  # Compile PI60 only
```
