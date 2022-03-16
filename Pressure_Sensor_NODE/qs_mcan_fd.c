/*
 * Copyright (c) 2019 System Industrie Electronic GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* \file  SAMV71_DPF.2.4.182/qs_mcan_fd.c */
/* \brief SAM MCAN Quick Start for FD mode */
 
 /**
 *  \mainpage MCAN example
 *
 *  \par Purpose
 *
 *  This example demonstrates the basic functions of MCAN controller.
 *
 *  \par Requirements
 *
 *  This package can be used with two SAMV71 Xplained Ultra boards.
 *  The CAN1 in two board should be connected externally before running
 *  the example.
 *
 *  \par Description
 *
 *  In this example, one board sends messages over CAN bus to another board.
 *  The CAN message will display on the terminal window.
 *
 *  \par Usage
 *
 *  -# Build the program and download it into the evaluation board.
 *  -# On the computer, open and configure a terminal application with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Connect CAN1 in two boards.
 *  -# Start the application.
 *  -# Upon startup, the application will output the following lines
 *     on the terminal window.
 *      \code
			"  -- Select the action:\r\n"
			"  0: Set standard filter ID 0: 0x45A, store into Rx buffer. \r\n"
			"  1: Set standard filter ID 1: 0x469, store into Rx FIFO 0. \r\n"
			"  2: Send FD standard message with ID: 0x45A and 64 byte data 0 to 63. \r\n"
			"  3: Send FD standard message with ID: 0x469 and 64 byte data 128 to 191. \r\n"
			"  4: Set extended filter ID 0: 0x100000A5, store into Rx buffer. \r\n"
			"  5: Set extended filter ID 1: 0x10000096, store into Rx FIFO 1. \r\n"
			"  6: Send FD extended message with ID: 0x100000A5 and 64 byte data 0 to 63. \r\n"
			"  7: Send FD extended message with ID: 0x10000096 and 64 byte data 128 to 191. \r\n"
			"  a: Send normal standard message with ID: 0x469 and 8 byte data 0 to 7. \r\n"
			"  h: Display menu \r\n\r\n");
 \endcode
 *  -# Press '0' or '1' or '4'  or '5' key in the terminal window to configure one board to
 *     receive CAN message.
 *  -# Press '2' or '3' or '6'  or '7' key in the terminal window to configure another board to
 *     send CAN message. The message will be displayed on the terminal window.
 */

#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <string.h>
#include <misc/printk.h>
#include <console.h>
#include "conf_can_sam.h"
#include "can_sam.h"

#define LED_PORT LED0_GPIO_CONTROLLER
#define LED	 LED0_GPIO_PIN

#define CAN_SILENT_PORT "PORTA"
#define CAN_SILENT_PIN  1

/* 1000 msec = 1 sec */
#define SLEEP_TIME	500

/* module_inst */
static struct mcan_module mcan_instance;

/* mcan_filter_setting */
#define MCAN_RX_STANDARD_FILTER_INDEX_0    0
#define MCAN_RX_STANDARD_FILTER_INDEX_1    1
#define MCAN_RX_STANDARD_FILTER_ID_0     0x45A
#define MCAN_RX_STANDARD_FILTER_ID_0_BUFFER_INDEX     2
#define MCAN_RX_STANDARD_FILTER_ID_1     0x469
#define MCAN_RX_EXTENDED_FILTER_INDEX_0    0
#define MCAN_RX_EXTENDED_FILTER_INDEX_1    1
#define MCAN_RX_EXTENDED_FILTER_ID_0     0x100000A5
#define MCAN_RX_EXTENDED_FILTER_ID_0_BUFFER_INDEX     1
#define MCAN_RX_EXTENDED_FILTER_ID_1     0x10000096

/* mcan_transfer_message_setting */
#define MCAN_TX_BUFFER_INDEX    0
static uint8_t tx_message_0[CONF_MCAN_ELEMENT_DATA_SIZE];
static uint8_t tx_message_1[CONF_MCAN_ELEMENT_DATA_SIZE];


/* mcan_receive_message_setting */
static volatile uint32_t standard_receive_index = 0;
static volatile uint32_t extended_receive_index = 0;
static struct mcan_rx_element_fifo_0 rx_element_fifo_0;
static struct mcan_rx_element_fifo_1 rx_element_fifo_1;
static struct mcan_rx_element_buffer rx_element_buffer;

