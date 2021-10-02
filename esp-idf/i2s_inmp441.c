i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 11025, // or 44100 if you like
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Ground the L/R pin on the INMP441.
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = ESP_NOW_MAX_DATA_LEN * 4,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0,
};
if (ESP_OK != i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL)) {
    Serial.println("i2s_driver_install: error");
}

i2s_pin_config_t pin_config = {
    .bck_io_num = 14,   // Bit Clock.
    .ws_io_num = 15,    // Word Select aka left/right clock aka LRCL.
    .data_out_num = -1,
    .data_in_num = 34,  // Data-out of the mic. (someone used 23 on forums).
};
if (ESP_OK != i2s_set_pin(I2S_NUM_0, &pin_config)) {
    Serial.println("i2s_set_pin: error");
}