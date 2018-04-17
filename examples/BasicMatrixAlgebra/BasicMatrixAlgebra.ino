#include <MatrixLibrary.h>

Matrix myMatrix;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  myMatrix.Eye(3);
//  myMatrix.Multiply(3);
  myMatrix.PrintMatrix();

  Matrix standard;
  standard.NewMatrix(3, 3);
  standard.SetValueAtLocation(0,0,1);
  standard.SetValueAtLocation(0,1,2);
  standard.SetValueAtLocation(0,2,3);
  standard.SetValueAtLocation(1,0,4);
  standard.SetValueAtLocation(1,1,5);
  standard.SetValueAtLocation(1,2,6);
  standard.SetValueAtLocation(2,0,7);
  standard.SetValueAtLocation(2,1,8);
  standard.SetValueAtLocation(2,2,9);
  standard.PrintMatrix();
  
  standard.Transpose();
  standard.PrintMatrix();
  
  Matrix mult = myMatrix.Multiply(&standard);
  mult.PrintMatrix();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
