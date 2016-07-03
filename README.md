==========================
Marlin 3D Printer Firmware
==========================
# Marlin 3D Printer Firmware
<img align="top" width=175 src="Documentation/Logo/Marlin%20Logo%20GitHub.png" />
 Additional documentation can be found in [The Marlin Wiki](https://github.com/MarlinFirmware/Marlin/wiki).

## Release Candidate -- Marlin 1.1.0-RC6 - 24 April 2016

About this fork
===============
This fork is setup to work with the BAM 3D printer (Big Alu Mendel) http://reprap.org/wiki/BAM that is based on Makeblock aluminium extrusions, Megatronics 2 electronics and the Hexagon all metal hotend. I'll update this fork against Erik's original branch (as required).

Quick Information
===================
This RepRap firmware is a mashup between <a href="https://github.com/kliment/Sprinter">Sprinter</a>, <a href="https://github.com/simen/grbl/tree">grbl</a> and many original parts.

You can download earlier versions of Marlin on the [Releases page](https://github.com/MarlinFirmware/Marlin/releases). (The latest "stable" release of Marlin is 1.0.2-1.)

You'll always find the latest Release Candidate in the ["RC" branch](https://github.com/MarlinFirmware/Marlin/tree/RC). Bugs that we find in the current Release Candidate are patched in the ["RCBugFix" branch](https://github.com/MarlinFirmware/Marlin/tree/RC), so during beta testing this is where you can always find the latest code on its way towards release.

Future development (Marlin 1.2 and beyond) takes place in the [MarlinDev repository](https://github.com/MarlinFirmware/MarlinDev/).

## Recent Changes
- RCBugFix
  - Throw error if compiling with older versions (<1.60) of Arduino due to serious problems with outdated Arduino versions
  - Please upgrade your IDE at least to Arduino 1.6.0. Thanks.

- RC6 - 23 Apr 2016
  - Completed support for CoreXY / CoreXZ in planner
  - Changes to positioning behavior
  - Various issues fixed. More details pending.

- RC5 - 01 Apr 2016
  - Warn if compiling with older versions (<1.50) of Arduino
  - Fix various LCD menu issues
  - Add formal support for MKSv1.3 and Sainsmart (RAMPS variants)
  - Fix bugs in M104, M109, and M190
  - Fix broken M404 command
  - Fix issues with M23 and "Start SD Print"
  - More output for M111
  - Rename FILAMENT_SENSOR to FILAMENT_WIDTH_SENSOR
  - Fix SD card bugs
  - and a lot more
  - see https://github.com/MarlinFirmware/Marlin/releases/tag/1.1.0-RC5 for details

- RC4 - 24 Mar 2016
  - Many lingering bugs and nagging issues addressed
  - Improvements to LCD menus, CoreXY/CoreXZ, Delta, Bed Leveling, and more…

- RC3 - 01 Dec 2015
  - A number of language sensitive strings have been revised
  - Formatting of the LCD display has been improved to handle negative coordinates better
  - Various compiler-related issues have been corrected

- RC2 - 29 Sep 2015
  - File styling reverted
  - LCD update frequency reduced

- RC1 - 19 Sep 2015
  - Published for testing

## Submitting Patches
Proposed patches should be submitted as a Pull Request against the [RCBugFix](https://github.com/MarlinFirmware/Marlin/tree/RCBugFix) branch.

- Don't submit new feature proposals. The RCBugFix branch is for fixing bugs in existing features.
- Do submit questions and concerns. The "naive" question is often the one we forget to ask.
- Follow the proper coding style. Pull requests with styling errors will be delayed. See our [Coding Standards](https://github.com/MarlinFirmware/Marlin/wiki/DNE-Coding-Standards) page for more information.

## Current Status: Testing

Please test this firmware and inform us if it misbehaves in any way. Volunteers are standing by!

[![Coverity Scan Build Status](https://scan.coverity.com/projects/2224/badge.svg)](https://scan.coverity.com/projects/2224)
[![Travis Build Status](https://travis-ci.org/MarlinFirmware/MarlinDev.svg)](https://travis-ci.org/MarlinFirmware/MarlinDev)

##### [RepRap.org Wiki Page](http://reprap.org/wiki/Marlin)

## Credits

The current Marlin dev team consists of:

 - Scott Lahteine [@thinkyhead] - English
 - [@Wurstnase] - Deutsch, English
 - F. Malpartida [@fmalpartida] - English, Spanish
 - Jochen Groppe [@CONSULitAS] - Deutsch, English
 - [@maverikou]
 - Chris Palmer [@nophead]
 - [@paclema]
 - Edward Patel [@epatel] - Swedish, English
 - Erik van der Zalm [@ErikZalm]
 - David Braam [@daid]
 - Bernhard Kubicek [@bkubicek]
 - Roxanne Neufeld [@Roxy-3DPrintBoard] - English

If your hardware supports it, you can build yourself a LCD-CardReader+Click+encoder combination. It will enable you to realtime tune temperatures,
accelerations, velocities, flow rates, select and print files from the SD card, preheat, disable the steppers, and do other fancy stuff.
One working hardware is documented here: http://www.thingiverse.com/thing:12663
Also, with just a 20x4 or 16x2 display, useful data is shown.

SD card folders:
----------------

If you have an SD card reader attached to your controller, also folders work now. Listing the files in pronterface will show "/path/subpath/file.g".
You can write to file in a subfolder by specifying a similar text using small letters in the path.
Also, backup copies of various operating systems are hidden, as well as files not ending with ".g".

SD card folders:
----------------

If you place a file auto[0-9].g into the root of the sd card, it will be automatically executed if you boot the printer. The same file will be executed by selecting "Autostart" from the menu.
First *0 will be performed, than *1 and so on. That way, you can heat up or even print automatically without user interaction.

Endstop trigger reporting:
--------------------------

If an endstop is hit while moving towards the endstop, the location at which the firmware thinks that the endstop was triggered is outputed on the serial port.
This is useful, because the user gets a warning message.
However, also tools like QTMarlin can use this for finding acceptable combinations of velocity+acceleration.

Coding paradigm:
----------------

Not relevant from a user side, but Marlin was split into thematic junks, and has tried to partially enforced private variables.
This is intended to make it clearer, what interacts which what, and leads to a higher level of modularization.
We think that this is a useful prestep for porting this firmware to e.g. an ARM platform in the future.
A lot of RAM (with enabled LCD ~2200 bytes) was saved by storing char []="some message" in Program memory.
In the serial communication, a #define based level of abstraction was enforced, so that it is clear that
some transfer is information (usually beginning with "echo:"), an error "error:", or just normal protocol,
necessary for backwards compatibility.

Interrupt based temperature measurements:
-----------------------------------------

An interrupt is used to manage ADC conversions, and enforce checking for critical temperatures.
This leads to less blocking in the heater management routine.

Implemented G Codes:
====================

*  G0  -> G1
*  G1  - Coordinated Movement X Y Z E
*  G2  - CW ARC
*  G3  - CCW ARC
*  G4  - Dwell S<seconds> or P<milliseconds>
*  G10 - retract filament according to settings of M207
*  G11 - retract recover filament according to settings of M208
*  G28 - Home all Axis
*  G29 - Detailed Z-Probe, probes the bed at 3 points.  You must de at the home position for this to work correctly.
*  G30 - Single Z Probe, probes bed at current XY location.
*  G90 - Use Absolute Coordinates
*  G91 - Use Relative Coordinates
*  G92 - Set current position to cordinates given

M Codes
*  M0   - Unconditional stop - Wait for user to press a button on the LCD (Only if ULTRA_LCD is enabled)
*  M1   - Same as M0
*  M17  - Enable/Power all stepper motors
*  M18  - Disable all stepper motors; same as M84
*  M20  - List SD card
*  M21  - Init SD card
*  M22  - Release SD card
*  M23  - Select SD file (M23 filename.g)
*  M24  - Start/resume SD print
*  M25  - Pause SD print
*  M26  - Set SD position in bytes (M26 S12345)
*  M27  - Report SD print status
*  M28  - Start SD write (M28 filename.g)
*  M29  - Stop SD write
*  M30  - Delete file from SD (M30 filename.g)
*  M31  - Output time since last M109 or SD card start to serial
*  M32  - Select file and start SD print (Can be used when printing from SD card)
*  M42  - Change pin status via gcode Use M42 Px Sy to set pin x to value y, when omitting Px the onboard led will be used.
*  M80  - Turn on Power Supply
*  M81  - Turn off Power Supply
*  M82  - Set E codes absolute (default)
*  M83  - Set E codes relative while in Absolute Coordinates (G90) mode
*  M84  - Disable steppers until next move, or use S<seconds> to specify an inactivity timeout, after which the steppers will be disabled.  S0 to disable the timeout.
*  M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
*  M92  - Set axis_steps_per_unit - same syntax as G92
*  M104 - Set extruder target temp
*  M105 - Read current temp
*  M106 - Fan on
*  M107 - Fan off
*  M109 - Sxxx Wait for extruder current temp to reach target temp. Waits only when heating
*         Rxxx Wait for extruder current temp to reach target temp. Waits when heating and cooling
*  M112 - Emergency stop
*  M114 - Output current position to serial port
*  M115 - Capabilities string
*  M117 - display message
*  M119 - Output Endstop status to serial port
*  M126 - Solenoid Air Valve Open (BariCUDA support by jmil)
*  M127 - Solenoid Air Valve Closed (BariCUDA vent to atmospheric pressure by jmil)
*  M128 - EtoP Open (BariCUDA EtoP = electricity to air pressure transducer by jmil)
*  M129 - EtoP Closed (BariCUDA EtoP = electricity to air pressure transducer by jmil)
*  M140 - Set bed target temp
*  M190 - Sxxx Wait for bed current temp to reach target temp. Waits only when heating
*         Rxxx Wait for bed current temp to reach target temp. Waits when heating and cooling
*  M200 D<millimeters>- set filament diameter and set E axis units to cubic millimeters (use S0 to set back to millimeters).
*  M201 - Set max acceleration in units/s^2 for print moves (M201 X1000 Y1000)
*  M202 - Set max acceleration in units/s^2 for travel moves (M202 X1000 Y1000) Unused in Marlin!!
*  M203 - Set maximum feedrate that your machine can sustain (M203 X200 Y200 Z300 E10000) in mm/sec
*  M204 - Set default acceleration: S normal moves T filament only moves (M204 S3000 T7000) im mm/sec^2  also sets minimum segment time in ms (B20000) to prevent buffer underruns and M20 minimum feedrate
*  M205 -  advanced settings:  minimum travel speed S=while printing T=travel only,  B=minimum segment time X= maximum xy jerk, Z=maximum Z jerk, E=maximum E jerk
*  M206 - set additional homeing offset
*  M207 - set retract length S[positive mm] F[feedrate mm/min] Z[additional zlift/hop], stays in mm regardless of M200 setting
*  M208 - set recover=unretract length S[positive mm surplus to the M207 S*] F[feedrate mm/min]
*  M209 - S<1=true/0=false> enable automatic retract detect if the slicer did not support G10/11: every normal extrude-only move will be classified as retract depending on the direction.
*  M218 - set hotend offset (in mm): T<extruder_number> X<offset_on_X> Y<offset_on_Y>
*  M220 S<factor in percent>- set speed factor override percentage
*  M221 S<factor in percent>- set extrude factor override percentage
*  M240 - Trigger a camera to take a photograph
*  M280 - Position an RC Servo P<index> S<angle/microseconds>, ommit S to report back current angle
*  M300 - Play beepsound S<frequency Hz> P<duration ms>
*  M301 - Set PID parameters P I and D
*  M302 - Allow cold extrudes
*  M303 - PID relay autotune S<temperature> sets the target temperature. (default target temperature = 150C)
*  M304 - Set bed PID parameters P I and D
*  M400 - Finish all moves
*  M401 - Lower z-probe if present
*  M402 - Raise z-probe if present
*  M500 - stores paramters in EEPROM
*  M501 - reads parameters from EEPROM (if you need reset them after you changed them temporarily).
*  M502 - reverts to the default "factory settings".  You still need to store them in EEPROM afterwards if you want to.
*  M503 - print the current settings (from memory not from eeprom)
*  M540 - Use S[0|1] to enable or disable the stop SD card print on endstop hit (requires ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED)
*  M600 - Pause for filament change X[pos] Y[pos] Z[relative lift] E[initial retract] L[later retract distance for removal]
*  M907 - Set digital trimpot motor current using axis codes.
*  M908 - Control digital trimpot directly.
*  M350 - Set microstepping mode.
*  M351 - Toggle MS1 MS2 pins directly.
*  M928 - Start SD logging (M928 filename.g) - ended by M29
*  M999 - Restart after being stopped by error


Configuring and compilation:
============================

Install the arduino software IDE/toolset v23 (Some configurations also work with 1.x.x)
   http://www.arduino.cc/en/Main/Software

Download the Marlin firmware
   https://github.com/ErikZalm/Marlin/tree/Marlin_v1
   Use the "Download Zip" button on the right.

For gen6/gen7 and sanguinololu the Sanguino directory in the Marlin dir needs to be copied to the arduino environment.
  copy ArduinoAddons\Arduino_x.x.x\sanguino <arduino home>\hardware\Sanguino

Start the arduino IDE.
Select Tools -> Board -> Arduino Mega 2560    or your microcontroller
Select the correct serial port in Tools ->Serial Port
Open Marlin.pde

Click the Verify/Compile button

Click the Upload button
If all goes well the firmware is uploading

That's ok.  Enjoy Silky Smooth Printing.

===============================================
Instructions for configuring Bed Auto Leveling
===============================================
Uncomment the "ENABLE_AUTO_BED_LEVELING" define (commented by default)

You will probably need a swivel Z-MIN endstop in the extruder. A rc servo do a great job.
Check the system working here: http://www.youtube.com/watch?v=3IKMeOYz-1Q (Enable English subtitles)
Teasing ;-) video: http://www.youtube.com/watch?v=x8eqSQNAyro

In order to get the servo working, you need to enable:

* \#define NUM_SERVOS 1 // Servo index starts with 0 for M280 command

* \#define SERVO_ENDSTOPS {-1, -1, 0} // Servo index for X, Y, Z. Disable with -1

* \#define SERVO_ENDSTOP_ANGLES {0,0, 0,0, 165,60} // X,Y,Z Axis Extend and Retract angles


The first define tells firmware how many servos you have.
The second tells what axis this servo will be attached to. In the example above, we have a servo in Z axis.
The third one tells the angle in 2 situations: Probing (165º) and resting (60º). Check this with command M280 P0 S{angle} (example: M280 P0 S60 moves the servo to 60º)

For RAMPS users:
----------------

By default, RAMPS have no power on servo bus (if you happen to have a multimeter, check the voltage on servo power pins).
In order to get the servo working, you need to supply 5V to 5V pin.. You can do it using your power supply (if it has a 5V output) or jumping the "Vcc" from Arduino to the 5V RAMPS rail.
These 2 pins are located just between the Reset Button and the yellow fuses... There are marks in the board showing 5V and VCC.. just connect them..
If jumping the arduino Vcc do RAMPS 5V rail, take care to not use a power hungry servo, otherwise you will cause a blackout in the arduino board ;-)


Next you need to define the Z endstop (probe) offset from hotend.
My preferred method:

* a) Make a small mark in the bed with a marker/felt-tip pen.
* b) Place the hotend tip as *exactly* as possible on the mark, touching the bed. Raise the hotend 0.1mm (a regular paper thickness) and zero all axis (G92 X0 Y0 Z0);
* d) Raise the hotend 10mm (or more) for probe clearance, lower the Z probe (Z-Endstop) with M401 and place it just on that mark by moving X, Y and Z;
* e) Lower the Z in 0.1mm steps, with the probe always touching the mark (it may be necessary to adjust X and Y as well) until you hear the "click" meaning the mechanical endstop was trigged. You can confirm with M119;
* f) Now you have the probe in the same place as your hotend tip was before. Perform a M114 and write down the values, for example: X:24.3 Y:-31.4 Z:5.1;
* g) You can raise the z probe with M402 command;
* h) Fill the defines bellow multiplying the values by "-1" (just change the signal)


