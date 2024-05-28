#include "../include/cpu6502.h"
#include <stdio.h>

void initialize_cpu(Cpu6502 *cpu){
    cpu->pc = 0x0000;
    cpu->sp = 0x00FD;
    cpu->st = 0x00;
    cpu->u = 1;
    cpu->a = 0x00;
    cpu->x = 0x00;
    cpu->y = 0x00;
    cpu->fetched = 0x00;
    cpu->opcode = 0x00;
    cpu->address_absolute = 0x0000;
    cpu->address_relative = 0x0000;
    cpu->cycles = 0;

    Instruction instructions[] = {
		{ "BRK", &BRK, &IMM, 7 },{ "ORA", &ORA, &IZX, 6 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 3 },{ "ORA", &ORA, &ZP0, 3 },{ "ASL", &ASL, &ZP0, 5 },{ "???", &XXX, &IMP, 5 },
        { "PHP", &PHP, &IMP, 3 },{ "ORA", &ORA, &IMM, 2 },{ "ASL", &ASL, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "???", &NOP, &IMP, 4 },{ "ORA", &ORA, &ABS, 4 },{ "ASL", &ASL, &ABS, 6 },{ "???", &XXX, &IMP, 6 },
		{ "BPL", &BPL, &REL, 2 },{ "ORA", &ORA, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 4 },{ "ORA", &ORA, &ZPX, 4 },{ "ASL", &ASL, &ZPX, 6 },{ "???", &XXX, &IMP, 6 },
        { "CLC", &CLC, &IMP, 2 },{ "ORA", &ORA, &ABY, 4 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 7 },
        { "???", &NOP, &IMP, 4 },{ "ORA", &ORA, &ABX, 4 },{ "ASL", &ASL, &ABX, 7 },{ "???", &XXX, &IMP, 7 },
		{ "JSR", &JSR, &ABS, 6 },{ "AND", &AND, &IZX, 6 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "BIT", &BIT, &ZP0, 3 },{ "AND", &AND, &ZP0, 3 },{ "ROL", &ROL, &ZP0, 5 },{ "???", &XXX, &IMP, 5 },
        { "PLP", &PLP, &IMP, 4 },{ "AND", &AND, &IMM, 2 },{ "ROL", &ROL, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "BIT", &BIT, &ABS, 4 },{ "AND", &AND, &ABS, 4 },{ "ROL", &ROL, &ABS, 6 },{ "???", &XXX, &IMP, 6 },
		{ "BMI", &BMI, &REL, 2 },{ "AND", &AND, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 4 },{ "AND", &AND, &ZPX, 4 },{ "ROL", &ROL, &ZPX, 6 },{ "???", &XXX, &IMP, 6 },
        { "SEC", &SEC, &IMP, 2 },{ "AND", &AND, &ABY, 4 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 7 },
        { "???", &NOP, &IMP, 4 },{ "AND", &AND, &ABX, 4 },{ "ROL", &ROL, &ABX, 7 },{ "???", &XXX, &IMP, 7 },
		{ "RTI", &RTI, &IMP, 6 },{ "EOR", &EOR, &IZX, 6 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 3 },{ "EOR", &EOR, &ZP0, 3 },{ "LSR", &LSR, &ZP0, 5 },{ "???", &XXX, &IMP, 5 },
        { "PHA", &PHA, &IMP, 3 },{ "EOR", &EOR, &IMM, 2 },{ "LSR", &LSR, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "JMP", &JMP, &ABS, 3 },{ "EOR", &EOR, &ABS, 4 },{ "LSR", &LSR, &ABS, 6 },{ "???", &XXX, &IMP, 6 },
		{ "BVC", &BVC, &REL, 2 },{ "EOR", &EOR, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 4 },{ "EOR", &EOR, &ZPX, 4 },{ "LSR", &LSR, &ZPX, 6 },{ "???", &XXX, &IMP, 6 },
        { "CLI", &CLI, &IMP, 2 },{ "EOR", &EOR, &ABY, 4 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 7 },
        { "???", &NOP, &IMP, 4 },{ "EOR", &EOR, &ABX, 4 },{ "LSR", &LSR, &ABX, 7 },{ "???", &XXX, &IMP, 7 },
		{ "RTS", &RTS, &IMP, 6 },{ "ADC", &ADC, &IZX, 6 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 3 },{ "ADC", &ADC, &ZP0, 3 },{ "ROR", &ROR, &ZP0, 5 },{ "???", &XXX, &IMP, 5 },
        { "PLA", &PLA, &IMP, 4 },{ "ADC", &ADC, &IMM, 2 },{ "ROR", &ROR, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "JMP", &JMP, &IND, 5 },{ "ADC", &ADC, &ABS, 4 },{ "ROR", &ROR, &ABS, 6 },{ "???", &XXX, &IMP, 6 },
		{ "BVS", &BVS, &REL, 2 },{ "ADC", &ADC, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 4 },{ "ADC", &ADC, &ZPX, 4 },{ "ROR", &ROR, &ZPX, 6 },{ "???", &XXX, &IMP, 6 },
        { "SEI", &SEI, &IMP, 2 },{ "ADC", &ADC, &ABY, 4 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 7 },
        { "???", &NOP, &IMP, 4 },{ "ADC", &ADC, &ABX, 4 },{ "ROR", &ROR, &ABX, 7 },{ "???", &XXX, &IMP, 7 },
		{ "???", &NOP, &IMP, 2 },{ "STA", &STA, &IZX, 6 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 6 },
        { "STY", &STY, &ZP0, 3 },{ "STA", &STA, &ZP0, 3 },{ "STX", &STX, &ZP0, 3 },{ "???", &XXX, &IMP, 3 },
        { "STY", &STY, &ABS, 4 },{ "STA", &STA, &ABS, 4 },{ "STX", &STX, &ABS, 4 },{ "???", &XXX, &IMP, 4 },
		{ "BCC", &BCC, &REL, 2 },{ "STA", &STA, &IZY, 6 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 6 },
        { "STY", &STY, &ZPX, 4 },{ "STA", &STA, &ZPX, 4 },{ "STX", &STX, &ZPY, 4 },{ "???", &XXX, &IMP, 4 },
        { "DEY", &DEY, &IMP, 2 },{ "???", &NOP, &IMP, 2 },{ "TXA", &TXA, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "TYA", &TYA, &IMP, 2 },{ "STA", &STA, &ABY, 5 },{ "TXS", &TXS, &IMP, 2 },{ "???", &XXX, &IMP, 5 },
        { "???", &NOP, &IMP, 5 },{ "STA", &STA, &ABX, 5 },{ "???", &XXX, &IMP, 5 },{ "???", &XXX, &IMP, 5 },
		{ "LDY", &LDY, &IMM, 2 },{ "LDA", &LDA, &IZX, 6 },{ "LDX", &LDX, &IMM, 2 },{ "???", &XXX, &IMP, 6 },
        { "LDY", &LDY, &ZP0, 3 },{ "LDA", &LDA, &ZP0, 3 },{ "LDX", &LDX, &ZP0, 3 },{ "???", &XXX, &IMP, 3 },
        { "TAY", &TAY, &IMP, 2 },{ "LDA", &LDA, &IMM, 2 },{ "TAX", &TAX, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "LDY", &LDY, &ABS, 4 },{ "LDA", &LDA, &ABS, 4 },{ "LDX", &LDX, &ABS, 4 },{ "???", &XXX, &IMP, 4 },
		{ "BCS", &BCS, &REL, 2 },{ "LDA", &LDA, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 5 },
        { "LDY", &LDY, &ZPX, 4 },{ "LDA", &LDA, &ZPX, 4 },{ "LDX", &LDX, &ZPY, 4 },{ "???", &XXX, &IMP, 4 },
        { "CLV", &CLV, &IMP, 2 },{ "LDA", &LDA, &ABY, 4 },{ "TSX", &TSX, &IMP, 2 },{ "???", &XXX, &IMP, 4 },
        { "LDY", &LDY, &ABX, 4 },{ "LDA", &LDA, &ABX, 4 },{ "LDX", &LDX, &ABY, 4 },{ "???", &XXX, &IMP, 4 },
		{ "CPY", &CPY, &IMM, 2 },{ "CMP", &CMP, &IZX, 6 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "CPY", &CPY, &ZP0, 3 },{ "CMP", &CMP, &ZP0, 3 },{ "DEC", &DEC, &ZP0, 5 },{ "???", &XXX, &IMP, 5 },
        { "INY", &INY, &IMP, 2 },{ "CMP", &CMP, &IMM, 2 },{ "DEX", &DEX, &IMP, 2 },{ "???", &XXX, &IMP, 2 },
        { "CPY", &CPY, &ABS, 4 },{ "CMP", &CMP, &ABS, 4 },{ "DEC", &DEC, &ABS, 6 },{ "???", &XXX, &IMP, 6 },
		{ "BNE", &BNE, &REL, 2 },{ "CMP", &CMP, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 4 },{ "CMP", &CMP, &ZPX, 4 },{ "DEC", &DEC, &ZPX, 6 },{ "???", &XXX, &IMP, 6 },
        { "CLD", &CLD, &IMP, 2 },{ "CMP", &CMP, &ABY, 4 },{ "NOP", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 7 },
        { "???", &NOP, &IMP, 4 },{ "CMP", &CMP, &ABX, 4 },{ "DEC", &DEC, &ABX, 7 },{ "???", &XXX, &IMP, 7 },
		{ "CPX", &CPX, &IMM, 2 },{ "SBC", &SBC, &IZX, 6 },{ "???", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "CPX", &CPX, &ZP0, 3 },{ "SBC", &SBC, &ZP0, 3 },{ "INC", &INC, &ZP0, 5 },{ "???", &XXX, &IMP, 5 },
        { "INX", &INX, &IMP, 2 },{ "SBC", &SBC, &IMM, 2 },{ "NOP", &NOP, &IMP, 2 },{ "???", &SBC, &IMP, 2 },
        { "CPX", &CPX, &ABS, 4 },{ "SBC", &SBC, &ABS, 4 },{ "INC", &INC, &ABS, 6 },{ "???", &XXX, &IMP, 6 },
		{ "BEQ", &BEQ, &REL, 2 },{ "SBC", &SBC, &IZY, 5 },{ "???", &XXX, &IMP, 2 },{ "???", &XXX, &IMP, 8 },
        { "???", &NOP, &IMP, 4 },{ "SBC", &SBC, &ZPX, 4 },{ "INC", &INC, &ZPX, 6 },{ "???", &XXX, &IMP, 6 },
        { "SED", &SED, &IMP, 2 },{ "SBC", &SBC, &ABY, 4 },{ "NOP", &NOP, &IMP, 2 },{ "???", &XXX, &IMP, 7 },
        { "???", &NOP, &IMP, 4 },{ "SBC", &SBC, &ABX, 4 },{ "INC", &INC, &ABX, 7 },{ "???", &XXX, &IMP, 7 },
	};

    for(int i = 0; i < 256; i++) cpu->lookup[i] = instructions[i];
}

