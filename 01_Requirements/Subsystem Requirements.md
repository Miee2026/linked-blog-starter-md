
Mechanical Requirements

| ID     | Requirement                                                                                               | Rationale                         | Verification | Parent System Req | Subsystem | Type     |
| ------ | --------------------------------------------------------------------------------------------------------- | --------------------------------- | ------------ | ----------------- | --------- | -------- |
| MR-001 | The structure shall support the solar panel, motor, sensor, and battery without tipping during operation. | Ensure safe and stable operation  | Test         | SR-006            | Structure | Physical |
| MR-002 | The support frame shall maintain panel alignment during manual handling and motorized adjustment.         | Maintain tracking accuracy        | Test         | SR-002            | Structure | Physical |
| MR-003 | The system shall fit within a compact tabletop-scale size for portability.                                | Support easy carrying and storage | Inspection   | SR-005            | Structure | Physical |
| MR-004 | The frame shall be manufacturable using 3D-printing methods and common prototyping materials.             | Enable rapid fabrication          | Inspection   | SR-007            | Structure | Physical |
| MR-005 | The base shall provide stable contact with the ground or table during outdoor use.                        | Prevent slipping or falling       | Test         | SR-006            | Structure | Physical |
| MR-006 | The rotating joint shall allow controlled panel movement without excessive looseness or friction.         | Support reliable motion           | Test         | SR-004            | Actuation | Physical |

Electrical Requirements

| ID     | Requirement                                                                                      | Rationale                              | Verification | Parent System Req | Subsystem              | Type       |
| ------ | ------------------------------------------------------------------------------------------------ | -------------------------------------- | ------------ | ----------------- | ---------------------- | ---------- |
| ER-001 | The solar panel shall generate electrical power from sunlight for charging and system operation. | Primary energy source                  | Test         | SR-001            | Solar Panel            | Electrical |
| ER-002 | The system shall include a battery module to store generated electrical energy.                  | Enable later use of power              | Test         | SR-008            | Power Storage          | Electrical |
| ER-003 | The system shall include a charging/output module to provide power to small devices.             | Deliver usable output                  | Test         | SR-009            | Output                 | Electrical |
| ER-004 | The electrical system shall provide power to sensors, controller, and motor as needed.           | Support automatic tracking             | Test         | SR-002            | Power Distribution     | Electrical |
| ER-005 | The wiring shall be secured to avoid interference with moving parts.                             | Improve safety and reliability         | Inspection   | SR-006            | Electrical Integration | Electrical |
| ER-006 | The system shall regulate electrical power to protect connected components from unstable input.  | Improve stability and component safety | Test         | SR-009            | Power Management       | Electrical |

Control Requirements

| ID     | Requirement                                                                                             | Rationale                          | Verification | Parent System Req | Subsystem         | Type       |
| ------ | ------------------------------------------------------------------------------------------------------- | ---------------------------------- | ------------ | ----------------- | ----------------- | ---------- |
| CR-001 | The control system shall read real-time input from the light sensor module.                             | Detect sunlight direction          | Test         | SR-003            | Sensing/Control   | Functional |
| CR-002 | The control system shall compare sensor input and determine the required panel adjustment direction.    | Enable automatic tracking logic    | Test         | SR-002            | Control           | Functional |
| CR-003 | The control system shall command the motorized adjustment system to reposition the panel automatically. | Execute tracking behavior          | Test         | SR-004            | Control/Actuation | Functional |
| CR-004 | The control system shall stop panel motion when the desired orientation is reached.                     | Prevent overshoot and wasted power | Test         | SR-002            | Control           | Functional |
| CR-005 | The control system shall support repeatable tracking behavior under outdoor lighting conditions.        | Ensure consistent function         | Test         | SR-010            | Control           | Functional |

Integration Requirements

| ID     | Requirement                                                                                                                                           | Rationale                           | Verification  | Parent System Req | Subsystem          | Type        |
| ------ | ----------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------- | ------------- | ----------------- | ------------------ | ----------- |
| IR-001 | The solar panel, sensor, motor, battery, and support frame shall be integrated into one portable system.                                              | Create a complete working prototype | Inspection    | SR-010            | System Integration | Integration |
| IR-002 | The light sensor module shall interface with the control system to support automatic panel adjustment.                                                | Enable closed-loop tracking         | Test          | SR-003            | Sensing/Control    | Integration |
| IR-003 | The control system shall interface with the motorized adjustment system to reposition the solar panel.                                                | Connect decision and action         | Test          | SR-004            | Control/Actuation  | Integration |
| IR-004 | The solar panel shall interface with the battery and output module to support energy storage and power delivery.                                      | Enable charging fucntionality       | Test          | SR-008/SR-009     | Power System       | Integration |
| IR-005 | The integrated system shall maintain stable operation during outdoor use and panel movement.                                                          | Ensure real-world usability         | Test          | SR-006/SR-010     | System Integration | Integration |
| IR-006 | The integrated prototype shall demonstrate sunlight collection, automatic adjustment, energy storage, and electrical output as one complete workflow. | Verify end-to-end functionality     | Demonstration | SR-001-SR-010     | System             | Integration |