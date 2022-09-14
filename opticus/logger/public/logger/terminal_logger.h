#pragma once

namespace opticus {

enum PrintType { P_LINE, P_DEBUG, P_INFO };
enum ErrorType { ERR_ERROR, ERR_WARNING, ERR_SCRIPT, ERR_CRITICAL };

class TerminalLogger {
 public:
  static void set_priority(PrintType new_priority);
  static void set_error_priority(ErrorType new_priority);

  static void print(const char* print_format, PrintType print_type, ...);
  static void print_error(const char* print_error_format, ErrorType error_type, ...);

  static void log(const char* print_format);

  static PrintType priority;
  static ErrorType error_priority;
};

// To solve external symbol error (somehow).
PrintType TerminalLogger::priority;
ErrorType TerminalLogger::error_priority;

} // namespace levelgd
