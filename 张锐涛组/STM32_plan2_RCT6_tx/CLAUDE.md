优先中文回复。

# 项目编译准则

## 编译工具

使用 `agent-harness/` 目录下的 Keil CLI 工具进行命令行编译，底层调用 UV4.exe。

## 编译命令

### 增量编译（推荐日常使用）
```bash
python -m cli_anything.keil.keil_cli -p "Project/STM32KeilPrj.uvprojx" build
```

### 全量重新编译（修改头文件或配置后使用）
```bash
python -m cli_anything.keil.keil_cli -p "Project/STM32KeilPrj.uvprojx" clean-build
```

### 查看项目信息
```bash
python -m cli_anything.keil.keil_cli -p "Project/STM32KeilPrj.uvprojx" project info
```

## 环境要求

- Keil MDK-ARM V5 (UV4.exe 位于 `C:/Keil_v5/UV4/UV4.exe`)
- Python >= 3.8
- 首次使用前安装 agent-harness: `pip install -e agent-harness/`

## 工具链信息

- 编译器: ARMCC V5.06 update 2
- 标准外设库: V3.5.0
- MCU 型号: STM32F103RCT6 (Cortex-M3, 256KB Flash, 48KB SRAM)
- 宏定义: STM32F10X_HD, USE_STDPERIPH_DRIVER
- 工程文件: Project/STM32KeilPrj.uvprojx
- 输出目录: Project/Objects/
- 编码格式: GB2312

## 代码修改后必做事项

1. **修改代码后必须编译验证**，确保 0 错误 0 警告
2. 使用 `clean-build` 命令进行全量编译
3. 确认编译输出中 `Result: 0 error(s), 0 warning(s)` 才算通过
