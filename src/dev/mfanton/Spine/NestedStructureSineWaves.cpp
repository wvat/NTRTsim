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

/**
 * @file NestedStructureSineWaves.cpp
 * @brief Contains the implementation of class NestedStructureSineWaves
 * @author Brian Tietz
 * @version 1.0.0
 * $Id$
 */

// This module
#include "NestedStructureSineWaves.h"

// Its subject
#include "NestedStructureTestModel.h"

// NTRTSim
#include "core/tgLinearString.h"
#include "core/ImpedanceControl.h"
#include "tgcreator/tgUtil.h"

NestedStructureSineWaves::NestedStructureSineWaves() :
    in_controller(new ImpedanceControl(300, 0, 0)),
    out_controller(new ImpedanceControl(100, 200, 400)),
    segments(1.0),
    insideLength(20.0),
    outsideLength(15.0),
    offsetSpeed(0.0),
    cpgAmplitude(20.0),
    cpgFrequency(2.51),
    bodyWaves(1.0),
    simTime(0.0),
    cycle(0.0),
    target(0.0)
{
    phaseOffsets.clear();
    phaseOffsets.push_back(M_PI/2);
    phaseOffsets.push_back(0);
    phaseOffsets.push_back(0);
}

NestedStructureSineWaves::~NestedStructureSineWaves()
{
	delete in_controller;
	delete out_controller;
}

void NestedStructureSineWaves::applyImpedanceControlInside(const std::vector<tgLinearString*> stringList, double dt)
{
    for(std::size_t i = 0; i < stringList.size(); i++)
    {
        double setTension = in_controller->control(stringList[i],
                                            dt,
                                            insideLength
                                            );
        #if (0) // Conditional compile for verbose control
        std::cout << "Inside String " << i << " tension " << setTension
        << " act tension " << stringList[i]->getMuscle()->getTension()
        << " length " << stringList[i]->getMuscle()->getActualLength() << std::endl;
        #endif
    }    
}

void NestedStructureSineWaves::applyImpedanceControlOutside(const std::vector<tgLinearString*> stringList,
                                                            double dt,
                                                            std::size_t phase)
{
    for(std::size_t i = 0; i < stringList.size(); i++)
    {
        cycle = sin(simTime * cpgFrequency + 2 * bodyWaves * M_PI * i / (segments) + phaseOffsets[phase]);
        target = offsetSpeed + cycle*cpgAmplitude;
        
        double setTension = out_controller->control(stringList[i],
                                            dt,
                                            outsideLength,
                                            target
                                            );
        #if(0) // Conditional compile for verbose control
        std::cout << "Outside String " << i << " com tension " << setTension
        << " act tension " << stringList[i]->getMuscle()->getTension()
        << " length " << stringList[i]->getMuscle()->getActualLength() << std::endl;
        #endif
    }    
}

void NestedStructureSineWaves::onStep(NestedStructureTestModel& subject, double dt)
{
    simTime += dt;
    
    segments = subject.getSegments();
    
    applyImpedanceControlInside(subject.getMuscles("inner top"), dt);
    applyImpedanceControlInside(subject.getMuscles("inner left") , dt);
    applyImpedanceControlInside(subject.getMuscles("inner right"), dt);
    
    applyImpedanceControlOutside(subject.getMuscles("inner top"), dt, 0);
    applyImpedanceControlOutside(subject.getMuscles("inner left"), dt, 1);
    applyImpedanceControlOutside(subject.getMuscles("inner right"), dt, 2);
}
    

