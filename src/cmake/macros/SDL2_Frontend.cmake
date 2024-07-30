MACRO(CONFIGURE_SDL2_FRONTEND _NAME_TARGET)

    INCLUDE(FindPkgConfig)

    PKG_SEARCH_MODULE(SDL2 sdl2)
    PKG_SEARCH_MODULE(SDL2_TTF SDL2_ttf>=2.0.0)
    PKG_SEARCH_MODULE(SDL2_IMAGE SDL2_image>=2.0.0)

    IF(SDL2_FOUND AND SDL2_IMAGE_FOUND AND SDL2_TTF_FOUND)

        TARGET_LINK_LIBRARIES(${_NAME_TARGET} PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
        TARGET_INCLUDE_DIRECTORIES(${_NAME_TARGET} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
        TARGET_COMPILE_DEFINITIONS(${_NAME_TARGET} PRIVATE -D USE_SDL2)
        TARGET_COMPILE_OPTIONS(${_NAME_TARGET} PRIVATE ${SDL2_CFLAGS} ${SDL2_TTF_CFLAGS} ${SDL2_IMAGE_CFLAGS})
        TARGET_LINK_OPTIONS(${_NAME_TARGET} PRIVATE ${SDL2_LDFLAGS} ${SDL2_TTF_CFLAGS} ${SDL2_IMAGE_CFLAGS})
        MESSAGE(STATUS "Support for SDL2 front end - Ready")

    ELSE()

        MESSAGE(FATAL_ERROR "Support for SDL2 front end - Failed")

    ENDIF()

ENDMACRO()
