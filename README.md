BrightRoll Palo Alto Arcade
=========

This program is for an Arduino Leonardo, and allows for the control of a joystick and arcade buttons at BrightRoll's Palo Alto front door.  Key presses are are held, without repeating, until a release signal is sent (just as a real keyboard would do, when you hold a key down).

## Keys are as follows:

```bash
up: w (pin 12)
down: s (pin 11)
left: a (pin 10)
right: d (pin 9)
fire1: v (pin 8)
fire2: b (pin 7)
fire3: n (pin 6)
```

Pull pin 4 off of ground to prevent USB keyboard characters from overwhelming the computer. The Arduino must be reset after doing so.

## Wiring

Internal pull-up resistors are used on all inputs.  Signals are picked up when the mechanical switch on the arcade panel grounds the input line.

## Noise

If a long wire is used to connect to the Arcade, noise may cause false character signals.  In that case, tie each input line to 5v with a 10k resistor.

## HAX Team

* Owen
* Jens
* ChrisD
* Wing
* Jason
