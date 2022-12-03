#include "interrupt_handler.h"
#include "../../../include/stdio.h"

void isr_0() {
    printk("Divide by zero!!!");
    while(1);
}

void default_handler(uint64_t code) {
    printk("Error code: %d", code);
    while (1);
}