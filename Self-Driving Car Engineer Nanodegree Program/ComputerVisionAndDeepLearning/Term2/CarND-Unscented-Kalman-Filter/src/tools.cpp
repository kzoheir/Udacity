#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  // Calculate the RMSE here.
  VectorXd rmse(4);
  rmse << 0,0,0,0;

  if(estimations.size() != ground_truth.size() || estimations.size() == 0){
    cout << "Invalid estimation / ground_truth data" << endl;
    return rmse;
  }

  // accumulate squared residuals
  for(int i=0; i < estimations.size(); i++){
    VectorXd residual = estimations[i] - ground_truth[i];
    residual = residual.array()*residual.array();
    rmse += residual;
  }

  // calculate mean
  rmse = rmse/estimations.size();

  // calculate square-root
  rmse = rmse.array().sqrt();

  return rmse;
}


double Tools::CalculeNIS(const VectorXd &z_diff, const MatrixXd &S_inverse){

  double epislon = 0;
  //compute error
  epislon = z_diff.transpose() * S_inverse * z_diff;

  return epislon;
}
