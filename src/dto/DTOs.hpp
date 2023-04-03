
#ifndef oatpp_mongo_DTOs_hpp
#define oatpp_mongo_DTOs_hpp

#include <iostream>

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class characteristicsDTO: public oatpp::DTO {

  DTO_INIT(characteristicsDTO, DTO)

  DTO_FIELD(String, tamanio);
  DTO_FIELD(String, nombre_patron);
  DTO_FIELD(String, estilo);

};

class variationsDTO: public oatpp::DTO {

  DTO_INIT(variationsDTO, DTO)

  DTO_FIELD(Object<characteristicsDTO>, characteristics);
};

class SearchProductoDto : public oatpp::DTO {

  DTO_INIT(SearchProductoDto, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Vector<oatpp::String>, image);
  DTO_FIELD(String, asin);
  DTO_FIELD(Int16, price);
  DTO_FIELD(String, browser_node_id);
  //DTO_FIELD(Object<variationsDTO>, pagina);
  DTO_FIELD(String, position);
  DTO_FIELD(Int16, peso);

};

class ProductoModelDto : public oatpp::DTO {

  DTO_INIT(ProductoModelDto, DTO)

  DTO_FIELD(String, title);
  DTO_FIELD(String, shipper);
  DTO_FIELD(String, asin);
  DTO_FIELD(String, brand);
  DTO_FIELD(String, category);
  DTO_FIELD(Int16, price);
  DTO_FIELD(Int16, weight);
  DTO_FIELD(String, parent_asin);
  DTO_FIELD(String, name_category);
  DTO_FIELD(Vector<oatpp::String>, frecuentlyBoughtTogheter);
  DTO_FIELD(String, url);
  DTO_FIELD(Vector<oatpp::String>, imagenes);
  DTO_FIELD(Vector<oatpp::String>, features);
  DTO_FIELD(String, description);
  DTO_FIELD(Object<characteristicsDTO>, characteristics);
  DTO_FIELD(Object<variationsDTO>, variations);
};

class HelloDto : public oatpp::DTO {
  
  DTO_INIT(HelloDto, DTO)
  
  DTO_FIELD(String, userAgent, "user-agent");
  DTO_FIELD(String, message);
  DTO_FIELD(String, server);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* oatpp_mongo_DTOs_hpp */
