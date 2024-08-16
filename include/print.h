#include <stdio.h>
namespace global {
extern char out_buf[256];
}

#define printf(...)                                                            \
  {                                                                            \
    snprintf(global::out_buf, sizeof(global::out_buf), __VA_ARGS__);           \
    Serial.print(global::out_buf);                                             \
  }
