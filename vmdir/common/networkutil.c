#include "includes.h"

DWORD
VmDirOpenServerConnection(
	PVM_DIR_CONNECTION *ppConnection
	)
{
	DWORD dwError = 0;
	if (ppConnection == NULL){
		dwError = ERROR_INVALID_PARAMETER;
		BAIL_ON_VMDIR_ERROR (dwError);
	}
	dwError = VmDirOpenServerConnectionImpl(ppConnection);
	BAIL_ON_VMDIR_ERROR (dwError);
cleanup:
	return dwError;
error:
	if (ppConnection != NULL){
		*ppConnection = NULL;
	}
	goto cleanup;

}

VOID
VmDirCloseServerConnection(
	PVM_DIR_CONNECTION pConnection
	)
{
	if (pConnection){
		VmDirCloseServerConnectionImpl(pConnection);

	}
}

VOID
VmDirShutdownServerConnection(
	PVM_DIR_CONNECTION pConnection
	)
{
	if (pConnection){
		VmDirShutdownServerConnectionImpl(pConnection);

	}
}


VOID
VmDirFreeServerConnection(
	PVM_DIR_CONNECTION pConnection
	)
{
	if (pConnection){
                VmDirCloseServerConnection (pConnection);
		VmDirFreeConnectionImpl(pConnection);
	}
}

DWORD
VmDirOpenClientConnection(
	PVM_DIR_CONNECTION *ppConnection
	)
{
	DWORD dwError = 0;
	if (ppConnection == NULL){
		dwError = ERROR_INVALID_PARAMETER;
		BAIL_ON_VMDIR_ERROR (dwError);
	}
	dwError = VmDirOpenClientConnectionImpl(ppConnection);
	BAIL_ON_VMDIR_ERROR (dwError);
cleanup:
	return dwError;
error:
	if (ppConnection != NULL){
		*ppConnection = NULL;
	}
	goto cleanup;
}

VOID
VmDirCloseClientConnection(
	PVM_DIR_CONNECTION pConnection
	)
{
	if (pConnection){
		VmDirCloseClientConnectionImpl(pConnection);

	}
}

VOID
VmDirFreeClientConnection(
	PVM_DIR_CONNECTION pConnection
	)
{
	if (pConnection){
                VmDirCloseClientConnection (pConnection);
		VmDirFreeConnectionImpl(pConnection);
        }
}

DWORD
VmDirAcceptConnection(
	PVM_DIR_CONNECTION pConnection,
	PVM_DIR_CONNECTION *ppConnection
	)
{
	DWORD dwError = 0;
	if (pConnection == NULL){
		dwError = ERROR_INVALID_PARAMETER;
		BAIL_ON_VMDIR_ERROR (dwError);
	}
	dwError = VmDirAcceptConnectionImpl(pConnection,ppConnection);
	BAIL_ON_VMDIR_ERROR(dwError);
cleanup:
	return dwError;
error:
	goto cleanup;
}

DWORD
VmDirReadData(
	PVM_DIR_CONNECTION pConnection,
	PBYTE *ppResponse,
	PDWORD pdwResponseSize
    )
{
	DWORD dwError = 0;
	if (ppResponse == NULL || pConnection == NULL || pdwResponseSize == NULL){
		dwError = ERROR_INVALID_PARAMETER;
		BAIL_ON_VMDIR_ERROR(dwError);
	}
	dwError = VmDirReadDataImpl(pConnection,ppResponse,pdwResponseSize);
	BAIL_ON_VMDIR_ERROR (dwError);
cleanup:
	return dwError;
error:
	if (ppResponse != NULL){
		*ppResponse = NULL;
	}
	if (pdwResponseSize != NULL){
		*pdwResponseSize = 0;
	}
	goto cleanup;
}

DWORD
VmDirWriteData(
	PVM_DIR_CONNECTION pConnection,
	PBYTE pRequest,
	DWORD dwRequestSize
	)
{
	DWORD dwError = 0;
	if (pConnection == NULL || pRequest == NULL){
		dwError = ERROR_INVALID_PARAMETER;
		BAIL_ON_VMDIR_ERROR(dwError);
	}
	if (dwRequestSize > 0){
		dwError = VmDirWriteDataImpl (pConnection, pRequest, dwRequestSize);
	}
cleanup:
	return dwError;
error:
	goto cleanup;
}

DWORD
VmDirMakeServerRequest(
	PVM_DIR_CONNECTION pConnection,
	PBYTE pRequest,
	DWORD dwRequestSize,
	PBYTE *ppResponse,
	PDWORD pdwResponseSize
	)
{
	DWORD dwError = 0;
	if (pConnection == NULL || pRequest == NULL || !dwRequestSize){
		dwError = ERROR_INVALID_PARAMETER;
		BAIL_ON_VMDIR_ERROR (dwError);
	}
	dwError = VmDirWriteData(pConnection, pRequest, dwRequestSize);
	BAIL_ON_VMDIR_ERROR (dwError);
        dwError = VmDirReadData (pConnection, ppResponse, pdwResponseSize);
        BAIL_ON_VMDIR_ERROR (dwError);
cleanup:
	return dwError;
error:
	if (ppResponse != NULL){
		*ppResponse = NULL;
	}
	if (pdwResponseSize != NULL){
		*pdwResponseSize = 0;
	}
	goto cleanup;
}
