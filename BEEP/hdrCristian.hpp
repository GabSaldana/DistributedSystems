/* CABECERA PARA LA ESTRUCTURA DE CRISTIAN */
#include <inttypes.h>

// Opcodes
#define NOP       0 // Ninguna operación (placeholder)
#define SVR_CLK  10 // Hora del servidor
#define ERR     100 // Error del servidor
#define OK      200 // OK del servidor

typedef struct {
  int64_t tv_sec;
  int64_t tv_usec;
} time64_t;

typedef struct {
  int32_t opcode;
  time64_t time;
} paqCristian;
