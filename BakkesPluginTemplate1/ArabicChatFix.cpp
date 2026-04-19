#include "pch.h"
#include "ArabicChatFix.h"

BAKKESMOD_PLUGIN(ArabicChatFix, "Arabic Chat Fix", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
std::shared_ptr<GameWrapper> _globalGameWrapper;

void ArabicChatFix::onLoad()
{
    _globalCvarManager = cvarManager;
    _globalGameWrapper = gameWrapper;

    // The Golden Hook: Safely intercepts Epic Games UI chat
    gameWrapper->HookEventWithCaller<ActorWrapper>(
        "Function TAGame.GFxData_Chat_TA.OnChatMessage",
        [this](ActorWrapper caller, void* params, std::string eventname) {
            OnChatMessage(params);
        }
    );
}

void ArabicChatFix::onUnload()
{
    // BakkesMod handles unloading automatically
}