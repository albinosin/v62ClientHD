#include "stdafx.h"
#include "Client.h"
#include "Logger.h"
#include <vector>

int Client::m_nGameWidth = 1280;
int Client::m_nGameHeight = 720;
int nStatusBarY = Client::m_nGameHeight - 578;

#pragma region status bar
const DWORD dwStatusBarPosRetn = 0x0073912B;
__declspec(naked) void AdjustStatusBar() {
	__asm {
		push nStatusBarY
		push ebx 
		mov ecx, esi
		jmp dword ptr[dwStatusBarPosRetn]
	}
}
const DWORD dwStatusBarBackgroundPosRetn = 0x0071F516;
__declspec(naked) void AdjustStatusBarBG() {
	__asm {
		push nStatusBarY
		movsd
		push 0
		jmp dword ptr[dwStatusBarBackgroundPosRetn]
	}
}
const DWORD dwStatusBarInputPosRetn = 0x00565028;
__declspec(naked) void AdjustStatusBarInput() {
	__asm {
		push nStatusBarY
		push edi
		lea ecx, [esi + 0x0CD0]
		jmp dword ptr[dwStatusBarInputPosRetn]
	}
}
#pragma endregion

void Client::UpdateResolution() {
	nStatusBarY = Client::m_nGameHeight - 578;

	Memory::WriteInt(0x00827734 + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0082773A + 1, m_nGameWidth);	//push 800 ; CWvsApp::InitializeGr2D

	Memory::CodeCave(AdjustStatusBar, 0x00739126, 5);
	Memory::CodeCave(AdjustStatusBarBG, 0x0071F514, 5);
	Memory::CodeCave(AdjustStatusBarInput, 0x00565022, 9);

	Memory::WriteInt(0x0045552F + 1, m_nGameHeight);//push 600 ; CSoundMan::PlayBGM // ok
	Memory::WriteInt(0x0073B66E + 1, m_nGameHeight - 33);	//push 567 ; IWzVector2D::RelMove //ok
	Memory::WriteInt(0x00746A6D + 1, m_nGameHeight - 20);	//push 580 // ok
	Memory::WriteInt(0x00746D07 + 1, m_nGameHeight - 20);	//push 580 // ok
	Memory::WriteInt(0x0074161D + 1, m_nGameHeight - 19);	//push 581 // ok
	Memory::WriteInt(0x00741D9D + 1, m_nGameHeight - 19);	//push 581
	Memory::WriteInt(0x0074161D + 1, m_nGameHeight - 19);	//push 581 //008D9373  move mana bar outline? //ty rynyan
	Memory::WriteInt(0x007424E8 + 1, m_nGameHeight - 19);	//push  // ok
	Memory::WriteInt(0x0073AD10 + 1, m_nGameHeight - 22);	//push 578 // ok
	Memory::WriteInt(0x0073AD15 + 1, m_nGameWidth);	//push 800 // ok
	Memory::WriteInt(0x0073AFB4 + 1, m_nGameHeight - 22);	//push 578
	Memory::WriteInt(0x0073AFB9 + 1, m_nGameWidth);	//push 800 ; CUIStatusBar
	Memory::WriteInt(0x00596C6D + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x00596C72 + 1, m_nGameWidth);	//push 800 ; (UI/Logo/NXXXon)
	Memory::WriteInt(0x004BC68A + 1, m_nGameWidth);	//mov ecx,800
	Memory::WriteInt(0x004BC679 + 1, m_nGameHeight);//mov ecx,600 ; CreateWnd

	Memory::WriteInt(0x00457837 + 1, m_nGameWidth);
	Memory::WriteInt(0x00457825 + 1, m_nGameHeight);

	Memory::WriteInt(0x004A2D6B + 1, m_nGameWidth);
	Memory::WriteInt(0x004A2D80 + 2, m_nGameHeight);

	Memory::WriteInt(0x00532B63 + 1, m_nGameWidth);
	Memory::WriteInt(0x00532B53 + 1, m_nGameHeight);

	/* Default UI Window Pos */
	Memory::WriteInt(0x00533AFC + 1, m_nGameWidth);
	Memory::WriteInt(0x00533AEC + 1, m_nGameHeight);

	/* Misc. */
	Memory::WriteInt(0x0075103C, m_nGameWidth);
	Memory::WriteInt(0x00751058, m_nGameHeight);

	Memory::WriteInt(0x005A72D2, m_nGameWidth);
	Memory::WriteInt(0x005A72DC, m_nGameHeight);

	//Memory::WriteInt(0x004EDAD8 + 1, m_nGameWidth);	//mov ecx,800
	 
	Memory::WriteInt(0x00826D8C + 1, m_nGameHeight);	// dd 600
	Memory::WriteInt(0x00826D91 + 1, m_nGameWidth);	// dd 800
	 
	Memory::WriteInt(0x0096AA10, (int)floor(m_nGameWidth / 2));	// dd 400
	Memory::WriteInt(0x0096C3C4, (int)floor(m_nGameHeight / 2));	// dd 300
	Memory::WriteInt(0x0096C3C0, (int)floor(m_nGameWidth / 2));	// dd 400
	Memory::WriteInt(0x005A5DDF + 2, (int)floor(-m_nGameWidth / 2));		//add edi,-400 ;


	Memory::WriteInt(0x0069B436 + 2, m_nGameWidth);//??related to displaying server message at top of screen
	Memory::WriteInt(0x0069B436 + 2, m_nGameWidth);//??related to displaying server message at top of screen

	Memory::WriteInt(0x0069B10C + 1, m_nGameHeight);//push 600
	Memory::WriteInt(0x0069B111 + 1, m_nGameWidth);	//push 800 ; CWnd::GetCanvas //!!length of server message at top

	NegativeRects(m_nGameWidth, m_nGameHeight);

	PositiveRects(m_nGameWidth, m_nGameHeight);

	UIPosition(m_nGameWidth, m_nGameHeight);

	ToastText(m_nGameWidth, m_nGameHeight);

	if (m_nGameHeight != 600 || m_nGameWidth != 800) {
		Memory::WriteInt(0x005032C4 + 1, m_nGameHeight);//push -300
		Memory::WriteInt(0x005032CA + 1, m_nGameWidth); //push -400
		Logger::Info("[Client] Custom resolution found, hiding login screen book frame");
	}
	
}


