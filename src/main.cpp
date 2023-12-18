#include "ASMGenerator.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     SPDLOG_ERROR("You must set the input / output files path");
    //     exit(EXIT_FAILURE);
    // }

    Parser parser("../../../../examples/0.ash");
    ASMGenerator generator = ASMGenerator();

    generator.create_asm("../../../../out.asm", parser.parseFile());
    return EXIT_SUCCESS;
}
