cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

add_executable(acme_pim
    main.cpp
    src/Lab/LabLogic/Queue.cpp
    src/Lab/LabMenu.cpp
    src/View/terminal_implementations.cpp
    src/View/terminal.cpp
    src/View/SubMenus/Search/Busqueda.cpp
    src/View/SubMenus/Products/Productos.cpp
    src/View/SubMenus/Category/Categorias.cpp
    src/View/SubMenus/Attributes/Atributos.cpp
    src/View/SubMenus/Variants/Variantes.cpp
)