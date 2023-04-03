
#ifndef oatpp_mongo_Database_hpp
#define oatpp_mongo_Database_hpp

#include "dto/DTOs.hpp"
#include "Model.hpp"

#include "oatpp-mongo/bson/mapping/ObjectMapper.hpp"

#include <mongocxx/pool.hpp>
#include <bsoncxx/document/value.hpp>

namespace db {

class Database {
private:
  std::shared_ptr<mongocxx::pool> m_pool;
  std::string m_databaseName;
  std::string m_collectionName;
  oatpp::mongo::bson::mapping::ObjectMapper m_objectMapper;
private:
  oatpp::Object<SearchProductoDto> dtoSearchProductModel(const oatpp::Object<ProductoDb>& productos_set);
  oatpp::Object<ProductoModelDto> dtoProductoModel(const oatpp::Object<ProductoDb>& productos_set);
private:
  bsoncxx::document::value createMongoDocument(const oatpp::Void &polymorph);
public:

  Database(const mongocxx::uri &uri, const std::string &dbName, const std::string &collectionName);

  oatpp::Object<ProductoModelDto> Search(std::string key_db,const oatpp::String& key);
  oatpp::Object<SearchProductoDto> Search_cat(std::string key_db,const oatpp::String& key);
  //oatpp::List<oatpp::Object<SearchProductoDto>> getAllProducts();
};

}

#endif //oatpp_mongo_Database_hpp
