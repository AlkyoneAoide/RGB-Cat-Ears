# JSON LED configuration format

### `effect`: string
Which effect to apply to the ears.  Defaults to "static".  Possible values:
- `audio` (app only probably)
- `breathing`
- `gradient`
- `gyro`
- `rainbow`
- `stars`
- `static`

---

### `speed`: int
The speed of the chosen effect, 0-255, defaults to 128.

---

### `direction`: int
The direction the effect travels in, given as an angle in degrees (-360 - 360).  A negative angle will reverse the direction traveled.  Defaults to 0.

---

### `randomOrder`: boolean
True if the color order should be randomized, false if not. Defaults to false.

---

### `colors`: [int, (h, s, v)...] OR [[int, (h, s, v)...], [int, (h, s, v)...]]
Array of colors to be included in the effect.  If two arrays are provided, they map to the two ears.  Should only either include one color, or one color per pixel.  Defaults to [[1, hsv(210, 100, 100)], [1, hsv(30, 100, 100)]]
(h: 0-355, s/v: 0-100)

# TODO: figure out how to differentiate wanting gradients vs multiple colors in sequence (like breathing with blue+orange -> green+pink)

---

### `perEarColors`: boolean
True if the `colors` property is two arrays nested instead of one single array

---

### `audioHalfEar`: boolean
False if the audio visualizer should treat each ear independently, true if it should use half ears.  Defaults to false.

---

### `gyroIdle`: string
The effect that the ears should display if the gyro sensor has not been sufficiently shaken in a while.  Defaults to rainbow.

---

### `gyroIdleStyle`: string
The style of the `gyroIdle` effect.  Defaults to static.

---

### `gyroSensitivity`: int
How much force is needed to activate the gyro effects.  0-255, defaults to 10.

---

### `gyroTimeout`: int
How long until the fallback effect should kick in, in miliseconds.  Defaults to 5000.

---

### `style`: string
Specify the specific style of the selected effect that you want.
`static`
- `alternating` (alternates between provided colors)
- `together` (divides provided colors equally among length) Default.
`rainbow`
- `static` (static rainbow) Default.
- `moving` (strip effect that moves side-to-side)
- `wipe` (moving rainbow, direction depends on `direction`)
- `gyro` (brightness depends on rotation rate)
`gradient`
- `static` (static gradient) Default.
- `moving` (moves in a similar way to rainbow.movingStrip)
`audio`
- `volume` (use volume exclusively for visualizer)
- `frequency` (use traditional frequency-based visualizer) Default.
`gyro`
- `static` (brightness = force)
- `map` (axes of rotation map to r (roll), g (pitch), b (yaw))
- `strength` (the stronger the force, the more lights come on, center of strip is maximum) Default.
