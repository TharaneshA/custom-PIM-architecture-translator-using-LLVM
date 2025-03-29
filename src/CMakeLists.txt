add_executable(pim_translator main.cpp ir_parser.h parallel_loop_analyzer.h pim_memory_mapper.h instruction_generator.h)
target_link_libraries(pim_translator ${llvm_libs})