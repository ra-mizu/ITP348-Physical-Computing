---
marp: false
theme: itp

week: 11
category: lectures
title: Ultrasonic Distance Sensor
---

<!-- headingDivider: 2 -->

# Ultrasonic Distance Sensor

<img src="lecture_ultrasonic_distance_sensor.assets/1574364327550.png" alt="1574364327550" style="width:800px;" />





## Ultrasonic Distance Sensor

* Like SONAR! 
* Sends 40 KHz sound pulses (higher than human hearing)
* Waits for return sound wave ("echoes" or bounces off nearby objects)
* Distance to object can be calculated

## Uses

* Auto-range finder
* Self-parking cars
* Obstacle avoidance
* Autonomous vehicles
* Fun fact: This is how dolphins and bats navigate

## Parameters

* Operating range

  * 2 cm - 4 m (1 in - 13 ft)

* Angle

  * 15 degrees

  

## Sensor Wiring

| Sensor | Argon     | Function                    |
| ------ | --------- | --------------------------- |
| GND    | GND       | Ground                      |
| VCC    | VUSB      | Power **(requires 5v)**     |
| TRIG   | Ouput Pin | start output pulse sequence |
| ECHO   | Input Pin | receive reflection response |

## Timing Diagram
<img src="lecture_ultrasonic_distance_sensor.assets/1574365317310.png" alt="1574365317310" style="width:1200px" />

## Timing Part 1: Trigger

* Output sequence
  * LOW for 2 microseconds 
  * HIGH for 10 microseconds
  * LOW

```c++
delayMicroseconds(<<DELAY_VAL>>);
```

* Sensor sends out 8 sonic pulses

## Timing Part 2: Echo

* Sensor "listens" for sound wave to reflect / bounce off object
* Sensor automatically makes echo pin **LOW**
* When sound wave reflection is received, echo pin goes **HIGH**
* In order to measure the time it takes for an input to be received, use the ```pulseIn()```

## Measure Time with ```pulseIn```

* Syntax

```c++
//measure time in microseconds
//returns 0 if no signal received after 3 seconds
int time = pulseIn(<<PIN>>, <<VALUE>>); 
```
* Example

```c++
//Start timing when D2 is LOW
//Stop timing when D2 is HIGH
int time = pulseIn(D2, HIGH); 
```

## Calculating Distance

* ```pulseIn``` retuns the time for a signal to reach the nearest object and return
* How do we calculate the distance? Let's start with **cm**
* Speed of sound @ 20°C (68 ° F) = 343.5 m/s 

<!-- 
speed = dist/time -> dist = time*speed
convert speed from m/s to c/uS
  speed(m/s) * 100 (cm/m) * 1/10^6 (s/uS)
  speed = 0.03435 cm/uS
dist = 0.03435 * time  
NOTE: dist is the round trip time so divide by 2 for distance to object
CONV_FACTOR_CM_TO_IN = 0.3437
-->

## Cautions

* Sound waves can reflect off surfaces in room can give incorrect readings
* For example, air conditioning vents and other nearby ultrasonic sensors can cause interference
* There should be **500 ms** delay between readings

## Lab

* Getting started
  * Download project: Go to [http://kinolien.github.io/gitzip/](http://kinolien.github.io/gitzip/)
  * Paste the following link into the top right
    https://github.com/reparke/ITP348-Physical-Computing/tree/master/_exercises/week11/ultrasonic_oled_start

## Lab

* Connect the ultrasonic distance sensor
* Using the serial monitor, display
  * Error message when out of range
  * Warning message when less than 5 inches
  * Distance message otherwise

## Credit

- [Sparkfun](https://www.sparkfun.com/products/15569)
- [Sensor Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)

