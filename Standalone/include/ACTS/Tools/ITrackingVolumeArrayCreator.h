///////////////////////////////////////////////////////////////////
// ITrackingVolumeArrayCreator.h, ACTS project
///////////////////////////////////////////////////////////////////

#ifndef ACTS_GEOMETRYINTERFACES_ITRACKINGVOLUMEARRAYCREATOR_H
#define ACTS_GEOMETRYINTERFACES_ITRACKINGVOLUMEARRAYCREATOR_H 1

// Geometry module
#include "ACTS/GeometryUtils/BinnedArray.h"
#include "ACTS/GeometryUtils/BinningType.h"
// STL
#include <vector>
#include <memory>

namespace Acts
{
  /** forward declarations*/
  class TrackingVolume;
  typedef std::shared_ptr< const TrackingVolume > TrackingVolumePtr;

  /** @typedef TrackingVolumeArray */
  typedef BinnedArray< TrackingVolumePtr > TrackingVolumeArray;
  typedef std::vector< TrackingVolumePtr > TrackingVolumeVector;
  
  /** @class ITrackingVolumeArrayCreator
    
    Interface class ITrackingVolumeArrayCreators It inherits from IAlgTool. 
    
    It is designed to centralize the code to create
    Arrays of Tracking Volumes for both:
  
      - confinement in another TrackingVolume
      - navigation and glueing
  
    Arrays for glueing and confinement are often the same, 
    therefore the newly created TrackingVolumeArray is done by a shared_ptr

    @author Andreas.Salzburger@cern.ch
    */
  class ITrackingVolumeArrayCreator
  {  
    public:
      /**Virtual destructor*/
    virtual ~ITrackingVolumeArrayCreator() = default;

    /** TrackingVolumeArrayCreator interface method - creates array depending on the binning type */
    virtual std::shared_ptr<const TrackingVolumeArray> trackingVolumeArray(const TrackingVolumeVector& vols, BinningValue bVal) const = 0;      
  };
} // end of namespace

#endif

