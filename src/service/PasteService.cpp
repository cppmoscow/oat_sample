
#include "PasteService.hpp"

oatpp::Object<PostPasteDTO>
PasteService::createPaste(const oatpp::String &content) {
  auto dbResult = m_database->createPaste(content);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PostPasteDTO>>>();
  return result[0];
}

oatpp::String PasteService::getPaste(const oatpp::String &code) {
  auto dbResult = m_database->getPasteContent(code);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<GetPasteDTO>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_404, "");
  return result[0]->content;
}

void PasteService::updatePaste(const oatpp::String &token,
                               const oatpp::String &content) {
  auto dbResult = m_database->updatePaste(token, content);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->getKnownCount() == 1, Status::CODE_401, "");
}

void PasteService::deletePaste(const oatpp::String &token) {
  auto dbResult = m_database->deletePaste(token);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500,
                    dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->getKnownCount() == 1, Status::CODE_401, "");
}