
#ifndef EXAMPLE_POSTGRESQL_PASTEDB_HPP
#define EXAMPLE_POSTGRESQL_PASTEDB_HPP

#include "dto/PasteDTO.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * PasteDb client definitions.
 */
class PasteDb : public oatpp::orm::DbClient {
public:
  PasteDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
      : oatpp::orm::DbClient(executor) {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */,
                      DATABASE_MIGRATIONS "/001_init.sql");
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("PasteDb", "Migration - OK. Version=%d.", version);
  }

  QUERY(getPasteContent, "SELECT content FROM pastes WHERE code=:code;",
        PREPARE(true), PARAM(oatpp::String, code));

  QUERY(createPaste,
        "INSERT INTO pastes (content) VALUES(:content) RETURNING "
        "code, token;",
        PREPARE(true), PARAM(oatpp::String, content));

  QUERY(updatePaste, "UPDATE pastes SET content=:content WHERE token=:token;",
        PREPARE(true), PARAM(oatpp::String, token),
        PARAM(oatpp::String, content));

  QUERY(deletePaste, "DELETE FROM pastes WHERE token=:token", PREPARE(true),
        PARAM(oatpp::String, token));
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif // EXAMPLE_POSTGRESQL_PASTEDB_HPP
