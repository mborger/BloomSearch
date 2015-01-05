#include <inttypes.h>

#define FNV64_1A_INIT 0xcbf29ce484222325ULL

uint64_t fnv64a(unsigned char *buf, uint64_t len, uint64_t hval = FNV64_1A_INIT);
