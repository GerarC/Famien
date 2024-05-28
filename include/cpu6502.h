#ifndef CPU6502_H
#define CPU6502_H

#include "types.h"


/*
 * Enum that saves Symbol and value of cpu flags
 */
typedef enum {
    C = (1 << 0),
    Z = (1 << 1),
    I = (1 << 2),
    D = (1 << 3),
    B = (1 << 4),
    U = (1 << 5),
    V = (1 << 6),
    N = (1 << 7)
} Flags6502;

/*
 * Intruction represent an asm operation of the 6502 cpu, its address mode and
 * needed cycles to do the operation.
 *
 * This class is very useful to translate bits in the current asm intructions.
 *
 */
typedef struct {
    char name[3];
    uint8_t (*operate)(Cpu6502 *cpu);
    uint8_t (*addrmode)(Cpu6502 *cpu);
    uint8_t cycles;
} Instruction;

/*
 * This struct represents a 6502 
 */
typedef struct cpu6502_t{
    Bus* bus;
    Word pc; // Program counter
    Word sp; // Stack pointer
    Byte a;  // Accumulator Register
    Byte x;  // X register
    Byte y;  // Y Register
    union {
        Byte st; // Status Register
        struct {
            Byte c : 1; // Carry
            Byte z : 1; // Zero
            Byte i : 1; // Interrupt disable
            Byte d : 1; // Decimal
            Byte b : 1; // Break
            Byte u : 1; // Unused
            Byte v : 1; // Overflow
            Byte n : 1; // Negative
        };
    } ;

    Byte fetched;
    Word address_absolute;
    Word address_relative;
    Word temp;
    Byte opcode;
    Word cycles;
    Instruction lookup[256];
    
    /*Writes data in the Ram connected to the given bus*/
    void (* write_ram)(Bus* bus, Word address, Byte data);
    /*Reads data from Ram connected to the given bus*/
    Byte (* read_ram)(Bus* bus, Word address);

} Cpu6502;


/*
 * initialize the given CPU to default values
 *
 * Initial values are all zero and the lookup that is the data base of instructions
 *
 * input:
 *  cpu: the cpu to re init.
 */
void initialize_cpu(Cpu6502 *cpu);

void execute_cpu(Cpu6502 *cpu);

/*
 * Connect the CPU the given bus
 *
 * Input:
 *  cṕu: the required cpu
 *  bus: bus where the cpu will be connected.
 */
void connect_bus(Cpu6502 *cpu, Bus *bus);

/*
 * Connects the ram with the methods that allows to read and write data in
 * Ram connected in the Bus.
 *
 * Input:
 *  cpu: the cpu to connect.
 *  write_ram: a function that receives a bus, an address and data.
 *  read_ram: a function that receives a bus and an address to read data
 *
 */
void connect_bus_methods(Cpu6502 *cpu, 
    void (* write_ram)(Bus* bus, Word address, Byte data),
    Byte (* read_ram)(Bus* bus, Word address));

/*
 * Resets the given CPU to default values of the registers and directions and
 * loads the initial pc from ram.
 *
 * Cpu, read_ram and write_ram must be connected to the cpu
 *
 */
void reset_cpu(Cpu6502 *cpu);

/*
 * Reads the program counter and executes the instruction of the retrieved opcode
 *
 * input:
 *  cpu: the cpu that executes the instruction.
 * */
void clock(Cpu6502 *cpu);

/*
 * Fetches data that is in absolute address and return it
 *
 * input:
 *  cpu that needs that information
 * return:
 *  (Byte) fetched data.
 *
 */
Byte fetch(Cpu6502 *cpu);

/*
 * Sets a flag in the cpu if v is true, else sets a 0 in the flag status position
 *
 * Input:
 *  cpu: needed cpu
 *  flag: flag to set or unset
 *  v: int that lets to choose setting or unsetting.
 * */
void set_flag(Cpu6502 *cpu, Flags6502 flag, int v);
/*Interrupt Request*/
void irq(Cpu6502 *cpu);
/*Non Maskable Interrupt*/
void nmi(Cpu6502 *cpu);

