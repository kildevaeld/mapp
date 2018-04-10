
set(SOURCES
    application.cpp
    command.cpp
)


add_library(mapp ${SOURCES})
target_link_libraries(mapp ${LIBUV_LIBRARIES})
target_include_directories(mapp 
    PUBLIC ${PROJECT_SOURCE_DIR}/vendor/args
)
