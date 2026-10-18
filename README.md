# LVGL V8.3 ported to the GD32F5HC_EVAL

本工程将 `LVGL V8.3` 移植至 `GD32F5HC` 平台，用于 `GUI演示`。

## Hardware Information

The `GD32F5HC_EVAL` is based on:

- `GD32F5HCVKT6` microcontroller (`ARM Cortex-M33` core, `200MHz`, FPU, DSP, TrustZone security)
- `2048 Kb` on-chip Flash memory and `320 KB` on-chip RAM
- `2.2 寸` `<TFT>` display (`<240*32>`, `<SPI>`)
- no input device
- `Jlink V9` debugger/programmer for download and debugging
- `On-board GD-LINK debugger/programmer for one-click download adn debugging`
- `USB / I2C / I2S / IFRP / ADC / LED / KEY`
- ` QSPI FLASH `

## Project Information

- GUI framework: `LVGL V8.3.11`
- Toolchain: `< Keil MDK / IAR / GD32EmbeddedBuilder>`
- Target board: `<GD32F5HC_EVAL V1.0>`
- Display configuration: `<240*320 / 16bit / 纵向>`

## Third-Party Components

| Category | In use | Component | Version | License |
| --- | --- | --- | --- | --- |
| GUI | `Yes` | `LVGL` | `V 8.3.11` | `MIT` |

> 引入新的第三方库时，请同步更新本表，并保留其许可证文本与版权声明。
