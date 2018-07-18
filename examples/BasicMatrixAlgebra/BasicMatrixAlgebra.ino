#include <MatrixLibrary.h>

Matrix myMatrix;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.println("myMatrix:");
  myMatrix.Eye(3);
//  myMatrix.Math(Matrix::MULTIPLY, 3);
  myMatrix.PrintMatrix();

  Serial.println("Standard:");
  Matrix standard;
  standard.NewMatrix(3, 3);
  standard.SetValueAt(0,0,1);
  standard.SetValueAt(0,1,2);
  standard.SetValueAt(0,2,3);
  standard.SetValueAt(1,0,4);
  standard.SetValueAt(1,1,5);
  standard.SetValueAt(1,2,6);
  standard.SetValueAt(2,0,7);
  standard.SetValueAt(2,1,8);
  standard.SetValueAt(2,2,9);
  standard.PrintMatrix();

  Serial.println("Standard':");
  standard.Transpose();
  standard.PrintMatrix();

  Serial.println("myMatrix * standard':");
  Matrix mult = myMatrix.Math(Matrix::MULTIPLY, &standard);
  mult.PrintMatrix();

  Serial.println("myMatrix + standard':");
  Matrix addition = myMatrix.Math(Matrix::ADD, &standard);
  addition.PrintMatrix();

  Serial.println("standard' - myMatrix:");
  Matrix subtract = standard.Math(Matrix::SUBTRACT, &myMatrix);
  subtract.PrintMatrix();

  Serial.println("standard' - standard':");
  Matrix subtract2 = standard.Math(Matrix::SUBTRACT, &standard);
  subtract2.PrintMatrix();
}

void loop() {
  // put your main code here, to run repeatedly:

}
