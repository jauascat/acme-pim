#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

int sequentialSearch(const std::vector<std::string> &collection, const std::string &target) {
  for (size_t i = 0; i < collection.size(); ++i) {
    if (collection[i] == target) return i;
  }
  return -1;
}

int binarySearch(const std::vector<std::string> &collection, const std::string &target) {
  size_t left_limit = 0;
  size_t right_limit = collection.size() - 1;

  while (left_limit <= right_limit) {
    size_t mid_point_index = left_limit + (right_limit - left_limit) / 2;

    int stringComparison = std::strcmp(collection[mid_point_index].c_str(), target.c_str()); 
    if (stringComparison == 0)
      return mid_point_index;
    
    if (stringComparison < 0)
      left_limit = mid_point_index + 1;
    else
      right_limit = mid_point_index - 1;
    
  }
  return -1; 
}

int main() {
  std::vector<std::string> greek_parthenon = {
    "Zeus", "Poseidon", "Demeter", "Athena", 
    "Apollo", "Artemis", "Ares", "Aphrodite", "Hephaestus", "Hera",
    "Hermes", "Dionysus", "Hades", "Hypnos", "Nike",
  };

  std::string target = "Hera";

  int indexSequential = sequentialSearch(greek_parthenon, target);
  std::cout << "Sequential:" << target 
            << (indexSequential != -1 ? " found at index " : " not found. Index: ") 
            << indexSequential << " // from collection: " + greek_parthenon[indexSequential] << '\n';


  std::sort(greek_parthenon.begin(), greek_parthenon.end());
  std::cout << "Sorted Parthenon: " << '\n';
  for (const auto& god : greek_parthenon) std::cout << god << ' ';
  std::cout << '\n' << '\n';

  int indexBinary = binarySearch(greek_parthenon, target);
  std::cout << "Binary:" << target 
            << (indexBinary != -1 ? " found at index " : " not found. Index: ") 
            << indexBinary << " // from collection: " + greek_parthenon[indexBinary] << '\n';

  return 0;
}
