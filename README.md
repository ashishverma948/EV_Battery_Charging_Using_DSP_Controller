The goal of this project is to design and implement a smart EV battery charging system using a Digital Signal Processor (DSP) controller. The DSP ensures efficient, safe, and fast charging of an electric vehicle (EV) battery while implementing advanced features like monitoring, phase control, and adaptive charging algorithms.

Key Components of the Project
1->EV Battery:

A lithium-ion battery pack is typically used as the energy storage device.
Characteristics like voltage, current, temperature, and state-of-charge (SOC) need to be monitored during charging.
2->DSP Controller:

A DSP processor (like TI’s TMS320F28069 or TMS320F28379D) is used to manage the entire charging process.
DSP is preferred due to its real-time processing capabilities, high computational speed, and ability to handle multiple control loops.
3->Power Electronics:

AC/DC Converter: Converts grid AC power into DC power to charge the battery.
DC/DC Converter: Ensures stable DC voltage and current supply to the battery.
PWM Control: Controlled by the DSP to regulate the switching of power converters.
4->Sensors:

Voltage Sensors: Monitor battery voltage.
Current Sensors: Ensure the charging current does not exceed safe limits.
Temperature Sensors: Monitor battery temperature to prevent overheating.
5->User Interface:

LCD/LED display to show battery status (voltage, current, SOC, temperature).
Buttons or a touchscreen for user interaction and mode selection.
6->Protection Mechanisms:

Overvoltage, overcurrent, and overtemperature protection ensure safety during the charging process.
