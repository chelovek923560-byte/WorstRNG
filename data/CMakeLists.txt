string(TIMESTAMP PROJECT_DATE "%Y-%m-%d" UTC)

configure_file(org.doomedrng.doomedrng.metainfo.in
               org.doomedrng.doomedrng.metainfo.xml
               ESCAPE_QUOTES @ONLY)

if(UNIX AND NOT APPLE)
    install(FILES org.doomedrng.doomedrng.desktop DESTINATION share/applications)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/org.doomedrng.doomedrng.metainfo.xml"
            DESTINATION share/metainfo)
    install(FILES org.doomedrng.doomedrng-setup.desktop DESTINATION share/applications)
    install(FILES doomedrng.png DESTINATION share/icons/hicolor/128x128/apps)
    install(FILES doomedrng-setup.png DESTINATION share/icons/hicolor/128x128/apps)
endif()
