
#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "db/Database.hpp"

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"
#include "oatpp/core/macro/component.hpp"

#include <mongocxx/client.hpp>

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
  private:
    oatpp::base::CommandLineArguments m_cmdArgs;
  public:

    AppComponent(const oatpp::base::CommandLineArguments& cmdArgs)
    : m_cmdArgs(cmdArgs)
    {}
  
  public:

    /**
     * Create Async Executor
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)([] {
      return std::make_shared<oatpp::async::Executor>(
        9 /* Data-Processing threads */,
        2 /* I/O threads */,
        1 /* Timer threads */
      );
    }());

    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
      /* non_blocking connections should be used with AsyncHttpConnectionHandler for AsyncIO */
      return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8000, oatpp::network::Address::IP_4});
    }());
    
    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
      return oatpp::web::server::HttpRouter::createShared();
    }());
    
    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
      OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
      OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor); // get Async executor component
      return oatpp::web::server::AsyncHttpConnectionHandler::createShared(router, executor);
    }());
    
    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    objectMapper->getDeserializer()->getConfig()->allowUnknownFields = false;
    objectMapper->getSerializer()->getConfig()->useBeautifier = true;
    return objectMapper;
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<db::Database>, database)([this] {

    oatpp::String connectionString = std::getenv("MONGO_CONN_STR_URI");
    if(!connectionString){
      connectionString = m_cmdArgs.getNamedArgumentValue("--conn-str", "mongodb://aplicacionScraper:%3Fv%3DDyDfgMOUjCI@44.195.193.19:27017/");
    }

    mongocxx::uri uri(*connectionString);
    
    return std::make_shared<db::Database>(uri, "json_collection", "product");

  }());

};

#endif /* AppComponent_hpp */
