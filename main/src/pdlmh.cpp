#include "../include/pdlmh.h"

#if 1
int __stdcall WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
#else
int main()
#endif
{
	Path::AutoCurrentFolder();
	if (Process::LockSelf()) {
		if (WinUI::Initialize()) WinUIMain();
		WinUI::End();
	}
	return 0;
}