#include "connections_handler.h"
#include "json.hpp"
#include "global.h"
#include <fstream>
#include <filesystem>

using nlohmann::json;
using std::ofstream;
using std::ifstream;

// 保存连接数据库信息
int con_handler::save_con_data(const vector<string> &data){
    if (data.size() != CON_DATA_SIZE) return CON_FILE_ERROR_DATA;
    else if (data[CON_NAME].empty()) return CON_FILE_ERROR_NAME_EMPTY;

    for (auto &name : get_all_connections()){
        if (data[CON_NAME] == name) return CON_FILE_ERROR_NAME_SAME;
    }

    json save_data;
    save_data["ip"] = data[CON_IP];
    save_data["port"] = data[CON_PORT];
    save_data["db_name"] = data[CON_DB_NAME];
    save_data["user"] = data[CON_USER];
    save_data["passwd"] = data[CON_PASSWD];

    string file_dir = "./connections/";
    string file_name = data[CON_NAME];
    file_name += ".json";
    
    ofstream out_file(file_dir + file_name);
    if (!out_file.is_open()) {
        out_file.close();
        return CON_FILE_ERROR_OPEN_FILE;
    }

    if (out_file << save_data) {
        out_file.close();
        return CON_FILE_OK;
    }
    else {
        out_file.close();
        return CON_FILE_ERROR_JSON;
    }
}


vector<string> con_handler::get_con_data(const string &name){
    json data;
    vector<string> res;
    ifstream input_file(string("./connections/") + name + ".json");
    if (!input_file.is_open()) return vector<string>();
    if (data << input_file){
        res.push_back(string(name));
        res.push_back(data["db_name"]);
        res.push_back(data["ip"]);
        res.push_back(data["port"]);
        res.push_back(data["user"]);
        res.push_back(data["passwd"]);
        return res;
    }
    else return vector<string>();

}


using std::filesystem::path;
using std::filesystem::directory_iterator;

std::unordered_set<string> con_handler::get_all_connections(){
    std::unordered_set<string> res;

    path dir("./connections");
    for(directory_iterator end, cur(dir); cur != end; cur++){
        res.insert(cur->path().stem().string());
    }
    return res;
}