/**
 * \brief Register handler for interrupt
 *
 * For NVIC the interrupt vectors are put in vector table. So nothing
 * to do to register them, except defined the vector function with
 * right name.
 *
 * Usage:
 * \code
	irq_initialize_vectors();
	irq_register_handler(foo_irq_handler);
\endcode
 *
 * \note The function \a func must be defined with the \ref ISR macro.
 * \note The functions prototypes can be found in the device exception header
 *       files (exceptions.h).
 */
#  define irq_register_handler(int_num, int_prio)                      \
	NVIC_ClearPendingIRQ(    (IRQn_Type)int_num);                      \
	NVIC_SetPriority(    (IRQn_Type)int_num, int_prio);                \
	NVIC_EnableIRQ(      (IRQn_Type)int_num);                          \

#define MCAN_IRQ_PRIORITY    0
#define MCAN_IRQ_FLAGS       0
extern void MCAN1_INT0_Handler(void);

/**
 * \brief MCAN module initialization.
 *
 */
static void configure_mcan(void)
{
	uint32_t i;
	/* Initialize the memory. */
	for (i = 0; i < CONF_MCAN_ELEMENT_DATA_SIZE; i++) {
		tx_message_0[i] = i;
		tx_message_1[i] = i + 0x80;
	}

	/* Initialize the module. */
	struct mcan_config config_mcan;
	mcan_get_config_defaults(&config_mcan);
	mcan_init(&mcan_instance, MCAN1, &config_mcan);

	mcan_enable_fd_mode(&mcan_instance);
	mcan_start(&mcan_instance);

	/* Enable interrupts for this MCAN module */
	irq_register_handler(MCAN1_INT0_IRQn, 1);
	mcan_enable_interrupt(&mcan_instance, MCAN_FORMAT_ERROR | MCAN_ACKNOWLEDGE_ERROR
			| MCAN_BUS_OFF);
	IRQ_CONNECT(MCAN1_INT0_IRQn, MCAN_IRQ_PRIORITY, MCAN1_INT0_Handler, MCAN1, MCAN_IRQ_FLAGS);
	irq_enable(MCAN1_INT0_IRQn);
}

/**
 * \brief set receive standard MCAN ID, dedicated buffer
 *
 */
static void mcan_set_standard_filter_0(void)
{
	struct mcan_standard_message_filter_element sd_filter;

	mcan_get_standard_message_filter_element_default(&sd_filter);
	sd_filter.S0.bit.SFID2 = MCAN_RX_STANDARD_FILTER_ID_0_BUFFER_INDEX;
	sd_filter.S0.bit.SFID1 = MCAN_RX_STANDARD_FILTER_ID_0;
	sd_filter.S0.bit.SFEC =
			MCAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_STRXBUF_Val;

	mcan_set_rx_standard_filter(&mcan_instance, &sd_filter,
			MCAN_RX_STANDARD_FILTER_INDEX_0);
	mcan_enable_interrupt(&mcan_instance, MCAN_RX_BUFFER_NEW_MESSAGE);
}

/**
 * \brief set receive standard MCAN ID,FIFO buffer.
 *
 */
static void mcan_set_standard_filter_1(void)
{
	struct mcan_standard_message_filter_element sd_filter;

	mcan_get_standard_message_filter_element_default(&sd_filter);
	sd_filter.S0.bit.SFID1 = MCAN_RX_STANDARD_FILTER_ID_1;

	mcan_set_rx_standard_filter(&mcan_instance, &sd_filter,
			MCAN_RX_STANDARD_FILTER_INDEX_1);
	mcan_enable_interrupt(&mcan_instance, MCAN_RX_FIFO_0_NEW_MESSAGE);
}

/**
 * \brief set receive extended MCAN ID, dedicated buffer
 *
 */
static void mcan_set_extended_filter_0(void)
{
	struct mcan_extended_message_filter_element et_filter;

	mcan_get_extended_message_filter_element_default(&et_filter);
	et_filter.F0.bit.EFID1 = MCAN_RX_EXTENDED_FILTER_ID_0;
	et_filter.F0.bit.EFEC =
			MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STRXBUF_Val;
	et_filter.F1.bit.EFID2 = MCAN_RX_EXTENDED_FILTER_ID_0_BUFFER_INDEX;

	mcan_set_rx_extended_filter(&mcan_instance, &et_filter,
			MCAN_RX_EXTENDED_FILTER_INDEX_0);
	mcan_enable_interrupt(&mcan_instance, MCAN_RX_BUFFER_NEW_MESSAGE);
}

