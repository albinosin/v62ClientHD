#pragma once
#include <vector>

#ifdef BUILDING_MY_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

class Client
{
public:
	DLL_EXPORT static void UpdateResolution();
	static void NegativeRects(int width, int height);
	static void PositiveRects(int width, int height);
	static void UIPosition(int width, int height);
	static void ToastText(int width, int height);

	static int m_nGameHeight;
	static int m_nGameWidth;
};