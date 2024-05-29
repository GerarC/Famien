#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void disassembly(Cpu6502 cpu, map_str_t* instructions, Word start, Word end){
    u32 address = start;
    Byte value = 0x00;
    Byte low = 0x00;
    Byte high = 0x00;
    Word line_addr = 0x0000;

    while(address <= (u32) end){
        line_addr = address;
        static char laddr_str[9];
        static char parsed_instruction[32];


        char* parsed_phrase = (char*) malloc(sizeof(char)*32);
        Byte opcode = cpu.read_ram(cpu.bus, address);
        address++;
        Instruction instruction = cpu.lookup[opcode];
        snprintf(laddr_str, sizeof(laddr_str), "%04X", line_addr);

        if(instruction.addrmode == &IMP)
            snprintf(
                    parsed_instruction,
                    sizeof(parsed_instruction),
                    "$%04X: %s {IMP}",
                    line_addr, instruction.name
            );
        else if(instruction.addrmode == &IMM){
            value = cpu.read_ram(cpu.bus, address);
            address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s #$%02X {IMM}",
                    line_addr, instruction.name, value
            );
        }
        else if(instruction.addrmode == &ZP0){
            low = cpu.read_ram(cpu.bus, address);
            address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%02X {ZP0}",
                    line_addr, instruction.name, low
            );
        }
        else if(instruction.addrmode == &ZPX){
            low = cpu.read_ram(cpu.bus, address);
            address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%02X, X {ZPX}",
                    line_addr, instruction.name, low
            );
        }
        else if(instruction.addrmode == &ZPY){
            low = cpu.read_ram(cpu.bus, address);
            address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%02X, Y {ZPY}",
                    line_addr, instruction.name, low
            );
        }
        else if(instruction.addrmode == &IZX){
            low = cpu.read_ram(cpu.bus, address);
            address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s ($%02X, X) {IZX}",
                    line_addr, instruction.name, low
            );
        }
        else if(instruction.addrmode == &IZY){
            low = cpu.read_ram(cpu.bus, address);
            address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s ($%02X, Y) {IZY}",
                    line_addr, instruction.name, low
            );
        }
        else if(instruction.addrmode == &ABS){
            low = cpu.read_ram(cpu.bus, address); address++;
            high = cpu.read_ram(cpu.bus, address); address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%04X {ABS}",
                    line_addr, instruction.name, (Word) high<< 8 | low
            );
        }
        else if(instruction.addrmode == &ABX){
            low = cpu.read_ram(cpu.bus, address); address++;
            high = cpu.read_ram(cpu.bus, address); address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%04X, X {ABX}",
                    line_addr, instruction.name, (Word) high<< 8 | low
            );
        }
        else if(instruction.addrmode == &ABY){
            low = cpu.read_ram(cpu.bus, address); address++;
            high = cpu.read_ram(cpu.bus, address); address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%04X, Y {ABY}",
                    line_addr, instruction.name, (Word) high<< 8 | low
            );
        }
        else if(instruction.addrmode == &IND){
            low = cpu.read_ram(cpu.bus, address); address++;
            high = cpu.read_ram(cpu.bus, address); address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s ($%04X) {IND}",
                    line_addr, instruction.name, (Word) high<< 8 | low
            );
        }
        else if(instruction.addrmode == &REL){
            value = cpu.read_ram(cpu.bus, address); address++;
            snprintf(
                    parsed_instruction, sizeof(parsed_instruction),
                    "$%04X: %s $%02X [$%04X] {REL}",
                    line_addr, instruction.name, value, address + value
            );
        }
        
        memcpy(parsed_phrase, parsed_instruction, 32);
        map_set(instructions, laddr_str, parsed_phrase);

        /* const char* key; */
        /* map_iter_t iter = map_iter(instructions); */
        /* while((key = map_next(&iter))){ */
        /*     printf("%s_%s\n", key, *map_get(instructions, key)); */
        /* } */
        /* printf("\n"); */

    }
}

