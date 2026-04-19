#include "pch.h"
#include "ArabicChatFix.h"
#include "UTF8_Persian_Arabic_Reshaper.h"
#include <windows.h>
#include <codecvt>
#include <locale>
#include <algorithm>

// --- THE HARDWARE SAFETY NET ---
bool UnsafeReadFString(void* base, int offset, wchar_t* outBuf, int maxLen) {
    __try {
        wchar_t** strPtr = reinterpret_cast<wchar_t**>(reinterpret_cast<char*>(base) + offset);
        int32_t* arrNum = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(base) + offset + 8);

        if (*strPtr != nullptr && *arrNum > 0 && *arrNum < maxLen) {
            for (int i = 0; i < *arrNum; i++) {
                outBuf[i] = (*strPtr)[i];
            }
            outBuf[*arrNum] = L'\0';
            return true;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    return false;
}

// --- ARABIC TEXT WRAPPER (Smart Flip) ---
std::string ArabicChatFix::ProcessArabicText(const std::string& input) {
    UTF8_Persian_Arabic_Reshaper reshaper;
    std::string shaped = reshaper.reshape(input);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    try {
        std::wstring wShaped = conv.from_bytes(shaped);
        bool containsArabic = false;
        for (wchar_t c : wShaped) {
            if ((c >= 0x0600 && c <= 0x06FF) || (c >= 0xFB50 && c <= 0xFDFF) || (c >= 0xFE70 && c <= 0xFEFF)) {
                containsArabic = true;
                break;
            }
        }
        if (containsArabic) {
            std::reverse(wShaped.begin(), wShaped.end());
        }
        return conv.to_bytes(wShaped);
    }
    catch (...) { return shaped; }
}

// --- THE CHAT INTERCEPTOR ---
void ArabicChatFix::OnChatMessage(void* params) {
    if (!params) return;

    wchar_t nameBuf[256] = { 0 };
    wchar_t msgBuf[512] = { 0 };

    bool foundName = UnsafeReadFString(params, 0x8, nameBuf, 256);
    bool foundMsg = UnsafeReadFString(params, 0x18, msgBuf, 512);

    if (!foundMsg) return;

    std::wstring wMsg(msgBuf);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    std::string utf8Message;
    try { utf8Message = conv.to_bytes(wMsg); }
    catch (...) { return; }

    std::string pName = "Unknown";
    if (foundName) {
        std::wstring wName(nameBuf);
        try { pName = conv.to_bytes(wName); }
        catch (...) {}
    }

    std::string reshapedMsg = ProcessArabicText(utf8Message);
    std::string finalLine = "[" + pName + "]: " + reshapedMsg;

    std::lock_guard<std::mutex> lock(chatMutex);
    liveChatFeed.push_back(finalLine);
    if (liveChatFeed.size() > 8) {
        liveChatFeed.erase(liveChatFeed.begin());
    }
}

// --- IMGUI SETUP ---
void ArabicChatFix::SetImGuiContext(uintptr_t ctx) {
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
    if (!isFontLoaded) {
        ImGuiIO& io = ImGui::GetIO();
        auto fontPath = gameWrapper->GetDataFolder() / "ArabicFont.ttf";

        for (int i = 0; i < io.Fonts->Fonts.Size; i++) {
            ImFont* existingFont = io.Fonts->Fonts[i];
            if (existingFont->ConfigData && std::string(existingFont->ConfigData[0].Name).find("ArabicFont.ttf") != std::string::npos) {
                arabicFont = existingFont; break;
            }
        }

        if (arabicFont == nullptr) {
            if (std::filesystem::exists(fontPath)) {
                static const ImWchar arabic_ranges[] = {
                    0x0020, 0x00FF, 0x0600, 0x06FF, 0xFB50, 0xFDFF, 0xFE70, 0xFEFF, 0,
                };
                arabicFont = io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 20.0f, NULL, arabic_ranges);
                cvarManager->executeCommand("cl_gui_scale 1.001; cl_gui_scale 1.0");
            }
        }
        isFontLoaded = true;
    }
}

// --- F2 PLUGINS SETTINGS MENU ---
void ArabicChatFix::RenderSettings() {
    // 1. The Big Red Warning
    ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "CRITICAL WARNING: Do NOT use 'plugin reload' in the F6 console!");
    ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "If the plugin breaks, completely restart Rocket League to avoid game crashes.");
    ImGui::Separator();
    ImGui::Spacing();

    // 2. The Interactive Settings
    ImGui::Text("Chat Box Settings");
    ImGui::Checkbox("Edit Mode (Unlock Window to Move & Resize)", &editMode);

    if (editMode) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "-> Drag the window title to move it. Drag the bottom right corner to resize.");
    }

    ImGui::Checkbox("Show Dark Background", &showBackground);

    // 3. The Font Size Slider
    ImGui::SliderFloat("Text Size", &chatScale, 0.5f, 2.5f, "%.2f");
}
std::string ArabicChatFix::GetPluginName() { return "Arabic Chat Fix"; }

// --- RENDER LOOP (The Actual Chat Window) ---
void ArabicChatFix::Render() {
    if (!arabicFont) return;

    ImGuiWindowFlags windowFlags = 0;

    // If Edit Mode is OFF, lock the window down!
    if (!editMode) {
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        if (!showBackground) {
            windowFlags |= ImGuiWindowFlags_NoBackground;
        }
    }

    ImGui::SetNextWindowPos(ImVec2(50, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(800, 250), ImGuiCond_FirstUseEver);

    // Change title depending on mode
    ImGui::Begin(editMode ? "Arabic Chat (EDIT MODE)" : "Custom Arabic Chat", nullptr, windowFlags);

    ImGui::PushFont(arabicFont);
    ImGui::SetWindowFontScale(chatScale); // <--- THIS MAKES THE TEXT BIGGER OR SMALLER!

    std::lock_guard<std::mutex> lock(chatMutex);

    for (const std::string& chatLine : liveChatFeed) {
        float windowWidth = ImGui::GetWindowWidth();
        float textWidth = ImGui::CalcTextSize(chatLine.c_str()).x;
        // Adjust spacing based on if the scrollbar is visible
        ImGui::SetCursorPosX(windowWidth - textWidth - 15.0f);

        ImGui::TextUnformatted(chatLine.c_str());
    }

    ImGui::SetWindowFontScale(1.0f); // Reset scale for other windows
    ImGui::PopFont();
    ImGui::End();
}

// --- BAKKESMOD WINDOW BOILERPLATE ---
std::string ArabicChatFix::GetMenuName() { return "arabicchatfix"; }
std::string ArabicChatFix::GetMenuTitle() { return "Arabic Chat Fix"; }
bool ArabicChatFix::ShouldBlockInput() { return false; }
bool ArabicChatFix::IsActiveOverlay() { return true; }
void ArabicChatFix::OnOpen() { isWindowOpen = true; }
void ArabicChatFix::OnClose() { isWindowOpen = false; }