* \#define X_PROBE_OFFSET_FROM_EXTRUDER -24.3
* \#define Y_PROBE_OFFSET_FROM_EXTRUDER 31.4
* \#define Z_PROBE_OFFSET_FROM_EXTRUDER -5.1


The following options define the probing positions. These are good starting values.
I recommend to keep a better clearance from borders in the first run and then make the probes as close as possible to borders:

* \#define LEFT_PROBE_BED_POSITION 30
* \#define RIGHT_PROBE_BED_POSITION 140
* \#define BACK_PROBE_BED_POSITION 140
* \#define FRONT_PROBE_BED_POSITION 30

A few more options:

* \#define XY_TRAVEL_SPEED 6000

X and Y axis travel speed between probes, in mm/min.
Bear in mind that really fast moves may render step skipping. 6000 mm/min (100mm/s) is a good value.

* \#define Z_RAISE_BEFORE_PROBING 10
* \#define Z_RAISE_BETWEEN_PROBINGS 10

The Z axis is lifted when traveling to the first probe point by Z_RAISE_BEFORE_PROBING value
and then lifted when traveling from first to second and second to third point by Z_RAISE_BETWEEN_PROBINGS.
All values are in mm as usual. 

That's it.. enjoy never having to calibrate your Z endstop neither leveling your bed by hand anymore ;-)
More features have been added by:
  - Alberto Cotronei [@MagoKimbra]
  - Lampmaker,
  - Bradley Feldman,
  - and others...

## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.

While we can't prevent the use of this code in products (3D printers, CNC, etc.) that are closed source or crippled by a patent, we would prefer that you choose another firmware or, better yet, make your own.

[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=ErikZalm&url=https://github.com/MarlinFirmware/Marlin&title=Marlin&language=&tags=github&category=software)