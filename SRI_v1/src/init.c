#include "LPC17xx.h"
#include "lpc_types.h"
#include "lpc17xx_uart.h"   /* Central include file */
#include "lpc17xx_nvic.h"
#include "lpc17xx_pinsel.h"

void init_uart2(uint32_t baudrate) {
  // UART Configuration structure variable
  UART_CFG_Type UARTConfigStruct;
  // UART FIFO configuration Struct variable
  UART_FIFO_CFG_Type UARTFIFOConfigStruct;
  // Pin configuration for UART2
  PINSEL_CFG_Type PinCfg;

  // DeInit NVIC and SCBNVIC
  NVIC_DeInit();
  NVIC_SCBDeInit();

  PinCfg.Funcnum = 1;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 10;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 11;
  PINSEL_ConfigPin(&PinCfg);

  UART_ConfigStructInit(&UARTConfigStruct);

  UARTConfigStruct.Baud_rate = baudrate;

  // Initialize UART2 peripheral with given to corresponding parameter
  UART_Init(LPC_UART2, &UARTConfigStruct);

  /* Initialize FIFOConfigStruct to default state:
   *        - FIFO_DMAMode = DISABLE
   *        - FIFO_Level = UART_FIFO_TRGLEV0
   *        - FIFO_ResetRxBuf = ENABLE
   *        - FIFO_ResetTxBuf = ENABLE
   *        - FIFO_State = ENABLE
   */
  UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

  // Initialize FIFO for UART3 peripheral
  UART_FIFOConfig(LPC_UART2, &UARTFIFOConfigStruct);


  // Enable UART Transmit
  UART_TxCmd(LPC_UART2, ENABLE);
}

void init_uart3(void) {
  // UART Configuration structure variable
  UART_CFG_Type UARTConfigStruct;
  // UART FIFO configuration Struct variable
  UART_FIFO_CFG_Type UARTFIFOConfigStruct;
  // Pin configuration for UART2
  PINSEL_CFG_Type PinCfg;

  // DeInit NVIC and SCBNVIC
  NVIC_DeInit();
  NVIC_SCBDeInit();

  PinCfg.Funcnum = 2;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 0;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 1;
  PINSEL_ConfigPin(&PinCfg);

  UART_ConfigStructInit(&UARTConfigStruct);

  UARTConfigStruct.Baud_rate = 57600;

  // Initialize UART3 peripheral with given to corresponding parameter
  UART_Init(LPC_UART3, &UARTConfigStruct);

  /* Initialize FIFOConfigStruct to default state:
   *        - FIFO_DMAMode = DISABLE
   *        - FIFO_Level = UART_FIFO_TRGLEV0
   *        - FIFO_ResetRxBuf = ENABLE
   *        - FIFO_ResetTxBuf = ENABLE
   *        - FIFO_State = ENABLE
   */
  UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

  // Initialize FIFO for UART3 peripheral
  UART_FIFOConfig(LPC_UART3, &UARTFIFOConfigStruct);


  // Enable UART Transmit
  UART_TxCmd(LPC_UART3, ENABLE);
}

void init_io(void) {
  LPC_GPIO0->FIODIR = (1<<0) | (1<<2) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<9) | (1<<10) | (1<<15) | (1<<17) | (1<<19) | (1<<20) | (1<<21) | (1<<22) | (1<<27) | (1<<28);
  LPC_GPIO1->FIODIR = (1<<1) | (1<<26);
  LPC_GPIO2->FIODIR = (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<9);
  LPC_GPIO3->FIODIR = (1<<25);
  LPC_GPIO4->FIODIR = (1<<28) | (1<<29);    /* P4.28 + P4.29 defined as Outputs */

	/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCL */
	/* function to 01 on both SDA and SCL. */
	LPC_PINCON->PINSEL1 &= ~((0x03<<22)|(0x03<<24));
	LPC_PINCON->PINSEL1 |= ((0x01<<22)|(0x01<<24));

  LPC_PINCON->PINSEL0 &= ~0xC0000000;
  LPC_PINCON->PINSEL0 |= 0x40000000;	/* Enable RxD1 P0.16, TxD1 P0.15 */
  LPC_PINCON->PINSEL1 &= ~0x00000003;
  LPC_PINCON->PINSEL1 |= 0x00000001;

  LPC_PINCON->PINSEL0 &= ~0x000000F0;
  LPC_PINCON->PINSEL0 |= 0x00000050;  /* RxD0 is P0.3 and TxD0 is P0.2 */

  LPC_SC->PCONP |= (1<<24);

  LPC_PINCON->PINSEL0 &= ~0x00F00000;
  LPC_PINCON->PINSEL0 |= 0x00500000;  /* Enable RxD2 P0.10, TxD2 P0.11 */

  LPC_SC->PCONP |= (1<<25);

  LPC_PINCON->PINSEL0 &= ~0x0000000F;
  LPC_PINCON->PINSEL0 |= 0x0000000A;  /* Enable RxD3 P0.01, TxD3 P0.00 */

  //configuration for the pins QEI
  LPC_PINCON->PINSEL3 |= ((1<<8) | (1<<14));//PH A&B & index

  LPC_PINCON->PINSEL3 &= ~(1<<13);
  LPC_PINCON->PINSEL3 &= ~(1<<12);

  LPC_PINCON->PINSEL4 |= (1<<18); //Turn on USB soft connect

  //Turn off both LEDs on the board
  LPC_GPIO4->FIOSET |= (1<<29) | (1<<28);

  //Set the D+ pulled up by 1.5k to 3V3
  LPC_GPIO2->FIOCLR = (1<<9);
}