void execute_cpu(Cpu6502 *cpu){
    int x =  0;
     while (cpu->cycles >= 0) {
        clock(cpu);

        if(cpu->cycles == 0){
            printf("(%s)", cpu->lookup[cpu->opcode].name);
            printf("%s\n", parse_cpu_str(*cpu));
            x++;
        }
        if(x == 16) break;
     }
}

void connect_bus(Cpu6502 *cpu, Bus *bus){
    cpu->bus = bus;
}

void connect_bus_methods(
        Cpu6502 *cpu, void (*write_ram)(Bus *, Word, Byte), Byte (*read_ram)(Bus *, Word)){
    cpu->read_ram = read_ram;
    cpu->write_ram = write_ram;
}

void reset_cpu(Cpu6502 *cpu){
    cpu->address_absolute = 0xFFFC;

    Word low = (cpu->read_ram)(cpu->bus, cpu->address_absolute + 0);
    Word high = cpu->read_ram(cpu->bus, cpu->address_absolute + 1);

    cpu->pc = (high << 8) | low;
    cpu->sp = 0x00FD;
    cpu->st = 0x00 | U;
    cpu->a = 0x00;
    cpu->x = 0x00;
    cpu->y = 0x00;
    cpu->fetched = 0x00;
    cpu->opcode = 0x00;
    cpu->address_absolute = 0x0000;
    cpu->address_relative = 0x0000;
    cpu->cycles = 8;
}