void Client::NegativeRects(int width, int height)
{
	int newWidth = (width / 2) * -1;
	int newHeight = (height / 2) * -1;

	Memory::WriteInt(0x00526507 + 2, newWidth);
	Memory::WriteInt(0x005264FB + 2, newHeight);

	Memory::WriteInt(0x00564127 + 1, newWidth);
	Memory::WriteInt(0x00564121 + 1, newHeight);

	Memory::WriteInt(0x00502FA2 + 1, newWidth);
	Memory::WriteInt(0x00502F9D + 1, newHeight);

	Memory::WriteInt(0x005A67C4 + 1, newHeight);
	Memory::WriteInt(0x005A67CC + 1, newWidth);

	Memory::WriteInt(0x00817B95 + 1, newWidth);
	Memory::WriteInt(0x00817B8F + 1, newHeight);

	Memory::WriteInt(0x005A5DDF + 1, newWidth);
}

void Client::PositiveRects(int width, int height)
{
	int newWidth = (width / 2);
	int newHeight = (height / 2);

	Memory::WriteInt(0x0096AA10, newWidth);
	Memory::WriteInt(0x0096AA14, newHeight);

	Memory::WriteInt(0x0096C3C0, newWidth);
	Memory::WriteInt(0x0096C3C4, newHeight);

	Memory::WriteInt(0x005A5BC7 + 1, newWidth);
	Memory::WriteInt(0x005A5BCC + 1, newHeight);

	Memory::WriteInt(0x007DB740 + 1, newWidth);
	Memory::WriteInt(0x007DB73B + 1, newHeight);

	Memory::WriteInt(0x005A5DAF + 1, newWidth);
}

void Client::UIPosition(int width, int height)
{
	int newWidth = width - 93;
	int newHeight = height - 93;

	Memory::WriteInt(0x0073D027 + 1, newHeight);
	Memory::WriteInt(0x0073D099 + 1, newWidth);

	newWidth = width - 22;
	newHeight = height - 22;

	Memory::WriteInt(0x00740D1A + 1, newHeight);
	Memory::WriteInt(0x00740D1F + 1, newWidth);

	Memory::WriteInt(0x0073AFB4 + 1, newHeight);
	Memory::WriteInt(0x0073AFB9 + 1, newWidth);

	Memory::WriteInt(0x0073AD10 + 1, newHeight);
	Memory::WriteInt(0x0073AD15 + 1, newWidth);

	Memory::WriteInt(0x0073911C + 1, newHeight);
	Memory::WriteInt(0x00739121 + 1, newWidth);

	newWidth = width - 33;
	newHeight = height - 33;

	Memory::WriteInt(0x00465116 + 1, newHeight);
	Memory::WriteInt(0x00465142 + 1, newHeight);
}

void Client::ToastText(int width, int height) {
	width = (width / 2) + 250;
	height -= 20;

	Memory::WriteInt(0x007130F3 + 1, width);
	Memory::WriteInt(0x007133EA + 1, width);
	Memory::WriteInt(0x00713032 + 1, height);
}
