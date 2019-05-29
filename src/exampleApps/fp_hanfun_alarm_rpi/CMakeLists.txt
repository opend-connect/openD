project(fp_hanfun_alarm_rpi)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

link_directories(
    ${CMAKE_SOURCE_DIR}/src/opend/dialog/fp_hanfun/include/lib_linux
    ${CMAKE_SOURCE_DIR}/src/opend/dspg/fp_hanfun/include/lib
)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/fp_hanfun_alarm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/devicelist.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

#---------------------------------------------------------------------------------------
# Include
#---------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BOARD STREQUAL DialogMmiRpi)

    #---------------------------------------------------------------------------------------
    # Link target
    #---------------------------------------------------------------------------------------
    target_link_libraries(${PROJECT_NAME}
        stdc++
        iwu
        hanfun_api
        hanfunLib
        pthread
        microhttpd
        UleSdkPhoenixRpiLinux
        rt
    )

elseif(BOARD STREQUAL DspgDectRpi)

    #---------------------------------------------------------------------------------------
    # Link target
    #---------------------------------------------------------------------------------------
    target_link_libraries(${PROJECT_NAME}
        stdc++
        iwu
        hanfun_api
        dspg-cmbs-lib
        dspg-cmbs-frame
        dspg-cmbs-testLib
        hanfunLib
        pthread
    )

endif()
