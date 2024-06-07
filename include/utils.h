#ifndef UTILS_H
#define UTILS_H

#include "cpu6502.h"
#include "map.h"
#include "types.h"

/*
 * Parses a hex number to a char*
 * With a limit of 8 hex symbols
 *
 * input:
 *  u32 hex: any hex number.
 *  Byte size: the size of the hex.
 *
 * output:
 *  a char* of the parsed hex.
 */
char *hex_string(u32 hex, Byte size);

/*
 * Disassembles a section of the ram.
 *
 * input:
 *  cpu: Cpu that is connected with the ram.
 *  instructions: a map that will contain instructions.
 *  start: memory address where to start disassembly process.
 *  end: memory address limit.
 *
 *  output:
 *      map with the ram portion parsed, where key is the memory address and the
 * value is the disassembled instruction.
 */
void disassembly(Cpu6502 cpu, map_str_t *instructions, Word start, Word end);

#endif // UTILS_H
