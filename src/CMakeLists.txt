add_executable(pim_translator main.cpp ir_parser.cpp parallel_loop_analyzer.cpp pim_memory_mapper.cpp instruction_generator.cpp)
target_link_libraries(pim_translator ${llvm_libs})