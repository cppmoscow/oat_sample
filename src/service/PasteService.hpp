
#ifndef EXAMPLE_POSTGRESQL_USERSERVICE_HPP
#define EXAMPLE_POSTGRESQL_USERSERVICE_HPP

#include "db/PasteDb.hpp"

#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class PasteService {
private:
  typedef oatpp::web::protocol::http::Status Status;

private:
  OATPP_COMPONENT(std::shared_ptr<PasteDb>,
                  m_database); // Inject database component
public:
  oatpp::Object<PostPasteDTO> createPaste(const oatpp::String &content);
  oatpp::String getPaste(const oatpp::String &code);
  void updatePaste(const oatpp::String &token, const oatpp::String &content);
  void deletePaste(const oatpp::String &token);
};

#endif // EXAMPLE_POSTGRESQL_USERSERVICE_HPP
