cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(acme_pim
    main.cpp
    src/database/database.cpp
    src/models/pim.cpp
    src/views/operation.cpp
    src/views/menu.cpp
    src/views/menus/products.cpp
    src/views/app.cpp
    # src/views/SubMenus/Search/Busqueda.h
    # src/views/SubMenus/Search/Busqueda.cpp
    # src/views/SubMenus/Products/Productos.cpp
    # src/views/SubMenus/Products/Productos.h
    # src/views/SubMenus/Category/Categorias.cpp
    # src/views/SubMenus/Category/Categorias.h
    # src/views/SubMenus/Attributes/Atributos.cpp
    # src/views/SubMenus/Attributes/Atributos.h
    # src/views/SubMenus/Variants/Variantes.cpp
    # src/views/SubMenus/Variants/Variantes.h
)

target_link_libraries(acme_pim SQLite::SQLite3)
