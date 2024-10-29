cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(acme_pim
    main.cpp
    src/database/database.cpp
    src/models/pim.cpp
    src/View/terminal_operation.cpp
    # src/View/terminal.cpp
    # src/View/terminal_implementations.cpp
    # src/View/SubMenus/Search/Busqueda.h
    # src/View/SubMenus/Search/Busqueda.cpp
    # src/View/SubMenus/Products/Productos.cpp
    # src/View/SubMenus/Products/Productos.h
    # src/View/SubMenus/Category/Categorias.cpp
    # src/View/SubMenus/Category/Categorias.h
    # src/View/SubMenus/Attributes/Atributos.cpp
    # src/View/SubMenus/Attributes/Atributos.h
    # src/View/SubMenus/Variants/Variantes.cpp
    # src/View/SubMenus/Variants/Variantes.h
)

target_link_libraries(acme_pim SQLite::SQLite3)