void clock(Cpu6502 *cpu){
    if(cpu->cycles == 0){
        cpu->opcode = cpu->read_ram(cpu->bus, cpu->pc);
        set_flag(cpu, U, 1);
        cpu->pc++;
        cpu->cycles = cpu->lookup[cpu->opcode].cycles;
        Byte additional_cycle1 = cpu->lookup[cpu->opcode].addrmode(cpu);
        Byte additional_cycle2 = cpu->lookup[cpu->opcode].operate(cpu);
        cpu->cycles += additional_cycle1 & additional_cycle2;
        set_flag(cpu, U, 1);
    }
    cpu->cycles--;
}
    
Byte fetch(Cpu6502 *cpu){
    if(!(cpu->lookup[cpu->opcode].addrmode == &IMP))
        cpu->fetched = cpu->read_ram(cpu->bus, cpu->address_absolute);
    return cpu->fetched;
}

void set_flag(Cpu6502 *cpu, Flags6502 flag, int v){
    if(v) cpu->st |= flag;
    else cpu->st &= ~flag;
}


void irq(Cpu6502 *cpu){
    if(cpu->i == 0){
        cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, (cpu->pc >> 8) & 0x00FF);
        cpu->sp--;
        cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->pc & 0x00FF);
        cpu->sp--;
        set_flag(cpu, B, 0);
        set_flag(cpu, U, 1);
        set_flag(cpu, I, 1);
        cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->st);
        cpu->sp--;

        cpu->address_absolute = 0xFFFE;
        Word low = cpu->read_ram(cpu->bus, cpu->address_absolute + 0);
        Word high = cpu->read_ram(cpu->bus, cpu->address_absolute + 1);
        cpu->pc = (high << 8) | low;
        cpu->cycles = 7;
    }
}

