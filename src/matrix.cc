#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <math.h>
#include <iostream>

using namespace std;

void fail(const char* msg) {
  fprintf(stderr, "FAIL: %s\n", msg);
  exit(EXIT_FAILURE);
}

typedef struct {
  const gsize dim;
  int* data;
} Matrix_t;

typedef Matrix_t* Matrix;

Matrix allocMatrix(const gsize dim);
int inputMatrix(Matrix *matrix);
void freeMatrix(Matrix matrix);
template <typename T>
static void inputValue(T *value, const char* errStr);

void printPositiveRows(Matrix matrix);
void minDiagSum(Matrix matrix);

int main(void) {
  cout << "= Two dimension matrix processing. =" << endl;

  Matrix matrix;

  inputMatrix(&matrix);
  printPositiveRows(matrix);
  minDiagSum(matrix);

  exit(EXIT_SUCCESS);
}

int inputMatrix(Matrix *matrix) {
  gsize dim;

  cout << "Input matrix dimension: ";
  inputValue(&dim, "Wrong dimension value. Try again.");

  *matrix = allocMatrix(dim);

  cout << "Input all matrix values in С style (by rows) one by one and press enter after each." << endl;

  gsize i = 0, j = 0, k = 0;
  do {
    cout << "Input cell ["<< i <<"][" << j << "]"<< endl;
    inputValue(&(*matrix)->data[k], "Wrong matrix value. Try again.\n");

    if (j == dim - 1) {
      i++;
      j = 0;
    }
    else {
      j++;
    }

    k++;
  } while (k < dim * dim);

  return 0;
}

Matrix allocMatrix(const gsize dim) {
  Matrix matrix = g_new(Matrix_t, 1);
  int *data = g_new0(int, dim * dim);

  *(gsize *) &matrix->dim = dim;
  matrix->data = data;

  return matrix;
}

void freeMatrix(Matrix matrix) {
  g_free(matrix->data);
  g_free(matrix);
}

template <typename T>
static void inputValue(T *value, const char* errStr) {
  cin >> *value;

  while (!cin.good()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cerr << errStr;
    cin >> *value;
  }
}

void printPositiveRows(Matrix matrix) {
  cout << endl;

  for (gsize i = 0; i < matrix->dim; i++) {
    int sum = 0;

    for (gsize j = 0; j < matrix->dim; j++) {
      gsize idx = matrix->dim * i + j;
      int val = matrix->data[idx];

      if (val < 0) {
        cout << "Row: " << i << " has negative number." << endl;
        goto nextrow;
      }
      else {
        sum += val;
      }
    }

    cout << "Row: " << i << ", sum: " << sum << "." << endl;

    nextrow:
    ;
  }
}


void minDiagSum(Matrix matrix) {
  gsize vectorLUsize = matrix->dim * 2 - 2;
  int *vectorLU = g_new0(int, vectorLUsize);
  gsize Uoffset = matrix->dim - 1;

  for (gsize i = 0; i < matrix->dim; i++) {
    for (gsize j = 0; j < matrix->dim; j++) {
      gsize idx = matrix->dim * i + j;
      int val = matrix->data[idx];

      if (i < j) {
        gsize Upos = Uoffset + j - 1 - i;
        vectorLU[Upos] += val;
      }
      else if (i > j) {
        gsize Lpos = i - 1 - j;
        vectorLU[Lpos] += val;
      }
    }
  }

  cout << endl;

  int minimum = INT_MAX;

  for (gsize i = 0; i < vectorLUsize; i++) {
    if (i < vectorLUsize / 2) {
      cout << "L" << i + 1 << "sum = ";
    }
    else {
      cout << "U" << i - vectorLUsize / 2 + 1 << "sum = ";
    }

    cout << vectorLU[i] << endl;

    minimum = min(minimum, vectorLU[i]);
  }

  cout << endl << "Minimum diag sum: " << minimum << endl;
}
