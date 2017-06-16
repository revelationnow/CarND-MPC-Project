#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

class MPC {
 public:
  MPC()
  {
    prev_delta = 0;
    prev_acc = 0;
  }

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
  vector<double> pred_x;
  vector<double> pred_y;
  double prev_delta;
  double prev_acc;
};

#endif /* MPC_H */
