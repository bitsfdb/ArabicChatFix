#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "imgui/imgui.h"
#include <vector>
#include <string>
#include <mutex>

constexpr auto plugin_version = "1.0";

class ArabicChatFix : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
public:
    virtual void onLoad() override;
    virtual void onUnload() override;

    // Live Chat Feed
    std::vector<std::string> liveChatFeed;
    std::mutex chatMutex;
    int hookFires = 0; // <--- ADDED DEBUG COUNTER
    void OnChatMessage(void* params);

    // Window State
    bool isWindowOpen = false;
    bool isSetImGuiContextCalled_ = false;
    bool isFontLoaded = false;
    ImFont* arabicFont = nullptr;

    void Render() override;
    std::string GetMenuName() override;
    std::string GetMenuTitle() override;
    void SetImGuiContext(uintptr_t ctx) override;
    bool ShouldBlockInput() override;
    bool IsActiveOverlay() override;
    void OnOpen() override;
    void OnClose() override;
};