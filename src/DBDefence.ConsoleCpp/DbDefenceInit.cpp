#include <Windows.h>

typedef void (WINAPI* INITPROC)(BOOL);
typedef void (WINAPI* ADDPASSWORDPROC)(const wchar_t* /*Database Name*/, const wchar_t*/*Password*/);

bool InitializeDBDefence(const wchar_t* databaseName, const wchar_t* password) {
    bool result = false;
    BOOL skipDialog = TRUE;

    // Get a handle to the DLL module.

    HINSTANCE dllInstanceHandle = LoadLibrary(LR"(C:\tmp\DbDefence\dbd_clnt.dll)");

    // If the handle is valid, try to get the function address.

    if (dllInstanceHandle != NULL) {
#pragma warning( push )
#pragma warning(disable : 4191)
        INITPROC InitializeProc = reinterpret_cast<INITPROC>(GetProcAddress(dllInstanceHandle, "Initialize"));

        // If the function address is valid, call the function.

        if (NULL != InitializeProc) {
            InitializeProc(skipDialog);
        }

        // Free the DLL module.

        ADDPASSWORDPROC AddPwdAdd = reinterpret_cast<ADDPASSWORDPROC>(GetProcAddress(dllInstanceHandle, "AddPassword"));

        if (NULL != AddPwdAdd) {
            AddPwdAdd(databaseName, password);
            result = true;
        }
#pragma warning( pop )

        result &= FreeLibrary(dllInstanceHandle);
    }

    return result;
}