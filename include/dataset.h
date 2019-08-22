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
  Dataset(unsigned long _n) : n(_n), pos(_n) {
    unsigned long i = 0;
    const float scale = 3.0 * M_PI / 16.0;
    while (i < n) {
      float R = 1.0 / sqrt( (pow(drand48(), -2.0 / 3.0) - 1.0) );
      if (R < 100.0) {
	float Z = (1.0 - 2.0 * drand48()) * R;
        float theta = 2.0 * M_PI * drand48();
	float X = sqrt(R * R - Z * Z) * cos(theta);
	float Y = sqrt(R * R - Z * Z) * sin(theta);
	X *= scale; Y *= scale; Z *= scale;
	pos[i][0] = ((float) abs(rand()) / (RAND_MAX)) + 1;
	pos[i][1] = ((float) abs(rand()) / (RAND_MAX)) + 1;
	pos[i][2] = ((float) abs(rand()) / (RAND_MAX)) + 1;
	pos[i][3] = ((float) abs(rand()) / (RAND_MAX)) + 1;
	printDots(i);
	i++;
      }
    }
    print_random_data(100);
  }
};
