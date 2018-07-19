#include <MatrixLibrary.h>

Matrix eye;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.println("eye:");
  eye.Eye(3);
//  eye.Math(Matrix::MULTIPLY, 3);
  eye.PrintMatrix();

  Serial.println("DET(eye):");
  Serial.println(eye.FindDeterminant());
  Serial.println();

  eye.PrintMatrix();

  Serial.println("myMatrix:");
  Matrix myMatrix;
  myMatrix.NewMatrix(3, 3);
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
  Serial.println(myMatrix.FindDeterminant());
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
  
  Serial.println("myMatrixTranspose:");
  Matrix myMatrixTranspose = myMatrix.Transpose();
  myMatrixTranspose.PrintMatrix();
}

void loop() {
  // put your main code here, to run repeatedly:

}
