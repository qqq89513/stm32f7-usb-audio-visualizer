# USB Audio Visualizer
An audio visualizer as an USB sound card.  
Thanks to [DiscoveryF7Audio](http://www.tjaekel.com/DiscoveryF7Audio/index.html), I don't have to crack the USB audio and on board DAC playback on my own.

## Features
> Demonstration Video
> [![](https://user-images.githubusercontent.com/35174145/106248618-34ee4880-624c-11eb-80fc-388bd78132eb.png)](http://www.youtube.com/watch?v=4pvzuPMfhR8 "")
- Recongized as an USB audio sound card(via USB_FS connector on the board)
- Audio Playback(via 3.5mm OUT on the board)
- Output volume adjustment
  - Via slide bar at the bottom of the GUI
  - Scale of left and right VU-meters changes with the slider
  - Scale of the wave graph doesn't change with the slider
- Wave graph
  - Color adjustment
  - If left and right audio are different, the graph will be partially columnized
    |                                                 Sin wave(550 Hz)                                                |                                                 Sin wave(550 Hz)                                                |
    |:---------------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------:|
    |                                           Left-right channel balanced                                           |                                               Right channel louder                                              |
    | ![image](https://user-images.githubusercontent.com/35174145/106250988-60266700-624f-11eb-9abe-5d60a2c6bcf3.png) | ![image](https://user-images.githubusercontent.com/35174145/106250995-63215780-624f-11eb-9946-10a05fc4d054.png) |

## Development Enviroment
It's possible to have this project build in GNU enviroment, not replying on STM32CubeIDE, just using `makefile`. When generating code from STM32CubeMX, you can select project as Keil, Eclipse, gcc..., etc.
- IDE: STM32CubeIDE 1.4.0  
- Toolchain: arm-none-eabi, GNU Arm Embedded Toolchain 9-2020-q2-update 9.3.1  
- Code Generator: STM32CubeMX 6.0.1
- GUI Framework: TouchGFX 4.15.0  
- OS: Windows 10  
<br>

## TODO
  - [ ] Fix #9 Audio corrupts(electronic noise) sometimes
  - [ ] Feat: Plot in frequency domain with histogram by using fast fourier transformation.
  - [ ] Feat: Change the frequency domain and output it in realtime, like an equalizer.

## File Structures
- Folder Tree
  ```c
  equalizer/
  ├── Core            // Top layer, main entry
  │   ├── Inc         // top layer header files
  │   └── Src         // main.c and interrupt subroutines here
  │
  ├── Drivers         // Mostly auto-generated, do not modify
  │   ├── BSP         // board support package
  │   ├── CMSIS
  │   └── STM32F7xx_HAL_Driver
  │
  ├── Middlewares     // Touchgfx and USB libraries
  │
  ├── TouchGFX        // GUI
  │   ├── assets      // fonts, images, texts
  │   ├── build       // object files compiled by touchGFX
  │   ├── generated   // auto-generated, do not modify
  │   ├── gui         // User features implementation. It is auto-generated only once.
  │   ├── equalizer.touchgfx  // touchGFX project file, json format
  │   └── simulator   // Visual Studio simulator project, not used
  │
  ├── .project        // stm32cubeIDE project file
  └── equalizer.ioc   // CubeMX project file
  ```
- Important files  
  | Description                   | Path                                            |
  |-------------------------------|-------------------------------------------------|
  | STM32CubeIDE project          | ./.project                                      |
  | GUI project (touchGFX)        | ./TouchGFX/equalizer.touchgfx                   |
  | GUI Features                  | ./TouchGFX/gui/src/screen_screen/screenView.cpp |
  | USB audio to on board DAC     | ./USB_DEVICE/App/usbd_audio_if.c                |
  | Binrary (not included in source control) | ./STM32CubeIDE/Debug/equalizer.bin              |
<br>
