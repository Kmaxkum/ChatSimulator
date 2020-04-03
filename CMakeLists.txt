# Минимальную версию CMake:
cmake_minimum_required(VERSION 3.1.0)

# Характеристики проекта:
project(test VERSION 1.0.0 LANGUAGES CXX)

# Включение автоматического вызова сборки MOC, UIC и RCC:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Автоматическое включение текузих исходных каталогов и 
# каталогов сборки в путь включения, если версия CMake меньше "3.7.0":
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Найти необходимые компоненты Qt5 "QtCore" "QtGui" "QtWigets":
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Установка значений переменных списков соответвующих исходных,
# заголовочных, инерфейсныхй и ресурсных файлов:
set(project_sources server_window.cpp main.cpp server.cpp user.cpp chat_view.cpp users_storage.cpp)
set(project_headers server_window.h server.h user.h chat_view.h users_storage.h)
set(project_ui server_window.ui chat_view.ui)
set(project_qrc server_window.qrc)

# Добавление в сборку исполняемого файл ${PROJECT_NAME}:
add_executable(${PROJECT_NAME}
    ${project_sources}
	${project_ui}
	${project_qrc}
)

# Установка параметров для главной цепи ${PROJECT_NAME}:
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Компоновка исполняемого файла ${PROJECT_NAME} с
# библиотеками QT5 "QtCore" "QtGui" "QtWigets":
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)

# Автоматическое копирование dll файлов для операционных систем Windows:
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms)
endif(WIN32)

# Установка цепи ${PROJECT_NAME} в каталог "bin":
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Автоматическая установка dll файлов для операционных систем Windows:
if (WIN32)
	install(
		FILES $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> DESTINATION bin/platforms)
	install(
		FILES $<TARGET_FILE:Qt5::Core> $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE:Qt5::Widgets> DESTINATION bin/)
endif()