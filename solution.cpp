/* ----------------------------------------------------------------------------
 * Copyright &copy; 2015 Dong Kim <donm93@csu.fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * A program to read unsigned integers from a text file and separate them into
 * two files, one for primes, another for composites.
 */


#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

/**
 * Find the maximum unsigned integer in `infilename`.
 *
 * Arguments:
 * - `infilename`: A string representing the file path to open.
 *     - Note: Since the string will not be changed, we declare it `const`.
 *       Since strings are objects (and therefore larger than fundamental
 *       types), we avoid copying it by passing it by reference.
 *
 * Returns:
 * - The maximum integer, or `-1` on error.
 *     - Note: It would be better style in C++ to throw an exception, but we
 *       haven't learned about those yet.
 */
int find_max(const string& infilename);
  ifstream infile(const string& infilename);
  if(! infile.is_open());
  return -1;


void sieve(const int size, bool primes[]);
for (int a = 0; a < size; a++) {
        primes[a] = true;
        return -1;

int write_primes( const int size,
                  bool primes[],
                  const string& infilename,
                  const string& outfilename );

/**
 * Read numbers from `infilename`, and if they are composite, output them to
 * `outfilename`, separated by newlines.
 *
 * Arguments:
 * - `size`: The size of (the number of elements in) the array.
 * - `primes`: An array of boolean values, with each element set to `true` if
 *   its index is prime, and `false` otherwise.
 * - `infilename`: A string representing the file path to read from.
 * - `outfilename`: A string representing the file path to write to.
 *
 * Returns:
 * - 0 on success, or -1 on error.
 */
int write_composites( const int size,
                      bool primes[],
                      const string& infilename,
                      const string& outfilename );

// ----------------------------------------------------------------------------

int main() {
    int max = find_max("input.txt");
    if (max == -1) {
        cout << "ERROR in `find_max()`" << endl;
        return 1;  // error
    }

    // - Runtime sized arrays are a C99 feature, and a GCC and Clang extension.
    //   Thus `bool primes[max+1];` is not standards compliant.  It should work
    //   on Xcode (which uses Clang) and in Linux (where most people use either
    //   GCC or Clang), but Visual Studio appears not to allow it.
    bool * primes = (bool *) malloc( sizeof(bool) * (max+1) );
    sieve(max+1, primes);

    int ret;  // for storing return values, to check for error codes
    //
    ret = write_primes(max+1, primes, "input.txt", "primes.txt");
    if (ret == -1) {
        cout << "ERROR in `write_primes()`" << endl;
        return 1;  // error
    }
    //
    ret = write_composites(max+1, primes, "input.txt", "composites.txt");
    if (ret == -1) {
        cout << "ERROR in `write_composites()`" << endl;
        return 1;  // error
    }

    return 0;  // success
}

// ----------------------------------------------------------------------------

int find_max(const string& infilename) {
    ifstream infile(infilename);
    if (!infile.is_open())
        return -1;  // error

    int max = -1;

    int n;
    for (infile >> n; infile.good(); infile >> n) {
        if (n > max)
            max = n;
    }

    return max;
}

void sieve(const int size, bool primes[]) {
    // set all entries to `true`
    for (int a = 0; a < size; a++) {
        primes[a] = true;
    }

    // mark special cases `0` and `1` as `false`
    primes[0] = false;
    primes[1] = false;

    // for the rest of the numbers, iterating from low indices to high, if a
    // number is marked as `true`, mark all multiples of it as `false`
    // - note that in the outer loop we could stop at `sqrt(size)`
    for (int a = 2; a < size; a++) {
        if (primes[a] == true)
            for (int b = a+a; b < size; b += a)
                primes[b] = false;
    }
}

int write_primes( const int size,
                  bool primes[],
                  const string& infilename,
                  const string& outfilename ) {

    ifstream infile(infilename);
    ofstream outfile(outfilename);
    if ( !infile.is_open() || !outfile.is_open() )
        return -1;  // error

    int n;
    for (infile >> n; infile.good(); infile >> n)
        if (primes[n] == true)
            outfile << n << endl;

    return 0;  // success
}

int write_composites( const int size,
                      bool primes[],
                      const string& infilename,
                      const string& outfilename ) {

    ifstream infile(infilename);
    ofstream outfile(outfilename);
    if ( !infile.is_open() || !outfile.is_open() )
        return -1;  // error

    int n;
    for (infile >> n; infile.good(); infile >> n)
        if (primes[n] == false)
            outfile << n << endl;

    return 0;  // success
}

