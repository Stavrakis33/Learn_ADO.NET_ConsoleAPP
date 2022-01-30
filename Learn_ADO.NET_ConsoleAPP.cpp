//CLR Console App (.Net Framework)

#include "pch.h"
#include <iostream>

#using <system.data.dll> // This is required for the ADO.NET Provider
#using <System.Xml.dll> // This is only required for the DataSet

using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Xml; // This is required for the DataSet
using namespace System::Runtime::InteropServices;

using namespace System;


int main(array<System::String ^> ^args)
{
    //SqlConnection^ mySQLConnection = nullptr;
    //SqlDataAdapter^ myDataAdapter = nullptr;
    //DataSet^ myDataSet = nullptr;

    //try
    //{
    //    char* connString = "";
    //    char* sqlString = "";
    //    char* srcTable = "";

    //    String^ _connString = Marshal::PtrToStringAnsi((IntPtr)connString);
    //    String^ _sqlString = Marshal::PtrToStringAnsi((IntPtr)sqlString);

    //    String^ _srcTable = Marshal::PtrToStringAnsi((IntPtr)srcTable);

    //    mySQLConnection = gcnew SqlConnection();
    //    mySQLConnection->ConnectionString = _connString;
    //    myDataAdapter = gcnew SqlDataAdapter();
    //    myDataSet = gcnew DataSet();

    //    mySQLConnection->Open();    // Open up the connection

    //    // Assign the SelectCommand with an SQL Select command
    //    myDataAdapter->SelectCommand = gcnew SqlCommand(_sqlString, mySQLConnection);

    //    // Use the DataAdapter to fill the DataSet
    //    // A DataSet can be made up of many results. I called
    //    // this result authors. The DataAdapter will know to use 
    //    // the SelectCommand property to populate the DataSet.
    //    myDataAdapter->Fill(myDataSet, _srcTable);

    //}
    //catch (Exception^ e) {
    //    Console::Write(e->ToString());
    //}
    //__finally {
    //    mySQLConnection->Close();
    //}

    return 0;
}

DataSet^ FillDataSet(char* connString, char* sqlString, char* srcTable, char* errorMessage, int startRecord=0, int maxRecord=0)
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

//void abc()
//{
//    SqlConnection^ mySQLConnection;
//    SqlCommand^ mySQL;
//    SqlDataReader^ myReader;
//
//    String^ connString = gcnew String("Persist Security Info = False; Integrated Security = true; Initial Catalog = pubs; server = (local)");
//    String^ sqlString = gcnew String("select * from authors");
//    try {
//        mySQLConnection = gcnew SqlConnection();
//        mySQLConnection->ConnectionString = connString;
//
//        mySQLConnection->Open(); // Open up the connection
//
//
//        mySQL = gcnew SqlCommand(sqlString, mySQLConnection);
//
//
//        myReader = mySQL->ExecuteReader();
//
//        while (myReader->Read())
//            Console::WriteLine(myReader["au_lname"]->ToString());
//
//
//    }
//    catch (Exception^ e)
//    {
//        Console::Write(e->ToString());
//    }
//    __finally {
//        if ((myReader) && (!myReader->IsClosed))
//            myReader->Close();
//
//        if (mySQLConnection->State == ConnectionState::Open)
//            mySQLConnection->Close();
//    }
//}
