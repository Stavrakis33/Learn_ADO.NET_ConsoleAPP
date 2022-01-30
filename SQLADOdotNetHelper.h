#pragma once

using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Xml; // This is required for the DataSet

using namespace System;

ref class SQLADOdotNetHelperClass
{
private:
    //members
    char* m_errorMessage;
    int m_startRecordDataAdapter;
    int m_maxRecordDataAdapter;

    char* m_connString = "";
    char* m_sqlString = "";
    char* m_srcTable = "";

    SqlConnection^ mySQLConnection;
    SqlCommand^ mySQLCommand;
    SqlDataReader^ myReader;

public:
    //constructor
    SQLADOdotNetHelperClass();
    SQLADOdotNetHelperClass(char* InConnStr, char* InSqlString);
    SQLADOdotNetHelperClass(char* InConnStr, char* InSqlString, char* InSrcTable);
    SQLADOdotNetHelperClass(char* InConnStr, char* InSqlString, char* InSrcTable, int InStartRecord, int InMaxRecord);

    //destructor
    ~SQLADOdotNetHelperClass();

    //functions
    void executeSQLCommand(char* connString, char* sqlString);

    DataSet^ FillDataSet(char* connString, char* sqlString, char* srcTable, char* errorMessage, int startRecord, int maxRecord);
    
    //properties
    void seterrorMessage(char* errorMessage);
    char* geterrorMessage();

    void setStartRecordDataAdapter(int startRecord);
    int getStartRecordDataAdapter();

    void setMySQLConnection(SqlConnection^ InSqlConnection);
    SqlConnection^ getMySqlConnection();

    void setMySQLCommand(SqlCommand^ InMySQL);
    SqlCommand^ getMySQLCommand();

    void setMyReader(SqlDataReader^ InMyDataReader);
    SqlDataReader^ getMyDataReader();

    void setConnString(char* InConnString);
    char* getConnString();

    void setSqlString(char* InSqlString);
    char* getSqlString();

    void setSrcTable(char* InSrcTable);
    char* getSrcTable();

};

