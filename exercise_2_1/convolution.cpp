using namespace std;
std::vector<double> applyConvolution(vector<double> x, vector<double> w, bool pack_with_zeros) {
  std::vector<double> y;
  int packing_size = (w.size()-1)/2;

  for(int i = 0; i < x.size(); i++) {
    double accumulator = 0;
    for(int j = 0; j < w.size(); j++) {

      // Since kernel is filled in with 0's outside does not matter
      if(i - packing_size + j >= 0 && i - packing_size + j < x.size()) {
        accumulator += x[i - packing_size + j]*w[j];
      } else if(!pack_with_zeros && i - packing_size + j < 0) {
        // Handles the case where where we underflow indexes
        accumulator += x[0] * w[j];
      } else if(!pack_with_zeros && i - packing_size + j >= x.size()) {
        // Handles the case where we overflow indexes
        accumulator += x[x.size()-1] * w[j];
      }
    }
    y.push_back(accumulator);
  }
  return y;
}

void printVector(vector<double> vec) {
  std::cout << "{" << vec[0];
  for(int i = 1; i < vec.size(); i++) {
    std::cout << ", " << vec[i];
  }
  std::cout << "}" << std::endl;
}