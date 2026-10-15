#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Cấu hình chân L298N
#define PIN_INT1 D1  // Motor trái - IN1
#define PIN_INT2 D2  // Motor trái - IN2
#define PIN_INT3 D3 // Motor phải - IN1
#define PIN_INT4 D4  // Motor phải - IN2

#define PIN_ENA D5  // PWM motor trái
#define PIN_ENB D6  // PWM motor phải

#define MOTOR_SPEED 250     // Tốc độ động cơ mặc định (0-255)
#define MOTOR_LEFT_INVERTED false   // true nếu dây motor trái bị đảo chiều vật lý
#define MOTOR_RIGHT_INVERTED false  // true nếu dây motor phải bị đảo chiều vật lý

// Cấu hình Wi-Fi
#define WIFI "CAR_WIFI"
#define PASSWORD "24681088"

#endif
