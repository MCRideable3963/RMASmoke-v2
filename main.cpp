#include <tss2/tss2_esys.h>
#include <tss2/tss2_tcti_device.h>
#include <iostream>

ESYS_CONTEXT* init_tpm_context() {
    size_t tcti_size = 0;
    TSS2_RC rc;

    // Directing to the kernel resource manager path to avoid exclusive lock blocks
    const char* tcti_path = "/dev/tpmrm0"; 

    // Get the required buffer size for the device TCTI context
    rc = Tss2_Tcti_Device_Init(nullptr, &tcti_size, tcti_path);
    if (rc != TSS2_RC_SUCCESS) {
        std::cerr << "[-] Failed to calculate TCTI context size.\n";
        return nullptr;
    }

    TSS2_TCTI_CONTEXT* tcti_ctx = (TSS2_TCTI_CONTEXT*)malloc(tcti_size);
    rc = Tss2_Tcti_Device_Init(tcti_ctx, &tcti_size, tcti_path);
    if (rc != TSS2_RC_SUCCESS) {
        std::cerr << "[-] Failed to initialize TCTI device framework.\n";
        free(tcti_ctx);
        return nullptr;
    }

    // Initialize the Enhanced System API (Esys) context using our TCTI
    ESYS_CONTEXT* esys_ctx = nullptr;
    rc = Esys_Initialize(&esys_ctx, tcti_ctx, nullptr);
    if (rc != TSS2_RC_SUCCESS) {
        std::cerr << "[-] Failed to initialize Esys context backend.\n";
        free(tcti_ctx);
        return nullptr;
    }

    return esys_ctx;
}
