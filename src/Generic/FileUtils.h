#pragma once

#include <string>

#include "FilePackage.h"

namespace Generic {
namespace FileUtils {

std::string removeDir(const std::string& filename);
bool saveFile(const FilePackage& file);
ByteArray readFile(const std::string& filename);

} // namespace FileUtils
} // namespace Generic
