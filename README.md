# Rocket League Arabic Chat Fix

## Overview
This BakkesMod plugin resolves the persistent issue of Arabic text rendering incorrectly (appearing as disconnected letters, reversed text, or missing glyphs) within the native Rocket League chat interface. 

By hooking directly into the game's UI rendering pipeline (`TAGame.GFxData_Chat_TA.OnChatMessage`), the plugin safely extracts chat data from memory, processes the Arabic characters using a dedicated shaping algorithm, and displays them correctly in an integrated, transparent overlay.

## Features
* **Native Arabic Rendering:** Correctly shapes and connects Right-to-Left (RTL) Arabic text, rendering it seamlessly over the game environment.
* **Bilingual Auto-Detection:** Intelligently scans incoming messages to differentiate between Arabic and Latin characters, ensuring English text is not unintentionally reversed.
* **Memory-Safe Interception:** Utilizes hardware exception handling (`__try` / `__except`) to safely probe Unreal Engine memory structures, completely preventing Access Violation crashes during game updates.
* **Customizable Overlay:** Includes a built-in BakkesMod configuration menu (via F2) allowing users to unlock, move, resize, and scale the chat overlay to fit their screen resolution.
* **Font Persistence:** Caches the ImGui font texture in the GPU to prevent memory leak crashes during standard operation.

## Installation

### Prerequisites
* Rocket League (Steam or Epic Games)
* BakkesMod installed and up to date


## Configuration
The plugin integrates directly into the BakkesMod interface. 

1. Press `F2` in-game to open the BakkesMod menu.
2. Navigate to the **Plugins** tab.
3. Select **Arabic Chat Fix** from the left-hand menu.

**Available Settings:**
* **Edit Mode:** Unlocks the chat window, allowing you to drag the title bar to move it and use the bottom-right corner to resize it. Disable this to lock the overlay and hide the borders.
* **Show Dark Background:** Toggles a semi-transparent black background behind the text for better readability on bright maps.
* **Text Size:** A slider to dynamically scale the font size without losing texture quality.

## Developer Notes & Building from Source

### Dependencies
* Visual Studio 2022 (MSVC v143)
* Windows SDK
* BakkesMod SDK
* C++17 Standard

### Compilation Notes
* Ensure the project is set to `Release` and `x64`.
* The plugin utilizes standard C++ `<codecvt>` for UTF-8 to UTF-16 conversions. Because this library is marked as deprecated in C++17, you must add `_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING` to your Preprocessor Definitions to allow the project to compile.
* **Warning regarding Live Reloading:** Due to how ImGui manages font textures in the GPU memory space, utilizing the `plugin reload` command in the BakkesMod console during active development may cause instability. It is highly recommended to restart the game executable entirely when testing modifications to the ImGui initialization sequence.

## Acknowledgments
Arabic character shaping is handled via the UTF8 Persian/Arabic Reshaper algorithm.
