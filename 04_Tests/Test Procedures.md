
Functional Testing Plan

| Test ID | Test Name               | Objective                                                       | Test Method                                                            | Data Recorded                                                    | Success Criteria                                            |
| ------- | ----------------------- | --------------------------------------------------------------- | ---------------------------------------------------------------------- | ---------------------------------------------------------------- | ----------------------------------------------------------- |
| T1      | Sun Tracking Accuracy   | Verify that the panel rotates toward the strongest light source | Place a light source at different positions and observe panel movement | Light source position, final panel angle, angle error, pass/fail | Panel moves toward the light source within acceptable error |
| T2      | Dual-Axis Movement      | Verify horizontal and vertical movement                         | Command the panel to rotate left/right and up/down                     | Axis tested, commanded angle, observed motion, response time     | Both axes move smoothly without collision                   |
| T3      | Outdoor Charging Output | Verify usable charging output                                   | Place panel under sunlight and measure output                          | Voltage, current, power output                                   | Output is stable and suitable for charging                  |
| T4      | Remote Control          | Verify remote operation                                         | Send control commands through Wi-Fi/Bluetooth                          | Command sent, system response, delay, pass/fail                  | ESP32 receives commands and responds correctly              |