/**
 * \brief set receive extended MCAN ID,FIFO buffer.
 *
 */
static void mcan_set_extended_filter_1(void)
{
	struct mcan_extended_message_filter_element et_filter;

	mcan_get_extended_message_filter_element_default(&et_filter);
	et_filter.F0.bit.EFID1 = MCAN_RX_EXTENDED_FILTER_ID_1;

	mcan_set_rx_extended_filter(&mcan_instance, &et_filter,
			MCAN_RX_EXTENDED_FILTER_INDEX_1);
	mcan_enable_interrupt(&mcan_instance, MCAN_RX_FIFO_1_NEW_MESSAGE);
}

/**
 * \brief send standard CAN message,
 *
 *\param id_value standard CAN ID
 *\param *data  content to be sent
 */
static void mcan_send_standard_message(uint32_t id_value, uint8_t *data)
{
	uint32_t i;
	struct mcan_tx_element tx_element;

	mcan_get_tx_buffer_element_defaults(&tx_element);
	tx_element.T0.reg |= MCAN_TX_ELEMENT_T0_STANDARD_ID(id_value);
	tx_element.T1.bit.DLC = 8;
	for (i = 0; i < 8; i++) {
		tx_element.data[i] = *data;
		data++;
	}

	mcan_set_tx_buffer_element(&mcan_instance, &tx_element,
			MCAN_TX_BUFFER_INDEX);
	mcan_tx_transfer_request(&mcan_instance, 1 << MCAN_TX_BUFFER_INDEX);
}

/**
 * \brief send standard CAN message in fd mode,
 *
 *\param id_value standard CAN ID
 *\param *data  content to be sent
 */
static void mcan_fd_send_standard_message(uint32_t id_value, uint8_t *data)
{
	uint32_t i;
	struct mcan_tx_element tx_element;

	mcan_get_tx_buffer_element_defaults(&tx_element);
	tx_element.T0.reg |= MCAN_TX_ELEMENT_T0_STANDARD_ID(id_value);
	tx_element.T1.reg = (MCAN_TX_ELEMENT_T1_DLC(MCAN_TX_ELEMENT_T1_DLC_DATA64_Val) |
			MCAN_TX_ELEMENT_T1_FDF | MCAN_TX_ELEMENT_T1_BRS);
	for (i = 0; i < CONF_MCAN_ELEMENT_DATA_SIZE; i++) {
		tx_element.data[i] = *data;
		data++;
	}

	mcan_set_tx_buffer_element(&mcan_instance, &tx_element,
			MCAN_TX_BUFFER_INDEX);
	mcan_tx_transfer_request(&mcan_instance, 1 << MCAN_TX_BUFFER_INDEX);
}

/**
 * \brief send extended CAN message,
 *
 *\param id_value extended CAN ID
 *\param *data  content to be sent
 */
static void mcan_fd_send_extended_message(uint32_t id_value, uint8_t *data)
{
	uint32_t i;
	struct mcan_tx_element tx_element;

	mcan_get_tx_buffer_element_defaults(&tx_element);
	tx_element.T0.reg |= MCAN_TX_ELEMENT_T0_EXTENDED_ID(id_value) |
			MCAN_TX_ELEMENT_T0_XTD;
	tx_element.T1.reg = (MCAN_TX_ELEMENT_T1_EFC | 
			MCAN_TX_ELEMENT_T1_DLC(MCAN_TX_ELEMENT_T1_DLC_DATA64_Val) | 
			MCAN_TX_ELEMENT_T1_FDF | MCAN_TX_ELEMENT_T1_BRS);
	for (i = 0; i < CONF_MCAN_ELEMENT_DATA_SIZE; i++) {
		tx_element.data[i] = *data;
		data++;
	}

	mcan_set_tx_buffer_element(&mcan_instance, &tx_element,
			MCAN_TX_BUFFER_INDEX);
	mcan_tx_transfer_request(&mcan_instance, 1 << MCAN_TX_BUFFER_INDEX);
}

