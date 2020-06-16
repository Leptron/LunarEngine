project(LunarEngine)

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/source/*.c
        ${PROJECT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADER_FILES
        ${PROJECT_SOURCE_DIR}/public/*.h
        ${PROJECT_SOURCE_DIR}/public/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/Lib/include 
                    ${CMAKE_SOURCE_DIR}/glfw/include)

add_library(LunarEngine STATIC ${SOURCE_FILES} "public/LunarShaderGen.h" "source/LunarUtils/LunarShaderGen.cpp" "public/LunarShaderManager.h" "source/LunarUtils/LunarShaderManager.cpp" "public/LunarPrimitives/SpriteRenderer.h"  "source/LunarRenderer/LunarPrimitives/SpriteRenderer.cpp" "public/LunarPrimitives/SpriteManager.h" "source/LunarRenderer/LunarPrimitives/SpriteManager.cpp" "public/LunarPrimitives/LunarTexture.h" "source/LunarRenderer/LunarPrimitives/LunarTexture.cpp" "source/LunarUtils/LunarUtils.cpp")
if(WIN32)
target_link_libraries(${PROJECT_NAME} glfw -mwindows)
else(UNIX)
target_link_libraries(${PROJECT_NAME} glfw )
endif()