/*
 * Parses a given cpu in a string to print.
 *
 * Input: 
 *  Cpu to parse
 *
 * output:
 *  (Char*) parsed cpu.
 *
 */
char* parse_cpu_str(Cpu6502 cpu);

// Addressing Modes
uint8_t IMP(Cpu6502 *cpu);	uint8_t IMM(Cpu6502 *cpu);	
uint8_t ZP0(Cpu6502 *cpu);	uint8_t ZPX(Cpu6502 *cpu);	
uint8_t ZPY(Cpu6502 *cpu);	uint8_t REL(Cpu6502 *cpu);
uint8_t ABS(Cpu6502 *cpu);	uint8_t ABX(Cpu6502 *cpu);	
uint8_t ABY(Cpu6502 *cpu);	uint8_t IND(Cpu6502 *cpu);	
uint8_t IZX(Cpu6502 *cpu);	uint8_t IZY(Cpu6502 *cpu);

// Operation Code
uint8_t ADC(Cpu6502 *cpu);	uint8_t AND(Cpu6502 *cpu);	uint8_t ASL(Cpu6502 *cpu);	uint8_t BCC(Cpu6502 *cpu);
uint8_t BCS(Cpu6502 *cpu);	uint8_t BEQ(Cpu6502 *cpu);	uint8_t BIT(Cpu6502 *cpu);	uint8_t BMI(Cpu6502 *cpu);
uint8_t BNE(Cpu6502 *cpu);	uint8_t BPL(Cpu6502 *cpu);	uint8_t BRK(Cpu6502 *cpu);	uint8_t BVC(Cpu6502 *cpu);
uint8_t BVS(Cpu6502 *cpu);	uint8_t CLC(Cpu6502 *cpu);	uint8_t CLD(Cpu6502 *cpu);	uint8_t CLI(Cpu6502 *cpu);
uint8_t CLV(Cpu6502 *cpu);	uint8_t CMP(Cpu6502 *cpu);	uint8_t CPX(Cpu6502 *cpu);	uint8_t CPY(Cpu6502 *cpu);
uint8_t DEC(Cpu6502 *cpu);	uint8_t DEX(Cpu6502 *cpu);	uint8_t DEY(Cpu6502 *cpu);	uint8_t EOR(Cpu6502 *cpu);
uint8_t INC(Cpu6502 *cpu);	uint8_t INX(Cpu6502 *cpu);	uint8_t INY(Cpu6502 *cpu);	uint8_t JMP(Cpu6502 *cpu);
uint8_t JSR(Cpu6502 *cpu);	uint8_t LDA(Cpu6502 *cpu);	uint8_t LDX(Cpu6502 *cpu);	uint8_t LDY(Cpu6502 *cpu);
uint8_t LSR(Cpu6502 *cpu);	uint8_t NOP(Cpu6502 *cpu);	uint8_t ORA(Cpu6502 *cpu);	uint8_t PHA(Cpu6502 *cpu);
uint8_t PHP(Cpu6502 *cpu);	uint8_t PLA(Cpu6502 *cpu);	uint8_t PLP(Cpu6502 *cpu);	uint8_t ROL(Cpu6502 *cpu);
uint8_t ROR(Cpu6502 *cpu);	uint8_t RTI(Cpu6502 *cpu);	uint8_t RTS(Cpu6502 *cpu);	uint8_t SBC(Cpu6502 *cpu);
uint8_t SEC(Cpu6502 *cpu);	uint8_t SED(Cpu6502 *cpu);	uint8_t SEI(Cpu6502 *cpu);	uint8_t STA(Cpu6502 *cpu);
uint8_t STX(Cpu6502 *cpu);	uint8_t STY(Cpu6502 *cpu);	uint8_t TAX(Cpu6502 *cpu);	uint8_t TAY(Cpu6502 *cpu);
uint8_t TSX(Cpu6502 *cpu);	uint8_t TXA(Cpu6502 *cpu);	uint8_t TXS(Cpu6502 *cpu);	uint8_t TYA(Cpu6502 *cpu);

uint8_t XXX(Cpu6502 *cpu);

#endif//CPU6502_H