void nmi(Cpu6502 *cpu){
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, (cpu->pc >> 8) & 0x00FF);
    cpu->sp--;
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->pc & 0x00FF);
    cpu->sp--;
    set_flag(cpu, B, 0);
    set_flag(cpu, U, 1);
    set_flag(cpu, I, 1);
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->st);
    cpu->sp--;

    cpu->address_absolute = 0xFFFA;
    Word low = cpu->read_ram(cpu->bus, cpu->address_absolute + 0);
    Word high = cpu->read_ram(cpu->bus, cpu->address_absolute + 1);
    cpu->pc = (high << 8) | low;
    cpu->cycles = 8;
}


char* parse_cpu_str(Cpu6502 cpu){
    static char buffer[128];
    snprintf(buffer, sizeof(buffer),
            "Cpu {pc: %04X, sp: %04X, a: %02X, x: %02X, y: %02X, flags: %02X, opcode: %02X, cycles: %i, addr_abs: %04X}",
            cpu.pc, cpu.sp, cpu.a, cpu.x, cpu.y, cpu.st, cpu.opcode, cpu.cycles, cpu.address_absolute);
    return buffer;
}

// Addressing Modes
Byte IMP(Cpu6502 *cpu){
    cpu->fetched = cpu->a;
    return 0;
}

Byte IMM(Cpu6502 *cpu){
    cpu->address_absolute = cpu->pc++;
    return 0;
}

Byte ZP0(Cpu6502 *cpu){
    cpu->address_absolute = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    cpu->address_absolute &= 0x00FF;
    return 0;
}

