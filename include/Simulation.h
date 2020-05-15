//
//
#include "Parameters.h"

#include "Population.h"
#include "Domain.h"
#include "Dynamics.h"
#include "Interaction.h"
#include "Particle.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>


#ifndef CAPMD_SIMULATION_H
#define CAPMD_SIMULATION_H


// We tie it all together in the simulation
class Simulation : virtual public Particle{

    private:
        Parameters params;

    public:

        std::vector<Particle> particles;
        std::vector<std::list<int>> neighbours;

        // As container, has the different sub-pieces
        Domain domain;
        Population population;
        Dynamics dynamics;
        Interaction interaction;

        // Members (taken from parameters but included incase changing through python script)
        // Number of particles
        int N;
        // Neighbour list (cutoff) and contact cutoff range (cutoffZ)
        double cutoff, cutoffZ;
        // time step
        double dt;
        // neighbour list total move threshold (should be of the order of 0.5)
        double maxmove;
        // running counter on particle flags
        int currentflag;

        // Constructors:
        Simulation();
        void initSimulation(Domain domain,Population population, Parameters params);

        // Methods to initialise the system, including creating the particle vector and the first NeighbourList
        void initialise();
        void initPopulation(); // Just to initialise a population

        // Methods for particle dynamics
        void move(void);
        void populationDynamics(int);

        // Methods for getting sim data
        int popSize(void){ return particles.size();}
        Particle getParticle(int);
        std::list<int> getNeighbours(Particle);
        std::vector<std::vector<double>> getPopulationPosition(std::list<int> &index);
        std::vector<double> getPopulationRadius(std::list<int> &index);

        //  I/O for sim data
        void savePopulation(std::string);
        void loadPopulation(std::string);
};


#endif //CAPMD_SIMULATION_H