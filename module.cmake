# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# HEADERS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( APP_CORE_PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/app/core/public/tetrix/core/" )
set( APP_HEADERS
    "${APP_CORE_PUBLIC}game/TetrixGame.hpp"
    ${APP_HEADERS}
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# SOURCES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( APP_CORE_PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/app/core/private/tetrix/core/" )
set( APP_SOURCES
    "${APP_CORE_PRIVATE}game/TetrixGame.cpp"
    ${APP_SOURCES}
)

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
