# DISCLAIMER

You use this software and instructions at your own risk - if you break something, hurt someone or something or anything else happens
that is entirely on you.

-------------------------------------------------------------------------------------------------------
# OVERVIEW

The Cruisin Brain was created as a brain for an electric car. 

That car could be a rear wheel drive car, it could be a 4x4 with dual electronic transaxle, it could be 2x4, it could be a single engine with rear transaxle or a dual motor with electronic transaxle, a tri motor with an electronic rear transaxle and a front mechanical transaxle. The car could be steered manually, using power steering or via skid steer. The car could have cruise control or no cruise control. The car could be overridden by external remote control. The car could use any motor controller that allowed itself to be controlled externally. The possibilities are endless.

This isn't possible when the smarts are inside the motor controllers, which is the current state of what is available. I set out to create a brain that can interface not only with the tech of today but the tech of tomorrow and be the brain of your electric car.

The Cruisin Brain is a drive by wire system that takes inputs from the driver as well as other sensors and translates them into outputs for the various systems within your electric car.

## DETAILS

At it's simplest the Cruisin Brain was developed to take input from two momentary switches (buttons) (named Right and Left) and translate button pushes into motion.

- Pressing the Right button, results in the car moving forwards
- Pressing both the Right and Left buttons results in the car moving reverse
- Holding the Right button for longer than 30 seconds, results in Cruise Control being enabled (car moves forward without input)
- When Cruise Control is enabled pressing the Left (at any time) or Right (5 seconds after Cruise Control is enabled) button disables Cruise Control and the car will brake
- Pressing no buttons results in the car braking/stopping (unless Cruise Control is enabled)
- Fully electronic braking

It can be much more complex than this but hopefully the above gives you an idea of how Cruisin Brain works and the simplicity of it being able to take two inputs and fully control an electric car.

## HISTORY

Cruisin Brain was developed on Arduino for some electric cars that I built for my children and their friends. You can see more details about the electric cars I built and how you could build one of your own here - https://nathanaherne.github.io/kids-electric-car/

## WARNING ON CRUISE CONTROL
This software has a feature called Cruise Control (enabled by default can be disabled) which results in Cruisin Brain holding full throttle without input after Forward has been commanded a set amount of time (default 30 seconds but can be changed). Cruise Control can have an unintended side effect where the driver gets out of the vehicle while Cruise Control is enabled, which results in the car continuing on its merry way without a driver.

-------------------------------------------------------------------------------------------------------

# MOTOR CONTROLLERS SUPPORTED

This software was developed to interface with one or more external motor controllers using PWM or serial commands. Cruisin Brain can be expanded to communicate using many other communication schemes with all sorts of motor controllers. Cruisin Brain is motor controller agnostic.

## Motor controllers that have been tested and work with Cruisin Brain

Theoretically Cruisin Brain can work with any motor controller as long as it configured to do so.

1. Dimension Engineering Syren50 (single motor control) (serial)
2. Dimension Engineering Sabertooth2x32 (dual motor control) (serial)
3. Spark Motor Controller (single motor control) (PWM)

### Syren50

Mobility scooters can have one motor with a physical differential or two motors, one motor per wheel. The Syren50 will work with both types. To use the Syren50 with one motor, just wire it as per the manual. To use the Syren50 with two motors, you should wire the motors in series so that you get an electronic differential.

NOTE: To use the Syren50 with a mobility scooter you will need to
1. remove the electronic brake attached to the end of the motor (unless you implement control of the brake using a separate piece of hardware). 
2. Cut off all proprietary plugs and connect the correct wires directly to the motor controller as per the Syren50's manual.

### Sabertooth2x32

The Sabertooth2x32 has the ability to control two electric motors (among a number of other features). This software has been designed to support the Sabertooth2x32. The main issue with using the Sabertooth2x32 with two rear motors is there will be no differential, ideally I would implement an electronic differential which would make things better. The Sabertooth2x32 is useful can be used to control a single motor and to control the electronic brake, though at this time, I have yet to implement or test this functionality.

The Sabertooth 2x32 has the ability to engage/disengage the electronic brake that you often find on mobility scooter motors so you can leave it attached if you wish. This is a good safety feature, like a hand brake in a car but it is not required.

<br>

-------------------------------------------------------------------------------------------------------

# WIRING

The software expects the following wiring connections (the Cruisin Brain pins can be changed in settings.h):

1. Right button - digital pin 5 and Gnd on Cruisin Brain board (pushing the button grounds the pin)
2. Left button - digital pin 7 and Gnd on Cruisin Brain board (pushing the button grounds the pin)

If using Syren50 or Sabertooth2x32

1. Serial Tx to S1 on motor controller
2. 5v and Gnd on Cruisin Brain to 5v and 0v on motor controller (the Cruisin Brain can be powered by the motor controller) or an external 5v source.

If using digital potentiometer
1. Digital pin 10 on Cruisin Brain to (SS) or Chip Select pin on potentiometer chip,
2. Digital pin 11 (or MOSI) on Cruisin Brain board to MOSI pin on potentiometer chip
3. Digital pin 12 (or MISO) on Cruisin Brain to MISO pin on potentiometer chip
4. Digital pin 13 (or SCK) on  Cruisin Brain to SCK pin on potentiometer chip

You will need to wire potentiometer HIGH, potentiometer wiper and potentiometer LOW from the controller to
the corresponding pins on the digital potentiometer.

<br>

-------------------------------------------------------------------------------------------------------

# CONFIGURATION

You can configure Cruisin Brain in the settings.h file.

The top of the file provides a number of configurable options for the software, including (but not limited to)

1. Motor Controller options
2. Reverse motor direction (change forward motion to reverse motion)
3. Maximum Forward speed
4. Maximum Reverse speed
5. Maximum CruiseControl speed
6. Turn on/off debugging output

You can also configure acceleration (for Forward/Reverse/Cruise Control) and deceleration (braking)

<br>
