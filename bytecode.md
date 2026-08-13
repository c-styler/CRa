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
