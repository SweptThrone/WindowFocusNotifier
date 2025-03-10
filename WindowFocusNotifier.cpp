#include <iostream>
#include <Windows.h>
#include <Psapi.h>

HWND fgWindow = GetForegroundWindow();
const int numChars = 256;

int main() {
	while ( true ) {
		if ( fgWindow != GetForegroundWindow() ) {
			WCHAR windName[ numChars ];
			fgWindow = GetForegroundWindow();

			if ( fgWindow ) {
				DWORD dummy = 0;
				DWORD* pid = &dummy;
				DWORD tid = GetWindowThreadProcessId( fgWindow, pid );

				if ( pid ) {
					HANDLE proc = OpenProcess( PROCESS_ALL_ACCESS, true, *pid );

					if ( proc ) {
						GetModuleBaseNameW( proc, NULL, windName, numChars );
						wprintf( L"New foreground window: %s\n", windName );
					} else {
						std::cout << "No proc :( " << GetLastError() << std::endl;
					}
				} else {
					std::cout << "No pid :( " << GetLastError() << std::endl;
				}
			} else {
				// std::cout << "No fgWindow :( " << GetLastError() << std::endl; -- this just happens sometimes alongside a valid catch
			}
		}
	}
}
