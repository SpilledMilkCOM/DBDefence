#include <Windows.h>

typedef void (WINAPI* INITPROC)(BOOL);
typedef void (WINAPI* ADDPASSWORDPROC)(const wchar_t* /*Database*/, const wchar_t*/*Password*/);

bool InitializeDBDefence(const wchar_t* databaseName, const wchar_t* password) {
    bool result = false;

    // Get a handle to the DLL module.

    HINSTANCE hinstLib = LoadLibrary(LR"(C:\tmp\DbDefence\dbd_clnt.dll)");

    // If the handle is valid, try to get the function address.

    if (hinstLib != NULL) {
#pragma warning( push )
#pragma warning(disable : 4191)
        INITPROC InitializeProc = reinterpret_cast<INITPROC>(GetProcAddress(hinstLib, "Initialize"));

        // If the function address is valid, call the function.

        if (NULL != InitializeProc) {
            (InitializeProc)(TRUE /*Skip dialog*/);
        }

        // Free the DLL module.

        ADDPASSWORDPROC AddPwdAdd = reinterpret_cast<ADDPASSWORDPROC>(GetProcAddress(hinstLib, "AddPassword"));

        if (NULL != AddPwdAdd) {
            AddPwdAdd(databaseName, password);
            result = true;
        }
#pragma warning( pop )
        // fFreeResult = FreeLibrary(hinstLib);
    }

    return result;
}