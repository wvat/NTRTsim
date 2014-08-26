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


#ifndef TG_WORLDBULLETPHYSICSIMPL_H
#define TG_WORLDBULLETPHYSICSIMPL_H

/**
 * @file tgWorldBulletPhysicsImpl.h
 * @brief Contains the definition of class tgWorldBulletPhysicsImpl
 * @author Lee Brownston
 * $Id$
 */

// This application
#include "tgWorld.h"
#include "tgWorldImpl.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"

// Forward declarations
class btCollisionShape;
class btSoftRigidDynamicsWorld;
class btRigidBody;
class IntermediateBuildProducts;
class tgBulletGround;

/**
 * Concrete class derived from tgWorldImpl for Bullet Physics
 * implementations.
 */
class tgWorldBulletPhysicsImpl : public tgWorldImpl
{
 public:

  /** 
   * The only constructor.
   * @param[in] gravity the gravitational acceleration in m/sec^2
   */
  tgWorldBulletPhysicsImpl(const tgWorld::Config& config,
                            tgBulletGround* ground);

  /** Clean up Bullet Physics state. */
  ~tgWorldBulletPhysicsImpl();

  /**
   * Advance the simulation.
   * @param[in] dt the number of seconds since the previous call;
   * must be positive
   */
  virtual void step(double dt);

  /**
   * Return a reference to the dynamics world.
   * @return a reference to the dynamics world
   */
  btSoftRigidDynamicsWorld& dynamicsWorld() const
  {
    return *m_pDynamicsWorld;
  }
  
        /**
     * Add a btCollisionShape the a collection for deletion upon
     * destruction.
     * @param[in] pShape a pointer to a btCollisionShape; do nothing if NULL
     */
        void addCollisionShape(btCollisionShape* pShape);

 private:
    
        /**
     * Create a new dynamics world. Needs to be in the namespace so we
     * can free the pointers it creates.
     * @return the newly-created btSoftRigidDynamicsWorld
     */
        btSoftRigidDynamicsWorld* createDynamicsWorld() const;
    
    /**
     * Create the ground - needs to be in the namespace so we can
     * free the pointers it creates
     */
    btRigidBody* createGroundRigidBody();
    btRigidBody* createBoxRigidBody(btVector3 boxDimensions, btVector3 Origin);
    btRigidBody* createInvisibleBox(btVector3 boxDimensions, btVector3 Origin);
//    btRigidBody* createSphereRigidBody();
    
    
    /** Integrity predicate. */
    bool invariant() const;

 private:
    
    /** Used to build the btSoftRigidDynamicsWorld. */
    IntermediateBuildProducts * const m_pIntermediateBuildProducts;
    
    /** The Bullet Physics representation of the tgWorld. */
    btSoftRigidDynamicsWorld* m_pDynamicsWorld;
    
    /* 
     * A vector of collision shapes for easy reference. Does not affect
     * physics or rendering unles the shape is placed into the dynamics
     * world. Bullet encourages reuse of collision shapes when possible
     * for efficiency.
     */
    btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
};

#endif  // TG_WORLDBULLETPHYSICSIMPL_H
