# ArduinoMatrixLibrary
A library for Arduino to simplify matrix algebra. 

Functions available:
```
// Constructors
Matrix(const Matrix* matrix); ..................................... // Creates a copy of 'matrix' into a new matrix
Matrix(int rows, int cols, double initialValue = 0.0); ............ // Creates a matrix of specific rows/columns, with default value of 0.0
Matrix(int squareSize, bool isIdentityMatrix = false); ............ // Creates a square matrix, with the option of setting it as an identity matrix

// Create a new matrix
Matrix NewMatrix(int rows, int cols, double initialValue = 0.0); .. // Creates a matrix with specific rows/columns and initial value
Matrix Ones(int rows, int cols); .................................. // Creates a matrix with specific rows/columns, all values are 1
Matrix Zeros(int rows, int cols); ................................. // Creates a matrix with specific rows/columns, all values are 0
Matrix Eye(int rowCol); ........................................... // Creates an identity matrix of specific size

// Get/set values
int Rows(); ....................................................... // Number of rows
int Columns(); .................................................... // Number of columns
void RemoveRow(int row); .......................................... // Remove specific row
void RemoveColumn(int column); .................................... // Remove specific column
double GetValueAt(int row, int col); .............................. // Get a specific value in the matrix
void Row(double* location, int row); .............................. // Get a specific row
void Column(double* location, int col); ........................... // Get a specific column
void SetValueAt(int row, int col, double value); .................. // Set the value at a specific point

// Matrix operations
Matrix Transpose(); ............................................... // Transposes the matrix
double Determinant(); ............................................. // Finds the determinant of the matrix
Matrix Inverse(); ................................................. // Finds the inverse of the matrix
Matrix Math(Operation operation, double value); ................... // Does a matrix algebraic operation with a value
Matrix Math(Operation operation, Matrix* matrix); ................. // Does a matrix algebraic operation with another matrix

// Print matrix to serial port
void PrintMatrix(); ............................................... // Prints the matrix to the serial port
```

## Quick examples
Below is a series of quick examples of how to use the library:
```
Matrix myMatrix(2, 3); ............ // 2 rows and 3 columns. All items are number 0

Matrix eyeMatrix;
eyeMatrix.Eye(4); ................. // 4x4 Identity matrix

Matrix allOnes;
allOnes.Ones(3, 4); ............... // 3 rows and 4 columns. All items are number 1

Matrix anotherMatrix(&myMatrix); .. // Copies 'myMatrix' into 'anotherMatrix'
```

This library uses zero-indexing to access the rows and columns of the matrices. For example:
```
Matrix myMatrix(2, 3);      // Creates a 2x3 matrix 
myMatrix.GetValueAt(0, 0);  // Gets the value of the first row and first column
myMatrix.GetValueAt(1, 2);  // Gets the value of the last row and last column
```

Check out the example sketch to find out more applied examples, and how to implement the library in your code!
