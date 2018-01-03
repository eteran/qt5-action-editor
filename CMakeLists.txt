cmake_minimum_required (VERSION 3.0)
project(qt5-action-editor CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.0.0 REQUIRED Widgets Gui PrintSupport)

add_executable(qt5-action-editor
	ActionsDialog.cpp
	ActionsDialog.h
	ActionsDialog.ui
	ApplicationWindow.cpp
	ApplicationWindow.h
	ApplicationWindow.ui
	main.cpp
)

target_link_libraries(qt5-action-editor
	Qt5::Widgets
	Qt5::Gui
	Qt5::PrintSupport
)
