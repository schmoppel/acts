// This file is part of the Acts project.
//
// Copyright (C) 2016-2018 Acts project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// ParticleDefinitions.h, Acts project
///////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include "Acts/Utilities/Definitions.hpp"
#include "Acts/Utilities/Units.hpp"

// barcodes
typedef unsigned long barcode_type;
typedef int           process_type;
typedef int           pdg_type;

// define the particle hypotheses
#define PARTICLETYPES 11

namespace Acts {

/// @enum ParticleType
///
/// Enumeration for Particle type respecting
/// the interaction with the material
///
enum ParticleType {

  nonInteracting = 0,  //!< for non-interacting extrapolation
  electron  = 1,  //!< reconstruction + fatras : type as electron hypothesis
  muon      = 2,  //!< reconstruction + fatras : type as muon hypothesis
  pion      = 3,  //!< reconstruction + fatras : type as pion hypothesis
  kaon      = 4,  //!< reconstruction + fatras : type as kaon hypothesis
  proton    = 5,  //!< reconstruction + fatras : type as proton hypothesis
  photon    = 6,  //!< for fatras usage
  neutron   = 7,  //!< for fatras usage
  pi0       = 8,  //!< for fatras usage
  k0        = 9,  //!< for fatras usage
  undefined = 99
};

// Helper functions

/// Convert to ParticleType from pdg
/// @param[in] pdg The pdg type
/// @param[out] stable Output if the particle is stable
/// @param[out] exiting Output if the particle is exiting
/// @param[in] charge The charge of the particle
ParticleType
convertToParticleType(pdg_type pdg, bool& stable, bool& exiting, double charge);

/// convert to pdg from ParticleType
/// @param[in] particleHypo The Acts particle type
/// @param[in] charge The charge of the particle
/// @param[in] dist @todo find out
int
convertToPdg(ParticleType particleHypo, double charge, bool dist);

/// @struct ParticleMasses
/// Mass declaration of particles covered
/// in the ParticleType.
/// Masses are given in MeV and taken from:
///
/// Review of Particle Physics (2010)
/// K. Nakamura et al. (Particle Data Group), J. Phys. G 37, 075021 (2010)
///
struct ParticleMasses
{
  /// the vector of masses - in MeV
  std::vector<double> mass;

  /// Default constructor
  ParticleMasses()
  {
    mass.reserve(PARTICLETYPES);

    mass.push_back(0.);                        // non interacting mass
    mass.push_back(0.51099891 * units::_MeV);  // electron mass
    mass.push_back(105.658367 * units::_MeV);  // muon mass
    mass.push_back(139.57018 * units::_MeV);   // charged pion mass
    mass.push_back(493.677 * units::_MeV);     // kaon mass
    mass.push_back(938.272013 * units::_MeV);  // proton mass
    mass.push_back(0. * units::_MeV);          // photon rest mass
    mass.push_back(939.565346 * units::_MeV);  // neutron rest mass
    mass.push_back(134.9766 * units::_MeV);    // pi0 rest mass
    mass.push_back(497.614 * units::_MeV);     // K0 rest mass
    mass.push_back(105.658367 * units::_MeV);  // muon mass
  }
};

/// @class ParticleProperties
///
/// very simplistic class for particle properties,
/// in order to be used for association in tracking
/// this is not designed for physics analyses
class ParticleProperties
{
public:
  /// constructor with arguments, describes the
  /// particle properties at any given vertex
  /// - needs to be attached to a vertex
  /// @param [in] momentum particle momentum at the vertex
  /// @param [in] mass the particle mass
  /// @param [in] charge is the particle charge
  /// @param [in] pID is the PDG code
  /// @param [in] barcode is the unique particle identification
  ParticleProperties(const Vector3D& momentum,
                     double          mass    = 0.,
                     double          charge  = 0.,
                     pdg_type        pID     = 0.,
                     barcode_type    barcode = 0)
    : m_momentum(momentum)
    , m_mass(mass)
    , m_charge(charge)
    , m_pdgID(pID)
    , m_barcode(barcode)
  {
  }

