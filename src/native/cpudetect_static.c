#include <stdio.h>

#if defined (__i386__) || defined (__x86_64__)

#include <cpuid.h>

#define __x86__

/* `clang` calls this `bit_AESNI`. No-one can accuse them of conformism, at least. */
#define bit_AES (1 << 25)

/* This looks absent in the headers on OSX, even though they derive from a
 * `clang` which has them. */
#define signature_INTEL_ebx 0x756e6547
#define signature_AMD_ebx   0x68747541

#endif

static int features () {
#if defined (__x86__)

  unsigned int sig, eax, ebx, ecx, edx;
  int max = __get_cpuid_max (0, &sig);

  if (max < 1) return 1;

  if (sig == signature_INTEL_ebx || sig == signature_AMD_ebx) {
    __cpuid (1, eax, ebx, ecx, edx);
    if (ecx & bit_AES) return 0;
  }
#endif
  return 1;
}

int main () {
  return features ();
}