Byte ZPX(Cpu6502 *cpu){
    cpu->address_absolute = cpu->read_ram(cpu->bus, cpu->pc + cpu->x);
    cpu->pc++;
    cpu->address_absolute &= 0x00FF;
    return 0;
}

Byte ZPY(Cpu6502 *cpu){
    cpu->address_absolute = cpu->read_ram(cpu->bus, cpu->pc + cpu->y);
    cpu->pc++;
    cpu->address_absolute &= 0x00FF;
    return 0;
}

Byte REL(Cpu6502 *cpu){
    cpu->address_relative = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    if(cpu->address_relative & 0x80) cpu->address_relative |= 0xFF00;
    return 0;
}

Byte ABS(Cpu6502 *cpu){
    Word lo = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    Word hi = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    cpu->address_absolute = (hi << 8) | lo;
    return 0;
}

Byte ABX(Cpu6502 *cpu){
    Word lo = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    Word hi = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;

    cpu->address_absolute = (hi << 8) | lo;
    cpu->address_absolute += cpu->x;

    if((cpu->address_absolute & 0xFF00) != (hi << 8)) return 1;
    return 0;
}

Byte ABY(Cpu6502 *cpu){
    Word lo = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    Word hi = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;

    cpu->address_absolute = (hi << 8) | lo;
    cpu->address_absolute += cpu->y;

    if((cpu->address_absolute & 0xFF00) != (hi << 8)) return 1;
    return 0;
}

Byte IND(Cpu6502 *cpu){
    Word ptr_lo = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;
    Word ptr_hi = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;

    Word ptr = (ptr_hi << 8) | ptr_lo;
        
    if (ptr_lo == 0x00FF) 
        cpu->address_absolute = (
            cpu->read_ram(cpu->bus, ptr & 0xFF00) << 8 | cpu->read_ram(cpu->bus, ptr + 0)
        );
    else 
        cpu->address_absolute = (
            cpu->read_ram(cpu->bus, ptr + 1) << 8 | cpu->read_ram(cpu->bus, ptr + 0)
        );
    return 0;
}

Byte IZX(Cpu6502 *cpu){
    Word t = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;

    Word lo = cpu->read_ram(cpu->bus, (Word)(t + (Word)cpu->x) & 0x00FF);
    Word hi = cpu->read_ram(cpu->bus, (Word)(t + (Word)cpu->x + 1) & 0x00FF);

    cpu->address_absolute = (hi << 8) | lo;

    return 0;
}

Byte IZY(Cpu6502 *cpu){
    Word t = cpu->read_ram(cpu->bus, cpu->pc);
    cpu->pc++;

    Word lo = cpu->read_ram(cpu->bus, t & 0x00FF);
    Word hi = cpu->read_ram(cpu->bus, (Word)(t + 1) & 0x00FF);

    cpu->address_absolute = (hi << 8) | lo;
    cpu->address_absolute += cpu->y;

    if((cpu->address_absolute & 0xFF00) != (hi << 0)) return 1;
    return 0;
}

// ============================================================================
// Operation Code
Byte ADC(Cpu6502 *cpu){
    fetch(cpu);

    cpu->temp = (Word)cpu->a + (Word)cpu->fetched + cpu->c;
    set_flag(cpu, C, cpu->temp > 0xFF);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, V, (
                ~((Word)cpu->a ^ (Word)cpu->fetched) & 
                ((Word)cpu->a ^ (Word)cpu->temp)
            ) & 0x0080);
    set_flag(cpu, N, cpu->temp & 0x80);
    cpu->a = cpu->temp & 0x00FF;

    return 1;
}

Byte SBC(Cpu6502 *cpu){
    fetch(cpu);

    Word value = (Word) cpu->fetched ^ 0x00FF; 
    cpu->temp = (Word)cpu->a + value + (Word)cpu->c;
    set_flag(cpu, C, cpu->temp & 0xFF00);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, V, (cpu->temp ^ (Word)cpu->a) 
            & (cpu->temp ^ value) 
            & 0x0080);
    set_flag(cpu, N, cpu->temp & 0x80);
    cpu->a = cpu->temp & 0x00FF;
    return 1;
}

