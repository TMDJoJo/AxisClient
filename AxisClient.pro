SOURCES += \
    Main.cpp \
    Login/LoginScene.cpp \
    MainWindow.cpp \
    Navigation/navigation.cpp \
    Navigation/MyTableView.cpp \
    Navigation/mystandarditemmodel.cpp \
    Navigation/myitemdelegate.cpp \
    WorkScene/IWorkScene.cpp \
    WorkScene/WelcomeScene.cpp \
    WorkScene/TestWorkScene.cpp \
    Logo/LogoScene.cpp \
    Tray/Tray.cpp \
    Tray/TrayIconMenu.cpp \
    AxisBaseWidget/AErrorWidget.cpp \
    AxisBaseWidget/AMessageBox.cpp

HEADERS += \
    Login/LoginScene.h \
    MainWindow.h \
    Navigation/navigation.h \
    Navigation/MyTableView.h \
    Navigation/mystandarditemmodel.h \
    Navigation/myitemdelegate.h \
    WorkScene/IWorkScene.h \
    WorkScene/WelcomeScene.h \
    WorkScene/TestWorkScene.h \
    Logo/LogoScene.h \
    Tray/Tray.h \
    Tray/TrayIconMenu.h \
    AxisBaseWidget/AErrorWidget.h \
    AxisBaseWidget/Common.h \
    AxisBaseWidget/AMessageBox.h

FORMS += \
    Login/LoginScene.ui \
    WorkScene/WelcomeScene.ui \
    WorkScene/TestWorkScene.ui \
    Logo/LogoScene.ui

OTHER_FILES += \
    Resource/QSS/Theme.css

RESOURCES += \
    WorkDirectory.qrc

QT += webkit
