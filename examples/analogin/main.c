/* Copyright (c) 2021 Arm Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 #include "bootstrap/mbed_trace.h"
 #include "bootstrap/mbed_wait_api.h"
 #include "hal/analogin_api.h"
 #include "hal/serial_api.h"

 #define TRACE_GROUP "main"
 #define VOLTAGE_MULTIPLIER 3.3

 static serial_t stdio_uart;

 void serial_print(const char *string)
 {
     while (*string != '\0') {
         serial_putc(&stdio_uart, *string);
         string++;
     }
     serial_putc(&stdio_uart, '\n');
 }

 int main(void)
 {
     analogin_t analog_input;

     float input_voltage;
     float real_voltage;
     uint16_t unsigned_real_voltage;

     serial_init(&stdio_uart, CONSOLE_TX, CONSOLE_RX);
     serial_baud(&stdio_uart, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);

     mbed_trace_init();
     mbed_trace_print_function_set(serial_print);

     analogin_init(&analog_input, ARDUINO_UNO_A0);

     tr_info("Starting analog in example.");

     while (1) {
       input_voltage = analogin_read(&analog_input);
       real_voltage = input_voltage * VOLTAGE_MULTIPLIER;
       unsigned_real_voltage = (uint16_t)(real_voltage * 100.);
       tr_info("The voltage on the A0 pin is %u.%02uV", (unsigned_real_voltage / 100U), (unsigned_real_voltage % 100U));
       wait_us(1000000U);
     }
 }
