#include <assert.h>

#include "chip8_stack.h"
#include "chip8.h"

/*
* Check if the stack pointer is in bounds.
*/
static void chipt8_stack_in_bounds(uint8_t stack_pointer_reg)
{
    assert( stack_pointer_reg < CHIP8_STACK_SIZE );
}

/*
* Push a value onto the stack.
* Increment the stack pointer.
*/
void chip8_stack_push(struct_chip8_stack_t* system_stack, uint8_t* stack_pointer_reg, uint16_t value)   // This function could have been used with less arguments if the forward declaration was used
{
    (*stack_pointer_reg)++;
    chipt8_stack_in_bounds(*stack_pointer_reg);
    system_stack->stack[*stack_pointer_reg] = value;
}

/*
* Pop a value from the stack.
* Decrement the stack pointer.
*/
uint16_t chip8_stack_pop(struct_chip8_stack_t* system_stack, uint8_t* stack_pointer_reg)
{
    chipt8_stack_in_bounds(*stack_pointer_reg);
    uint16_t value = system_stack->stack[*stack_pointer_reg];
    (*stack_pointer_reg)--;
    return value;
}