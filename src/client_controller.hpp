/*!
 * \file client_controller.hpp
 * \brief Defines the interface for designating rovers and base station
 *   connections.
 * \author Anthony Arnold, 2015. anthony.arnold(at)uqconnect.edu.au
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) Anthony Arnold 2015
 *
 * Genesis is a realtime multi-station GNSS receiver.
 *
 * This file is part of Genesis.
 *
 * Genesis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Genesis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Genesis. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */
#pragma once
#ifndef GENESIS_CLIENT_CONTROLLER_HPP
#define GENESIS_CLIENT_CONTROLLER_HPP

#include <boost/move/core.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>
#include "concurrent_dictionary.h"
#include "gnss_sdr_data.h"
#include "gps_ref_time.h"
#include <vector>

namespace genesis {

class station;

/*!
 * \brief This class keeps track of which clients are connected
 *  and what kind of client they are.
 */
class client_controller {
public:
   typedef boost::system::error_condition error_type;
   typedef concurrent_dictionary <Gps_Ref_Time> ref_time_map;
   typedef boost::shared_ptr<ref_time_map> ref_time_ptr;
   typedef std::vector<gnss_sdr_data> observable_vector;
private:
   BOOST_MOVABLE_BUT_NOT_COPYABLE (client_controller)

public:
   client_controller ();
   ~client_controller ();

   error_type add_station (const station &st);

   error_type remove_station (const station &st);

   bool has_base () const;

   error_type reset_base ();

   ref_time_ptr base_ref_time () const;

   observable_vector base_observables () const;

   void set_base_observables (observable_vector v);

private:
   struct impl;
   boost::shared_ptr <impl> impl_;
};

}

#endif // GENESIS_CLIENT_CONTROLLER_HPP
