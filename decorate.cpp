#include "decorate.h"

int main(int argc, char** argv) {
  if (!PeekNamedPipe(GetStdHandle(STD_INPUT_HANDLE), NULL, NULL, NULL, NULL, NULL)) {
    printf("error: no piping input\n");
    return -1;
  }
  std::ostringstream figletout;
  char buf[256];
  while (fgets(buf, sizeof(buf), stdin))
    figletout << buf;
  std::string figlet = figletout.str();

  auto parseint = [](const char* str) { 
    // TODO: throws format error
    return std::atoi(str);
  };
  int optc;
  int mode = 0;
  int padl = 0, padr = 0, padt = 0, padb = 0;
  while ((optc = getopt(argc, argv, "m:l:r:t:b:")) != -1) {
    switch (optc) {
      case 'm': mode = parseint(optarg); break;
      case 'l': padl = parseint(optarg); break;
      case 'r': padr = parseint(optarg); break;
      case 't': padt = parseint(optarg); break;
      case 'b': padb = parseint(optarg); break;
    }
  }
  enum mode_t {
    mode_mixed = 0,
    mode_figlet = 1,
    mode_background = 2,
  };
  int maxw = 0;
  for (auto l : lines(figlet))
    maxw = std::max(maxw, (int)l.size());
  std::string randomstr = "0123456789ABCDEF";
  std::random_device rdev;
  auto getch = [mode, &rdev, &randomstr]() {
    if (mode == mode_figlet) return std::string(" ");
    auto min = std::random_device::min(), max = std::random_device::max();
    double r = static_cast<double>(rdev() - min) / (max - min);
    return randomstr.substr(round(r * (randomstr.size() - 1)), 1);
  };
  auto padvert = [maxw, padl, padr, getch](int h) {
    int w = maxw + padl + padr;
    for (int c = 0; c < h * w; c++)
      printf(c > 0 && (c + 1) % w == 0 ? "%s\n" : "%s", getch().c_str());
  };
  padvert(padt);
  for (auto l : lines(figlet)) {
    for (int c = -padl; c < maxw + padr; c++) {
      if (c < 0 || c >= l.size()) {
        printf(getch().c_str()); 
      }
      else {
        if (l[c] == 0x20)
          printf(getch().c_str());
        else
          printf(mode == mode_background ? " " : l.substr(c, 1).c_str());
      }
    }
    printf("\n");
  }
  padvert(padb);
  return 0;
}

std::vector<std::string> lines(std::string str) {
  std::regex r("\\r?\\n");
  std::string norm = std::regex_replace(str, r, "\n", std::regex_constants::match_any);
  std::ostringstream ostr;
  std::vector<std::string> vec;
  auto push = [&vec, &ostr]() { 
    if (ostr.str().size() > 0)
      vec.push_back(ostr.str());
    ostr.str("");
  };
  for (int c = 0; c < norm.size(); c++) {
    if (norm[c] == '\n') push();
    else ostr << norm[c];
  }
  push();
  return vec;
}
