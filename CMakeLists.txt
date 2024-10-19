cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

add_executable(acme_pim
    main.cpp
        src/View/terminal.cpp
        src/View/terminal_implementations.cpp
        src/View/SubMenus/Search/Busqueda.h
        src/View/SubMenus/Search/Busqueda.cpp
        src/View/SubMenus/Products/Productos.cpp
        src/View/SubMenus/Products/Productos.h
        src/View/SubMenus/Category/Categorias.cpp
        src/View/SubMenus/Category/Categorias.h
        src/View/SubMenus/Attributes/Atributos.cpp
        src/View/SubMenus/Attributes/Atributos.h
        src/View/SubMenus/Variants/Variantes.cpp
        src/View/SubMenus/Variants/Variantes.h
)