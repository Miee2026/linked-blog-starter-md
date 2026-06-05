|Risk|Type|Impact|Likelihood|Mitigation|
|---|---|---|---|---|

| Risk                                       | Type      | Impact | Likehood | Mitigation                                                              |
| ------------------------------------------ | --------- | ------ | -------- | ----------------------------------------------------------------------- |
| Servo torque is insufficient               | Technical | High   | Medium   | Calculate required torque and select servo with higher torque margin    |
| Frame is unstable or tips over             | Technical | High   | Medium   | Use a wider base and verify stability through structural testing        |
| LDR readings are noisy                     | Technical | Medium | Medium   | Use averaging, threshold values, and calibration                        |
| Wiring becomes loose during testing        | Technical | Medium | Medium   | Secure wires and verify all connections before operation                |
| Solar panel output is lower than expected  | Technical | Medium | Medium   | Test panel under different lighting conditions and document limitations |
| Remote control connection is unreliable    | Technical | Medium | Low      | Test ESP32 web server range and include manual fallback control         |
| 3D printed parts take longer than expected | Schedule  | Medium | Medium   | Print early and prepare extra time for redesign                         |
| Integration takes longer than planned      | Schedule  | High   | Medium   | Test subsystems separately before full assembly                         |

