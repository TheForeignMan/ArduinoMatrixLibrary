/*
MatrixLibrary.cpp - Class file for the Matrix Algebra Library for Arduino.

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

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <MatrixLibrary.h>

Matrix::Matrix(const Matrix* matrix)
{
	Zeros(matrix->Rows(), matrix->Columns());
	for (int rowIndex = 0; rowIndex < thisRows; rowIndex++)
	{
        for (int columnIndex = 0; columnIndex < thisCols; columnIndex++)
		{
			SetValueAt(rowIndex, columnIndex, matrix->GetValueAt(rowIndex, columnIndex));
		}
	}
}

Matrix::Matrix(int rows, int cols)
{
	Zeros(rows, cols);
}

Matrix Matrix::NewMatrix(int rows, int cols)
{
    return NewMatrix(rows, cols, 0.0f);
}

Matrix Matrix::NewMatrix(int rows, int cols, double initialValue)
{
    thisMatrix = malloc(rows * cols * sizeof(double));
	thisRows = rows;
	thisCols = cols;
	
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			SetValueAt(i, j, initialValue);
		}
	}
	
	return *this;
}

Matrix Matrix::Ones(int rows, int cols)
{
    return NewMatrix(rows, cols, 1.0f);
}

Matrix Matrix::Zeros(int rows, int cols)
{
    return NewMatrix(rows, cols, 0.0f);
}

Matrix Matrix::Eye(int rowCol)
{
	NewMatrix(rowCol, rowCol);
	for (int rowIndex = 0; rowIndex < thisRows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < thisCols; columnIndex++)
		{
			if (rowIndex == columnIndex)
			{
				SetValueAt(rowIndex, columnIndex, 1.0f);
			}
			else
			{
				SetValueAt(rowIndex, columnIndex, 0.0f);
			}
		}
	}
	return *this;
}

Matrix Matrix::Random(int rowCol)
{
	NewMatrix(rowCol, rowCol);
	for (int rowIndex = 0; rowIndex < thisRows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < thisCols; columnIndex++)
		{
			SetValueAt(rowIndex, columnIndex, (rowIndex * 100) + columnIndex);
		}
	}
			
	return *this;
}

Matrix Matrix::Clone()
{
	Matrix clonedMatrix(thisRows, thisCols);
	for(int rowIndex = 0; rowIndex < thisRows; rowIndex++)
	{
        for(int columnIndex = 0; columnIndex < thisCols; columnIndex++)
		{
			clonedMatrix.SetValueAt(rowIndex, columnIndex, GetValueAt(rowIndex, columnIndex));
		}
	}
	
	return clonedMatrix;
}


int Matrix::Rows()
{
	return thisRows;
}

int Matrix::Columns()
{
	return thisCols;
}

void Matrix::Row(double* location, int row)
{
	if(row < 0)
    {
		Serial.println("Row is <0");
        return;
    }
	else if(row > (thisRows - 1))
	{
		Serial.println("Row cannot be more than number of rows");
		return;
	}
	
	for (int colIndex = 0; colIndex < thisCols; colIndex++)
	{
		location[colIndex] = GetValueAt(row, colIndex);
	}
}

void Matrix::Column(double* location, int col)
{
	if(col < 0)
    {
		Serial.print("Col = "); Serial.println(col);
        return;
    }
	else if(col > (thisCols - 1))
	{
		Serial.print("Col = "); Serial.println(col);
		Serial.println("Col cannot be more than number of columns");
		return;
	}

    for (int rowIndex = 0; rowIndex < thisRows; rowIndex++)
	{
		location[rowIndex] = GetValueAt(rowIndex, col);
	}
}

void Matrix::RemoveRow(int row)
{
	Matrix tempClone = Clone();
	Zeros(Rows() - 1, Columns());
	byte hasRowBeenFound = 0;
	for (int rows = 0; rows < tempClone.Rows(); rows++)
	{
		if (rows == row)
		{
			hasRowBeenFound = 1;
		}
		else
		{
			for (int cols = 0; cols < tempClone.Columns(); cols++)
			{
				if (hasRowBeenFound == 1)
				{
					SetValueAt(rows - 1, cols, tempClone.GetValueAt(rows, cols));
				}
				else
				{
					SetValueAt(rows, cols, tempClone.GetValueAt(rows, cols));
				}
			}
		}
	}
}

void Matrix::RemoveColumn(int column)
{
	Matrix tempClone = Clone();
	Zeros(Rows(), Columns() - 1);
	byte hasColBeenFound = 0;
	for (int cols = 0; cols < tempClone.Columns(); cols++)
	{
		if (cols == column)
		{
			hasColBeenFound = 1;
		}
		else
		{
			for (int rows = 0; rows < tempClone.Rows(); rows++)
			{
				if (hasColBeenFound == 1)
				{
					SetValueAt(rows, cols - 1, tempClone.GetValueAt(rows, cols));
				}
				else
				{
					SetValueAt(rows, cols, tempClone.GetValueAt(rows, cols));
				}
			}
		}
	}
}

double Matrix::GetValueAt(int row, int col)
{
	return *(thisMatrix + (row * thisCols) + col);
}

void Matrix::SetValueAt(int row, int col, double value)
{
	*(thisMatrix + (row * thisCols) + col) = value;
}


Matrix Matrix::Transpose()
{
	// switch the row/column value around
    Matrix temp(Columns(), Rows());
	
    for(int rowIndex = 0; rowIndex < Rows(); rowIndex++)
	{
        for(int columnIndex = 0; columnIndex < Columns(); columnIndex++)
		{
			temp.SetValueAt(columnIndex, rowIndex, GetValueAt(rowIndex, columnIndex));
		}
	}
	
	return temp;
}


// Perform a mathematical operation on the Matrix
Matrix Matrix::Math(Matrix::Operation operation, double value)
{
	Matrix resultantMatrix(Rows(), Columns());

    for (int matrixRow = 0; matrixRow < thisRows; matrixRow++)
    {
        for (int matrixColumn = 0; matrixColumn < thisCols; matrixColumn++)
        {
			switch(operation)
			{
				case Matrix::MULTIPLY:
					resultantMatrix.SetValueAt(
						matrixRow, matrixColumn, 
						GetValueAt(matrixRow, matrixColumn) * value);
					break;
					
				case Matrix::ADD:
					resultantMatrix.SetValueAt(
						matrixRow, matrixColumn, 
						GetValueAt(matrixRow, matrixColumn) + value);
					break;
					
				case Matrix::SUBTRACT:
					resultantMatrix.SetValueAt(
						matrixRow, matrixColumn, 
						GetValueAt(matrixRow, matrixColumn) - value);
					break;
			}
        }
    }

    return resultantMatrix;
}


// Perform a mathematical operation on the Matrix
Matrix Matrix::Math(Matrix::Operation operation, Matrix* matrix2)
{
	int matrix1Rows = Rows();
	int matrix2Cols = matrix2->Columns();
    Matrix resultantMatrix(matrix1Rows, matrix2Cols);

	if(!(matrix1Rows && matrix2Cols))
	{
		Serial.println("Row and/or Col are empty");
		return resultantMatrix;
	}
	else if(matrix1Rows != matrix2Cols)
	{
		Serial.println("Vector lengths do not match.");
		return resultantMatrix;
	}
	
	switch(operation)
	{
		case Matrix::MULTIPLY:
			if (Columns() != matrix2->Rows())
			{
				Serial.println("Invalid matrices");
				return resultantMatrix;
			}
			break;
			
		case Matrix::ADD:
		case Matrix::SUBTRACT:
			if ((Rows() != matrix2->Rows()) && (Columns() != matrix2->Columns()))
			{
				Serial.println("Invalid matrices");
				return resultantMatrix;
			}
			break;
			
		default:
			Serial.println("Invalid operation");
			return resultantMatrix;
	}
	
	double vector1[matrix1Rows] = {0};
	double vector2[matrix2Cols] = {0};
	
	for(int matrix1Row = 0; matrix1Row < matrix1Rows; matrix1Row++)
	{
		Row(vector1, matrix1Row);
		for(int matrix2Column = 0; matrix2Column < matrix2Cols; matrix2Column++)
		{
			Row(vector1, matrix1Row);
			matrix2->Column(vector2, matrix2Column);
			
			double result = 0.0;
			switch(operation)
			{
				case Matrix::ADD:
					result = GetValueAt(matrix1Row, matrix2Column);
					result += matrix2->GetValueAt(matrix1Row, matrix2Column);
					resultantMatrix.SetValueAt(matrix1Row, matrix2Column, result);
					break;
					
				case Matrix::SUBTRACT:
					result = GetValueAt(matrix1Row, matrix2Column);
					result -= matrix2->GetValueAt(matrix1Row, matrix2Column);
					break;
					
				case Matrix::MULTIPLY:
					for (int i = 0; i < matrix1Rows; i++)
					{
						result += vector1[i] * vector2[i];
					}
					break;
			}
			
			resultantMatrix.SetValueAt(matrix1Row, matrix2Column, result);
		}
	}

    return resultantMatrix;
}


// Find the determinant of the current matrix.
double Matrix::Determinant()
{
	if (Rows() != Columns())
	{
		Serial.flush();
		Serial.print("Determinant: "); Serial.print(Rows()); Serial.print(", "); 
		Serial.print(Columns()); Serial.println(". not a square matrix!");
		return 0.0;
	}
	else if ((Rows() == 0) && (Columns() == 0))
	{
		Serial.flush();
		Serial.print("Determinant: "); Serial.print(Rows()); Serial.print(", "); 
		Serial.print(Columns()); Serial.println(" empty matrix!");
		return 0.0;
	}
	else if((Rows() == 1) && (Columns() == 1))
	{
		return GetValueAt(0, 0);
	}
	else if((Rows() == 2) && (Columns() == 2))
	{
		double a, b, c, d;
		a = GetValueAt(0, 0);
		b = GetValueAt(0, 1);
		c = GetValueAt(1, 0);
		d = GetValueAt(1, 1);
		return ((a * d) - (b * c));
	}
	
	// 1. Isolate the first row from the rest of the matrix.
	//    Example:
	//    { a b c      { a b c }
	//      d e f   => { d e f
	//      g h i }      g h i }
	// 2. For each column, obtain the surrounding matrix.
	//    Example:
	//    { a b c }    { a _ _ }  { _ b _ }  { _ _ c }
	//    { d e f   => { _ e f    { d _ f    { d e _
	//      g h i }      _ h i }    g _ i }    g h _ }
	// 3. For each column, assign a sign (+/-) and calculate
	//    the determinant of the smaller matrix.
	//    Example:
	//            { e f              { d f               { d e
	//    + a det(  h i } )  - b det(  g i } )  + c det(   g h } )

	int8_t sign = 1;
	double determinant = 0.0;
	Matrix isolatedMatrix(Rows() - 1, Columns() - 1);
	for(int column = 0; column < Columns(); column++)
	{
		for(int row = 1; row < Rows(); row++)
		{
			int elementValue = 0;
			for(int element = 0; element < Columns(); element++)
			{
				if(element == column)
				{
					continue;
			    }
				
				isolatedMatrix.SetValueAt(row - 1, elementValue, GetValueAt(row, element));
				elementValue++;
				elementValue = elementValue % (Columns() - 1);
			}
		}
		determinant += sign * GetValueAt(0, column) * isolatedMatrix.Determinant();
		sign = -sign;
	}
	
	return determinant;
}


// Calculate the inverse of the current matrix using 
// Minors, Cofactors and Adjugate. This method is used
// because there seems to be a specific path from input
// matrix to output matrix, and this can be coded much
// more easily than the Gauss-Jordan method. Process is
// explained at 
// https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
Matrix Matrix::Inverse()
{
	// 1. Calculate the determinant. Get that out of the way first
	double determinant = Determinant();
	if ((determinant == 0) ||
		(Rows() != Columns()))
	{
		return Zeros(Rows(), Columns());
	}
	
	// 2. Calculate the Matrix of Minors, and convert to the 
	// matrix of Cofactors. The procedure is similar to calculating 
	// the determinant, but there are some differences.
	Matrix temp(Rows() - 1, Columns() - 1);
	Matrix minorsCofactors(Rows(), Columns());
	bool positive = true;
	for (int column = 0; column < Columns(); column++)
	{
		for (int row = 0; row < Rows(); row++)
		{
			int rowCount = 0;
			int rowSet = 0;
			int colCount = 0;
			int colSet = 0;
			while (1)
			{
				if ((rowCount != row) && (colCount != column))
				{
					temp.SetValueAt(rowSet, colSet, GetValueAt(rowCount, colCount));
					colSet = (colSet + 1) % temp.Columns();
					if (colSet == 0)
					{
						rowSet = (rowSet + 1) % temp.Rows();
					}
				}
				
				colCount = (colCount + 1) % Columns();
				
				if (colCount == 0)
				{
					rowCount = (rowCount + 1) % Rows();
					if(rowCount == 0)
					{
						break;
					}
				}
			}
			
			double det = temp.Determinant();
			if(!positive)
			{
				det = det * -1;
			}
			minorsCofactors.SetValueAt(row, column, det);
			
			// To set the matrix of cofactors
			positive = !positive;
		}
	}
	
	// 3. Transpose the matrix of cofactors.
	Matrix adjunct = minorsCofactors.Transpose();
	
	// 4. Multiply by 1/determinant of original matrix
	Matrix inverse = adjunct.Math(Matrix::MULTIPLY, (1 / determinant));
	
	return inverse;
}


void Matrix::PrintMatrix()
{
	for(int matrixRow = 0; matrixRow < thisRows; matrixRow++)
	{
		for(int matrixCol = 0; matrixCol < thisCols; matrixCol++)
		{
			Serial.print(GetValueAt(matrixRow, matrixCol));
			Serial.print('\t');
		}
		Serial.println();
	}
	Serial.println();
}


