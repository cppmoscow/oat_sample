
#ifndef PasteController_hpp
#define PasteController_hpp

#include "service/PasteService.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class PasteController : public oatpp::web::server::api::ApiController {
public:
  PasteController(const std::shared_ptr<ObjectMapper> &objectMapper)
      : oatpp::web::server::api::ApiController(objectMapper) {}

private:
  PasteService m_userService; // Create user service.
public:
  static std::shared_ptr<PasteController> createShared(OATPP_COMPONENT(
      std::shared_ptr<ObjectMapper>,
      objectMapper) // Inject objectMapper component here as default parameter
  ) {
    return std::make_shared<PasteController>(objectMapper);
  }

  ENDPOINT("POST", "pastes", createPaste, BODY_STRING(String, content)) {
    return createDtoResponse(Status::CODE_200,
                             m_userService.createPaste(content));
  }

  ENDPOINT("GET", "pastes", getPaste, QUERY(String, code)) {
    return createDtoResponse(Status::CODE_200, m_userService.getPaste(code));
  }

  ENDPOINT("PUT", "pastes", updatePaste, QUERY(String, token),
           BODY_STRING(String, content)) {
    return createDtoResponse(Status::CODE_200,
                             m_userService.updatePaste(token, content));
  }

  ENDPOINT("DELETE", "pastes", deletePaste, QUERY(String, token)) {
    return createDtoResponse(Status::CODE_200,
                             m_userService.deletePaste(token));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* PasteController_hpp */
