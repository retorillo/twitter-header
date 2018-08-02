#include "divider.h"

int main(int argn, char** argv) {
  std::vector<std::shared_ptr<std::ofstream>> files;

  std::string title = "divided";
  int n = 3;
  int optc;
  while ((optc = getopt(argn, argv, "t:n:")) != -1) switch (optc) {
    case 'n': n = std::atoi(optarg); break;
    case 't': title = optarg; break;
  }
  char filename[256];
  for (int c = 0; c < n; c++) {
    std::snprintf(filename, 256, "%s_%02d.txt", title.c_str(), c);
    std::shared_ptr<std::ofstream> file(new std::ofstream(filename));
    files.push_back(file);
  }

  std::random_device random;
  auto rand = [&random](int min, int max) {
    double d = (static_cast<double>(random() - random.min()) / (random.max() - random.min()));
    return static_cast<int>(round(d * (max - min) + min));
  };

  if (!PeekNamedPipe(GetStdHandle(STD_INPUT_HANDLE), NULL, NULL, NULL, NULL, NULL))
    return -1;
  std::ostringstream input_s;
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), stdin))
    input_s << buffer;

  std::string input = input_s.str();
  for (int c = 0; c < input.size(); c++) {
    int r = rand(0, files.size() - 1);
    for (int d = 0; d < files.size(); d++) {
      *files[d] << (input[c] != '\n' && d != r ? ' ' : input[c]);
    }
  }
}
