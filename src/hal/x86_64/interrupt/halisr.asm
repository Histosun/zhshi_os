extern default_handler
extern isr_0

%include "/halisr.inc"

global exc_divide_error
global exc_default

[SECTION .text]
[BITS 64]

ALIGN 16
exc_divide_error:
    ISR_FAULT isr_0

ALIGN 16
exc_default:
    ISR_DEFAULT 13

ALIGN 16
