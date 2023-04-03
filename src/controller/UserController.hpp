
#ifndef oatpp_mongo_UserController_hpp
#define oatpp_mongo_UserController_hpp

#include "db/Database.hpp"
#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)



class UserController : public oatpp::web::server::api::ApiController {
private:
  OATPP_COMPONENT(std::shared_ptr<db::Database>, m_database);
public:
  UserController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  static std::shared_ptr<UserController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
  {
    return std::make_shared<UserController>(objectMapper);
  }

  ENDPOINT_ASYNC("GET", "/", Root) {
    
    ENDPOINT_ASYNC_INIT(Root)
    
    /**
     *  Coroutine entrypoint act()
     *  returns Action (what to do next)
     */
    Action act() override {
      auto dto = HelloDto::createShared();
      dto->message = "Hello Async!";
      dto->server = Header::Value::SERVER;
      dto->userAgent = request->getHeader(Header::USER_AGENT);
      return _return(controller->createDtoResponse(Status::CODE_200, dto));
    }
    
  };
  
  ENDPOINT("GET", "api/search/{key}", Search,
           PATH(String, key)) {
    //std::string stdString = key->c_str();    
    //std::cout<<stdString<<"\n";
    auto producto = m_database->Search("_id", key);
    OATPP_ASSERT_HTTP(producto, Status::CODE_404, "search key not found");
    return createDtoResponse(Status::CODE_200, producto);
  }

  ENDPOINT("GET", "api/category/{category}", Prueba_func,
           PATH(String, category)) {
    
    auto producto = m_database->Search("category",category);
    OATPP_ASSERT_HTTP(producto, Status::CODE_404, "search key not found");
    return createDtoResponse(Status::CODE_200, producto);
  }

  /*ENDPOINT("GET", "api/all_products", getAllProducts) {
    return createDtoResponse(Status::CODE_200, m_database->getAllProducts());
  }*/
  
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* oatpp_mongo_UserController_hpp */
