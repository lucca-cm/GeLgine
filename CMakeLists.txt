cmake_minimum_required(VERSION 3.20)

project(app
    VERSION 1.0
    LANGUAGES C CXX
)

# ------------------------------------------------------------
# Language standards
# ------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


# ------------------------------------------------------------
# Compiler warnings
# ------------------------------------------------------------

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()


# ------------------------------------------------------------
# Source files
# ------------------------------------------------------------

file(GLOB_RECURSE SRC_CPP CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)

file(GLOB_RECURSE SRC_C CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)


# ------------------------------------------------------------
# Executable
# ------------------------------------------------------------

add_executable(app
    ${SRC_CPP}
    ${SRC_C}
)

target_include_directories(app PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# ------------------------------------------------------------
# GLM
# ------------------------------------------------------------

set(GLM_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/../CPP_Libraries/GLM"
)

if(NOT EXISTS "${GLM_ROOT}/glm/glm.hpp")
    message(FATAL_ERROR
        "GLM headers not found at: ${GLM_ROOT}"
    )
endif()

target_include_directories(app PRIVATE
    "${GLM_ROOT}"
)


# ------------------------------------------------------------
# GLFW
# ------------------------------------------------------------

if(WIN32)

    set(GLFW_ROOT
        "${CMAKE_CURRENT_SOURCE_DIR}/../CPP_Libraries/GLFW"
    )

    set(GLFW_INCLUDE_DIR
        "${GLFW_ROOT}/include"
    )

    set(GLFW_LIBRARY
        "${GLFW_ROOT}/lib-mingw-w64/libglfw3.a"
    )

    if(NOT EXISTS "${GLFW_INCLUDE_DIR}/GLFW/glfw3.h")
        message(FATAL_ERROR
            "GLFW headers not found at: ${GLFW_INCLUDE_DIR}"
        )
    endif()

    if(NOT EXISTS "${GLFW_LIBRARY}")
        message(FATAL_ERROR
            "GLFW library not found at: ${GLFW_LIBRARY}"
        )
    endif()

    target_include_directories(app PRIVATE
        "${GLFW_INCLUDE_DIR}"
    )

else()

    find_package(glfw3 CONFIG REQUIRED)

endif()


# ------------------------------------------------------------
# OpenGL
# ------------------------------------------------------------

find_package(OpenGL REQUIRED)


# ------------------------------------------------------------
# Libraries
# ------------------------------------------------------------

if(WIN32)

    target_link_libraries(app PRIVATE
        "${GLFW_LIBRARY}"
        OpenGL::GL
    )

else()

    target_link_libraries(app PRIVATE
        glfw
        OpenGL::GL
    )

endif()