/**
 * \brief Interrupt handler for MCAN,
 *   inlcuding RX,TX,ERROR and so on processes.
 */
void MCAN1_INT0_Handler(void)
{
	volatile uint32_t status, i, rx_buffer_index;
	status = mcan_read_interrupt_status(&mcan_instance);

	if (status & MCAN_RX_BUFFER_NEW_MESSAGE) {
		mcan_clear_interrupt_status(&mcan_instance, MCAN_RX_BUFFER_NEW_MESSAGE);
		for (i = 0; i < CONF_MCAN0_RX_BUFFER_NUM; i++) {
			if (mcan_rx_get_buffer_status(&mcan_instance, i)) {
				rx_buffer_index = i;
				mcan_rx_clear_buffer_status(&mcan_instance, i);
				mcan_get_rx_buffer_element(&mcan_instance, &rx_element_buffer,
				rx_buffer_index);
				if (rx_element_buffer.R0.bit.XTD) {
					printk("\n\r Extended FD message received in Rx buffer. The received data is: \r\n");
				} else {
					printk("\n\r Standard FD message received in Rx buffer. The received data is: \r\n");
				}
				for (i = 0; i < CONF_MCAN_ELEMENT_DATA_SIZE; i++) {
					printk("  %d",rx_element_buffer.data[i]);
				}
				printk("\r\n\r\n");
			}
		}
	}

	if (status & MCAN_RX_FIFO_0_NEW_MESSAGE) {
		mcan_clear_interrupt_status(&mcan_instance, MCAN_RX_FIFO_0_NEW_MESSAGE);
		mcan_get_rx_fifo_0_element(&mcan_instance, &rx_element_fifo_0,
				standard_receive_index);
		mcan_rx_fifo_acknowledge(&mcan_instance, 0,
				standard_receive_index);
		standard_receive_index++;
		if (standard_receive_index == CONF_MCAN0_RX_FIFO_0_NUM) {
			standard_receive_index = 0;
		}
		if (rx_element_fifo_0.R1.bit.EDL) {
			printk("\n\r Standard FD message received in FIFO 0. The received data is: \r\n");
			for (i = 0; i < CONF_MCAN_ELEMENT_DATA_SIZE; i++) {
				printk("  %d",rx_element_fifo_0.data[i]);
			}
		} else {
			printk("\n\r Standard normal message received in FIFO 0. The received data is: \r\n");
			for (i = 0; i < rx_element_fifo_0.R1.bit.DLC; i++) {
				printk("  %d",rx_element_fifo_0.data[i]);
			}
		}
		printk("\r\n\r\n");
	}

	if (status & MCAN_RX_FIFO_1_NEW_MESSAGE) {
		mcan_clear_interrupt_status(&mcan_instance, MCAN_RX_FIFO_1_NEW_MESSAGE);
		mcan_get_rx_fifo_1_element(&mcan_instance, &rx_element_fifo_1,
				extended_receive_index);
		mcan_rx_fifo_acknowledge(&mcan_instance, 0,
				extended_receive_index);
		extended_receive_index++;
		if (extended_receive_index == CONF_MCAN0_RX_FIFO_1_NUM) {
			extended_receive_index = 0;
		}

		printk("\n\r Extended FD message received in FIFO 1. The received data is: \r\n");
		for (i = 0; i < CONF_MCAN_ELEMENT_DATA_SIZE; i++) {
			printk("  %d",rx_element_fifo_1.data[i]);
		}
		printk("\r\n\r\n");
	}

	if ((status & MCAN_ACKNOWLEDGE_ERROR)
			|| (status & MCAN_FORMAT_ERROR)) {
		mcan_clear_interrupt_status(&mcan_instance, MCAN_ACKNOWLEDGE_ERROR
				| MCAN_FORMAT_ERROR);
		printk("Protocol error, please double check the clock in two boards. \r\n\r\n");
	}

	if (status & MCAN_BUS_OFF) {
		mcan_clear_interrupt_status(&mcan_instance, MCAN_BUS_OFF);
		mcan_stop(&mcan_instance);
		printk(": MCAN bus off error, re-initialization. \r\n\r\n");
		configure_mcan();
	}
}

