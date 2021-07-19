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
#include "hal/crc_api.h"
#include "hal/serial_api.h"

#define TRACE_GROUP "main"

static serial_t stdio_uart;

static const uint32_t message[128] = {
    0x068209dc, 0x15c94130, 0x7c328809, 0x5ccadfa7, 0x29f0950f, 0x67b62849, 
    0x4fd98056, 0x46ae067b, 0x5a06fbea, 0x315e6b73, 0x5c5d5427, 0x3e2b25b0, 
    0x534b576a, 0x0af6148a, 0x70541220, 0x29de02c2, 0x77ca2927, 0x65c70dcc, 
    0x3facf3f5, 0x76442b7e, 0x200a126d, 0x6e257cdd, 0x4fba9f62, 0x08031d2f, 
    0x3cb13044, 0x759c48c2, 0x6cd2c652, 0x5650ad19, 0x45e5103c, 0x478204ff, 
    0x661c1543, 0x4f7a613c, 0x5d4b4630, 0x624e9d4c, 0x2c4540e3, 0x073bdb3f, 
    0x4a04c596, 0x7c1ec139, 0x4de9e1ba, 0x240bc180, 0x2d7d2cac, 0x2a4735e1, 
    0x6236e730, 0x00c88417, 0x353d4a6c, 0x528af950, 0x2aa686d9, 0x2d077393, 
    0x3852071c, 0x6a537acf, 0x234b9f11, 0x585c1989, 0x5878f7ac, 0x73063e73, 
    0x605f36b8, 0x152a27f1, 0x68a28735, 0x4d31fd0b, 0x6b7ad50a, 0x2e879772, 
    0x14b4020a, 0x5196ea4e, 0x7e01f8ae, 0x71ff483a, 0x33e5879a, 0x2a473992, 
    0x793b2379, 0x7dea4d30, 0x2665facb, 0x47250534, 0x21f60eb0, 0x53e32778, 
    0x716c3b15, 0x042cf5e0, 0x54abab8f, 0x26a98581, 0x56b7ef30, 0x7f523268, 
    0x53b0f914, 0x0f09f64d, 0x69a5ad37, 0x76fc9825, 0x67660fd6, 0x421ea4e4, 
    0x6a02d699, 0x47c5468f, 0x5748ccd5, 0x52a55dce, 0x14f7439a, 0x42c3a1df, 
    0x012cf540, 0x29ab45a4, 0x145a8c2d, 0x7f2eedef, 0x1baa8ddf, 0x484013c8, 
    0x29762781, 0x14e5b158, 0x462a60f8, 0x4fdc224c, 0x5c0ab68c, 0x68206fa9, 
    0x23bf49c4, 0x4d76f1a2, 0x6c4d6589, 0x786af553, 0x74207723, 0x430554ba, 
    0x77bd27bc, 0x47d17038, 0x520f4b07, 0x6162d4f3, 0x3ece085d, 0x39755add, 
    0x238179d7, 0x28d0def6, 0x013aa16c, 0x7aca46ac, 0x7b763cc5, 0x1631e506, 
    0x3d8de88c, 0x7ca33205, 0x3fdd2aab, 0x51e874b9, 0x7bd21ff4, 0x5b87b88a, 
    0x1a288881, 0x25484775 
};

static void serial_print(const char *string);
static void begin_trace(void);

int main(void)
{
    begin_trace();
    
    crc_mbed_config_t config = { 
        .polynomial = POLY_32BIT_ANSI, 
        .width = 32, 
        .initial_xor = 0,
        .final_xor = 0, 
        .reflect_in = false, 
        .reflect_out = false 
    };

    hal_crc_compute_partial_start(&config);
    hal_crc_compute_partial((uint8_t *)message, sizeof(message));
    uint32_t result = hal_crc_get_result();     
    
    tr_info("The CRC generated is: 0x%"PRIx32". The CRC should be: 0x8a876148", 
            result);

    return 0;
}

static void serial_print(const char *string)
{
    while (*string != '\0') {
        serial_putc(&stdio_uart, *string);
        string++;
    }
    serial_putc(&stdio_uart, '\n');
}

static void begin_trace(void) 
{
    serial_init(&stdio_uart, CONSOLE_TX, CONSOLE_RX);
    serial_baud(&stdio_uart, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);

    mbed_trace_init();
    mbed_trace_print_function_set(serial_print);
}

