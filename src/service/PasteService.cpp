
#include "PasteService.hpp"

oatpp::Object<PostPasteDTO>
PasteService::createPaste(const oatpp::String &content) {
  auto dbResult = m_database->createPaste(content);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PostPasteDTO>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
  return result[0];
}

oatpp::Object<GetPasteDTO> PasteService::getPaste(const oatpp::String &code) {
  auto dbResult = m_database->getPasteContent(code);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<GetPasteDTO>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_404, "Paste not found");
  return result[0];
}

oatpp::Object<StatusDto>
PasteService::updatePaste(const oatpp::String &token,
                          const oatpp::String &content) {
  auto dbResult = m_database->updatePaste(token, content);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Paste was successfully updated";
  return status;
}

oatpp::Object<StatusDto> PasteService::deletePaste(const oatpp::String &token) {
  auto dbResult = m_database->deletePaste(token);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Paste was successfully deleted";
  return status;
}