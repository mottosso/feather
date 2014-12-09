set(CMAKE_INCLUDE_CURRENT_DIR ON)

# INSTALL

FILE(GLOB QML_FILES "*.qml")

INSTALL(FILES ${QML_FILES} DESTINATION /usr/local/feather/ui/widgets/menus/main/file/import)
