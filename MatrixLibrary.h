/*
MatrixLibrary.h - Header file for the Matrix Algebra Library for Arduino.

Version: 1.0.0
(c) 2018 Thomas Bartleet
www.github.com/TheForeignMan

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MatrixLibrary_h
#define MatrixLibrary_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Matrix
{
    public:
	
	enum Operation
	{
		ADD,
		SUBTRACT,
		MULTIPLY
	};

	Matrix(const Matrix* matrix);
	Matrix(int rows, int cols, double initialValue = 0.0);
	Matrix(int squareSize, bool isIdentityMatrix = false);
	
	Matrix NewMatrix(int rows, int cols, double initialValue = 0.0);
	Matrix Ones(int rows, int cols);
	Matrix Zeros(int rows, int cols);
	Matrix Eye(int rowCol);
	
	int Rows();
	int Columns();
	void RemoveRow(int row);
	void RemoveColumn(int column);
	double GetValueAt(int row, int col);
	void Row(double* destination, int row);
	void Column(double* destination, int col);
	void SetValueAt(int row, int col, double value);
	
	Matrix Transpose();
	double Determinant();
	Matrix Inverse();
	Matrix Math(Operation operation, double value);
	Matrix Math(Operation operation, Matrix* matrix);
	
	void PrintMatrix();

    private:

	int thisRows;
	int thisCols;
	double *thisMatrix;
};

#endif