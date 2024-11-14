#include "stdafx.h"
#include "Client.h"
#include "INIReader.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

		INIReader reader("config.ini");
		if (reader.GetBoolean("general", "debug", false)) {
			Logger::CreateConsole();
		}

		if (reader.ParseError() == 0) Logger::Info("[Main] Config successfully parsed");
		else Logger::Warn("[Main] No config found. Skipping");

		Client::m_nGameWidth = reader.GetInteger("general", "width", 1024);
		Client::m_nGameHeight = reader.GetInteger("general", "height", 768);
		Logger::Info("[Main] Using resolution %dx%d", Client::m_nGameWidth, Client::m_nGameHeight);

		Client::UpdateResolution();
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		ExitProcess(0);
	}
    return TRUE;
}



