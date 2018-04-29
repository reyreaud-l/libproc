#include "plib.hh"

namespace plib
{
fs::path get_proc_root()
{
  return fs::path("/proc");
}

std::vector<fs::path> get_proc_dirs(const fs::path& root)
{
  if (!fs::is_directory(root))
  {
    throw std::invalid_argument("Expected directory as 1st argument, got: " +
                                root.string());
  }
  std::vector<fs::path> res;
  for (const auto& entry : fs::directory_iterator(root))
  {
    const auto& p = entry.path();
    if (!p.has_filename())
    {
      continue;
    }
    const auto& str_p = p.filename().string();
    if (!std::all_of(str_p.begin(), str_p.end(), ::isdigit))
    {
      continue;
    }
    res.push_back(p);
  }
  return res;
}

fs::path get_proc_dir(const fs::path& root, int uid)
{
  if (!fs::is_directory(root))
  {
    throw std::invalid_argument("Expected directory as 1st argument, got: " +
                                root.string());
  }
  for (const auto& entry : fs::directory_iterator(root))
  {
    auto p = entry.path();
    if (!p.has_filename())
    {
      continue;
    }
    const auto& str_p = p.filename().string();
    if (!std::all_of(str_p.begin(), str_p.end(), ::isdigit))
    {
      continue;
    }
    if (str_p != std::to_string(uid))
    {
      continue;
    }
    return p;
  }
  throw std::invalid_argument("Could not find a process for uid: " +
                              std::to_string(uid));
}
} // namespace plib
