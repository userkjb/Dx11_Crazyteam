#include "PreCompile.h"
#include "TextimeInput.h"

#include <EnginePlatform/EngineInput.h>


std::string UTextimeInput::ReadText ="";
HWND UTextimeInput::hwnd;
HIMC UTextimeInput::himc;

void UTextimeInput::IMEInput()
{
	if (true == UEngineInput::IsDown(VK_BACK))
	{
		if (ReadText.size() >0)
		{
			ReadText.pop_back();
		}
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		ReadText += " ";
		return;
	}

	for (int i = '0'; i <= '9'; i++)
	{
		if (true == UEngineInput::IsDown(i))
		{
			ReadText += static_cast<char>(i);
			return;
		}
	}

	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (true == UEngineInput::IsDown(i))
		{
			ReadText += static_cast<char>(i);
			return;
		}
	}
}

std::string UTextimeInput::GetReadText()
{
	return ReadText;
}



void UTextimeInput::SetIme(HWND _hWnd,UINT _msg, WPARAM _wparam, LPARAM _lParam)
{
	hwnd = _hWnd;
	himc = ImmGetContext(_hWnd);

	int len = 0;
	switch (_msg)
	{
	case WM_IME_COMPOSITION:

		if (_lParam & GCS_COMPSTR) // ������ ���� 
		{
			len = ImmGetCompositionString(himc, GCS_COMPSTR, NULL, 0);
			std::string Write;
			if (len > 0)
			{
				ImmGetCompositionString(himc, GCS_COMPSTR, &Write[0], len);
				ReadText += Write;
			}
		}
		
		if (_lParam & GCS_RESULTSTR) // �ϼ��� ����
		{
			len = ImmGetCompositionString(himc, GCS_RESULTSTR, NULL, 0);
			std::string Write;
			if (len > 0)
			{
				Write.resize(len);
				ImmGetCompositionString(himc, GCS_RESULTSTR, &Write[0], len);
				ReadText += Write;
			}

			ImmReleaseContext(hwnd, himc); Write = '\0';
		}
		break;
	case WM_CHAR:
		break;
	case WM_KEYDOWN:
		break;
	default:
		break;
	}
}