Byte AND(Cpu6502 *cpu){
    fetch(cpu);
    cpu->a &= cpu->fetched;
    set_flag(cpu, Z, cpu->a == 0);
    set_flag(cpu, N, cpu->a & 0x80);
    return 1;
}

Byte ASL(Cpu6502 *cpu){
    fetch(cpu);

    cpu->temp = (Word)cpu->fetched << 1;
    set_flag(cpu, C, cpu->temp & 0xFF00);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    if(cpu->lookup[cpu->opcode].addrmode == &IMP) 
        cpu->a = cpu->temp & 0x00FF;
    else cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->temp & 0x00FF);
    return 0;
}

Byte BCC(Cpu6502 *cpu){
    if(cpu-> c == 0) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BCS(Cpu6502 *cpu){
    if(cpu-> z == 1) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BEQ(Cpu6502 *cpu){
    if(cpu-> c == 1) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BIT(Cpu6502 *cpu){
    fetch(cpu);
    cpu->temp = cpu->a & cpu->fetched;
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->fetched & (1 << 7));
    set_flag(cpu, V, cpu->fetched & (1 << 6));
    return 0;
}

Byte BMI(Cpu6502 *cpu){
    if(cpu->n == 1) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BNE(Cpu6502 *cpu){
    if(cpu-> z == 0) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BPL(Cpu6502 *cpu){
    if(cpu->n == 0) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BRK(Cpu6502 *cpu){
    cpu->pc++;

    set_flag(cpu, I, 1);
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, (cpu->pc >> 8) & 0x00FF);
    cpu->sp--;
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->pc & 0x00FF);
    cpu->sp--;

    set_flag(cpu, B, 1);
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->st);
    cpu->sp--;
    set_flag(cpu, B, 0);

    cpu->pc = (Word)cpu->read_ram(cpu->bus, 0xFFFE)
        | ((Word)cpu->read_ram(cpu->bus, 0xFFFF) << 8);
    return 0;
}

Byte BVC(Cpu6502 *cpu){
    if(cpu->v == 0) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte BVS(Cpu6502 *cpu){
    if(cpu->v == 1) {
        cpu->cycles++;
        cpu->address_absolute = cpu->pc + cpu->address_relative;
        if((cpu->address_absolute & 0xFF00) != (cpu->pc & 0xFF00)) cpu->cycles++;
        cpu->pc = cpu->address_absolute;
    }
    return 0;
}

Byte CLC(Cpu6502 *cpu){
    set_flag(cpu, C, 0);
    return 0;
}

Byte CLD(Cpu6502 *cpu){
    set_flag(cpu, D, 0);
    return 0;
}

Byte CLI(Cpu6502 *cpu){
    set_flag(cpu, I, 0);
    return 0;
}

Byte CLV(Cpu6502 *cpu){
    set_flag(cpu, V, 0);
    return 0;
}

Byte CMP(Cpu6502 *cpu){
    fetch(cpu);
    cpu->temp = (Word)cpu->a & (Word)cpu->fetched;
    set_flag(cpu, C, cpu->a >= cpu->fetched);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    return 1;
}

Byte CPX(Cpu6502 *cpu){
    fetch(cpu);
    cpu->temp = (Word)cpu->x & (Word)cpu->fetched;
    set_flag(cpu, C, cpu->x >= cpu->fetched);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    return 0;
}

Byte CPY(Cpu6502 *cpu){
    fetch(cpu);
    cpu->temp = (Word)cpu->y & (Word)cpu->fetched;
    set_flag(cpu, C, cpu->y >= cpu->fetched);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    return 0;
}

Byte DEC(Cpu6502 *cpu){
    fetch(cpu);
    cpu->temp = (Word)cpu->fetched - 1;
    cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->temp & 0x00FF);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    return 0;
}

Byte DEX(Cpu6502 *cpu){
    cpu->x--;
    set_flag(cpu, Z, cpu->x == 0x0000);
    set_flag(cpu, N, cpu->x & 0x80);
    return 0;
}

Byte DEY(Cpu6502 *cpu){
    cpu->y--;
    set_flag(cpu, Z, cpu->y == 0x0000);
    set_flag(cpu, N, cpu->y & 0x80);
    return 0;
}

Byte EOR(Cpu6502 *cpu){
    fetch(cpu);
    cpu->a = cpu->a ^ cpu->fetched;
    set_flag(cpu, Z, cpu->a == 0x0000);
    set_flag(cpu, N, cpu->a & 0x80);
    return 1;
}

Byte INC(Cpu6502 *cpu){
    fetch(cpu);
    cpu->temp = (Word)cpu->fetched + 1;
    cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->temp & 0x00FF);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    return 0;
}

Byte INX(Cpu6502 *cpu){
    cpu->x++;
    set_flag(cpu, Z, cpu->x == 0x0000);
    set_flag(cpu, N, cpu->x & 0x80);
    return 0;
}

Byte INY(Cpu6502 *cpu){
    cpu->y++;
    set_flag(cpu, Z, cpu->y == 0x0000);
    set_flag(cpu, N, cpu->y & 0x80);
    return 0;
}

Byte JMP(Cpu6502 *cpu){
    cpu->pc = cpu->address_absolute;
    return 0;
}

Byte JSR(Cpu6502 *cpu){
    cpu->pc--;

    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, (cpu->pc >> 8) & 0x00FF);
    cpu->sp--;
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->pc & 0x00FF);
    cpu->sp--;

    cpu->pc = cpu->address_absolute;
    return 0;
}

