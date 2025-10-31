#pragma once

namespace default_effects {
  static constexpr String DEFAULT_STATIC_JSON = R"jsonliteral(
    {
      "effect": "static",
      "colors": [["blue", "off"], ["orange", "off"]],
      "style": "alternating" 
    }
  )jsonliteral";

  static constexpr String DEFAULT_GYRO_JSON = R"jsonliteral(
    {
      "effect": "gyro",
      "gyroFallback": "rainbow",
      "style": "map"
    }
  )jsonliteral";
}
