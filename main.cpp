#include <cwf/cppwebapplication.h>
#include <cwf/urlencoder.h>
#include <cwf/sqldatabasestorage.h>
#include <cwf/sqlquery.h>
#include "config.h"

#if defined(PSQL_HOST) && defined(PSQL_DB) && defined(PSQL_USER) && defined(PSQL_PASSWORD) && defined(PSQL_PORT)

CWF::SqlDatabaseStorage my_connection("QPSQL", PSQL_HOST, PSQL_DB, PSQL_USER, PSQL_PASSWORD, PSQL_PORT);

class CEPController : public CWF::Controller
{
public:    
    void doDelete(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery qry(my_connection.getDatabase());
	qry.prepare("DELETE FROM logradouro WHERE logr = :cep");
	qry.bindValue(":cep", request.getParameter("cep"));

        response.write(qry.exec());
    }

    void doPut(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery qry(my_connection.getDatabase());

        response.write(
		qry.updateFromJson(
			request.bodyToJsonObject(),
			"logradouro",
			"logr_cep = '" + request.getParameter("cep") + "'" // UNSAFE
		)
	);        
    }

    void doPost(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery qry(my_connection.getDatabase());

        response.write(
		qry.insertFromJson(
			request.bodyToJsonObject(),
			"logradouro"
		)
	);
    }

    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery qry(my_connection.getDatabase());

	qry.prepare("SELECT * FROM logradouro WHERE logr_cep = :cep");
	qry.bindValue(":cep", request.getParameter("cep"));
	qry.exec();

        response.write(qry.toJson());
    }
};

int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, SERVER_CONF_DIR);
    server.addController<CEPController>("/cep");
    return server.start();
}

#endif
