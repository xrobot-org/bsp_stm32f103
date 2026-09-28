#include "app_main.h"

#include "cdc_uart.hpp"
#include "libxr.hpp"
#include "main.h"
#include "stm32_adc.hpp"
#include "stm32_can.hpp"
#include "stm32_canfd.hpp"
#include "stm32_dac.hpp"
#include "stm32_flash.hpp"
#include "stm32_gpio.hpp"
#include "stm32_i2c.hpp"
#include "stm32_power.hpp"
#include "stm32_pwm.hpp"
#include "stm32_spi.hpp"
#include "stm32_timebase.hpp"
#include "stm32_uart.hpp"
#include "stm32_usb_dev.hpp"
#include "stm32_watchdog.hpp"
#include "flash_map.hpp"
#include "xrobot_main.hpp"

using namespace LibXR;

/* User Code Begin 1 */
/* User Code End 1 */
// NOLINTBEGIN
// clang-format off
/* External HAL Declarations */
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern PCD_HandleTypeDef hpcd_USB_FS;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;

/* DMA Resources */
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
#if defined(__SCB_DCACHE_LINE_SIZE)
#define XR_DCACHE_LINE_SIZE __SCB_DCACHE_LINE_SIZE
#else
#define XR_DCACHE_LINE_SIZE 32U
#endif
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint16_t data[16];
} adc1_buf_storage;
static constexpr auto& adc1_buf = adc1_buf_storage.data;
#else
alignas(4) static uint16_t adc1_buf[16];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart1_tx_buf_storage;
static constexpr auto& usart1_tx_buf = usart1_tx_buf_storage.data;
#else
alignas(4) static uint8_t usart1_tx_buf[128];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usart1_rx_buf_storage;
static constexpr auto& usart1_rx_buf = usart1_rx_buf_storage.data;
#else
alignas(4) static uint8_t usart1_rx_buf[128];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[32];
} i2c1_buf_storage;
static constexpr auto& i2c1_buf = i2c1_buf_storage.data;
#else
alignas(4) static uint8_t i2c1_buf[32];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[8];
} usb_fs_ep0_in_buf_storage;
static constexpr auto& usb_fs_ep0_in_buf = usb_fs_ep0_in_buf_storage.data;
#else
alignas(4) static uint8_t usb_fs_ep0_in_buf[8];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[8];
} usb_fs_ep0_out_buf_storage;
static constexpr auto& usb_fs_ep0_out_buf = usb_fs_ep0_out_buf_storage.data;
#else
alignas(4) static uint8_t usb_fs_ep0_out_buf[8];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usb_fs_ep1_in_buf_storage;
static constexpr auto& usb_fs_ep1_in_buf = usb_fs_ep1_in_buf_storage.data;
#else
alignas(4) static uint8_t usb_fs_ep1_in_buf[128];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[128];
} usb_fs_ep1_out_buf_storage;
static constexpr auto& usb_fs_ep1_out_buf = usb_fs_ep1_out_buf_storage.data;
#else
alignas(4) static uint8_t usb_fs_ep1_out_buf[128];
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
static struct alignas(XR_DCACHE_LINE_SIZE)
{
  uint8_t data[16];
} usb_fs_ep2_in_buf_storage;
static constexpr auto& usb_fs_ep2_in_buf = usb_fs_ep2_in_buf_storage.data;
#else
alignas(4) static uint8_t usb_fs_ep2_in_buf[16];
#endif

extern "C" void app_main(void) {
  // clang-format on
  // NOLINTEND
  /* User Code Begin 2 */
  /* User Code End 2 */
  // clang-format off
  // NOLINTBEGIN
  static STM32TimerTimebase timebase(&htim3);
  PlatformInit(2, 1024);
  static STM32PowerManager power_manager;

  /* GPIO Configuration */
  static STM32GPIO PA8(GPIOA, GPIO_PIN_8);
  static STM32GPIO LED(LED_GPIO_Port, LED_Pin);

  static STM32ADC adc1(&hadc1, adc1_buf, {ADC_CHANNEL_0}, 3.3);
  static auto& adc1_adc_channel_0 = adc1.GetChannel(0);
  UNUSED(adc1_adc_channel_0);

  static STM32PWM pwm_tim2_ch3(&htim2, TIM_CHANNEL_3, false);

  static STM32SPI spi1(&hspi1, {nullptr, 0}, {nullptr, 0}, 3);

  static STM32UART usart1(&huart1,
              usart1_rx_buf, usart1_tx_buf, 5);

  static STM32I2C i2c1(&hi2c1, i2c1_buf, 3);

  static constexpr auto USB_FS_LANG_PACK = LibXR::USB::DescriptorStrings::MakeLanguagePack(LibXR::USB::DescriptorStrings::Language::EN_US, "XRobot", "STM32 XRUSB USB CDC Demo", "XRUSB-DEMO-");
  static LibXR::USB::CDCUart usb_fs_cdc(LibXR::USB::Endpoint::EPNumber::EP1, LibXR::USB::Endpoint::EPNumber::EP1, LibXR::USB::Endpoint::EPNumber::EP2, 128, 128, 3);

  static STM32USBDeviceDevFs usb_fs(
      &hpcd_USB_FS,
      {
          {usb_fs_ep0_in_buf, usb_fs_ep0_out_buf, 8, 8},
          {usb_fs_ep1_in_buf, usb_fs_ep1_out_buf, 128, 128},
          {usb_fs_ep2_in_buf, 16, true}
      },
      USB::DeviceDescriptor::PacketSize0::SIZE_8,
      0x16D0, 0x1492, 0x100,
      {&USB_FS_LANG_PACK},
      {{&usb_fs_cdc}},
      {reinterpret_cast<void *>(UID_BASE), 12}
  );
  usb_fs.Init(false);
  usb_fs.Start(false);

  /* Terminal Configuration */
  STDIO::read_ = usb_fs_cdc.read_port_;
  STDIO::write_ = usb_fs_cdc.write_port_;

  static RamFS ramfs("XRobot");
  static Terminal<32, 32, 5, 5> terminal(ramfs);
  static auto terminal_task = Timer::CreateTask(terminal.TaskFun, &terminal, 10);
  Timer::Add(terminal_task);
  Timer::Start(terminal_task);

  XR_REGISTER(power_manager, LibXR::PowerManager);
  XR_REGISTER(PA8, LibXR::GPIO);
  XR_REGISTER(LED, LibXR::GPIO);
  XR_REGISTER(pwm_tim2_ch3, LibXR::PWM);
  XR_REGISTER(adc1_adc_channel_0, LibXR::ADC);
  XR_REGISTER(spi1, LibXR::SPI);
  XR_REGISTER(usart1, LibXR::UART);
  XR_REGISTER(i2c1, LibXR::I2C);
  XR_REGISTER(usb_fs_cdc, LibXR::UART);
  XR_REGISTER(ramfs, LibXR::RamFS);
  XR_REGISTER(terminal, LibXR::Terminal<32, 32, 5, 5>);

  // clang-format on
  // NOLINTEND
  /* User Code Begin 3 */
  /* User Code End 3 */
  XROBOT_MAIN();
}