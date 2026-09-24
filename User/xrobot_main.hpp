#pragma once
// xrobot-stamp: config=xrobot.yaml sha256=94adb17037ea7a2f1883a15b67e4b2e64ce0e2dbc1d7dbcfbd7cebb1e8293620
// xrobot-stamp: lock=../xrobot.lock sha256=ddcde4ce28dc4d9b6a14557a855002f5cde4d9fe5a62820036b48633da3cc828

#include <memory>
#include <type_traits>
#include <utility>
#include "libxr.hpp"
#include "thread.hpp"
#include "BlinkLED.hpp"

namespace xrobot_generated {
template <typename...> struct TypeList {};
template <typename Source, typename... Views>
struct RegistrationMatches
    : std::bool_constant<(!std::is_reference<Views>::value && ...) &&
                         (std::is_convertible<Source*, Views*>::value && ...)> {};

}  // namespace xrobot_generated

// Force only this entry inline in optimized Clang builds.
#if defined(__clang__) && defined(__OPTIMIZE__) && !defined(LIBXR_DEBUG_BUILD) && \
    ((defined(XROBOT_OPTIMIZED_BUILD) && XROBOT_OPTIMIZED_BUILD) || \
     (!defined(XROBOT_OPTIMIZED_BUILD) && defined(NDEBUG)))
#define XR_XROBOT_MAIN_INLINE [[gnu::always_inline]] inline
#else
#define XR_XROBOT_MAIN_INLINE inline
#endif

[[noreturn]] XR_XROBOT_MAIN_INLINE void XRobotMain(
    LibXR::GPIO& LED) {
  // modules[0]: blink_led
  static BlinkLED blink_led(
      static_cast<LibXR::GPIO&>(LED)
      , 250
  );
  static_assert(std::is_void_v<decltype(blink_led.OnMonitor())>, "blink_led.OnMonitor() must return void");
  for (;;) {
    blink_led.OnMonitor();
    LibXR::Thread::Sleep(1000);
  }
}

#undef XR_XROBOT_MAIN_INLINE

/* User Code Begin XRobotMain */
/* User Code End XRobotMain */
// clang-format off
// NOLINTBEGIN
#define XR_REGISTER_DETAIL_power_manager(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PowerManager>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(power_manager)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_PA8(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(PA8)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_LED(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::GPIO>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(LED)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_pwm_tim2_ch3(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::PWM>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(pwm_tim2_ch3)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_adc1_adc_channel_0(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::ADC>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(adc1_adc_channel_0)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_spi1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::SPI>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(spi1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usart1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usart1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_i2c1(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::I2C>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(i2c1)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_usb_fs_cdc(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::UART>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(usb_fs_cdc)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_ramfs(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::RamFS>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(ramfs)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER_DETAIL_terminal(...) \
  static_assert(std::is_same<::xrobot_generated::TypeList<__VA_ARGS__>, \
      ::xrobot_generated::TypeList<LibXR::Terminal<32, 32, 5, 5>>>::value && \
      ::xrobot_generated::RegistrationMatches< \
          std::remove_reference_t<decltype(terminal)>, __VA_ARGS__>::value, \
      "XR_REGISTER changed; regenerate xrobot_main.hpp")
#define XR_REGISTER(name, ...) XR_REGISTER_DETAIL_##name(__VA_ARGS__)

#define XROBOT_MAIN() ::XRobotMain(LED)

// NOLINTEND
// clang-format on
