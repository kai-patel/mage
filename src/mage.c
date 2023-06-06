#include "mage.h"
#include <stdint.h>
#include <stdio.h>

uint32_t addThenMultiply(uint32_t a, uint32_t b, uint32_t c) {
  uint32_t addition = a + b;
  return addition * a * b;
}

int main() {
  uint32_t result = addThenMultiply(5, 3, 2);
  printf("%d\n", result);

  return 0;
}
