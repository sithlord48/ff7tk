set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)

find_package(Qt${QT_DEFAULT_MAJOR_VERSION}LinguistTools)

set(ff7tk_TRS
    ff7tk_en.ts
    ff7tk_es.ts
    ff7tk_fr.ts
    ff7tk_de.ts
    ff7tk_ja.ts
    ff7tk_re.ts
    ff7tk_pl.ts
)

qt_create_translation(TRS ${CMAKE_SOURCE_DIR} ${ff7tk_TRS})
add_custom_target(ff7tk_translations ALL DEPENDS ${TRS})

install(FILES ${TRS} DESTINATION share/ff7tk/lang)
