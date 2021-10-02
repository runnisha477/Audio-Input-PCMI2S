#include "driver/i2s.h"

static const int i2s_num = 0; // i2s port number

i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_TX,
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S
    .tx_desc_auto_clear = false,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1  // Interrupt level 1, default 0
};

static const i2s_pin_config_t pin_config = {
    .bck_io_num = 4,
    .ws_io_num = 5,
    .data_out_num = 18,
    .data_in_num = I2S_PIN_NO_CHANGE
};

i2s_driver_install(i2s_num, &i2s_config, 0, NULL);   //install and start i2s driver
i2s_set_pin(i2s_num, &pin_config);

...
/* You can reset parameters by calling 'i2s_set_clk'
 *
 * The low 16 bits are the valid data bits in one chan and the high 16 bits are
 * the total bits in one chan. If high 16 bits is smaller than low 16 bits, it will
 * be set to a same value as low 16 bits.
 */
uint32_t bits_cfg = (I2S_BITS_PER_CHAN_32BIT << 16) | I2S_BITS_PER_SAMPLE_16BIT;
i2s_set_clk(i2s_num, 22050, bits_cfg, I2S_CHANNEL_STEREO);
...

i2s_driver_uninstall(i2s_num); //stop & destroy i2s driver