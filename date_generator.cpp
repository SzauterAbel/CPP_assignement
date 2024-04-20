#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "date.hpp"
#include "exceptions.hpp"

using namespace std;

void generate_dates(int N, int K, const string& output_file) {
    ofstream outfile;
    if (output_file != "-") {
        outfile.open(output_file);
        if (!outfile) {
            cerr << "Error: Unable to open file: " << output_file << endl;
            exit(EXIT_FAILURE);
        }
    }

    try {
        outfile << N << "\n" << K << "\n" ;
        ios_base::openmode mode = ofstream::out | ofstream::binary;
        srand(time(nullptr));
        int i = 0;
        while (i < N + K) {
            try {
                Date date = dateGenerator(
                    Date{1970, 1, 1},
                    Date{2038, 1, 19}
                );
                if (date.getYear() != 0) {
                    if (output_file != "-") {
                        outfile << date.getYear() << " "
                                << date.getMonth() << " "
                                << date.getDay() << endl;
                    } else {
                        cout << date.getYear() << " "
                                << date.getMonth() << " "
                                << date.getDay() << endl;
                    }
                    ++i;
                }
            } catch (const terrible_random_exception& e) {
                cerr << "Failed to generate random date." << endl;
                exit(EXIT_FAILURE);
            }
        }
        if (output_file != "-") {
            outfile.close();
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        cerr << "Usage: " << argv[0] << " N K [output_file|-]" << endl;
        return EXIT_FAILURE;
    }

    int N, K;
    try {
        N = stoi(argv[1]);
        K = stoi(argv[2]);
    } catch (const invalid_argument&) {
        cerr << "Error: N and K must be integers." << endl;
        return EXIT_FAILURE;
    }

    string output_file = (argc == 4) ? argv[3] : "-";

    generate_dates(N, K, output_file);

    return EXIT_SUCCESS;
}