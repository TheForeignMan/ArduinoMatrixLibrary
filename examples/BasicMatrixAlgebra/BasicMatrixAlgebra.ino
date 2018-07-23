/*
  BasicMatrixAlgebra

  This example sketch gives a brief overview of the capabilities
  of the MatrixLibrary.

  Hardware required:
  - Any Arduino

  Created 19 July 2018
  By Thomas Bartlet
  Modified 21 July 2018
  By Thomas Bartleet

  http://www.github.com/TheForeignMan

*/

#include <MatrixLibrary.h>

Matrix eye(3, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.println("eye:");
  eye.Eye(3);
  Matrix eye3 = eye.Math(Matrix::MULTIPLY, 3);
  eye.PrintMatrix();

  Serial.println("DET(eye):");
  Serial.println(eye.Determinant());
  Serial.println();

  Serial.println("myMatrix:");
  Matrix myMatrix(3, 3);
  myMatrix.SetValueAt(0,0,1);
  myMatrix.SetValueAt(0,1,2);
  myMatrix.SetValueAt(0,2,3);
  myMatrix.SetValueAt(1,0,4);
  myMatrix.SetValueAt(1,1,5);
  myMatrix.SetValueAt(1,2,6);
  myMatrix.SetValueAt(2,0,7);
  myMatrix.SetValueAt(2,1,8);
  myMatrix.SetValueAt(2,2,10);
  myMatrix.PrintMatrix();

  Serial.println("DET(myMatrix):");
  Serial.println(myMatrix.Determinant());
  Serial.println();

  Serial.println("eye * myMatrix:");
  Matrix mult = eye.Math(Matrix::MULTIPLY, &myMatrix);
  mult.PrintMatrix();

  Serial.println("eye + myMatrix:");
  Matrix addition = eye.Math(Matrix::ADD, &myMatrix);
  addition.PrintMatrix();

  Serial.println("myMatrix - eye:");
  Matrix subtract = myMatrix.Math(Matrix::SUBTRACT, &eye);
  subtract.PrintMatrix();

  Serial.println("myMatrix - myMatrix:");
  Matrix subtract2 = myMatrix.Math(Matrix::SUBTRACT, &myMatrix);
  subtract2.PrintMatrix();

  Serial.println("myMatrix + 5:");
  Matrix addition2 = myMatrix.Math(Matrix::ADD, 5);
  addition2.PrintMatrix();
  
  Serial.println("myMatrixTranspose:");
  Matrix myMatrixTranspose = myMatrix.Transpose();
  myMatrixTranspose.PrintMatrix();

  Serial.println("myMatrixTranspose without row 1:");
  myMatrixTranspose.RemoveRow(1);
  myMatrixTranspose.PrintMatrix();

  Serial.println("myMatrixTranspose without col 1:");
  myMatrixTranspose.RemoveColumn(1);  
  myMatrixTranspose.PrintMatrix();

  Serial.println("eye3 Inverse:");
  Matrix myMatrixInverse = eye3.Inverse();
  myMatrixInverse.PrintMatrix();

  Serial.println("myMatrix * myMatrixInverse:");
  Matrix result = eye3.Math(Matrix::MULTIPLY, &myMatrixInverse);
  result.PrintMatrix();
  
  Serial.println("END");
}

void loop() {
  // put your main code here, to run repeatedly:

}
