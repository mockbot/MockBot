# Provides a wheel drop event.
# This message is generated whenever one of the wheels is dropped (robot fell
# or was raised) or raised (normal condition).
# Note that, despite wheel_drop field on SensorState messages, state field is
# not a bitmask, but the new state of a single sensor.

# state
uint8 RAISED  = 0
uint8 DROPPED = 1

Header header
uint8 state
