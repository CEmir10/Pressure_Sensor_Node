#include <device.h>
#include <toolchain.h>

/* 1 : /soc/pinctrl@400e0e00/gpio@400e1600:
 * Direct Dependencies:
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00)
 * Supported:
 *   - (/soc/pinctrl@400e0e00/pe0b_tc3_tioa9)
 *   - (/soc/pinctrl@400e0e00/pe1b_tc3_tiob9)
 *   - (/soc/pinctrl@400e0e00/pe2b_tc3_tclk9)
 *   - (/soc/pinctrl@400e0e00/pe3b_tc3_tioa10)
 *   - (/soc/pinctrl@400e0e00/pe4b_tc3_tiob10)
 *   - (/soc/pinctrl@400e0e00/pe5b_tc3_tclk10)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_pinctrl_400e0e00_S_gpio_400e1600[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 2 : /soc/pinctrl@400e0e00/gpio@400e1400:
 * Direct Dependencies:
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00)
 * Supported:
 *   - (/soc/pinctrl@400e0e00/pd0a_gmac_gtxck)
 *   - (/soc/pinctrl@400e0e00/pd0c_spi1_npcs1)
 *   - (/soc/pinctrl@400e0e00/pd0d_usart0_dcd0)
 *   - (/soc/pinctrl@400e0e00/pd10a_gmac_gcrs)
 *   - (/soc/pinctrl@400e0e00/pd10c_ssc_td)
 *   - (/soc/pinctrl@400e0e00/pd11a_gmac_grx2)
 *   - (/soc/pinctrl@400e0e00/pd11c_gmac_gtsucomp)
 *   - (/soc/pinctrl@400e0e00/pd12a_gmac_grx3)
 *   - (/soc/pinctrl@400e0e00/pd12c_spi0_npcs2)
 *   - (/soc/pinctrl@400e0e00/pd13a_gmac_gcol)
 *   - (/soc/pinctrl@400e0e00/pd14a_gmac_grxck)
 *   - (/soc/pinctrl@400e0e00/pd15a_gmac_gtx2)
 *   - (/soc/pinctrl@400e0e00/pd15b_usart2_rxd2)
 *   - (/soc/pinctrl@400e0e00/pd16a_gmac_gtx3)
 *   - (/soc/pinctrl@400e0e00/pd16b_usart2_txd2)
 *   - (/soc/pinctrl@400e0e00/pd17a_gmac_gtxer)
 *   - (/soc/pinctrl@400e0e00/pd17b_usart2_sck2)
 *   - (/soc/pinctrl@400e0e00/pd18b_usart2_rts2)
 *   - (/soc/pinctrl@400e0e00/pd18c_uart4_urxd4)
 *   - (/soc/pinctrl@400e0e00/pd19b_usart2_cts2)
 *   - (/soc/pinctrl@400e0e00/pd19c_uart4_utxd4)
 *   - (/soc/pinctrl@400e0e00/pd1a_gmac_gtxen)
 *   - (/soc/pinctrl@400e0e00/pd1c_spi1_npcs2)
 *   - (/soc/pinctrl@400e0e00/pd1d_usart0_dtr0)
 *   - (/soc/pinctrl@400e0e00/pd20b_spi0_miso)
 *   - (/soc/pinctrl@400e0e00/pd20c_gmac_gtsucomp)
 *   - (/soc/pinctrl@400e0e00/pd21b_spi0_mosi)
 *   - (/soc/pinctrl@400e0e00/pd21c_tc3_tioa11)
 *   - (/soc/pinctrl@400e0e00/pd22b_spi0_spck)
 *   - (/soc/pinctrl@400e0e00/pd22c_tc3_tiob11)
 *   - (/soc/pinctrl@400e0e00/pd24b_ssc_rf)
 *   - (/soc/pinctrl@400e0e00/pd24c_tc3_tclk11)
 *   - (/soc/pinctrl@400e0e00/pd25b_spi0_npcs1)
 *   - (/soc/pinctrl@400e0e00/pd25c_uart2_urxd2)
 *   - (/soc/pinctrl@400e0e00/pd26b_ssc_td)
 *   - (/soc/pinctrl@400e0e00/pd26c_uart2_utxd2)
 *   - (/soc/pinctrl@400e0e00/pd26d_uart1_utxd1)
 *   - (/soc/pinctrl@400e0e00/pd27b_spi0_npcs3)
 *   - (/soc/pinctrl@400e0e00/pd27c_twihs2_twd2)
 *   - (/soc/pinctrl@400e0e00/pd28a_uart3_urxd3)
 *   - (/soc/pinctrl@400e0e00/pd28c_twihs2_twck2)
 *   - (/soc/pinctrl@400e0e00/pd2a_gmac_gtx0)
 *   - (/soc/pinctrl@400e0e00/pd2c_spi1_npcs3)
 *   - (/soc/pinctrl@400e0e00/pd2d_usart0_dsr0)
 *   - (/soc/pinctrl@400e0e00/pd30a_uart3_utxd3)
 *   - (/soc/pinctrl@400e0e00/pd31b_uart3_utxd3)
 *   - (/soc/pinctrl@400e0e00/pd3a_gmac_gtx1)
 *   - (/soc/pinctrl@400e0e00/pd3c_uart4_utxd4)
 *   - (/soc/pinctrl@400e0e00/pd3d_usart0_ri0)
 *   - (/soc/pinctrl@400e0e00/pd4a_gmac_grxdv)
 *   - (/soc/pinctrl@400e0e00/pd4d_usart2_dcd2)
 *   - (/soc/pinctrl@400e0e00/pd5a_gmac_grx0)
 *   - (/soc/pinctrl@400e0e00/pd5d_usart2_dtr2)
 *   - (/soc/pinctrl@400e0e00/pd6a_gmac_grx1)
 *   - (/soc/pinctrl@400e0e00/pd6d_usart2_dsr2)
 *   - (/soc/pinctrl@400e0e00/pd7a_gmac_grxer)
 *   - (/soc/pinctrl@400e0e00/pd7d_usart2_ri2)
 *   - (/soc/pinctrl@400e0e00/pd8a_gmac_gmdc)
 *   - (/soc/pinctrl@400e0e00/pd9a_gmac_gmdio)
 *   - (/soc/pinctrl@400e0e00/pd9c_afec1_adtrg)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_pinctrl_400e0e00_S_gpio_400e1400[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 3 : /soc/pinctrl@400e0e00/gpio@400e1200:
 * Direct Dependencies:
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00)
 * Supported:
 *   - (/soc/pinctrl@400e0e00/pc10b_tc2_tclk7)
 *   - (/soc/pinctrl@400e0e00/pc11b_tc2_tioa8)
 *   - (/soc/pinctrl@400e0e00/pc12b_tc2_tiob8)
 *   - (/soc/pinctrl@400e0e00/pc12c_can1_rx1)
 *   - (/soc/pinctrl@400e0e00/pc14b_tc2_tclk8)
 *   - (/soc/pinctrl@400e0e00/pc14c_can1_tx1)
 *   - (/soc/pinctrl@400e0e00/pc23b_tc1_tioa3)
 *   - (/soc/pinctrl@400e0e00/pc24b_tc1_tiob3)
 *   - (/soc/pinctrl@400e0e00/pc24c_spi1_spck)
 *   - (/soc/pinctrl@400e0e00/pc25b_tc1_tclk3)
 *   - (/soc/pinctrl@400e0e00/pc25c_spi1_npcs0)
 *   - (/soc/pinctrl@400e0e00/pc26b_tc1_tioa4)
 *   - (/soc/pinctrl@400e0e00/pc26c_spi1_miso)
 *   - (/soc/pinctrl@400e0e00/pc27b_tc1_tiob4)
 *   - (/soc/pinctrl@400e0e00/pc27c_spi1_mosi)
 *   - (/soc/pinctrl@400e0e00/pc28b_tc1_tclk4)
 *   - (/soc/pinctrl@400e0e00/pc28c_spi1_npcs1)
 *   - (/soc/pinctrl@400e0e00/pc29b_tc1_tioa5)
 *   - (/soc/pinctrl@400e0e00/pc29c_spi1_npcs2)
 *   - (/soc/pinctrl@400e0e00/pc30b_tc1_tiob5)
 *   - (/soc/pinctrl@400e0e00/pc30c_spi1_npcs3)
 *   - (/soc/pinctrl@400e0e00/pc31b_tc1_tclk5)
 *   - (/soc/pinctrl@400e0e00/pc5b_tc2_tioa6)
 *   - (/soc/pinctrl@400e0e00/pc6b_tc2_tiob6)
 *   - (/soc/pinctrl@400e0e00/pc7b_tc2_tclk6)
 *   - (/soc/pinctrl@400e0e00/pc8b_tc2_tioa7)
 *   - (/soc/pinctrl@400e0e00/pc9b_tc2_tiob7)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_pinctrl_400e0e00_S_gpio_400e1200[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 4 : /soc/pinctrl@400e0e00/gpio@400e1000:
 * Direct Dependencies:
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00)
 * Supported:
 *   - (/soc/pinctrl@400e0e00/pb0c_usart0_rxd0)
 *   - (/soc/pinctrl@400e0e00/pb0d_ssc_tf)
 *   - (/soc/pinctrl@400e0e00/pb12b_gmac_gtsucomp)
 *   - (/soc/pinctrl@400e0e00/pb13c_usart0_sck0)
 *   - (/soc/pinctrl@400e0e00/pb1b_gmac_gtsucomp)
 *   - (/soc/pinctrl@400e0e00/pb1c_usart0_txd0)
 *   - (/soc/pinctrl@400e0e00/pb1d_ssc_tk)
 *   - (/soc/pinctrl@400e0e00/pb2a_can0_tx0)
 *   - (/soc/pinctrl@400e0e00/pb2c_usart0_cts0)
 *   - (/soc/pinctrl@400e0e00/pb2d_spi0_npcs0)
 *   - (/soc/pinctrl@400e0e00/pb3a_can0_rx0)
 *   - (/soc/pinctrl@400e0e00/pb3c_usart0_rts0)
 *   - (/soc/pinctrl@400e0e00/pb4a_twihs1_twd1)
 *   - (/soc/pinctrl@400e0e00/pb4d_usart1_txd1)
 *   - (/soc/pinctrl@400e0e00/pb5a_twihs1_twck1)
 *   - (/soc/pinctrl@400e0e00/pb5d_ssc_td)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_pinctrl_400e0e00_S_gpio_400e1000[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 9, DEVICE_HANDLE_ENDS };

/* 5 : /soc/pinctrl@400e0e00/gpio@400e0e00:
 * Direct Dependencies:
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00)
 * Supported:
 *   - (/gpio_keys/button_1)
 *   - (/leds/led_0)
 *   - (/soc/pinctrl@400e0e00/pa0b_tc0_tioa0)
 *   - (/soc/pinctrl@400e0e00/pa10a_uart0_utxd0)
 *   - (/soc/pinctrl@400e0e00/pa10c_ssc_rd)
 *   - (/soc/pinctrl@400e0e00/pa15b_tc0_tioa1)
 *   - (/soc/pinctrl@400e0e00/pa16b_tc0_tiob1)
 *   - (/soc/pinctrl@400e0e00/pa1b_tc0_tiob0)
 *   - (/soc/pinctrl@400e0e00/pa21a_usart1_rxd1)
 *   - (/soc/pinctrl@400e0e00/pa22a_ssc_rk)
 *   - (/soc/pinctrl@400e0e00/pa23a_usart1_sck1)
 *   - (/soc/pinctrl@400e0e00/pa24a_usart1_rts1)
 *   - (/soc/pinctrl@400e0e00/pa25a_usart1_cts1)
 *   - (/soc/pinctrl@400e0e00/pa26a_usart1_dcd1)
 *   - (/soc/pinctrl@400e0e00/pa26b_tc0_tioa2)
 *   - (/soc/pinctrl@400e0e00/pa27a_usart1_dtr1)
 *   - (/soc/pinctrl@400e0e00/pa27b_tc0_tiob2)
 *   - (/soc/pinctrl@400e0e00/pa28a_usart1_dsr1)
 *   - (/soc/pinctrl@400e0e00/pa28b_tc0_tclk1)
 *   - (/soc/pinctrl@400e0e00/pa29a_usart1_ri1)
 *   - (/soc/pinctrl@400e0e00/pa29b_tc0_tclk2)
 *   - (/soc/pinctrl@400e0e00/pa31a_spi0_npcs1)
 *   - (/soc/pinctrl@400e0e00/pa3a_twihs0_twd0)
 *   - (/soc/pinctrl@400e0e00/pa3b_usart1_loncol1)
 *   - (/soc/pinctrl@400e0e00/pa4a_twihs0_twck0)
 *   - (/soc/pinctrl@400e0e00/pa4b_tc0_tclk0)
 *   - (/soc/pinctrl@400e0e00/pa4c_uart1_utxd1)
 *   - (/soc/pinctrl@400e0e00/pa5c_uart1_urxd1)
 *   - (/soc/pinctrl@400e0e00/pa6c_uart1_utxd1)
 *   - (/soc/pinctrl@400e0e00/pa8b_afec0_adtrg)
 *   - (/soc/pinctrl@400e0e00/pa9a_uart0_urxd0)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_pinctrl_400e0e00_S_gpio_400e0e00[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 8, 7, DEVICE_HANDLE_ENDS };

/* 6 : /soc/watchdog@400e1850:
 * Direct Dependencies:
 *   - (/soc)
 *   - (/soc/interrupt-controller@e000e100)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_watchdog_400e1850[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 7 : /soc/uart@400e0800:
 * Direct Dependencies:
 *   - (/soc)
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00/pa10a_uart0_utxd0)
 *   - (/soc/pinctrl@400e0e00/pa9a_uart0_urxd0)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_uart_400e0800[] = { 5, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 8 : /soc/i2c@40018000:
 * Direct Dependencies:
 *   - (/soc)
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00/pa3a_twihs0_twd0)
 *   - (/soc/pinctrl@400e0e00/pa4a_twihs0_twck0)
 * Supported:
 *   - (/soc/i2c@40018000/ag416@38)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_40018000[] = { 5, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 9 : /soc/can/can@40030000:
 * Direct Dependencies:
 *   - (/soc/can)
 *   - (/soc/interrupt-controller@e000e100)
 *   - (/soc/pinctrl@400e0e00/pb2a_can0_tx0)
 *   - (/soc/pinctrl@400e0e00/pb3a_can0_rx0)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_can_S_can_40030000[] = { 4, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };
