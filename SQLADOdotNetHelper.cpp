#include "pch.h"
#include "SQLADOdotNetHelper.h"
#include <iostream>
#include <string>
#include <gcroot.h>


using namespace System;
using namespace System::Runtime::InteropServices;


SQLADOdotNetHelperClass::SQLADOdotNetHelperClass()
{
    //throw gcnew System::NotImplementedException();
    Console::Write("errormessage member initialized");
    m_errorMessage = "";
}

SQLADOdotNetHelperClass::~SQLADOdotNetHelperClass()
{
    //throw gcnew System::NotImplementedException();
    // Deallocate the memory allocated using
    // Marshal::StringToHGlobalAnsi.
    Console::Write("errormessage member destroyd");
    //GlobalFree(m_errorMessage);
}

void SQLADOdotNetHelperClass::executeSQLCommand(char* connString, char* sqlString)
{
      //throw gcnew System::NotImplementedException();

      m_errorMessage = "";
      String^ _connString= Marshal::PtrToStringAnsi((IntPtr)connString);
      String^ _sqlString = Marshal::PtrToStringAnsi((IntPtr)sqlString);
    try {

        mySQLConnection = gcnew SqlConnection();
        mySQLConnection->ConnectionString = _connString;

        mySQLConnection->Open(); // Open up the connection


        mySQLCommand = gcnew SqlCommand(_sqlString, mySQLConnection);


        myReader = mySQLCommand->ExecuteReader();

        while (myReader->Read())
            Console::WriteLine(myReader["au_lname"]->ToString());


    }
    catch (Exception^ e)
    {
        Console::Write(e->ToString());
        m_errorMessage = (char*)Marshal::StringToHGlobalAnsi(e->ToString()).ToPointer();
        seterrorMessage(m_errorMessage);
    }
    __finally {
        if ((myReader) && (!myReader->IsClosed))
            myReader->Close();

        if (mySQLConnection->State == ConnectionState::Open)
            mySQLConnection->Close();
    }
  }

DataSet^ SQLADOdotNetHelperClass::FillDataSet(char* connString, char* sqlString, char* srcTable, char* errorMessage, int startRecord, int maxRecord)
{
    SqlConnection^ mySQLConnection = nullptr;
    SqlDataAdapter^ myDataAdapter = nullptr;
    DataSet^ myDataSet = nullptr;

    try
    {
        /*char* connString = "";
        char* sqlString = "";
        char* srcTable = "";*/

        String^ _connString = Marshal::PtrToStringAnsi((IntPtr)connString);
        String^ _sqlString = Marshal::PtrToStringAnsi((IntPtr)sqlString);
        String^ _srcTable = Marshal::PtrToStringAnsi((IntPtr)srcTable);

        mySQLConnection = gcnew SqlConnection();
        mySQLConnection->ConnectionString = _connString;
        myDataAdapter = gcnew SqlDataAdapter();
        myDataSet = gcnew DataSet();

        mySQLConnection->Open();    // Open up the connection

        // Assign the SelectCommand with an SQL Select command
        myDataAdapter->SelectCommand = gcnew SqlCommand(_sqlString, mySQLConnection);

        // Use the DataAdapter to fill the DataSet
        // A DataSet can be made up of many results. I called
        // this result authors. The DataAdapter will know to use 
        // the SelectCommand property to populate the DataSet.
        myDataAdapter->Fill(myDataSet, startRecord, maxRecord, _srcTable);

        return myDataSet;

    }
    catch (Exception^ e) {
        Console::Write(e->ToString());
        errorMessage = (char*)Marshal::StringToHGlobalAnsi(e->ToString()).ToPointer();
    }
    __finally {
        mySQLConnection->Close();
    }
}

SQLADOdotNetHelperClass::SQLADOdotNetHelperClass(char* InConnStr, char* InSqlString)
{
    m_connString = InConnStr;
    m_sqlString = InSqlString;
}

SQLADOdotNetHelperClass::SQLADOdotNetHelperClass(char* InConnStr, char* InSqlString, char* InSrcTable)
{
    m_connString = InConnStr;
    m_sqlString = InSqlString;
    m_srcTable = InSrcTable;
}

SQLADOdotNetHelperClass::SQLADOdotNetHelperClass(char* InConnStr, char* InSqlString, char* InSrcTable, int InStartRecord, int InMaxRecord)
{
    m_connString = InConnStr;
    m_sqlString = InSqlString;
    m_srcTable = InSrcTable;
    m_startRecordDataAdapter = InStartRecord;
    m_maxRecordDataAdapter = InMaxRecord;
}

void SQLADOdotNetHelperClass::seterrorMessage(char* errorMessage)
{
    m_errorMessage = errorMessage;
}

char* SQLADOdotNetHelperClass::geterrorMessage()
{
    return m_errorMessage;
}

int SQLADOdotNetHelperClass::getStartRecordDataAdapter()
{
    return m_startRecordDataAdapter;
}

void SQLADOdotNetHelperClass::setStartRecordDataAdapter(int startRecord)
{
    m_startRecordDataAdapter = startRecord;
}

void SQLADOdotNetHelperClass::setMySQLConnection(SqlConnection^ InSqlConnection)
{
    mySQLConnection = InSqlConnection;
}

SqlConnection^ SQLADOdotNetHelperClass::getMySqlConnection()
{
    return mySQLConnection;
}

void SQLADOdotNetHelperClass::setMySQLCommand(SqlCommand^ InMySQL)
{
    mySQLCommand = InMySQL;
}

SqlCommand^ SQLADOdotNetHelperClass::getMySQLCommand()
{
    return mySQLCommand;
}

void SQLADOdotNetHelperClass::setMyReader(SqlDataReader^ InMyDataReader)
{
    myReader = InMyDataReader;
}

SqlDataReader^ SQLADOdotNetHelperClass::getMyDataReader()
{
    return myReader;
}

void SQLADOdotNetHelperClass::setConnString(char* InConnString)
{
    m_sqlString = InConnString;
}
char* SQLADOdotNetHelperClass::getConnString() { return m_connString; }

void SQLADOdotNetHelperClass::setSqlString(char* InSqlString) 
{ 
    m_sqlString = InSqlString; 
}
char* SQLADOdotNetHelperClass::getSqlString() { return m_sqlString; }

void SQLADOdotNetHelperClass::setSrcTable(char* InSrcTable) 
{ 
    m_srcTable = InSrcTable; 
}
char* SQLADOdotNetHelperClass::getSrcTable() { return m_srcTable; }





