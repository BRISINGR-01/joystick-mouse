#include "data_constants.hpp"
#include <string>

void write_log(const std::string &str);
void log_err(const std::string &str);

bool fill(int bytes_read, int offset, data_unit *buf, data_unit *dest);