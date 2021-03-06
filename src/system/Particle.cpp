
//
#include <iostream>
#include <fstream>
#include <Particle.h>
#include <iomanip>      // std::setprecision

// Particle constructor
Particle::Particle(int pid, int ptype, std::vector<double> px, double ptheta, double pr)
{
    age = 0;
    force = {0,0};
    id = pid;
    type = ptype;
    position = px;
    theta = ptheta;
    radius = pr;
    numneigh = 0;

    std::cout << "Particle " << pid <<" Initialised" << std::endl;
}

Particle::Particle(const Particle & rhs)
{
    this->setId(rhs.getId());
    std::cout << "particle copied " << std::endl;
    age = rhs.age;
    force = rhs.force;
    type = rhs.type;
    position = rhs.position;
    theta = rhs.theta;
    radius = rhs.radius;
    numneigh = rhs.numneigh;
}

Particle::~Particle(){
//    delete this;
}

std::ostream& operator<<(std::ostream& out,const Particle& p)
{
    return out << p.getId() << '\t' << p.type << '\t' << p.age << '\t' << std::setprecision(4)
                << p.position[0]<< '\t' << std::setprecision(4) << p.position[1] <<  '\t' << std::setprecision(4)
                << p.theta << '\t' << std::setprecision(4) << p.radius << std::endl;
}

std::istream& operator>>(std::istream &in, const Particle &p)
{
    int id;
    std::vector<std::string> tmpProperties;
    std::string token;

    return in;
}
