# hellomicrobit - How to create from scratch a project for an executable with yotta

## Create project

```
> mkdir hellomicrobit
> cd hellomicrobit
```

```
> yt init
Enter the module name: <hellomicrobit> 
Enter the initial version: <0.0.0> 
Is this an executable (instead of a re-usable library module)? <no> yes
Short description: Hello micro:bit :)
Author: Viny Meuh <vinymeuh@gmail.com>
What is the license for this project (Apache-2.0, ISC, MIT etc.)?  <Apache-2.0> MIT
```

## Define the compilation target for micro:bit

```
> yt target bbc-microbit-classic-gcc
info: get versions for bbc-microbit-classic-gcc
info: download bbc-microbit-classic-gcc@0.2.3 from the public module registry
info: get versions for mbed-gcc
info: download mbed-gcc@0.1.3 from the public module registry
```

Check with:

```
> yt target
bbc-microbit-classic-gcc 0.2.3
mbed-gcc 0.1.3
```

## Add dependencies

At a minimum for the micro:bit, add module [lancaster-university/microbit](https://github.com/lancaster-university/microbit)

```
> yt install lancaster-university/microbit 
info: microbit, lancaster-university/microbit
info: get versions for microbit
info: download microbit@v2.0.0-rc4 from GitHub lancaster-university/microbit
info: dependency microbit: ^2.0.0-rc4 written to module.json
info: get versions for microbit-dal
info: download microbit-dal@v2.0.0-rc4 from GitHub lancaster-university/microbit-dal
info: get versions for mbed-classic
info: download mbed-classic@microbit_hfclk+mb5 from GitHub lancaster-university/mbed-classic
info: get versions for ble
info: download ble@v2.5.0+mb3 from GitHub lancaster-university/BLE_API
info: get versions for ble-nrf51822
info: download ble-nrf51822@v2.5.0+mb6 from GitHub lancaster-university/nRF51822
info: get versions for nrf51-sdk
info: download nrf51-sdk@v2.2.0+mb4 from GitHub lancaster-university/nrf51-sdk
```

Check with:

```
> yt list
hellomicrobit 0.0.0
┗━ microbit 2.0.0-rc4
  ┗━ microbit-dal 2.0.0-rc4 yotta_modules/microbit-dal
    ┣━ mbed-classic 0.0.4 yotta_modules/mbed-classic
    ┣━ ble 2.5.0 yotta_modules/ble
    ┣━ ble-nrf51822 2.5.0 yotta_modules/ble-nrf51822
    ┗━ nrf51-sdk 2.2.0 yotta_modules/nrf51-sdk
```

Checks in file **module.json** that the module is not referenced with version. 

For example

```
...
  "dependencies": {
    "microbit": "^2.0.0-rc4"
  }
```

must be fixed

```
...
  "dependencies": {
    "microbit": "lancaster-university/microbit"
  }
```

## Code

Source files must be under **./source** subdirectory.

## Build

```
> yt build
```

If everything is fine, the executable will be placed under **./build/bbc-microbit-classic-gcc/source** and named **hellomicrobit-combined.hex**

Copy it on the micro:bit et voilà :)
