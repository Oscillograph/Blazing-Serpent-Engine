#include <utils/PlatformUtils.h>
#include <GameData.h>

#include <commdlg.h>

#include <vendor/glfw/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <vendor/glfw/glfw3native.h>

namespace BSE {
	std::string FileDialogs::OpenFile(const char* filter){
		OPENFILENAME ofn; // common dialog box structure
		CHAR szFile[260] = { 0 }; // if using TCHAR macros
		// initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)GameData::m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileName(&ofn) == TRUE){
			return ofn.lpstrFile;
		}
		return std::string();
	}
	
	std::string FileDialogs::SaveFile(const char* filter){
		OPENFILENAME ofn; // common dialog box structure
		CHAR szFile[260] = { 0 }; // if using TCHAR macros
		
		// initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)GameData::m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileName(&ofn) == TRUE){
			return ofn.lpstrFile;
		}
		return std::string();
	}
}
