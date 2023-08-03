# Compiler options to enable Address
# and Leak sanitization checks
option(ENABLE_ASAN "Enable ASan" false)
option(ENABLE_LSAN "Enable LSan" false)
option(ENABLE_TSAN "Enable TSan" false)

# If options not specified, don't run
# the Address, Leak, and Thread checks.
if(${ENABLE_ASAN})
    # Enable address sanitizer (ASan) for the compiler
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    message("NOTE: Enabled Address Sanitization checks.")
endif()

if(${ENABLE_LSAN})
    # Enable memory leak sanitizer (LSan) for the compiler
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=leak")
    message("NOTE: Enabled Memory Leak Sanitization checks.")
endif()

if(${ENABLE_TSAN})
    # Enable thread sanitizer (TSan) for the compiler
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
    message("NOTE: Enabled Thread Sanitization checks.")
endif()