Byte LDA(Cpu6502 *cpu){
    fetch(cpu);
    cpu->a = cpu->fetched;
    set_flag(cpu, Z, cpu->a  == 0x0000);
    set_flag(cpu, N, cpu->a & 0x80);
    return 1;
}

Byte LDX(Cpu6502 *cpu){
    fetch(cpu);
    cpu->x = cpu->fetched;
    set_flag(cpu, Z, cpu->x  == 0x0000);
    set_flag(cpu, N, cpu->x & 0x80);
    return 1;
}

Byte LDY(Cpu6502 *cpu){
    fetch(cpu);
    cpu->y = cpu->fetched;
    set_flag(cpu, Z, cpu->y  == 0x0000);
    set_flag(cpu, N, cpu->y & 0x80);
    return 1;
}

Byte LSR(Cpu6502 *cpu){
    fetch(cpu);

    set_flag(cpu, C, cpu->fetched & 0x0001);

    cpu->temp = (Word)cpu->fetched >> 1;
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    if(cpu->lookup[cpu->opcode].addrmode == &IMP) 
        cpu->a = cpu->temp & 0x00FF;
    else cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->temp & 0x00FF);
    return 0;
}

Byte NOP(Cpu6502 *cpu){
    switch (cpu->opcode) {
        case 0x1C:
        case 0x3C:
        case 0x5C:
        case 0x7C:
        case 0xDC:
        case 0xFC:
            return 1;
            break;
    }
    return 0;
}

Byte ORA(Cpu6502 *cpu){
    fetch(cpu);
    cpu->a = cpu->a | cpu->fetched;
    set_flag(cpu, Z, cpu->a == 0x0000);
    set_flag(cpu, N, cpu->a & 0x80);
    return 1;
}

Byte PHA(Cpu6502 *cpu){
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->a);
    cpu->sp--;
    return 0;
}

Byte PHP(Cpu6502 *cpu){
    cpu->write_ram(cpu->bus, 0x0100 + cpu->sp, cpu->st | B | U);
    set_flag(cpu, B, 0);
    set_flag(cpu, U, 0);
    cpu->sp--;
    return 0;
}

Byte PLA(Cpu6502 *cpu){
    cpu->sp++;
    cpu->a = cpu->read_ram(cpu->bus, 0x0100 + cpu->sp);
    set_flag(cpu, Z, cpu->a == 0x0000);
    set_flag(cpu, N, cpu->a & 0x80);
    return 0;
}

