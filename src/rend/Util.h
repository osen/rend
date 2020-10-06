#include <vector>
#include <string>

namespace rend
{

struct Util
{
  static void splitStringLineEnding(const std::string& input, std::vector<std::string>& output);
  static void splitString(const std::string& input, char splitter, std::vector<std::string>& output);
  static void splitStringWhitespace(const std::string& input, std::vector<std::string>& output);
};

}
