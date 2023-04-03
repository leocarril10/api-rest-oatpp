cmake_minimum_required(VERSION 3.1)

set(project_name api-rest-oatpp) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/db/Database.cpp
        src/db/Database.hpp
        src/AppComponent.hpp
        src/AppComponentAsync.hpp
        src/controller/UserController.cpp
        src/controller/UserController.hpp
        src/dto/DTOs.hpp
        src/db/Model.hpp
)
###################################################################
# Find mongocxx

find_package(mongocxx REQUIRED)
message("LIBBSONCXX_INCLUDE_DIRS=${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES=${LIBBSONCXX_LIBRARIES}")

message("LIBMONGOCXX_INCLUDE_DIRS=${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBMONGOCXX_LIBRARIES=${LIBMONGOCXX_LIBRARIES}")

## link libs

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-mongo    1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
PUBLIC oatpp::oatpp
PUBLIC oatpp::oatpp-test
PUBLIC oatpp::oatpp-mongo
)

target_include_directories(${project_name}-lib PUBLIC src)

if (TARGET mongo::mongocxx_shared)
    target_link_libraries(${project_name}-lib
            PUBLIC mongo::mongocxx_shared
    )
    message("mongo::mongocxx_shared is used")
elseif(TARGET mongo::mongocxx_static)
    target_link_libraries(${project_name}-lib
            PUBLIC mongo::mongocxx_static
    )
endif()


## add executables

add_executable(${project_name}
        src/App.cpp
)
target_link_libraries(${project_name} ${project_name}-lib)
add_dependencies(${project_name} ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name} ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
