#include <Windows.h>

typedef void (WINAPI* INITPROC)(BOOL);
typedef void (WINAPI* ADDPASSWORDPROC)(wchar_t* /*Database Name*/, wchar_t*/*Password*/);

bool InitializeDBDefence(wchar_t* databaseName, wchar_t* password, const wchar_t* dllPath) {
    bool result = false;
    BOOL skipDialog = TRUE;

    // Get a handle to the DLL module.

    HINSTANCE dllInstanceHandle = LoadLibrary(dllPath);

    // If the handle is valid, try to get the function address.

    if (dllInstanceHandle != NULL) {
#pragma warning( push )
#pragma warning(disable : 4191)
        INITPROC InitializeProc = reinterpret_cast<INITPROC>(GetProcAddress(dllInstanceHandle, "Initialize"));

        // If the function address is valid, call the function.

        if (NULL != InitializeProc) {
            InitializeProc(skipDialog);
        }

        ADDPASSWORDPROC AddPwdAdd = reinterpret_cast<ADDPASSWORDPROC>(GetProcAddress(dllInstanceHandle, "AddPassword"));

        if (NULL != AddPwdAdd) {
            AddPwdAdd(databaseName, password);
            result = true;
        }
#pragma warning( pop )

        result &= (FreeLibrary(dllInstanceHandle)) ? true : false;
    }

    return result;
}