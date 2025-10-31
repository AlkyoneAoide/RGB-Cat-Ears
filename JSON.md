# JSON LED configuration format

### `effect`: string
Which effect to apply to the ears. Possible values:
- `audio` (app only probably, full or half ear, volume or low-mid-high frequencies)
- `breathing` (what color(s) to rotate through)
- `gradient` (moving or static/what colors/direction/speed/width of each color (snake/wipe))
- `gyro` (how it reacts/fallback if not moving much/sensitivity)
- `rainbow` (direction top to bottom, across ears left to right)
- `stars` (colors)
- `static` (what colors)

---

### `brightness`: int
The brightness (or maximum brightness) of the LEDs.

---

### `speed`: int
The speed of the chosen effect.

---

### `direction`: int
The direction the effect travels in, given as an angle in degrees.

---

### `randomOrder`: boolean
True if the color order should be randomized, false if not.

