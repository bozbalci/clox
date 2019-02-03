#include <clox/vm.h>

#include <clox/common.h>
#include <clox/debug.h>

#include <stdio.h>

static void resetStack(VM *vm) {
    vm->stackTop = vm->stack;
}

void initVM(VM *vm) {
    resetStack(vm);
}

void freeVM(VM *vm) {

}

static InterpretResult run(VM *vm) {
#define READ_BYTE() (*vm->ip++)
#define READ_CONSTANT() (vm->chunk->constants.values[READ_BYTE()])
#define PUSH(value) (push(vm, value))
#define POP() (pop(vm))
#define BINARY_OP(op) \
    do { \
        double b = POP(); \
        double a = POP(); \
        PUSH(a op b); \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value *slot = vm->stack; slot < vm->stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm->chunk, (int) (vm->ip - vm->chunk->code));
#endif
        uint8_t instruction;

        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                PUSH(constant);
                printf("\n");
                break;
            }
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            case OP_NEGATE: {
                PUSH(-POP());
                break;
            }
            case OP_RETURN: {
                printValue(POP());
                printf("\n");
                return INTERPRET_OK;
            }
            default: {
                // TODO Unknown opcode
            }
        }
    }
#undef BINARY_OP
#undef POP
#undef PUSH
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(VM *vm, Chunk *chunk) {
    vm->chunk = chunk;
    vm->ip = vm->chunk->code;
    return run(vm);
}

void push(VM *vm, Value value) {
    *vm->stackTop = value;
    vm->stackTop++;
}

Value pop(VM *vm) {
    vm->stackTop--;
    return *vm->stackTop;
}