cmake_minimum_required(VERSION 3.10)
project(ld42)

option(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_STANDARD 11)

add_executable(ld42 main.cpp GUI/Widgets/Text.cpp GUI/Widgets/Text.h GUI/Widgets/Widget.cpp GUI/Widgets/Widget.h GUI/Widgets/Clickable.cpp GUI/Widgets/Clickable.h GUI/Widgets/Button.cpp GUI/Widgets/Button.h GUI/UserInterface.cpp GUI/UserInterface.h GUI/Commands/GameCommand.cpp GUI/Commands/GameCommand.h Game.cpp Game.h GUI/Scene.cpp GUI/Scene.h GUI/Widgets/ImageWidget.cpp GUI/Widgets/ImageWidget.h GUI/Widgets/WidgetComposition.cpp GUI/Widgets/WidgetComposition.h GUI/Widgets/FilledRectangle.cpp GUI/Widgets/FilledRectangle.h GUI/Widgets/Animation.cpp GUI/Widgets/Animation.h GUI/Resources/FontManager.cpp GUI/Resources/FontManager.h GUI/Resources/BitmapManager.cpp GUI/Resources/BitmapManager.h GUI/Resources/ResourceManager.cpp GUI/Resources/ResourceManager.h GUI/Resources/AudioSampleManager.cpp GUI/Resources/AudioSampleManager.h GUI/SceneManager.cpp GUI/SceneManager.h GUI/SceneList.h GUI/CommandTimer.cpp GUI/CommandTimer.h GUI/AudioStuff.cpp GUI/AudioStuff.h)

target_link_libraries(ld42
        liballegro.dll.a liballegro_font.dll.a liballegro_ttf.dll.a liballegro_primitives.dll.a liballegro_image.dll.a liballegro_audio.dll.a liballegro_acodec.dll.a
        libyaml-cpp.a)

