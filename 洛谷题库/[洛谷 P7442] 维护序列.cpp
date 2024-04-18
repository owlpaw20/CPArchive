#include <cstdio>
#include <cstdint>

using u32 = uint32_t;

u32 N, M;
u32 shift, txor;

int main() {
  scanf("%u %u\n", &N, &M);

  do {
    int type;
    u32 x;

    scanf("%d %u\n", &type, &x);

    if (type == 1) {
      if (x) txor ^= (1 << shift);
      shift = (shift + 1 == N ? 0 : shift + 1);
    } else {
      if (!shift)
        printf("%u\n", x ^ txor);
      else
        printf("%u\n", ((x >> (N - shift)) | (x & ((1 << (N - shift)) - 1)) << shift) ^ txor);
    }
  } while (--M);

  return fflush(stdout), 0;
}
