# UCSB WaferSat
This repository contains software which runs on the [UCSB Deepspace and Cosmology Lab](https://www.deepspace.ucsb.edu)’s [Wafer Scale Spacecraft](https://www.deepspace.ucsb.edu/projects/wafer%20scale%20spacecraft%20development) project.
## Requirements
Currently, this project only compiles on Linux systems.
 
* GNU Make
* GNU ARM Toolchain (mainly `arm-none-eabi-gcc` and `arm-none-eabi-gdb`, and `arm-none-eabi-newlib`)
* [stlink](https://github.com/texane/stlink)
## Development Hardware Connections
* Breakout USB-micro -> USB power source
* Breakout PROGRAM -> ST-Link via ribbon cable
* ST-Link USB-mini -> development computer
* (optional) Breakout CONSOLE -> development computer via FTDI cable
 
If the CONSOLE port is unconnected, then `LOG_SERIAL` in `log.h` should be set to 0 in order to avoid possible fatal hanging.
We should probably have timeouts or something so that doesn’t happen. <- **TODO**
## Build
Just a `make` -- nothing special.
## Flash
*Note: you may need to change port permissions or run as superuser for the following*
 
`$ st-flash write build/ch.elf 0x8000000`
## Debug
*Note: you may need to change port permissions or run as superuser for the following*
 
`$ st-util -p 4444`

And from a different terminal:
```
$ arm-none-eabi-gdb build/ch.elf
(gdb) target extended localhost:4444
(gdb) load
(gdb)
```
## TODO
[ ] APRS Radio communication
[ ] Add back membench
[ ] Have an actual conf file
[ ] Create tests
[ ] clean ov5640.c -- lot of stuff in there
[ ] Log arrays
[ ] Many GPS messages are reading with invalid checksums? 
[ ] Read all values out of the IMU
[ ] Configure and use the EMMC on the three-inch WaferSat model
[ ] Laser comms
