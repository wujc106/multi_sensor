# Keil → CMake 转换清单：Template

- MCU：GD32F5HCRIH6
- Keil Target：GD32F5HCRI
- 生成时间：2026-09-24T02:33:36.594Z

> 勾选框默认按转换状态预置（已转换=勾选，部分转换/未转换=未勾选）。
> 请在实机编译/调试验证通过后，把"未转换"项也手动勾上，作为你自己的核对记录。

## [x] MCU 型号（已转换）

- **Keil 原配置**：GD32F5HCRI
- **转换结果(CMake)**：GD32F5HCRIH6

## [x] 调试符号文件（SVD）（已转换）

- **Keil 原配置**：(uvprojx 的 SFDFile 指向 Keil 设备包内的 SVD，未被采用)
- **转换结果(CMake)**：resources/svd/GD32F5HC.svd
- **备注**：SVD 固定使用本工具的 mcu_arm.xml 配置，不使用 Keil 工程 SFDFile 指向的设备包 SVD（两者内容通常一致）

## [ ] TrustZone 安全域（ArmAdsMisc/nSecure）（未转换）

- **Keil 原配置**：Non-Secure（nSecure=0）
- **转换结果(CMake)**：(未显式区分，仅通过实际使用的启动文件/链接脚本体现)
- **备注**：请自行确认本次导入使用的 gcc/ 目录下启动文件与链接脚本确实对应同一安全域（本例为 NS），本工具不做 Secure/Non-Secure 一致性校验

## [ ] Flash 分区 / 片上内存布局（FlashDriverDll、ArmAdsMisc/OnChipMemories）（未转换）

- **Keil 原配置**：UL2V8M(-S0 -C0 -P0 -FD20000000 -FC1000 -FN2 -FF0GD32F5HC_NS -FS08000000 -FL0200000 -FF1GD32F5HC_S -FS1C000000 -FL1200000 -FP0($$Device:GD32F5HCRI$Flash\GD32F5HC_NS.FLM) -FP1($$Device:GD32F5HCRI$Flash\GD32F5HC_S.FLM))
- **转换结果(CMake)**：(未解析，未与实际使用的 .ld MEMORY 区做交叉校验)
- **备注**：FlashDriverDll 编码了 Keil 编程算法看到的 Flash 分区地址/长度（TrustZone 工程通常含 NS/Secure 两段），OnChipMemories 里的 OCR_RVCT* 则是 Keil scatter 文件生成时的实际内存区间来源；本工具完全不解析这两处，内存布局是否正确完全取决于最终采用的 .ld 文件（工程自带优先），请自行核对

## [x] 预处理器宏定义（已转换）

- **Keil 原配置**：USE_STDPERIPH_DRIVER, SYS_NS, GD32F5HC, LV_LVGL_H_INCLUDE_SIMPLE, LV_DEMO_CONF_INCLUDE_SIMPLE
- **转换结果(CMake)**：USE_STDPERIPH_DRIVER, SYS_NS, GD32F5HC, FW_DEBUG_ERR_REPORT, GD_ECLIPSE_GCC, LV_LVGL_H_INCLUDE_SIMPLE, LV_DEMO_CONF_INCLUDE_SIMPLE
- **备注**：仅列出 Debug 配置；Release 配置额外含 NDEBUG，不含 GD_ECLIPSE_GCC

## [x] Include 路径（已转换）

- **Keil 原配置**：17 条（Cads/VariousControls/IncludePath）
- **转换结果(CMake)**：17 条

## [x] 硬件 FPU（已转换）

- **Keil 原配置**：FPU3(SFPU)
- **转换结果(CMake)**：-mfpu=fpv5-sp-d16 -mfloat-abi=hard
- **备注**：Keil 的 Cpu 字符串不含浮点 ABI（hard/softfp/soft）信息，已默认按 hard 处理，请核对

## [ ] 优化等级（Cads/Optim）（未转换）

- **Keil 原配置**：Optim=7
- **转换结果(CMake)**：Debug: -O0 -g3；Release: -O0 -g（未识别的 Optim 值，使用工具默认值）

## [ ] C 语言标准（Cads/v6Lang）（未转换）

- **Keil 原配置**：v6Lang=3（ARM Compiler 6 内部编号）
- **转换结果(CMake)**：固定为 -std=gnu11
- **备注**：本工具未确认 v6Lang 编号与具体语言标准的对照表，为避免猜错不做映射；如原工程使用 C90/C99 等非 C11 标准，请手动核对源码兼容性

## [ ] 编译警告等级（Cads/wLevel）（未转换）

- **Keil 原配置**：wLevel=3
- **转换结果(CMake)**：未额外设置 -W 系列参数（沿用 CMakeLists.txt 模板默认值）

## [x] char 默认符号性（Cads/PlainCh）（已转换）

- **Keil 原配置**：PlainCh=0（plain char 默认有符号）
- **转换结果(CMake)**：-fsigned-char

