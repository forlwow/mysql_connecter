#ifndef __GLOBAL_H_
#define __GLOBAL_H_

class QFont;

enum sql_connect_data{
    CON_NAME = 0, 
    CON_DB_NAME,
    CON_IP,
    CON_PORT,
    CON_USER,
    CON_PASSWD
};

extern QFont glo_font;


#endif