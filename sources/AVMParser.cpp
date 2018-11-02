#include "AVMParser.hpp"

/* ======== CANONICAL ======== */

AVMParser::AVMParser(): _lines(std::vector<std::string>(0)) {}
AVMParser::AVMParser(std::vector<std::string> lines): _lines(lines) {}
