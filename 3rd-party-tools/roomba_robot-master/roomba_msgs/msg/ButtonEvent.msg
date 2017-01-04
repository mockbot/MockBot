# Provides a button event.
# This message is generated whenever a particular button is pressed or released.
# Note that, despite buttons field on SensorState messages, state field is not a
# bitmask, but the new state of a single button.

uint8 Clean = 0
uint8 Spot = 1
uint8 Dock = 2
uint8 Day = 3
uint8 Hour = 4
uint8 Minute = 5
uint8 Schedule = 6
uint8 Clock = 7

uint8 RELEASED = 0
uint8 PRESSED  = 1

time stamp
uint8 button
uint8 state
