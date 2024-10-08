#include <QtQuickTest>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QCoreApplication>

#include "infraestructure/db/postgredatasource.h"
#include "interface/table/userTableModel.h"
#include "global/config/qml.h"
#include "global/test/testdatabase-options.h"

class Setup: public QObject
{
    Q_OBJECT

private:
    ErrorHandler* errorHandlerPtr;
    PostgreDataSource* datasourcePtr;
    qmlDto* dtoPtr;
    UserTableModel* userTableModelPtr;
    const QString connectionName = "qml-testing-setup-connection";

    void clearDatabase()
    {
        QSqlQuery query(QSqlDatabase::database(connectionName));
        const QString command = "DELETE FROM %1";
        query.exec(command.arg(datasourcePtr->tableName()));
    }

public:
    Setup(){}

public slots:

    // Called once before everything start
    void applicationAvailable()
    {
        QQuickStyle::setStyle(GlobalApplicationConfig::Qml::controlsStyle);

        errorHandlerPtr = new ErrorHandler();
        datasourcePtr = new PostgreDataSource(errorHandlerPtr,connectionName,"testing-users");
        dtoPtr = new qmlDto(datasourcePtr);
        userTableModelPtr = new UserTableModel(dtoPtr);

        datasourcePtr->connect(TestingConfig::databaseOptions);

        if(!datasourcePtr->dbIsOpen())        
            qFatal()<< "Could not connect to database. Testing aborted";                    
    }

    // Called once for each QML test file
    void qmlEngineAvailable(QQmlEngine *engine)
    {
        engine->rootContext()->setContextProperty("errorhandler", errorHandlerPtr);
        engine->rootContext()->setContextProperty("QmlDto", dtoPtr);
        engine->rootContext()->setContextProperty("usersTable", userTableModelPtr);
    }

    // Called once before everything finish
    void cleanupTestCase()
    {
        clearDatabase();
        delete userTableModelPtr;
    }
};

QUICK_TEST_MAIN_WITH_SETUP(qmlTest,Setup)
#include "test.moc"
