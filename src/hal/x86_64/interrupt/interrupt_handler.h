#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "halidt.h"
void isr_0();
void default_handler(uint64_t code);

#endif