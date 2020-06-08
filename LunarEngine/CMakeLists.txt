project(LunarEngine)

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/source/*.c
        ${PROJECT_SOURCE_DIR}/source/*.cpp
        ${CMAKE_SOURCE_DIR}/external/imgui/*.cpp)
file(GLOB_RECURSE HEADER_FILES
        ${PROJECT_SOURCE_DIR}/public/*.h
        ${PROJECT_SOURCE_DIR}/public/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/Lib/include 
                    ${CMAKE_SOURCE_DIR}/glfw/include
                    ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(LunarEngine STATIC ${SOURCE_FILES} "source/LunarIMGUI/LunarIMGUIInit.cpp")
if(WIN32)
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARY} ${ASSIMP_LIBRARIES} ${WINLIBS} glfw)
else(UNIX)
target_link_libraries(${PROJECT_NAME} glfw )
endif()