
#ifndef oatpp_mongo_Model_hpp
#define oatpp_mongo_Model_hpp

#include <iostream>

#include "dto/DTOs.hpp"
#include "oatpp/encoding/Base64.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace db {

class characteristicsDb: public oatpp::DTO {

  DTO_INIT(characteristicsDb, DTO)

  DTO_FIELD(String, tamanio, "Tamaño");
  DTO_FIELD(String, nombre_patron, "Nombre del patrón");
  DTO_FIELD(String, estilo, "Estilo");
};

class variationsDb: public oatpp::DTO {

  DTO_INIT(variationsDb, DTO)

  DTO_FIELD(Object<characteristicsDb>, characteristics, ".*B0.*");
};

class ProductoDb : public oatpp::DTO {

  DTO_INIT(ProductoDb, DTO)

    DTO_FIELD(String, _id);
    DTO_FIELD(String, title);
    DTO_FIELD(Vector<oatpp::String>, images);
    DTO_FIELD(String, asin);
    DTO_FIELD(Float64, price);
    DTO_FIELD(String, category);
    //DTO_FIELD(Object<variationsDb>, variations);
    DTO_FIELD(String, url);
    DTO_FIELD(Float64, weight);
    DTO_FIELD(String, shipper);
    DTO_FIELD(String, brand);
    DTO_FIELD(String, parent_asin);
    DTO_FIELD(String, name_category);
    DTO_FIELD(Vector<oatpp::String>, frecuentlyBoughtTogheter);
    DTO_FIELD(Vector<oatpp::String>, features);
    DTO_FIELD(String, description);
    DTO_FIELD(Object<characteristicsDb>, characteristics);
    DTO_FIELD(Object<variationsDb>, variations);

};

}

#include OATPP_CODEGEN_END(DTO)

#endif // oatpp_mongo_Model_hpp
