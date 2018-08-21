/*
 * Interface for reading and writing to the MySQL db.
 * Holds the counter configuration and seed settings.  Will add additional machine
 * settings in the future.
 */

/* 
 * File:   SeedDbInterface.cpp
 * Author: Dan
 * 
 * Created on May 6, 2017, 5:45 AM
 * 
 * 
 */

#include "SeedDbInterface.h"

SeedDbInterface::SeedDbInterface() {
}

SeedDbInterface::SeedDbInterface(const SeedDbInterface& orig) {
}

SeedDbInterface::~SeedDbInterface() {
}

QString SeedDbInterface::TestQuery() 
{
    QString stringResult;
 try {
  sql::Driver *driver = 0;
  sql::Connection *con = 0;
  sql::Statement *stmt = 0;
  sql::ResultSet *res = 0;
  sql::PreparedStatement *pstmt = 0;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("localhost:3306", "pi", MYSQL_DB); // this works, 5/9/2017
  /* Connect to the MySQL database */
  if(con)
    con->setSchema("mydb");
  else
  {
      stringResult = "Error";
      return stringResult;
  }
  stmt = con->createStatement();
  stmt->execute("DROP TABLE IF EXISTS test");
  stmt->execute("CREATE TABLE test(id INT)");
  delete stmt;

  pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
  for (int i = 1; i <= 10; i++) {
    pstmt->setInt(1, i);
    pstmt->executeUpdate();
  }
  if(res != 0)
    delete res;
  if(pstmt != 0)
    delete pstmt;
  if(con != 0)
    delete con;
  return stringResult;
} 
 catch (sql::SQLException &e) 
 {
  
 }   
}

 QString SeedDbInterface::LoadCounterConfig(DFG2Counter& CounterConfig)
 {  // works, 5/13/2017
    sql::SQLString statement;
    QString result;
    try {
      sql::Driver *driver = 0;
      sql::Connection *con = 0;
      sql::Statement *stmt = 0;
      sql::ResultSet *res = 0;
      sql::PreparedStatement *pstmt = 0;

      /* Create a connection */
      driver = get_driver_instance();
      result = "Trying driver->connect";

      con = driver->connect("localhost:3306", "pi", MYSQL_DB);
      
      if(con)
      {
          result = "trying setSchema";
        con->setSchema(DATABASE_NAME);    // Select the db to use.
        
      }
      else
      {
          return result;
      }
      statement = "SELECT *";
     // statement += TABLE_COUNTER_CONFIG_COLUMNS;
      statement += " FROM ";
      statement += TABLE_COUNTER_CONFIG;
      statement += " WHERE rowid=0";

      result = "trying prepareStatement";
      pstmt = con->prepareStatement(statement);
      result = "executeQuery";
      res = pstmt->executeQuery();
      while (res->next())
      {
          result = "copying results";
            CounterConfig.Teach(res->getInt(2)); 
            CounterConfig.ResponseSpeed(res->getInt(3));
            CounterConfig.OffsetPercent(res->getInt(4));
            CounterConfig.ButtonLock(res->getInt(5));
            CounterConfig.TotalCounts(res->getInt(6));
            CounterConfig.TotalOneShot(res->getInt(7));
            CounterConfig.DynamicEventStretch(res->getInt(8));
      }
      if(res != 0)
        delete res;
      if(pstmt != 0)
        delete pstmt;
      if(con != 0)
        delete con;
    } 
     catch (sql::SQLException &e) 
     {
         return result;
     }  
     return result;
 }
  
 /*
  *     Writes the values of current counter configuration to the 
  *     'counterconfig' table in the 'seedlist' table.
  */
 QString SeedDbInterface::SaveCounterConfig(DFG2Counter CounterConfig)
 {  // works, 5/12/2017
     sql::SQLString statement;
     QString result;
    try {
      sql::Driver *driver = 0;
      sql::Connection *con = 0;
      sql::Statement *stmt = 0;
      sql::ResultSet *res = 0;
      sql::PreparedStatement *pstmt = 0;

      /* Create a connection */
      driver = get_driver_instance();
      result = "Trying driver->connect";

      con = driver->connect("localhost:3306", "pi", MYSQL_DB);
      if(con)
      {
          result = "trying setSchema";
        con->setSchema(DATABASE_NAME);    // Select the db to use.
      }
      else
      {
          return QString("1");
      }
     
      statement = "UPDATE ";
      statement += TABLE_COUNTER_CONFIG;
      statement += " SET rowid=?, teach=?, responsespeed=?, offsetpercent=?, buttonlock=?, totalcounts=?, totaloneshot=?, dynamiceventstretch=? WHERE rowid=0";

      result = "trying prepareStatement";
      pstmt = con->prepareStatement(statement);
      pstmt->setInt(1,0);
      pstmt->setInt(2,CounterConfig.Teach());
      pstmt->setInt(3,CounterConfig.ResponseSpeed());
      pstmt->setInt(4,CounterConfig.OffsetPercent());
      pstmt->setInt(5,CounterConfig.ButtonLock());
      pstmt->setInt(6,CounterConfig.TotalCounts());
      pstmt->setInt(7,CounterConfig.TotalOneShot());
      pstmt->setInt(8,CounterConfig.DynamicEventStretch());
      result = "trying executeUpdate";
      pstmt->executeUpdate();
      result = "deleting memory";
      if(res != 0)
        delete res;
      if(pstmt != 0)
        delete pstmt;
      if(con != 0)
        delete con;

    } 
     catch (sql::SQLException &e) 
     {
         return QString(result);
     }  
     return QString("0");
}

  QString SeedDbInterface::PopulateDbVariables()
 {  // works, 5/13/2017
    sql::SQLString statement;
    QString result;
    try {
      sql::Driver *driver = 0;
      sql::Connection *con = 0;
      sql::Statement *stmt = 0;
      sql::ResultSet *res = 0;
      sql::PreparedStatement *pstmt = 0;

      /* Create a connection */
      driver = get_driver_instance();
      result = "Trying driver->connect";

      con = driver->connect("localhost:3306", "pi", MYSQL_DB);
      
      if(con)
      {
          result = "trying setSchema";
        con->setSchema(DATABASE_NAME);    // Select the db to use.
        
      }
      else
      {
          return result;
      }
      statement = "SELECT *";
     // statement += TABLE_COUNTER_CONFIG_COLUMNS;
      statement += " FROM ";
      statement += TABLE_COUNTER_CONFIG;
      statement += " WHERE rowid=0";

      result = "trying prepareStatement";
      pstmt = con->prepareStatement(statement);
      result = "executeQuery";
      res = pstmt->executeQuery();
      
      while (res->next())
      {
            result = "copying results";
            Teach = res->getInt(2); 
            ResponseSpeed=(res->getInt(3));
            OffsetPercent=(res->getInt(4));
            ButtonLock=(res->getInt(5));
            TotalCounts=(res->getInt(6));
            TotalOneShot=(res->getInt(7));
            DynamicEventStretch=(res->getInt(8));
      }
      if(res != 0)
        delete res;
      if(pstmt != 0)
        delete pstmt;
      if(con != 0)
        delete con;
    } 
     catch (sql::SQLException &e) 
     {
         return result;
     }  
     return result;
 }
  
  int SeedDbInterface::GetTeach(){ return Teach; }
    int SeedDbInterface::GetResponseSpeed(){ return ResponseSpeed; }
    int SeedDbInterface::GetOffsetPercent() { return OffsetPercent; }
    int SeedDbInterface::GetButtonLock() { return ButtonLock;}
    int SeedDbInterface::GetTotalCounts(){ return TotalCounts; }
    int SeedDbInterface::GetTotalOneShot() { return TotalOneShot; }
    int SeedDbInterface::GetDynamicEventStretch() { return DynamicEventStretch;} 