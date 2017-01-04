# Sends a command for controlling an LED.

# led
uint8 Warning = 0
uint8 Dock = 1
uint8 Spot = 2
uint8 Dirt = 3
uint8 Clean = 4
uint8 Sunday = 5
uint8 Monday = 6
uint8 Tuesday = 7
uint8 Wednesday = 8
uint8 Thursday = 9
uint8 Friday = 10
uint8 Saturday = 11
uint8 Colon = 12
uint8 PM = 13
uint8 AM = 14
uint8 Clock = 15
uint8 Schedule = 16

uint8 button
bool state
# You can only control the color and brightness on the Clean LED
uint8 color
uint8 brightness
