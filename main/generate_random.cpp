#include <iostream>
#include <sys/time.h>
#include <fstream>

using namespace std;


int main()
{
    const char* FILE_PATH = "random_number.csv";
    const double n = 1000000;

    cout << "Hello, World!" << endl;

    struct drand48_data _rand_buf;

    struct timeval _tv;
    gettimeofday(&_tv, NULL);

    srand48_r((_tv.tv_sec * 1000) + (_tv.tv_usec / 1000), &_rand_buf);

    ofstream oFile;
    oFile.open(FILE_PATH, ios::out | ios::trunc);

    double r;

    for (int i = 0; i < n; i ++)
    {
        drand48_r(&_rand_buf, &r);
        oFile << r << endl;
    }

    oFile.close();

    cout << "Writing finish! The file is '" << FILE_PATH << "'." << endl;

    return 0;
}