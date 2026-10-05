#ifndef TPM_MANAGER_HPP
#define TPM_MANAGER_HPP

#include <tss2/tss2_esys.h>

// Pre-compiler safety check: Ensures these functions use C++ linkage
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes the TCTI device context via the kernel resource manager (/dev/tpmrm0)
 * and sets up the primary ESYS context layer.
 * 
 * @return A valid pointer to an ESYS_CONTEXT, or nullptr on failure.
 */
ESYS_CONTEXT* init_tpm_context(void);

/**
 * Cleanly finalizes the ESYS context layer and frees the underlying TCTI buffer space
 * to avoid leaving dangling handles in the hardware subsystem.
 * 
 * @param esys_ctx Pointer to the active ESYS context to be destroyed.
 */
void close_tpm_context(ESYS_CONTEXT* esys_ctx);

#ifdef __cplusplus
}
#endif

#endif // TPM_MANAGER_HPP
