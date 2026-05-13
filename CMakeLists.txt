cmake_minimum_required(VERSION 3.19)
project(Lost_and_Found LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(Lost_and_Found
    WIN32 MACOSX_BUNDLE
    widget.cpp  widget.h   widget.ui
    editprofiledialog.cpp editprofiledialog.h
    homepage.cpp homepage.h
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    postdata.h
    postdetaildialog.cpp postdetaildialog.h
    postdialog.cpp postdialog.h
    postmanager.cpp postmanager.h
    postpage.cpp postpage.h postpage.ui
    profilepage.cpp profilepage.h
    showpostspage.cpp showpostspage.h
    soundmanager.cpp soundmanager.h
    userdata.h widget.cpp widget.h widget.ui


    resources.qrc

)

target_link_libraries(Lost_and_Found
    PRIVATE
        Qt6::Widgets
        Qt6::Multimedia
)

install(TARGETS Lost_and_Found
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


qt_generate_deploy_app_script(
    TARGET Lost_and_Found
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
