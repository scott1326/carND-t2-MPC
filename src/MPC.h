#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

// add this for command line usage
// and ease of change
struct Params {
    public:
  static double cte_wt;
  static double epsi_wt;
  static double v_wt;

  static double delta_wt;
  static double accel_wt;

  static double delta_diff_wt;
  static double accel_diff_wt;

  static double ref_v;
};

class MPC {
 public:
  MPC();

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
