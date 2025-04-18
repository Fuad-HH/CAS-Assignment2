################################## Catch2 ########################
find_package(Catch2 3 QUIET)
if(Catch2_FOUND)
    message(STATUS "Found Catch2: ${Catch2_DIR}")
else()
    message(STATUS "Catch2 not found. Fetching Catch2...")
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.4.0 # or a later release
    )
    FetchContent_MakeAvailable(Catch2)
endif()
###################################################################

##################### Catch2 Integration ##########################
include(CTest)
include(Catch)


########################### Tests ############################

# Unit tests
add_executable(unit_tests unit_tests.cpp ${CMAKE_SOURCE_DIR}/src/Mesh.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain Kokkos::kokkos)
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(unit_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


# Test assembly
add_executable(test_assembly test_assembly.cpp ${CMAKE_SOURCE_DIR}/src/Mesh.cpp ${CMAKE_SOURCE_DIR}/src/StiffnessMatrix.cpp)
target_link_libraries(test_assembly PRIVATE Catch2::Catch2WithMain Kokkos::kokkos)
target_include_directories(test_assembly PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(test_assembly WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


# Test Matrix Vector Multiplication
add_executable(test_matvecmult test_matvec_mult.cpp ${CMAKE_SOURCE_DIR}/src/MatVecMult.cpp)
target_link_libraries(test_matvecmult PRIVATE Catch2::Catch2WithMain Kokkos::kokkos)
target_include_directories(test_matvecmult PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(test_matvecmult WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


# Test Element Stiffness Matrix
add_executable(test_element_stiffness test_element_stiffness.cpp ${CMAKE_SOURCE_DIR}/src/CalculateStiffnessMatrixAndLoadVector.cpp ${CMAKE_SOURCE_DIR}/src/Mesh.cpp ${CMAKE_SOURCE_DIR}/src/StiffnessMatrix.cpp)
target_link_libraries(test_element_stiffness PRIVATE Catch2::Catch2WithMain Kokkos::kokkos)
target_include_directories(test_element_stiffness PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(test_element_stiffness WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Test Load Vector
add_executable(test_load_vector test_load_vector_assembly.cpp ${CMAKE_SOURCE_DIR}/src/Mesh.cpp ${CMAKE_SOURCE_DIR}/src/StiffnessMatrix.cpp ${CMAKE_SOURCE_DIR}/src/CalculateStiffnessMatrixAndLoadVector.cpp)
target_link_libraries(test_load_vector PRIVATE Catch2::Catch2WithMain Kokkos::kokkos)
target_include_directories(test_load_vector PRIVATE ${CMAKE_SOURCE_DIR}/src)
catch_discover_tests(test_load_vector WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