Byte PLP(Cpu6502 *cpu){
    cpu->sp++;
    cpu->st = cpu->read_ram(cpu->bus, 0x0100 + cpu->sp);
    set_flag(cpu, U, 1);
    return 0;
}

Byte ROL(Cpu6502 *cpu){
    fetch(cpu);

    cpu->temp = ((Word)cpu->fetched << 1) | cpu->c;
    set_flag(cpu, C, cpu->temp & 0xFF00);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    if(cpu->lookup[cpu->opcode].addrmode == &IMP) 
        cpu->a = cpu->temp & 0x00FF;
    else cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->temp & 0x00FF);
    return 0;
}

Byte ROR(Cpu6502 *cpu){
    fetch(cpu);

    cpu->temp = ((Word)cpu->c << 1) | (cpu->fetched >> 1);
    set_flag(cpu, C, cpu->fetched & 0x01);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, N, cpu->temp & 0x80);
    if(cpu->lookup[cpu->opcode].addrmode == &IMP) 
        cpu->a = cpu->temp & 0x00FF;
    else cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->temp & 0x00FF);
    return 0;
}

Byte RTI(Cpu6502 *cpu){
    cpu->sp++;
    cpu->st = cpu->read_ram(cpu->bus, 0x0100 + cpu->sp);
    set_flag(cpu, U, 0);
    set_flag(cpu, B, 0);

    cpu->sp++;
    cpu->pc = (Word)cpu->read_ram(cpu->bus, 0x0100 + cpu->sp);
    cpu->sp++;
    cpu->pc |= (Word)cpu->read_ram(cpu->bus, 0x0100 + cpu->sp) << 8;

    return 0;
}

Byte RTS(Cpu6502 *cpu){
    cpu->sp++;
    cpu->pc = (Word)cpu->read_ram(cpu->bus, 0x0100 + cpu->sp);
    cpu->sp++;
    cpu->pc |= (Word)cpu->read_ram(cpu->bus, 0x0100 + cpu->sp) << 8;

    cpu->pc++;
    return 0;
}

Byte SEC(Cpu6502 *cpu){
    set_flag(cpu, C, 1);
    return 0;
}

Byte SED(Cpu6502 *cpu){
    set_flag(cpu, D, 1);
    return 0;
}

Byte SEI(Cpu6502 *cpu){
    set_flag(cpu, I, 1);
    return 0;
}

Byte STA(Cpu6502 *cpu){
    cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->a);
    return 0;
}

Byte STX(Cpu6502 *cpu){
    cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->x);
    return 0;
}

Byte STY(Cpu6502 *cpu){
    cpu->write_ram(cpu->bus, cpu->address_absolute, cpu->y);
    return 0;
}

Byte TAX(Cpu6502 *cpu){
    cpu->x = cpu->a;
    set_flag(cpu, Z, cpu->x  == 0x0000);
    set_flag(cpu, N, cpu->x & 0x80);
    return 0;
}

Byte TAY(Cpu6502 *cpu){
    cpu->y = cpu->a;
    set_flag(cpu, Z, cpu->y  == 0x0000);
    set_flag(cpu, N, cpu->y & 0x80);
    return 0;
}

Byte TSX(Cpu6502 *cpu){
    cpu->x = cpu->sp;
    set_flag(cpu, Z, cpu->x  == 0x0000);
    set_flag(cpu, N, cpu->x & 0x80);
    return 0;
}

Byte TXA(Cpu6502 *cpu){
    cpu->a = cpu->x;
    set_flag(cpu, Z, cpu->a == 0x0000);
    set_flag(cpu, N, cpu->a & 0x80);
    return 0;
}

Byte TXS(Cpu6502 *cpu){
    cpu->sp = cpu->x;
    return 0;
}

Byte TYA(Cpu6502 *cpu){
    cpu->a = cpu->y;
    set_flag(cpu, Z, cpu->a == 0x0000);
    set_flag(cpu, N, cpu->a & 0x80);
    return 0;
}

Byte XXX(Cpu6502 *cpu){
    return 0;
}
