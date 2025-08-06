# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
option(CLEAN_TRS "Clean Obsolete translations from tr files" FALSE)
find_package(Qt6LinguistTools)

set(ff7tk_TRS
    ff7tk_de.ts
    ff7tk_en.ts
    ff7tk_es.ts
    ff7tk_fr.ts
    ff7tk_it.ts
    ff7tk_ja.ts
    ff7tk_re.ts
    ff7tk_pl.ts
    ff7tk_zh_CN.ts
    ff7tk_zh_TW.ts
)

if(CLEAN_TRS)
    set(CLEAN_OPTION "-no-obsolete")
else()
    set(CLEAN_OPTION "")
endif()

qt_create_translation(TRS ${CMAKE_SOURCE_DIR}/src ${ff7tk_TRS} OPTIONS -no-ui-lines -locations none ${CLEAN_OPTION})
add_custom_target(ff7tk_translations ALL DEPENDS ${TRS})

install(FILES ${TRS} DESTINATION ${CMAKE_INSTALL_DATADIR}/ff7tk/translations COMPONENT ff7tk_i18n)
