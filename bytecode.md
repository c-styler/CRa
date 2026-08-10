# Ra Bytecode Reference

This document defines the instruction set architecture (ISA) for the Ra Virtual Machine.

## Virtual Machine Architecture

* **Type**:
* **Instruction Size**: 1-byte opcode + 0 to N operand bytes
* **Endianness**: Big-Endian (for multi-byte operands)

---

## Instruction Set Table

| Opcode Name | Hex | Operands | Description |
| :--- | :--- | :--- | :---
| `OP_RETURN` | `0x00` | | |
| `OP_CONSTANT` | `0x01` | `index` (1 byte) | |

---

## Detailed Opcode Specifications

### 0x00: OP_RETURN
* **Operands**: None
* **Description**:

### 0x01: OP_CONSTANT
* **Operands**:
  * `index` (1 byte):
* **Description**:
