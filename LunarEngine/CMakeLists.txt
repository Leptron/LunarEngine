project(LunarEngine)

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/source/*.c
        ${PROJECT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADER_FILES
        ${PROJECT_SOURCE_DIR}/public/*.h
        ${PROJECT_SOURCE_DIR}/public/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/Lib/include 
                    ${CMAKE_SOURCE_DIR}/glfw/include)

add_library(LunarEngine STATIC ${SOURCE_FILES})
if(WIN32)
target_link_libraries(${PROJECT_NAME} base ${Vulkan_LIBRARY} ${ASSIMP_LIBRARIES} ${WINLIBS})
else(UNIX)
target_link_libraries(${PROJECT_NAME} base )
endif()