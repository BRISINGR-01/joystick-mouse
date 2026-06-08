#include "data_constants.hpp"
#include <string>

int open_port(const std::string &port_name);

void write_log(const std::string &str);
void log_err(const std::string &str);

bool fill(int bytes_read, int offset, data_unit *buf, data_unit *dest);
void debug(bool is_filled, int bytes_read, int offset, data_unit *buf, data_unit *curr);

Button get_btn(int btn_idx);
std::string get_btn_debug(int btn_idx);
