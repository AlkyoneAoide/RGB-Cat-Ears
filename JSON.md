# JSON LED configuration format

### `effect`: string
Which effect to apply to the ears. Possible values:
- `audio` (app only probably)
- `breathing`
- `gradient`
- `gyro`
- `rainbow`
- `stars`
- `static`

---

### `brightness`: int
The brightness (or maximum brightness) of the LEDs. 0-255, defaults to 255.

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

### `colors`: [strings] OR [[strings], [strings]]
Array of colors to be included in the effect.  If two arrays are provided, they map to the two ears.  Defaults to [["blue"], ["orange"]]

---

### `audioHalfEar`: boolean
False if the audio visualizer should treat each ear independently, true if it should use half ears.  Defaults to false.

---

### `gradientColorWidth`: [ints] OR [[ints], [ints]]
Array of integers matching the structure of `colors`, representing how much of the strip each color should take relative to the other colors available.  Defaults to even distribution.

---

### `gyroFallback`: string
The effect that the ears should display if the gyro sensor has not been sufficiently shaken in a while.  Defaults to rainbow.

---

### `gyroFallbackStyle`: string
The style of the `gyroFallback` effect.  Defaults to static.

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
`gradient`
- `static` (static gradient) Default.
- `moving` (moves in a similar way to rainbow.movingStrip)
`audio`
- `volume` (use volume exclusively for visualizer)
- `frequency` (use traditional frequency-based visualizer) Default.
`gyro`
- `static` (display color if sensed)
- `panic` (display random colors from list)
- `map` (axes of rotation map to r (roll), g (pitch), b (yaw))
- `strength` (the stronger the force, the more lights come on) Default.

