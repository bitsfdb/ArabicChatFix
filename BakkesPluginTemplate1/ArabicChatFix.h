#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "imgui/imgui.h"
#include <vector>
#include <string>
#include <mutex>

constexpr auto plugin_version = "1.0";

// Notice we added "PluginSettingsWindow" here!
class ArabicChatFix : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow, public BakkesMod::Plugin::PluginSettingsWindow
{
public:
    virtual void onLoad() override;
    virtual void onUnload() override;

    // Live Chat Engine
    std::vector<std::string> liveChatFeed;
    std::mutex chatMutex;
    void OnChatMessage(void* params);
    std::string ProcessArabicText(const std::string& input);

    // Window State
    bool isWindowOpen = false;
    bool isSetImGuiContextCalled_ = false;
    bool isFontLoaded = false;
    ImFont* arabicFont = nullptr;

    // --- NEW SETTINGS VARIABLES ---
    bool showBackground = false;
    bool editMode = false;
    float chatScale = 1.0f; // 1.0 is default font size

    // BakkesMod Window Overrides
    void Render() override;
    std::string GetMenuName() override;
    std::string GetMenuTitle() override;
    void SetImGuiContext(uintptr_t ctx) override;
    bool ShouldBlockInput() override;
    bool IsActiveOverlay() override;
    void OnOpen() override;
    void OnClose() override;

    // BakkesMod Settings Menu Overrides
    void RenderSettings() override;
    std::string GetPluginName() override;
};