/**
 * \brief display configuration menu.
 */
static void display_menu(void)
{
	printk("Menu :\r\n"
			"  -- Select the action:\r\n"
			"  0: Set standard filter ID 0: 0x45A, store into Rx buffer. \r\n"
			"  1: Set standard filter ID 1: 0x469, store into Rx FIFO 0. \r\n"
			"  2: Send FD standard message with ID: 0x45A and 64 byte data 0 to 63. \r\n"
			"  3: Send FD standard message with ID: 0x469 and 64 byte data 128 to 191. \r\n"
			"  4: Set extended filter ID 0: 0x100000A5, store into Rx buffer. \r\n"
			"  5: Set extended filter ID 1: 0x10000096, store into Rx FIFO 1. \r\n"
			"  6: Send FD extended message with ID: 0x100000A5 and 64 byte data 0 to 63. \r\n"
			"  7: Send FD extended message with ID: 0x10000096 and 64 byte data 128 to 191. \r\n"
			"  a: Send normal standard message with ID: 0x469 and 8 byte data 0 to 7. \r\n"
			"  h: Display menu \r\n\r\n");
}

int main(void)
{
	uint8_t key;
	int cnt = 0;
	struct device *led_port, *can_silent_port;

	printk("\n-- MCAN Quick Start FD example: %s --\n", "SAMV71_DPF.2.4.182");
	printk("-- Board: %s\n", CONFIG_BOARD);
	printk("-- Compiled: %s %s --\n\n", __DATE__, __TIME__);

	led_port = device_get_binding(LED_PORT);
	gpio_pin_configure(led_port, LED, GPIO_DIR_OUT);
	gpio_pin_write(led_port, LED, 0);

	can_silent_port = device_get_binding(CAN_SILENT_PORT);
	gpio_pin_configure(can_silent_port, CAN_SILENT_PIN, GPIO_DIR_OUT);
	gpio_pin_write(can_silent_port, CAN_SILENT_PIN, 0);

	configure_mcan();
	display_menu();
	console_init();

	while(1) {
		key = console_getchar();

		switch (key) {
		case 'h':
			display_menu();
			break;

		case '0':
			printk("  0: Set standard filter ID 0: 0x45A, store into Rx buffer. \r\n");
			mcan_set_standard_filter_0();
			break;

		case '1':
			printk("  1: Set standard filter ID 1: 0x469, store into Rx FIFO 0. \r\n");
			mcan_set_standard_filter_1();
			break;

		case '2':
			printk("  2: Send standard message with ID: 0x45A and 64 byte data 0 to 63. \r\n");
			mcan_fd_send_standard_message(MCAN_RX_STANDARD_FILTER_ID_0, tx_message_0);
			break;

		case '3':
			printk("  3: Send standard message with ID: 0x469 and 64 byte data 128 to 191. \r\n");
			mcan_fd_send_standard_message(MCAN_RX_STANDARD_FILTER_ID_1, tx_message_1);
			break;

		case '4':
			printk("  4: Set extended filter ID 0: 0x100000A5, store into Rx buffer. \r\n");
			mcan_set_extended_filter_0();
			break;

		case '5':
			printk("  5: Set extended filter ID 1: 0x10000096, store into Rx FIFO 1. \r\n");
			mcan_set_extended_filter_1();
			break;

		case '6':
			printk("  6: Send extended message with ID: 0x100000A5 and 64 byte data 0 to 63. \r\n");
			mcan_fd_send_extended_message(MCAN_RX_EXTENDED_FILTER_ID_0, tx_message_0);
			break;

		case '7':
			printk("  7: Send extended message with ID: 0x10000096 and 64 byte data 128 to 191. \r\n");
			mcan_fd_send_extended_message(MCAN_RX_EXTENDED_FILTER_ID_1, tx_message_1);
			break;

		case 'a':
			printk("  a: Send normal standard message with ID: 0x469 and 8 byte data 0 to 7. \r\n");
			mcan_send_standard_message(MCAN_RX_STANDARD_FILTER_ID_1, tx_message_0);
			break;

		default:
			break;
		}

		/* Set pin to HIGH/LOW every key press */
		cnt++;
		gpio_pin_write(led_port, LED, cnt % 2);
		k_sleep(SLEEP_TIME);
	}

}
