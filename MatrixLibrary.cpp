/*
HMC5883L.cpp - Class file for the HMC5883L Triple Axis Digital Compass Arduino Library.

Version: 1.1.0
(c) 2014 Korneliusz Jarzebski
www.jarzebski.pl

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

#include "MatrixLibrary.h"

Matrix* Matrix::NewMatrix(int rows, int cols)
{
    return NewMatrix(rows, cols, 0.0f);
}

Matrix* Matrix::NewMatrix(int rows, int cols, double initialValue)
{
    thisMatrix = malloc(rows * cols * sizeof(double));
	thisRows = rows;
	thisCols = cols;
	
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			SetValueAtLocation(i, j, initialValue);
	
	return this;
}

Matrix* Matrix::Ones(int rows, int cols)
{
    return NewMatrix(rows, cols, 1.0f);
}

Matrix* Matrix::Zeros(int rows, int cols)
{
    return NewMatrix(rows, cols, 0.0f);
}

Matrix* Matrix::Eye(int rowCol)
{
	NewMatrix(rowCol, rowCol);
	for (int rowIndex = 0; rowIndex < thisRows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < thisCols; columnIndex++)
		{
			if (rowIndex == columnIndex)
			{
				SetValueAtLocation(rowIndex, columnIndex, 1.0f);
			}
			else
			{
				SetValueAtLocation(rowIndex, columnIndex, 0.0f);
			}
		}
	}
	return this;
}

Matrix* Matrix::Random(int rowCol)
{
	NewMatrix(rowCol, rowCol);
	for (int rowIndex = 0; rowIndex < thisRows; rowIndex++)
		for (int columnIndex = 0; columnIndex < thisCols; columnIndex++)
			SetValueAtLocation(rowIndex, columnIndex, (rowIndex * 100) + columnIndex);
			
	return this;
}

void Matrix::Clone(Matrix* matrixToCloneTo)
{
	matrixToCloneTo->Zeros(thisRows, thisCols);
	for(int rowIndex = 0; rowIndex < thisCols; rowIndex++)
        for(int columnIndex = 0; columnIndex < thisRows; columnIndex++)
			matrixToCloneTo->SetValueAtLocation(rowIndex, columnIndex, ItemAt(rowIndex, columnIndex));
}


int Matrix::Rows()
{
	return thisRows;
}

int Matrix::Columns()
{
	return thisCols;
}

double Matrix::ItemAt(int row, int col)
{
	return *(thisMatrix + (row * thisCols) + col);
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
		location[colIndex] = ItemAt(row, colIndex);
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
		location[rowIndex] = ItemAt(rowIndex, col);
	}
}

void Matrix::SetValueAtLocation(int row, int col, double value)
{
	*(thisMatrix + (row * thisCols) + col) = value;
}


void Matrix::Transpose()
{
	// switch the row/column value around
    Matrix temp;
	Clone(&temp);
			
    for(int rowIndex = 0; rowIndex < thisCols; rowIndex++)
        for(int columnIndex = 0; columnIndex < thisRows; columnIndex++)
			SetValueAtLocation(rowIndex, columnIndex, temp.ItemAt(columnIndex, rowIndex));
}

// Find the determinant of the current matrix. (Currently only for 2x2)
double Matrix::Determinant()
{
    double determinant = 0;
    if((thisRows == thisCols) && (thisRows < 3))
    {
        determinant = (ItemAt(0, 0) * ItemAt(1, 1)) - (ItemAt(1, 0) * ItemAt(0, 1));
    }
    else
    {
        Serial.println("Cannot find determinant. Matrix needs to be square.");
		return 0.0f;
    }

    return determinant;
}


Matrix* Matrix::Multiply(double value)
{
	Matrix* resultantMatrix = this;

    for (int matrix1Row = 0; matrix1Row < thisRows; matrix1Row++)
    {
        for (int matrix2Column = 0; matrix2Column < thisCols; matrix2Column++)
        {
            resultantMatrix->SetValueAtLocation(matrix1Row, matrix2Column,  ItemAt(matrix1Row, matrix2Column) * value);
        }
    }

    return resultantMatrix;
}

Matrix Matrix::Multiply(Matrix* matrix2)
{
	int matrix1Rows = Rows();
	int matrix2Cols = matrix2->Columns();
    Matrix resultantMatrix;
	resultantMatrix.NewMatrix(matrix1Rows, matrix2Cols);

	if(!(matrix1Rows && matrix2Cols))
	{
		Serial.println("Row and/or Col are empty");
		Matrix m1;
		return m1;
	}
	
    if (Columns() != matrix2->Rows())
    {
        Serial.println("Invalid matrices");
		Matrix m2;
		return m2;
    }
    else
    {
		double vector1[matrix1Rows] = {0};
		double vector2[matrix2Cols] = {0};
		
        for(int matrix1Row = 0; matrix1Row < matrix1Rows; matrix1Row++)
        {
			Row(vector1, matrix1Row);
            for(int matrix2Column = 0; matrix2Column < matrix2Cols; matrix2Column++)
            {
				Row(vector1, matrix1Row);
				matrix2->Column(vector2, matrix2Column);

                if(matrix1Rows != matrix2Cols)
                {
                    Serial.println("Vector lengths do not match.");
					Matrix m3;
					return m3;
                }

                double result = 0;
                for (int i = 0; i < matrix1Rows; i++)
                {
                    result += vector1[i] * vector2[i];
                }

                resultantMatrix.SetValueAtLocation(matrix1Row, matrix2Column, result);
            }
        }
    }

    return resultantMatrix;
}

void Matrix::PrintMatrix()
{
	for(int matrixRow = 0; matrixRow < thisRows; matrixRow++)
	{
		for(int matrixCol = 0; matrixCol < thisCols; matrixCol++)
		{
			Serial.print(ItemAt(matrixRow, matrixCol));
			Serial.print('\t');
		}
		Serial.println();
	}
	Serial.println();
}