  /// copy constructor
  /// @param [in] pProperties are the source properties
  ParticleProperties(const ParticleProperties& pProperties)
    : m_momentum(pProperties.m_momentum)
    , m_mass(pProperties.m_mass)
    , m_charge(pProperties.m_charge)
    , m_pdgID(pProperties.m_pdgID)
    , m_barcode(pProperties.m_barcode)
  {
  }

  /// Destructor
  ~ParticleProperties() = default;

  /// Assignment operator
  /// @param [in] pProperties are the source properties
  ParticleProperties&
  operator=(const ParticleProperties& pProperties)
  {
    if (this != &pProperties) {
      m_momentum = pProperties.m_momentum;
      m_mass     = pProperties.m_mass;
      m_charge   = pProperties.m_charge;
      m_pdgID    = pProperties.m_pdgID;
      m_barcode  = pProperties.m_barcode;
    }
    return (*this);
  }

  /// assign the barcode
  /// @param barcode is the unique barcode
  void
  assign(barcode_type barcode)
  {
    m_barcode = barcode;
  }

  /// return the momentum
  const Vector3D&
  momentum() const
  {
    return m_momentum;
  }

  /// return the mass
  double
  mass() const
  {
    return m_mass;
  }

  /// return the charge
  double
  charge() const
  {
    return m_charge;
  }

  /// return the particle ID
  pdg_type
  pdgID() const
  {
    return m_pdgID;
  }

  /// return the particle barcode
  barcode_type
  barcode() const
  {
    return m_barcode;
  }

private:
  Vector3D     m_momentum;
  double       m_mass;
  double       m_charge;
  pdg_type     m_pdgID;
  barcode_type m_barcode;
};

/// @class ProcessVertex
///
/// process vertex class to hold minimal information for
/// fast track simulation and reconstruction development
class ProcessVertex
{
public:
  /// constructor with arguments
  /// @param [in] pVertex is the process vertex
  /// @param [in] pTime is the associated time stamp
  /// @param [in] pType is the process type of this vertex
  /// @param [in] pIncoming is(are) the incoming particles
  /// @param [in] pOutgoing is(are) the outgoing particles
  ProcessVertex(const Vector3D&                        pVertex,
                double                                 pTime,
                process_type                           pType,
                const std::vector<ParticleProperties>& pIncoming,
                const std::vector<ParticleProperties>& pOutgoing)
    : m_vertex(pVertex)
    , m_time(pTime)
    , m_type(pType)
    , m_incoming(pIncoming)
    , m_outgoing(pOutgoing)
  {
  }

  /// destructor
  ~ProcessVertex() {}

  /// shift the vertex
  // @param [in] shit is an applied shift
  void
  shift(const Vector3D& shift);

  /// Add a particle to incoming
  void
  addIncoming(const ParticleProperties& pProperties);

  /// Add a particle to outgoing
  void
  addOutgoing(const ParticleProperties& pProperties);

  /// Return the actual position
  const Vector3D&
  position() const;

  /// Return the time of production
  double
  interactionTime() const
  {
    return m_time;
  }

  /// Return the type of production
  process_type
  processType() const
  {
    return m_type;
  }

  /// Return the incoming particles
  const std::vector<ParticleProperties>&
  incomingParticles() const
  {
    return m_incoming;
  }
  /// Return the outgoing particles
  const std::vector<ParticleProperties>&
  out() const
  {
    return m_outgoing;
  }

private:
  Vector3D                        m_vertex;
  double                          m_time;
  process_type                    m_type;
  std::vector<ParticleProperties> m_incoming;
  std::vector<ParticleProperties> m_outgoing;
};

inline const Vector3D&
ProcessVertex::position() const
{
  return m_vertex;
}

inline void
ProcessVertex::shift(const Vector3D& shift)
{
  m_vertex += shift;
}

inline void
ProcessVertex::addIncoming(const ParticleProperties& pProperties)
{
  m_incoming.push_back(pProperties);
}

inline void
ProcessVertex::addOutgoing(const ParticleProperties& pProperties)
{
  m_outgoing.push_back(pProperties);
}

}  // namespace Acts
