#ifndef CPU6502_H
#define CPU6502_H

#include <stdint.h>

// Complementary Types
typedef struct bus bus_t;
typedef struct cpu6502 cpu6502_t;

typedef enum {
    C = (1 << 0), // Carry bit
    Z = (1 << 1), // Zero
    I = (1 << 2), // Disable Interrupts
    D = (1 << 3), // Decimal Mode
    B = (1 << 4), // Break
    U = (1 << 5), // Unused
    V = (1 << 6), // Overflow
    N = (1 << 7), // Negative
} FLAGS6502;

typedef struct instruction {
    char name[3];
    uint8_t (*operate)(cpu6502_t *cpu);
    uint8_t (*addrmode)(cpu6502_t *cpu);
    uint8_t cycles;
} instruction_t;

typedef struct cpu6502{
    bus_t *bus;
    FLAGS6502 flags;

    // Registers
    uint8_t a; // Accumulator register
    uint8_t x; // X register
    uint8_t y; // Y register
    uint8_t stack_pointer; // Stack pointer
    uint16_t program_counter; // Program Counter
    uint8_t status; // Status register

    uint8_t fetched;
    uint16_t address_absolute;
    uint16_t address_relative;
    uint16_t temp;
    uint8_t opcode;
    uint8_t cycles;
    instruction_t *lookup;

    // Methods
    void (* write)(cpu6502_t* cpu, uint16_t address, uint8_t data);
    uint8_t (* read)(cpu6502_t* cpu, uint16_t address);

    
} cpu6502_t;

// CPU Administration
cpu6502_t* create_cpu();
void destroy_cpu(cpu6502_t *cpu);
void connect_bus(cpu6502_t *cpu, bus_t *bus);
uint8_t get_flag(cpu6502_t *cpu, FLAGS6502 flag);
void set_flag(cpu6502_t *cpu, FLAGS6502 flag, int v);


void clock(cpu6502_t *cpu);
uint8_t fetch(cpu6502_t *cpu);
void reset(cpu6502_t *cpu);
void irq(cpu6502_t *cpu); // Interrupt Request Signal
void nmi(cpu6502_t *cpu); // Non Maskable Interrupt Request Signal

// Addressing Modes
uint8_t IMP(cpu6502_t *cpu);	uint8_t IMM(cpu6502_t *cpu);	
uint8_t ZP0(cpu6502_t *cpu);	uint8_t ZPX(cpu6502_t *cpu);	
uint8_t ZPY(cpu6502_t *cpu);	uint8_t REL(cpu6502_t *cpu);
uint8_t ABS(cpu6502_t *cpu);	uint8_t ABX(cpu6502_t *cpu);	
uint8_t ABY(cpu6502_t *cpu);	uint8_t IND(cpu6502_t *cpu);	
uint8_t IZX(cpu6502_t *cpu);	uint8_t IZY(cpu6502_t *cpu);

// Operation Code
uint8_t ADC(cpu6502_t *cpu);	uint8_t AND(cpu6502_t *cpu);	uint8_t ASL(cpu6502_t *cpu);	uint8_t BCC(cpu6502_t *cpu);
uint8_t BCS(cpu6502_t *cpu);	uint8_t BEQ(cpu6502_t *cpu);	uint8_t BIT(cpu6502_t *cpu);	uint8_t BMI(cpu6502_t *cpu);
uint8_t BNE(cpu6502_t *cpu);	uint8_t BPL(cpu6502_t *cpu);	uint8_t BRK(cpu6502_t *cpu);	uint8_t BVC(cpu6502_t *cpu);
uint8_t BVS(cpu6502_t *cpu);	uint8_t CLC(cpu6502_t *cpu);	uint8_t CLD(cpu6502_t *cpu);	uint8_t CLI(cpu6502_t *cpu);
uint8_t CLV(cpu6502_t *cpu);	uint8_t CMP(cpu6502_t *cpu);	uint8_t CPX(cpu6502_t *cpu);	uint8_t CPY(cpu6502_t *cpu);
uint8_t DEC(cpu6502_t *cpu);	uint8_t DEX(cpu6502_t *cpu);	uint8_t DEY(cpu6502_t *cpu);	uint8_t EOR(cpu6502_t *cpu);
uint8_t INC(cpu6502_t *cpu);	uint8_t INX(cpu6502_t *cpu);	uint8_t INY(cpu6502_t *cpu);	uint8_t JMP(cpu6502_t *cpu);
uint8_t JSR(cpu6502_t *cpu);	uint8_t LDA(cpu6502_t *cpu);	uint8_t LDX(cpu6502_t *cpu);	uint8_t LDY(cpu6502_t *cpu);
uint8_t LSR(cpu6502_t *cpu);	uint8_t NOP(cpu6502_t *cpu);	uint8_t ORA(cpu6502_t *cpu);	uint8_t PHA(cpu6502_t *cpu);
uint8_t PHP(cpu6502_t *cpu);	uint8_t PLA(cpu6502_t *cpu);	uint8_t PLP(cpu6502_t *cpu);	uint8_t ROL(cpu6502_t *cpu);
uint8_t ROR(cpu6502_t *cpu);	uint8_t RTI(cpu6502_t *cpu);	uint8_t RTS(cpu6502_t *cpu);	uint8_t SBC(cpu6502_t *cpu);
uint8_t SEC(cpu6502_t *cpu);	uint8_t SED(cpu6502_t *cpu);	uint8_t SEI(cpu6502_t *cpu);	uint8_t STA(cpu6502_t *cpu);
uint8_t STX(cpu6502_t *cpu);	uint8_t STY(cpu6502_t *cpu);	uint8_t TAX(cpu6502_t *cpu);	uint8_t TAY(cpu6502_t *cpu);
uint8_t TSX(cpu6502_t *cpu);	uint8_t TXA(cpu6502_t *cpu);	uint8_t TXS(cpu6502_t *cpu);	uint8_t TYA(cpu6502_t *cpu);

uint8_t XXX(cpu6502_t *cpu);

#endif//CPU6502_H
