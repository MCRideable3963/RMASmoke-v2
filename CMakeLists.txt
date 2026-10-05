cmake_minimum_required(VERSION 3.0.0)
project(RMASmoke-v2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# -------------------------------------------------------------------
# Define Imported Static Libraries
# -------------------------------------------------------------------

# tss2-sys
add_library(libtss2-sys STATIC IMPORTED)
set_target_properties(libtss2-sys PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libtss2-sys.a"    
)

# tss2-esys
add_library(libtss2-esys STATIC IMPORTED)
set_target_properties(libtss2-esys PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libtss2-esys.a"
)

# tss2-mu
add_library(libtss2-mu STATIC IMPORTED)
set_target_properties(libtss2-mu PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libtss2-mu.a"
)

# protobuf
add_library(libprotobufstatic STATIC IMPORTED)
set_target_properties(libprotobufstatic PROPERTIES 
    IMPORTED_LOCATION "/usr/lib/libprotobuf.a"
)


add_executable(rmasmoke 
    src/main.cpp 
    src/tnm_manager.cpp 
    src/nh.cpp
)

target_link_libraries(rmasmoke 
    PRIVATE 
    libtss2-sys 
    libtss2-esys 
    libtss2-mu 
    libprotobufstatic
)
