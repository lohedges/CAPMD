#include "Dynamics.h"

#include <cmath>
#include <random>

#include <iostream>

#define _USE_MATH_DEFINES

Dynamics::Dynamics() {
    // set active parameters here
    factive = params.factive;
    zeta = params.zeta;
    tau = params.tau;
}

// move a particle according to the force law, and add active motion
void Dynamics::step(Particle &p, double dt) {
    ////TODO: Better upgrading of position is possible...

    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(2002);

    std::uniform_real_distribution<> rng(0.0, 1);

    // get particle posn
    std::vector<double> x = p.getPosition();

    // compute the active force, according to its current direction along a unit vector that makes an angle theta with the x-axis
    std::vector<double> unit = {cos(p.theta),sin(p.theta)};
    std::vector <double> factvector = {factive[p.type]*unit[0], factive[p.type]*unit[1]};

    // update the positions, according to Euler in the simplest approach
    // Why not something more sophisticated? The angular, stochastic, step is much more complex otherwise
    for (int i = 0; i<2; i++){
        x[i] += (factvector[i] + p.force[i])/zeta[p.type]*dt;
    }
    p.position = x;

    // update the angle. Here, in the simplest approach, there is no angular torque from either active or passive sources
    // note stochastic calculus: The rotational diffusion constant is 2/tau, but the noise strength is 2/tau*sqrt(dt)
    // multiply by random number chosen from a normal distribution with mean 0 and standard deviation 1
    p.theta += 2.0/tau[p.type]*sqrt(dt)*rng(gen);

    ////TODO: Check this
    /// more general form if some form of torque or alignment is present:
    //i.theta += alignmentTorque*dt + 2.0/tau[i.type]*sqrt(dt)*rng.normal(0,1);
}