#pragma once
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>

class Dataset {
private:
  unsigned long n;

  void printDots(int i) {
    ldiv_t tmp_i = ldiv(i, n/33);
    if(tmp_i.rem == 0) {
      printf(".");
      fflush(stdout);
    }
  }

  bool read(const char * filename) {
    std::ifstream file(filename);
    if (!file.fail()) {
      unsigned long ntmp;
      file.read((char *)&ntmp, sizeof(unsigned long));
      if (n == ntmp) {
	file.read((char *)&pos[0], n*sizeof(double4));
	file.close();
	return true;
      }
    }
    file.close();
    return false;
  }

  void write(const char * filename) {
    std::ofstream file(filename);
    file.write((char *)&n, sizeof(unsigned long));
    file.write((char *)&pos[0], n*sizeof(double4));
    file.close();
  }

  void print_random_data( int num)
  {
      int idx = 0;
      for(int i=0;i<num;++i)
      {
          idx = rand() % n;
          printf("Data %d : %lf %lf %lf %lf\n", idx, pos[idx][0], pos[idx][1], pos[idx][2], pos[idx][3]);
      }
  }
public:
  std::vector<fvec4> pos;
  Dataset(unsigned long _n) : n(_n), pos(_n)
  {
      //Random Initialization
      unsigned long i = 0;
      while (i < n)
      {
          pos[i][0] = ((float) rand() / (RAND_MAX)) + 1;
          pos[i][1] = ((float) rand() / (RAND_MAX)) + 1;
          pos[i][2] = ((float) rand() / (RAND_MAX)) + 1;
          pos[i][3] = ((float) abs(rand()) / (RAND_MAX)) + 1;
          printDots(i);
          i++;
      }
  }
  Dataset(unsigned long _n, float *points, float *weights) : n(_n), pos(_n)
  {
      //Initialize with right data
      for(int i=0;i<n;++i)
      {
          for(int j=0;j<3;++j)
              pos[i][j] = points[i+n*j];
          pos[i][3] = weights[i];
      }
  }
};
