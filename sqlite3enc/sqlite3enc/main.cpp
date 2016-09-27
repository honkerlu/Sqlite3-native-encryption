//
//  main.cpp
//  sqlite3enc
//
//  Created by Windgod-World on 9/27/16.
//  Copyright (c) 2016 Windgod. All rights reserved.
//

#include <iostream>
#include "sqlite3.h"
#include <vector>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    sqlite3 *pdb;
    sqlite3_open("new.sqlite3", &pdb);
    //sqlite3_key(pdb, "123456789", strlen("123456789"));
    //sqlite3_rekey(pdb, "", 0);  // Cancel password
    char *error;
    sqlite3_exec(pdb, "CREATE TABLE GAMES(username text, sex text);", NULL, NULL, NULL);
//    bool ret = sqlite3_exec(pdb, "insert into X(xx,xxx) values(10000,500);", NULL, NULL, &error);
    bool ret = sqlite3_exec(pdb, "insert into GAMES(username,sex) values('狂败之渣','male');", NULL, NULL, &error);
    printf(ret == SQLITE_OK ? "success.\n" : "failure.\n");
    printf("%s",error);
    
    char **Result = NULL;
    char **errormsg = NULL;
    
    
    printf("versiont %s",sqlite3_version);
    int row = 0;
    
    int col = 0;
    std::string sql = "select *from GAMES;";
    std::vector<std::pair<std::string, std::string>> ve;
    int result = sqlite3_get_table(pdb, sql.c_str(), &Result, &row, &col,errormsg);
    
    int index = col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::pair<std::string, std::string> data;
            data.first = Result[j];
            if (Result[index] == NULL) {
                data.second = "";
            }else{
                data.second = Result[index];
            }
            
            ve.push_back(data);
            index++;
        }
    }
    
    if (result != SQLITE_OK) {
        printf("error :%s",sqlite3_errmsg(pdb));
        return false;
    }
    
    for (auto &itor:ve) {
        printf("key :%s,values:%s \n\n",itor.first.c_str(),
               itor.second.c_str());
    }

    
    
    sqlite3_close(pdb);
    return 0;
}
