#include "../include/cpu6502.h"
#include <stdint.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>

cpu6502_t* create_cpu(){
    cpu6502_t *cpu = (cpu6502_t *) malloc(sizeof(cpu6502_t));
    cpu->a = 0x00;
    cpu->x = 0x00;
    cpu->y = 0x00;
    cpu->stack_pointer = 0x00;
    cpu->status = 0x00;
    cpu->fetched = 0x00;
    cpu->opcode = 0x00;
    cpu->program_counter = 0x0000;
    cpu->address_absolute = 0x0000;
    cpu->address_relative = 0x0000;
    cpu->temp = 0x0000;
    cpu->cycles = 0;

    instruction_t instructions[] = {
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

    cpu->lookup = (instruction_t *) malloc(sizeof(instruction_t)*256);
    for(int i = 0; i < 256; i++) cpu->lookup[i] = instructions[i];

    return cpu;
}

void destroy_cpu(cpu6502_t *cpu){
    free(cpu->lookup);
    free(cpu);
}

void connect_bus(cpu6502_t *cpu, bus_t *bus){
    cpu->bus = bus;
}

void clock(cpu6502_t *cpu){
    if(cpu->cycles == 0){
        cpu->opcode = cpu->read(cpu, cpu->program_counter);
        cpu->program_counter++;
        cpu->cycles = cpu->lookup[0].cycles;
        (cpu->lookup->addrmode)(cpu);
        (cpu->lookup->operate)(cpu);
    }
    cpu->cycles--;
}
    
void set_flag(cpu6502_t *cpu, FLAGS6502 flag, int v){
    if(v) cpu->status |= flag;
    else cpu->status &= ~flag;
}

uint8_t get_flag(cpu6502_t *cpu, FLAGS6502 flag){
    return ((cpu->status &= flag) > 0) ? 1 : 0;
}

uint8_t fetch(cpu6502_t *cpu){
    if(!(cpu->lookup[cpu->opcode].addrmode == &IMP))
        cpu->fetched = cpu->read(cpu, cpu->address_absolute);
    return cpu->fetched;
}

// Addressing Modes
uint8_t IMP(cpu6502_t *cpu){
    cpu->fetched = cpu->a;
    return 0;
}

uint8_t IMM(cpu6502_t *cpu){
    cpu->address_absolute = cpu->program_counter++;
    return 0;
}

uint8_t ZP0(cpu6502_t *cpu){
    cpu->address_absolute = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    cpu->address_absolute &= 0x00FF;
    return 0;
}

uint8_t ZPX(cpu6502_t *cpu){
    cpu->address_absolute = cpu->read(cpu, cpu->program_counter + cpu->x);
    cpu->program_counter++;
    cpu->address_absolute &= 0x00FF;
    return 0;
}

uint8_t ZPY(cpu6502_t *cpu){
    cpu->address_absolute = cpu->read(cpu, cpu->program_counter + cpu->y);
    cpu->program_counter++;
    cpu->address_absolute &= 0x00FF;
    return 0;
}

uint8_t REL(cpu6502_t *cpu){
    cpu->address_relative = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    if(cpu->address_relative & 0x80) cpu->address_relative &= 0xFF00;
    return 0;
}

uint8_t ABS(cpu6502_t *cpu){
    uint16_t lo = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    uint16_t hi = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    cpu->address_absolute = (hi << 8) | lo;
    return 0;
}

uint8_t ABX(cpu6502_t *cpu){
    uint16_t lo = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    uint16_t hi = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;

    cpu->address_absolute = (hi << 8) | lo;
    cpu->address_absolute += cpu->x;

    if((cpu->address_absolute & 0xFF00) != (hi << 0)) return 1;
    return 0;
}

uint8_t ABY(cpu6502_t *cpu){
    uint16_t lo = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    uint16_t hi = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;

    cpu->address_absolute = (hi << 8) | lo;
    cpu->address_absolute += cpu->y;

    if((cpu->address_absolute & 0xFF00) != (hi << 0)) return 1;
    return 0;
}

uint8_t IND(cpu6502_t *cpu){
    uint16_t ptr_lo = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;
    uint16_t ptr_hi = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;

    uint16_t ptr = (ptr_hi << 8) | ptr_lo;
        
    if (ptr_lo == 0x00FF) 
        cpu->address_absolute = (
            cpu->read(cpu, ptr & 0xFF00) << 8 | cpu->read(cpu, ptr + 0)
        );
    else 
        cpu->address_absolute = (
            cpu->read(cpu, ptr + 1) << 8 | cpu->read(cpu, ptr + 0)
        );
    return 0;
}

uint8_t IZX(cpu6502_t *cpu){
    uint16_t t = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;

    uint16_t lo = cpu->read(cpu, (uint16_t)(t + (uint16_t)cpu->x) & 0x00FF);
    uint16_t hi = cpu->read(cpu, (uint16_t)(t + (uint16_t)cpu->x + 1) & 0x00FF);

    cpu->address_absolute = (hi << 8) | lo;

    return 0;
}

uint8_t IZY(cpu6502_t *cpu){
    uint16_t t = cpu->read(cpu, cpu->program_counter);
    cpu->program_counter++;

    uint16_t lo = cpu->read(cpu, t & 0x00FF);
    uint16_t hi = cpu->read(cpu, (uint16_t)(t + 1) & 0x00FF);

    cpu->address_absolute = (hi << 8) | lo;
    cpu->address_absolute += cpu->y;

    if((cpu->address_absolute & 0xFF00) != (hi << 0)) return 1;
    return 0;
}

// ============================================================================
// Operation Code
uint8_t ADC(cpu6502_t *cpu){
    fetch(cpu);

    cpu->temp = (uint16_t)cpu->a + (uint16_t)cpu->fetched + get_flag(cpu, C);
    set_flag(cpu, C, cpu->temp > 0xFF);
    set_flag(cpu, Z, (cpu->temp & 0x00FF) == 0x0000);
    set_flag(cpu, V, (
                ~((uint16_t)cpu->a ^ (uint16_t)cpu->fetched) & 
                ((uint16_t)cpu->a ^ (uint16_t)cpu->temp)
            ) & 0x0080);
    set_flag(cpu, N, cpu->temp & 0x80);


    return 1;
}

uint8_t SBC(cpu6502_t *cpu){
    fetch(cpu);

    return 0;
}

uint8_t AND(cpu6502_t *cpu){
    return 0;
}

uint8_t ASL(cpu6502_t *cpu){
    return 0;
}

uint8_t BCC(cpu6502_t *cpu){
    return 0;
}

uint8_t BCS(cpu6502_t *cpu){
    return 0;
}

uint8_t BEQ(cpu6502_t *cpu){
    return 0;
}

uint8_t BIT(cpu6502_t *cpu){
    return 0;
}

uint8_t BMI(cpu6502_t *cpu){
    return 0;
}

uint8_t BNE(cpu6502_t *cpu){
    return 0;
}

uint8_t BPL(cpu6502_t *cpu){
    return 0;
}

uint8_t BRK(cpu6502_t *cpu){
    return 0;
}

uint8_t BVC(cpu6502_t *cpu){
    return 0;
}

uint8_t BVS(cpu6502_t *cpu){
    return 0;
}

uint8_t CLC(cpu6502_t *cpu){
    return 0;
}

uint8_t CLD(cpu6502_t *cpu){
    return 0;
}

uint8_t CLI(cpu6502_t *cpu){
    return 0;
}

uint8_t CLV(cpu6502_t *cpu){
    return 0;
}

uint8_t CMP(cpu6502_t *cpu){
    return 0;
}

uint8_t CPX(cpu6502_t *cpu){
    return 0;
}

uint8_t CPY(cpu6502_t *cpu){
    return 0;
}

uint8_t DEC(cpu6502_t *cpu){
    return 0;
}

uint8_t DEX(cpu6502_t *cpu){
    return 0;
}

uint8_t DEY(cpu6502_t *cpu){
    return 0;
}

uint8_t EOR(cpu6502_t *cpu){
    return 0;
}

uint8_t INC(cpu6502_t *cpu){
    return 0;
}

uint8_t INX(cpu6502_t *cpu){
    return 0;
}

uint8_t INY(cpu6502_t *cpu){
    return 0;
}

uint8_t JMP(cpu6502_t *cpu){
    return 0;
}

uint8_t JSR(cpu6502_t *cpu){
    return 0;
}

uint8_t LDA(cpu6502_t *cpu){
    return 0;
}

uint8_t LDX(cpu6502_t *cpu){
    return 0;
}

uint8_t LDY(cpu6502_t *cpu){
    return 0;
}

uint8_t LSR(cpu6502_t *cpu){
    return 0;
}

uint8_t NOP(cpu6502_t *cpu){
    return 0;
}

uint8_t ORA(cpu6502_t *cpu){
    return 0;
}

uint8_t PHA(cpu6502_t *cpu){
    return 0;
}

uint8_t PHP(cpu6502_t *cpu){
    return 0;
}

uint8_t PLA(cpu6502_t *cpu){
    return 0;
}

uint8_t PLP(cpu6502_t *cpu){
    return 0;
}

uint8_t ROL(cpu6502_t *cpu){
    return 0;
}

uint8_t ROR(cpu6502_t *cpu){
    return 0;
}

uint8_t RTI(cpu6502_t *cpu){
    return 0;
}

uint8_t RTS(cpu6502_t *cpu){
    return 0;
}

uint8_t SEC(cpu6502_t *cpu){
    return 0;
}

uint8_t SED(cpu6502_t *cpu){
    return 0;
}

uint8_t SEI(cpu6502_t *cpu){
    return 0;
}

uint8_t STA(cpu6502_t *cpu){
    return 0;
}

uint8_t STX(cpu6502_t *cpu){
    return 0;
}

uint8_t STY(cpu6502_t *cpu){
    return 0;
}

uint8_t TAX(cpu6502_t *cpu){
    return 0;
}

uint8_t TAY(cpu6502_t *cpu){
    return 0;
}

uint8_t TSX(cpu6502_t *cpu){
    return 0;
}

uint8_t TXA(cpu6502_t *cpu){
    return 0;
}

uint8_t TXS(cpu6502_t *cpu){
    return 0;
}

uint8_t TYA(cpu6502_t *cpu){
    return 0;
}

uint8_t XXX(cpu6502_t *cpu){
    return 0;
}

