#include <clox/chunk.h>
#include <clox/common.h>
#include <clox/debug.h>
#include <clox/vm.h>

int main(int argc, const char *argv[]) {
    VM vm;
    initVM(&vm);
    Chunk chunk;
    initChunk(&chunk);

    int constant;

    constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE, 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test chunk");
    interpret(&vm, &chunk);
    freeVM(&vm);
    freeChunk(&chunk);
    return 0;
}