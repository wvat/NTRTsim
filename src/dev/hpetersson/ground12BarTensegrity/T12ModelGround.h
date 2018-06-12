/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

#ifndef T12_MODEL_H
#define T12_MODEL_H

/**
 * @file T12ModelGround.h
 * @brief Contains the definition of class T12ModelGround, using multiple springs.
 * $Id$
 */

// This library
#include "core/tgModel.h"
#include "core/tgSubject.h"
// The C++ Standard Library
#include <vector>

// Forward declarations
class tgBasicActuator;
class tgModelVisitor;
class tgStructure;
class tgWorld;

/**
 * Class that creates the six strut "superball" model using tgcreator
 */
class T12ModelGround : public tgSubject<T12ModelGround>, public tgModel
{
public: 
	
	/**
     * The only constructor. Utilizes default constructor of tgModel
     * Configuration parameters are within the .cpp file in this case,
     * not passed in. 
     */
    T12ModelGround();
	
    /**
     * Destructor. Deletes controllers, if any were added during setup.
     * Teardown handles everything else.
     */
    virtual ~T12ModelGround();
    
    /**
     * Create the model. Place the rods and strings into the world
     * that is passed into the simulation. This is triggered
     * automatically when the model is added to the simulation, when
     * tgModel::setup(world) is called (if this model is a child),
     * and when reset is called. Also notifies controllers of setup.
     * @param[in] world - the world we're building into
     */
    virtual void setup(tgWorld& world);
    
    /**
     * Undoes setup. Deletes child models. Called automatically on
     * reset and end of simulation. Notifies controllers of teardown
     */
    void teardown();
    
    /**
     * Step the model, its children. Notifies controllers of step.
     * @param[in] dt, the timestep. Must be positive.
     */
    virtual void step(double dt);
	
    /**
     * Receives a tgModelVisitor and dispatches itself into the
     * visitor's "render" function. This model will go to the default
     * tgModel function, which does nothing.
     * @param[in] r - a tgModelVisitor which will pass this model back
     * to itself 
     */
    virtual void onVisit(tgModelVisitor& r);

   /**
    * Returns the center of mass of this model as an <x,y,z>
    */
    std::vector<double> getBallCOM();
    
   /**
    * Returns the center of mass of given rod as an <x,y,z>
    */
    std::vector<double> getRodCOM(int rodIndex);

   /**
    * Returns the position vector relative to the origin for a node as an <x,y,z>
    * Outputs: result[0] = node 1 x
    * Outputs: result[1] = node 1 y
    * Outputs: result[2] = node 1 z
    * Outputs: result[3] = node 2 x
    * Outputs: result[4] = node 2 y
    * Outputs: result[5] = node 2 z
    */
    std::vector<double> getNodePosition(int rodIndex);

    /**
     * Return a vector of all muscles for the controllers to work with.
     * @return A vector of all of the muscles
     */
    const std::vector<tgBasicActuator*>& getAllMuscles() const;
    
    /**
     * Return a vector of passive muscles for the controllers to work with.
     * @return A vector of all of the muscles
     */
    const std::vector<tgBasicActuator*>& getPassiveMuscles() const;

    /**
     * Return a vector of active muscles for the controllers to work with.
     * @return A vector of all of the muscles
     */
    const std::vector<tgBasicActuator*>& getActiveMuscles() const;

    /**
     * Return a const of the ratio of spring constants for active and passive
     * muscles for the controllers to work with.
     * @return A vector of all of the muscles
     */
    virtual const double muscleRatio();

private:
	
    /**
     * A function called during setup that determines the positions of
     * the nodes based on construction parameters. Rewrite this function
     * for your own models
     * @param[in] tetra: A tgStructure that we're building into
     */
    static void addNodes(tgStructure& s);
	
    /**
     * A function called during setup that creates rods from the
     * relevant nodes. Rewrite this function for your own models.
     * @param[in] s A tgStructure that we're building into
     */
    static void addRods(tgStructure& s);
	
    /**
     * A function called during setup that creates muscles (Strings) from
     * the relevant nodes. Rewrite this function for your own models.
     * @param[in] s A tgStructure that we're building into
     */
    static void addMuscles(tgStructure& s);

private:
	
    /**
     * A list of all of the muscles. Will be empty until most of the way
     * through setup
     */
    std::vector<tgBasicActuator*> allMuscles;

    /**
     * A list of passively actuated muscles. Will be empty until most of the way
     * through setup
     */
    std::vector<tgBasicActuator*> passiveMuscles;

    /**
     * A list of passively actuated muscles. Will be empty until most of the way
     * through setup
     */
    std::vector<tgBasicActuator*> activeMuscles;
};

#endif  // T12_MODEL_H