## [x] C 运行库（ArmAdsMisc/useUlib）（已转换）

- **Keil 原配置**：MicroLib（微库）
- **转换结果(CMake)**：--specs=nano.specs（newlib-nano）
- **备注**：两者都是面向体积优化的精简 C 库，功能不完全等价，涉及 printf 浮点格式化等边界行为请自行验证

## [ ] 输出文件名（OutputName）（未转换）

- **Keil 原配置**：Project
- **转换结果(CMake)**：固定使用工程目录名作为 PROJECT_NAME
- **备注**：Keil 原配置的输出名与工程目录名不同，生成的 .elf/.hex/.bin 文件名会是 "Template.*"而不是 "Project.*"，如有下游脚本按文件名匹配请注意

## [ ] Hex 输出开关（CreateHexFile）（未转换）

- **Keil 原配置**：生成 .hex
- **转换结果(CMake)**：固定生成 .hex + .bin + .lst + .map（模板默认行为）

## [ ] 链接器杂项标志（LDads/Misc）（未转换）

- **Keil 原配置**：(无)
- **转换结果(CMake)**：(无)

## [x] ROM 符号复用（ROM-EXPORT/symbol）（已转换）

- **Keil 原配置**：(未检测到 ROM-EXPORT 引用)
- **转换结果(CMake)**：(无需处理)

## [x] 启动文件（已转换）

- **Keil 原配置**：..\..\Firmware\CMSIS\GD\GD32W51x_F5HC\Source\ARM\startup_gd32f5hc.s
- **转换结果(CMake)**：gcc_startup/startup_gd32f5hc.S
- **备注**：使用工程自带 gcc/ 目录下的启动文件

## [x] 链接脚本（已转换）

- **Keil 原配置**：(未声明 ScatterFile)
- **转换结果(CMake)**：ldscripts/gd32f5hc_flash.ld
- **备注**：未找到工程自带的 GCC 链接脚本，已使用内置模板（gd32w51x_f5hc）的通用链接脚本，请核对内存布局（尤其 TrustZone NS/S 划分）

## [x] 源文件清单（已转换）

- **Keil 原配置**：Keil Groups/Files 共 311 个条目
- **转换结果(CMake)**：310 个文件按 Keil 原始路径原地纳入 .project.json 的 sourceFiles 显式列表（未复制/未新建目录，gcc_startup/ 除外——启动文件因 GCC/ARMCLANG 语法不兼容必须替换）

## [x] CMSIS/CORE 头文件（已转换）

- **Keil 原配置**：RTE 声明使用 CMSIS/CORE 组件（Cversion=6.1.0）
- **转换结果(CMake)**：已加入 includePaths：../Firmware/CMSIS（来自工程自带 Firmware_Library）
- **备注**：未与内置/回退使用的 CMSIS-CORE 头文件版本做校验，如两者版本差异较大（如跨大版本）请手动确认 core_cmXX.h 是否兼容

## [ ] 编译后处理脚本（AfterMake）（未转换）

- **Keil 原配置**：(未配置)
- **转换结果(CMake)**：(未转换)

## [ ] 编译前处理脚本（BeforeCompile / BeforeMake）（未转换）

- **Keil 原配置**：(未配置)
- **转换结果(CMake)**：(未转换)

## [ ] Keil IDE 专属配置（调试器/仿真器 DLL、Flash 编程算法选择、Listing/Output 目录、批量编译标志等）（未转换）

- **Keil 原配置**：TargetDllName/TargetDlgDll、Flash1/Flash2 驱动选择、ListingPath/OutputDirectory、TargetStatus、CreateBatchFile 等
- **转换结果(CMake)**：(不适用)
- **备注**：这些字段描述的是 Keil uVision IDE 自身的调试器/仿真器/输出目录行为，在 GCC + CMake + GDB 工具链中没有对应概念，均不影响生成固件的实际行为，因此不做任何转换

## 导入过程告警

- Keil 工程的 Cpu 声明中检测到硬件 FPU（FPU3(SFPU)），已为本工程配置 -mfpu=fpv5-sp-d16 -mfloat-abi=hard；Keil 的 Cpu 字符串不包含浮点 ABI（hard/softfp/soft）信息，已默认按 hard 处理，请与原 Keil 工程的编译设置核对是否需要改为 softfp/soft。
- 已使用工程自带的 GCC 启动文件 ../Firmware/CMSIS/GD/GD32W51x_F5HC/Source/gcc/startup_gd32f5hc.S，未使用内置模板的通用启动文件。
- 未在工程目录中找到自带的 GCC 链接脚本（同级 gcc/ 目录不存在或为空），已使用内置模板（gd32w51x_f5hc）的通用链接脚本 gd32f5hc_flash.ld，请核对内存布局（尤其 TrustZone NS/S 划分）是否与原 Keil 工程一致。
- 目录扫描发现了 1 个 Keil 列表之外的源文件，请确认是否遗漏：GUI_APP/GD32EmbeddedUI/simulator/main.c
