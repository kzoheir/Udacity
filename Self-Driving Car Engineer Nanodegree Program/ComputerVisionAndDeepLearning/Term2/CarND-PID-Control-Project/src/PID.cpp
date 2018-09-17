#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;
  
}

void PID::UpdateError(double cte) {
  /*
  * Updates error values for calculating total error below.
  */
  
  d_error = (cte - p_error);
  i_error += cte;
  p_error = cte;
  
}

double PID::TotalError(double cte, double speed, double angle) {
   std::cout << std::endl << " count: " << count << " cte: " << cte << " speed: " << speed << " angle: " << angle << " total error: " << (-Kp * p_error - Kd * d_error - Ki * i_error) << std::endl;
   std::cout << " Kp: " << Kp << " p_error: " << p_error << " Kd: " << Kd << " d_error: " << d_error << " Ki: " << Ki << " i_error: " << i_error << " total error: " << (-Kp * p_error - Kd * d_error - Ki * i_error) << std::endl;
  count ++;
  // Return the total error of each coefficient multiplied by the respective error
  return -Kp * p_error - Kd * d_error - Ki * i_error;
  
}

