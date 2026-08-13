# Ra Bytecode Reference

This document defines the instruction set architecture (ISA) for the Ra Virtual Machine.

## Virtual Machine Architecture

* **Type**: Stack-Based
* **Instruction Size**: 1-byte opcode + 0 to N operand bytes
* **Endianness**: Big-Endian (for multi-byte operands)

---

## Instruction Set Table

| Opcode Name | Hex | Operands | Description |
| :--- | :--- | :--- | :---
| `OP_RETURN` | `0x00` | | |
| `OP_CONSTANT` | `0x01` | `index` (1 byte) | Pushes the index of the constant onto the stack |
| `OP_NEGATE` | `0x02` | | Pops the top stack value and pushes its negative onto the stack |
| `OP_ADD` | `0x03` | | Pops the 2 topmost stack values and pushes their sum onto the stack |
| `OP_SUBTRACT` | `0x04` | | Pops the 2 topmost stack values where b is topmost and a is second topmost, and pushes their difference (a - b) onto the stack |
| `OP_MULTIPLY` | `0x05` | | Pops the 2 topmost stack values and pushes their product onto the stack |
| `OP_DIVIDE` | `0x06` | | Pops the 2 topmost stack values where b is topmost and a is second topmost, and pushes their quotient (a / b) onto the stack |
