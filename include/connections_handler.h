#ifndef __CONNECTIONS_HANDLER_H_
#define __CONNECTIONS_HANDLER_H_

#include <vector>
#include <string>
#include <unordered_set>

using std::vector;
using std::string;

namespace con_handler{
enum con_save_condition{
    CON_FILE_OK = 0, 
    CON_FILE_ERROR, 
    CON_FILE_ERROR_NAME_SAME, 
    CON_FILE_ERROR_NAME_EMPTY,
    CON_FILE_ERROR_DATA,
    CON_FILE_ERROR_OPEN_FILE,
    CON_FILE_ERROR_JSON
};
const std::size_t CON_DATA_SIZE = 6;


vector<string> get_con_data(const string &name);

int save_con_data(const vector<string> &data);

std::unordered_set<string> get_all_connections();


}
#endif