#ifndef PasteDto_hpp
#define PasteDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class PostPasteDTO : public oatpp::DTO {
  DTO_INIT(PostPasteDTO, DTO)

  DTO_FIELD(String, code, "code");
  DTO_FIELD(String, token, "token");
};

class GetPasteDTO : public oatpp::DTO {
  DTO_INIT(GetPasteDTO, DTO)

  DTO_FIELD(String, content, "content");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* PasteDto_hpp */
