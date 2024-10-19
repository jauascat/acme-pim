#pragma once

#include <sqlite3.h>
#include <iostream>

void executeSQL(sqlite3 *db, const char *sql);

int buildDB();
