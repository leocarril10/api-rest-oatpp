#include <iostream>
#include <cmath>

#include "Database.hpp"

#include "db/Model.hpp"
#include "oatpp/core/data/stream/BufferStream.hpp"

#include <mongocxx/client.hpp>
#include <mongocxx/options/insert.hpp>
#include <mongocxx/exception/operation_exception.hpp>

namespace db {

Database::Database(const mongocxx::uri &uri, const std::string &dbName, const std::string &collectionName)
  : m_pool(std::make_shared<mongocxx::pool>(uri)), m_databaseName(dbName), m_collectionName(collectionName)
{}

oatpp::Object<SearchProductoDto> Database::dtoSearchProductModel(const oatpp::Object<ProductoDb>& producto) {
  auto dto_producto = SearchProductoDto::createShared();
  dto_producto->name = producto->title;
  dto_producto->image = producto->images;
  dto_producto->asin = producto->asin;
  dto_producto->price = std::round(producto->price);
  dto_producto->browser_node_id = producto->category;
  dto_producto->position = producto->url;
  dto_producto->peso = std::round(producto->weight);
  return dto_producto;
}

oatpp::Object<ProductoModelDto> Database::dtoProductoModel(const oatpp::Object<ProductoDb>& producto) {
  auto dto_producto = ProductoModelDto::createShared();
  dto_producto->title = producto->title;
  dto_producto->shipper = producto->shipper;
  dto_producto->asin = producto->asin;
  dto_producto->brand = producto->brand;
  dto_producto->category = producto->category;
  dto_producto->price = std::round(producto->price);
  dto_producto->weight = std::round(producto->weight);
  dto_producto->parent_asin = producto->parent_asin;
  dto_producto->name_category = producto->name_category;
  dto_producto->frecuentlyBoughtTogheter = producto->frecuentlyBoughtTogheter;
  dto_producto->url = producto->url;
  dto_producto->imagenes = producto->images;
  dto_producto->features = producto->features;
  dto_producto->description = producto->description;
  //dto_producto->characteristics = {};

  oatpp::Object<characteristicsDTO> dto_caracteristics = characteristicsDTO::createShared();
  dto_caracteristics->tamanio = producto->characteristics->tamanio;
  dto_caracteristics->nombre_patron = producto->characteristics->nombre_patron;
  dto_caracteristics->estilo = producto->characteristics->estilo;
  dto_producto->characteristics = dto_caracteristics;

  oatpp::Object<variationsDb> dto_variations = variationsDb::createShared();
  //dto_variations->characteristics->tamanio = producto->variations->characteristics->tamanio;

  //dto_producto->variations = dto_variations;

  return dto_producto;
}

bsoncxx::document::value Database::createMongoDocument(const oatpp::Void &polymorph) {
  // if you have huge docs, you may want to increase starting BufferOutputStream size.
  // Or you may want to use oatpp::data::stream::ChunkedBuffer instead - for no-copy growth.
  oatpp::data::stream::BufferOutputStream stream;
  m_objectMapper.write(&stream, polymorph);
  bsoncxx::document::view view(stream.getData(), stream.getCurrentPosition());
  return bsoncxx::document::value(view);
}

oatpp::Object<ProductoModelDto> Database::Search(std::string key_db, const oatpp::String& key) {
  auto conn = m_pool->acquire();
  auto collection = (*conn)[m_databaseName][m_collectionName];

  auto result =
    collection.find_one(createMongoDocument( // <-- Filter
      oatpp::Fields<oatpp::String>({
        {key_db, key}
      })
    ));
  
  if(result) {
    auto view = result->view();
    auto bson = oatpp::String((const char*)view.data(), view.length());
    auto product = m_objectMapper.readFromString<oatpp::Object<ProductoDb>>(bson);
    return dtoProductoModel(product);
  }

  return nullptr;
}

/*oatpp::List<oatpp::Object<ProductoDto>> Database::getAllProducts() {
  auto conn = m_pool->acquire();
  auto collection = (*conn)[m_databaseName][m_collectionName];

  auto cursor = collection.find(
    createMongoDocument(oatpp::Fields<oatpp::String>({})
  ));

  oatpp::List<oatpp::Object<ProductoDto>> list({});

  for(auto view : cursor) {
    auto bson = oatpp::String((const char*)view.data(), view.length());
    auto producto = m_objectMapper.readFromString<oatpp::Object<ProductoDb>>(bson);
    
    list->push_back(dtoFromProducto(producto));
  }

  return list;

}*/

}