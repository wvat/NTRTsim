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

#ifndef DUCTT_MECH_TEST_CONTROLLER_H
#define DUCTT_MECH_TEST_CONTROLLER_H

/**
 * @file DuCTTMechTestController.h
 * @brief Contains the definition of the class DuCTTMechTestController.
 * @author Alexander Xydes
 * $Id$
 */

// This library
#include "core/tgObserver.h"

// The Bullet Physics library
#include "LinearMath/btVector3.h"

// The C++ Standard Library
#include <vector>

// Forward declarations
class tgBasicActuator;
class tgBasicActuator;
class tgTouchSensorSphereModel;
class DuCTTRobotModel;
class tgImpedanceController;

class DuCTTMechTestController : public tgObserver<DuCTTRobotModel>
{
public:

    DuCTTMechTestController(double targetTime = -1, int testCase = 0, bool _freqSweep = false);
    
    virtual void onStep(DuCTTRobotModel& subject, double dt);
    
    /**
     * Applies the impedance controllers using a velocity setpoint determined.
     * by the phase parameter and
     * Called during this classes onStep function.
     * @param[in] stringList a std::vector of strings taken from the
     * subject's MuscleMap
     * @param[in] dt - a timestep. Must be positive.
     */
    double applyImpedanceControl(const std::vector<tgBasicActuator*> stringList,
                                    double dt, int phase);
    double applyImpedanceControl(tgBasicActuator* string, double dt, int phase);

private:
    double getCPGTarget(int phase);

    tgImpedanceController* in_controller;
    tgImpedanceController* impController;

    double simTime;
    double cycle;

    std::vector<double> phaseOffset;
    double offsetLength;
    double cpgAmplitude;
    double cpgFrequency;
    double bodyWaves;

    bool recordedStartCOM;
    btVector3 startCOM;

    bool startedFile;

    //for frequency sweeping test
    bool freqSweep;
    double timePerFreq;
    double freqTime;
    double maxFreq;

    double targetTime;
    double startTime;
    bool move;

    //0=all strings same sine, 1=upper vert opposite sines, 2=lower vert opposite sine
    int testCase;
};

#endif // PRETENSION_CONTROLLER_H