#ifndef HAL_CONSOLE_H
#define HAL_CONSOLE_H
#include "../../include/type.h"

#define VGA_RAM_SADR 0xB8000                        // Graphics card memory starting address
#define VGA_WIDTH 80                                // screen text columns
#define VGA_HEIGHT 25                               // screen text rows
#define VGA_RAM_SZ VGA_WIDTH * VGA_HEIGHT * 2       // Graphics card memory size
#define VGA_RAM_EADR (VGA_RAM_SADR + VGA_RAM_SZ)    // Graphics card memory end address
#define ROW_SIZE (VGA_WIDTH * 2)                    // bytes per line
#define SCR_SIZE (ROW_SIZE * VGA_HEIGHT)

void clear_console();
void init_console();
void write_console(const char * buff);

#endif