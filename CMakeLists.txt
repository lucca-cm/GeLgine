cmake_minimum_required(VERSION 3.20)

project(app
    VERSION 1.0
    LANGUAGES C CXX
)

# ============================================================
# Language standards
# ============================================================

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ============================================================
# Source files
# ============================================================

file(GLOB_RECURSE SRC_CPP CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)

file(GLOB_RECURSE SRC_C CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)


# ============================================================
# Executable
# ============================================================

add_executable(app
    ${SRC_CPP}
    ${SRC_C}
)

target_include_directories(app PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# ============================================================
# Compiler warnings
# ============================================================

if(MSVC)

    target_compile_options(app PRIVATE
        /W4
    )

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(app PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# ============================================================
# Dependencies
#
# Windows:
#   Use locally installed libraries:
#       ../CPP_Libraries/
#
# macOS/Linux:
#   Use globally installed libraries.
# ============================================================

if(WIN32)

    message(STATUS "Platform: Windows")
    message(STATUS "Using local libraries from CPP_Libraries")


    # --------------------------------------------------------
    # GLM - Windows local
    # --------------------------------------------------------

    set(GLM_ROOT
        "${CMAKE_CURRENT_SOURCE_DIR}/../CPP_Libraries/GLM"
    )

    if(NOT EXISTS "${GLM_ROOT}/glm/glm.hpp")
        message(FATAL_ERROR
            "GLM headers not found at:\n"
            "  ${GLM_ROOT}"
        )
    endif()

    target_include_directories(app PRIVATE
        "${GLM_ROOT}"
    )


    # --------------------------------------------------------
    # GLFW - Windows local
    # --------------------------------------------------------

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
            "GLFW headers not found at:\n"
            "  ${GLFW_INCLUDE_DIR}"
        )
    endif()

    if(NOT EXISTS "${GLFW_LIBRARY}")
        message(FATAL_ERROR
            "GLFW library not found at:\n"
            "  ${GLFW_LIBRARY}"
        )
    endif()

    target_include_directories(app PRIVATE
        "${GLFW_INCLUDE_DIR}"
    )

    target_link_libraries(app PRIVATE
        "${GLFW_LIBRARY}"
    )


    # --------------------------------------------------------
    # OpenGL - Windows
    # --------------------------------------------------------

    find_package(OpenGL REQUIRED)

    target_link_libraries(app PRIVATE
        OpenGL::GL
    )


elseif(APPLE)

    message(STATUS "Platform: macOS")
    message(STATUS "Using globally installed libraries")


    # --------------------------------------------------------
    # GLM - macOS global
    # --------------------------------------------------------

    find_path(GLM_INCLUDE_DIR
        NAMES glm/glm.hpp
        REQUIRED
    )

    target_include_directories(app PRIVATE
        "${GLM_INCLUDE_DIR}"
    )


    # --------------------------------------------------------
    # GLFW - macOS global
    # --------------------------------------------------------

    find_package(glfw3 CONFIG REQUIRED)

    target_link_libraries(app PRIVATE
        glfw
    )


    # --------------------------------------------------------
    # OpenGL - macOS
    # --------------------------------------------------------

    find_package(OpenGL REQUIRED)

    target_link_libraries(app PRIVATE
        OpenGL::GL
    )

    # GLFW requires these macOS frameworks.
    target_link_libraries(app PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )


elseif(UNIX)

    message(STATUS "Platform: Linux")
    message(STATUS "Using globally installed libraries")


    # --------------------------------------------------------
    # GLM - Linux global
    # --------------------------------------------------------

    find_path(GLM_INCLUDE_DIR
        NAMES glm/glm.hpp
        REQUIRED
    )

    target_include_directories(app PRIVATE
        "${GLM_INCLUDE_DIR}"
    )


    # --------------------------------------------------------
    # GLFW - Linux global
    # --------------------------------------------------------

    find_package(glfw3 CONFIG REQUIRED)

    target_link_libraries(app PRIVATE
        glfw
    )


    # --------------------------------------------------------
    # OpenGL - Linux
    # --------------------------------------------------------

    find_package(OpenGL REQUIRED)

    target_link_libraries(app PRIVATE
        OpenGL::GL
    )


else()

    message(FATAL_ERROR
        "Unsupported operating system: ${CMAKE_SYSTEM_NAME}"
    )

endif()



target_compile_options(app PRIVATE
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_link_options(app PRIVATE
    -fsanitize=address
)
# ============================================================
# Build information
# ============================================================

message(STATUS "")
message(STATUS "========================================")
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")
message(STATUS "========================================")
message(STATUS "OS:       ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++:      ${CMAKE_CXX_STANDARD}")
message(STATUS "========================================")
message(STATUS "")