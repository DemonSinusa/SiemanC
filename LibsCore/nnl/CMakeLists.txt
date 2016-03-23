cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(NewNeuroLib)				# Название проекта (NewLibLazy too)

set(SOURCE_LIB Quproquowing.cpp)		# Установка переменной со списком исходников

add_library(NNL STATIC ${SOURCE_LIB})# Создание статической библиотеки
