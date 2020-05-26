project (Sandbox)

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/source/*.c
        ${PROJECT_SOURCE_DIR}/source/*.cpp
        )
file(GLOB_RECURSE HEADER_FILES
        ${PROJECT_SOURCE_DIR}/public/*.h
        ${PROJECT_SOURCE_DIR}/public/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/Lib/include
	${CMAKE_SOURCE_DIR}/LunarEngine/public
        ${CMAKE_SOURCE_DIR}/glfw/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/bin)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} VkLayer_utils vulkan pthread LunarEngine)
