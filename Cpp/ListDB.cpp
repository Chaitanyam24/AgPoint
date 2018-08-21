/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ListDB.h"


ListDB::ListDB(){ 
}
ListDB::~ListDB(){
    
}
QString ListDB::DeleteCounterConfig(){
    sql::SQLString statement;
    QString result;
       
    try {
      sql::Driver *driver = 0;
      sql::Connection *con = 0;
      sql::Statement *stmt = 0;
      

      /* Create a connection */
      driver = get_driver_instance();
      result = "Trying driver->connect";

      con = driver->connect("localhost:3306", "pi", COM_MYSQL_DB);
      
      if(con)
      {
          result = "trying setSchema";
        con->setSchema(COMMODITY_DATABASE);    // Select the db to use.
        
      }
      else
      {
          return result;
      }
        stmt = con->createStatement();

        stmt->execute("DELETE from counterconfig");
        delete stmt;
        delete con;
    }
     catch (sql::SQLException &e) 
     {
         return result;
     }  
     return result;
 }

QString ListDB::LoadSelectedSeed(int SeedId){
    sql::SQLString statement;
    QString result;
    std::string s = std::to_string(SeedId);
    char const *pchar = s.c_str();
    
    try {
      sql::Driver *driver = 0;
      sql::Connection *con = 0;
      sql::Statement *stmt = 0;
      sql::ResultSet *res = 0;
      sql::PreparedStatement *pstmt = 0;

      /* Create a connection */
      driver = get_driver_instance();
      result = "Trying driver->connect";

      con = driver->connect("localhost:3306", "pi", COM_MYSQL_DB);
      
      if(con)
      {
          result = "trying setSchema";
        con->setSchema(COMMODITY_DATABASE);    // Select the db to use.
        
      }
      else
      {
          return result;
      }
      
      statement = "INSERT INTO counterconfig(";
      statement += TABLE_COLUMNS;
      statement += ") SELECT ";
      statement += TABLE_COLUMNS;
      statement += " from seedinfo";
      statement += " WHERE seed=";
      statement += pchar;
     
      result = "trying prepareStatement";
      pstmt = con->prepareStatement(statement);
      result = "executeQuery";
      res = pstmt->executeQuery();
      
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

QString ListDB::TestQuery() 
{
    QString stringResult;
    
 try {
  sql::Driver *driver = 0;
  sql::Connection *con = 0;
  sql::Statement *stmt = 0;
  sql::ResultSet *res = 0;
  sql::PreparedStatement *pstmt = 0;

  /* Create a connection */
  stringResult = "Trying driver->connect";
  driver = get_driver_instance();
  con = driver->connect("localhost:3306", "pi", COM_MYSQL_DB); // this works, 5/9/2017
  /* Connect to the MySQL database */
  if(con){
    con->setSchema(COMMODITY_DATABASE);
  }
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
