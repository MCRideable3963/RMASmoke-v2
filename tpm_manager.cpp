void close_tpm_context(ESYS_CONTEXT* esys_ctx) {
    if (esys_ctx != nullptr) {
        TSS2_TCTI_CONTEXT* tcti_ctx = nullptr;
        // Retrieve the underlying TCTI context to free it cleanly
        Esys_GetTcti(esys_ctx, &tcti_ctx);
        Esys_Finalize(&esys_ctx);
        if (tcti_ctx != nullptr) {
            free(tcti_ctx);
        }
    }
}
