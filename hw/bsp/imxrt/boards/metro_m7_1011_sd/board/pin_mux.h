/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define BOARD_INITPINS_IOMUXC_GPR_GPR26_GPIO_SEL_MASK 0x08U /*!< Select GPIO1 or GPIO2: affected bits mask */

/* GPIO_09 (number 3), LPUART1_RXD/J56[2] */
/* Routed pin properties */
#define BOARD_INITPINS_UART1_RXD_PERIPHERAL                              LPUART1   /*!< Peripheral name */
#define BOARD_INITPINS_UART1_RXD_SIGNAL                                      RXD   /*!< Signal name */

/* GPIO_10 (number 2), LPUART1_TXD/J56[4] */
/* Routed pin properties */
#define BOARD_INITPINS_UART1_TXD_PERIPHERAL                              LPUART1   /*!< Peripheral name */
#define BOARD_INITPINS_UART1_TXD_SIGNAL                                      TXD   /*!< Signal name */

/* GPIO_03 (number 10), SAI1_RXD0/U10[16] */
/* Routed pin properties */
#define BOARD_INITPINS_USER_LED_PERIPHERAL                                 GPIO1   /*!< Peripheral name */
#define BOARD_INITPINS_USER_LED_SIGNAL                                gpiomux_io   /*!< Signal name */
#define BOARD_INITPINS_USER_LED_CHANNEL                                       3U   /*!< Signal channel */

/* GPIO_13 (number 79), USB_OTG1_ID/J9[4]/Q9[2] */
/* Routed pin properties */
#define BOARD_INITPINS_TRACE1_PERIPHERAL                                     ARM   /*!< Peripheral name */
#define BOARD_INITPINS_TRACE1_SIGNAL                                       TRACE   /*!< Signal name */
#define BOARD_INITPINS_TRACE1_CHANNEL                                         1U   /*!< Signal channel */

/* GPIO_12 (number 80), USB_OTG1_OC/U7[A2] */
/* Routed pin properties */
#define BOARD_INITPINS_USB_OTG1_OC_PERIPHERAL                                ARM   /*!< Peripheral name */
#define BOARD_INITPINS_USB_OTG1_OC_SIGNAL                                  TRACE   /*!< Signal name */
#define BOARD_INITPINS_USB_OTG1_OC_CHANNEL                                    2U   /*!< Signal channel */

/* GPIO_AD_02 (number 58), ADC12_2/J26[12]/J56[16] */
/* Routed pin properties */
#define BOARD_INITPINS_ADC12_2_PERIPHERAL                                    ARM   /*!< Peripheral name */
#define BOARD_INITPINS_ADC12_2_SIGNAL                              arm_trace_clk   /*!< Signal name */

/* GPIO_11 (number 1), GPIO_11 */
/* Routed pin properties */
#define BOARD_INITPINS_GPIO_11_PERIPHERAL                                    ARM   /*!< Peripheral name */
#define BOARD_INITPINS_GPIO_11_SIGNAL                                      TRACE   /*!< Signal name */
#define BOARD_INITPINS_GPIO_11_CHANNEL                                        3U   /*!< Signal channel */

/* GPIO_AD_00 (number 60), USB_OTG1_PWR */
/* Routed pin properties */
#define BOARD_INITPINS_USB_OTG1_PWR_PERIPHERAL                               ARM   /*!< Peripheral name */
#define BOARD_INITPINS_USB_OTG1_PWR_SIGNAL                                 TRACE   /*!< Signal name */
#define BOARD_INITPINS_USB_OTG1_PWR_CHANNEL                                   0U   /*!< Signal channel */

/* GPIO_08 (number 4), SAI1_MCLK/U10[11] */
/* Routed pin properties */
#define BOARD_INITPINS_USER_BUTTON_PERIPHERAL                              GPIO1   /*!< Peripheral name */
#define BOARD_INITPINS_USER_BUTTON_SIGNAL                             gpiomux_io   /*!< Signal name */
#define BOARD_INITPINS_USER_BUTTON_CHANNEL                                    8U   /*!< Signal channel */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
