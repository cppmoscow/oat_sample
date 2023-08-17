cmake_minimum_required(VERSION 3.1)

set(project_name example-postgresql) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/controller/PasteController.hpp
        src/db/PasteDb.hpp
        src/dto/ConfigDto.hpp
        src/dto/PasteDTO.hpp
        src/service/PasteService.cpp
        src/service/PasteService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp
        src/ServiceComponent.hpp
)

target_include_directories(${project_name}-lib PUBLIC src)

## link libs

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-postgresql   1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-postgresql
)

add_definitions(
        # Path to config file #
        -DCONFIG_PATH="${CMAKE_CURRENT_LIST_DIR}/resources/config.json"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

#################################################################
## add executables

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)
