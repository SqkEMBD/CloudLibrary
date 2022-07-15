/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

uint8_t buffer[64];
uint8_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);
uint8_t usb_buffer[64];
UART_HandleTypeDef huart1;

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
		0x06, 0x00, 0xff, //Usage Page(Undefined )
		0x09, 0x01, // USAGE (Undefined)
		0xa1, 0x01, // COLLECTION (Application)
		0x15, 0x00, // LOGICAL_MINIMUM (0)
		0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
		0x75, 0x08, // REPORT_SIZE (8)
		0x95, 0x40, // REPORT_COUNT (64)
		0x09, 0x01, // USAGE (Undefined)
		0x81, 0x02, // INPUT (Data,Var,Abs)
		0x95, 0x40, // REPORT_COUNT (64)
		0x09, 0x01, // USAGE (Undefined)
		0x91, 0x02, // OUTPUT (Data,Var,Abs)
		0x95, 0x01, // REPORT_COUNT (1)
		0x09, 0x01, // USAGE (Undefined)
		0xb1, 0x02, // FEATURE (Data,Var,Abs)
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */




/* USER CODE END PRIVATE_VARIABLES */


/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t* state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t* state)
{
	/* USER CODE BEGIN 6 */


	memcpy(buffer, state, 64 * sizeof(uint8_t));
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)buffer,64); // PC HID Terminal

	USBD_Changename(buffer);

	return (0);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

uint8_t calculateChecksum(uint8_t* startByte, uint8_t* endByte)
{
    uint8_t checksum = 0;
    while(startByte <= endByte)
    {
        checksum += *startByte;
        startByte++;
    }
    checksum = ~checksum + 1;
    return checksum;
}

void MCU_UART_Transmit(uint8_t *Data, uint16_t dataSize)
{
    for(uint16_t i = 0; i < dataSize; i++)
    {
	      HAL_UART_Transmit(&huart1, &Data[i], 1, 50);
    }
}

void USBD_Changename(uint8_t* usbbuffer)
{
	uint8_t buffer[32];
	uint8_t* ptr_packet_len = &usbbuffer[0]; // ptr to Add:usbbuffer[0] -> len
	uint8_t packet_len = *(ptr_packet_len) + 1 ;  // ptr to uint8_t 1-> cmdID


	uint8_t crc_pos = packet_len+3;

	buffer[0] = 0xAA;
	buffer[1] = 0x00;
	buffer[2] = packet_len; 	// Data_len
	buffer[3] = 0x05; 			// BTM CMD_ID
	memcpy(buffer + 4, &usbbuffer[1], packet_len+4 );

//	buffer[crc_pos] = 'X';
	buffer[crc_pos] = calculateChecksum(&buffer[2], &buffer[packet_len+3]) ; // CRC

	uint8_t packet_end = crc_pos+1;

//	uint8_t checksum = calculateChecksum(&buffer[2], &buffer[end_packet]) ; // CRC
//	uint8_t checksum = 'X';

	for(uint8_t i = 0; i < packet_end; i++)
	{
		HAL_UART_Transmit(&huart1, &buffer[i], 1, 100);
	}


}




/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

