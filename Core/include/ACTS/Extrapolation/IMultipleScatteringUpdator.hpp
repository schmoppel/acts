// This file is part of the ACTS project.
//
// Copyright (C) 2016 ACTS project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// IMultipleScatteringUpdator.h, ACTS project
///////////////////////////////////////////////////////////////////

#ifndef ACTS_EXTRAPOLATIONINTERFACES_IMULTIPLESCATTERINGUPDATOR_H
#define ACTS_EXTRAPOLATIONINTERFACES_IMULTIPLESCATTERINGUPDATOR_H 1

#include "ACTS/EventData/ParticleDefinitions.hpp"

namespace Acts {

  class MaterialProperties;
   
  /**@class IMultipleScatteringUpdator
     Interface class IMultipleScatteringUpdator
     
     @author Andreas.Salzburger@cern.ch
    */
  class IMultipleScatteringUpdator {
      
     public:
       /**Virtual destructor*/
       virtual ~IMultipleScatteringUpdator(){}
       
       
      /** Calculate the sigma on theta introduced by multiple scatteringt */
      virtual double sigmaSquare(const MaterialProperties& mat,
                                 double p,
                                 double pathcorrection,
                                 ParticleType particle=pion,
                                 double deltaE=0.) const = 0;  
  };


} // end of namespace

#endif // ACTS_EXTRAPOLATIONINTERFACES_IMULTIPLESCATTERINGUPDATOR_H
