# Cloud-BT2 Firmware Development

Cloud-BT2 Wall Plate Bluetooth Audio

## Cloud-BT1 
[Cloud BT1 Bluetooth Module](https://www.cloud.co.uk/news/bt1-bluetooth-module-shipping)

## Embedded Devices

### MCU

ST-Microelectronics: [STM32G0B0RE](https://www.st.com/en/microcontrollers-microprocessors/stm32g0b0re.html)

### Bluetooth Module

Microchip: [Microchip-BM83](https://www.microchip.com/en-us/product/BM83)

## Technical Documents

### MCU

STM32G0B0RE Datasheet: [STM32G0B0RE](https://www.st.com/resource/en/datasheet/stm32g0b0re.pdf)

STM32G0 HAL-API: [STM32G0 HAL-API](https://www.st.com/resource/en/user_manual/um2319-description-of-stm32g0-hal-and-lowlayer-drivers-stmicroelectronics.pdf)

### Bluetooth 

[IS2083/BM83 Bluetooth Application Design Guide](https://ww1.microchip.com/downloads/en/Appnotes/00003118C.pdf)

[BM83 Host MCU Firmware Development Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/BM83_Host_MCU_Firmware_Development_Guide_DS50002896A.pdf)

[Reference Design Schematics](https://ww1.microchip.com/downloads/en/DeviceDoc/BM83%20Embedded%20Mode%20Reference%20Circuit.pdf)

[Firmware MSPK2v1.3 Release Note](https://ww1.microchip.com/downloads/en/DeviceDoc/MSPK2v1.3_Release_Notes.pdf)

[IS2083-SDK](https://ww1.microchip.com/downloads/en/DeviceDoc/IS2083%20Software%20&%20Tools%20(v1.0.3).zip)

## Sample code

```c

// GPIO Control using HAL API
HAL_GPIO_Write(GPIO_PIN_XX);

// Get Pin Value (pinRead)
HAL_GPIO_Read(GPIO_PIN_XX);

```

## License

.... Commercial