/*!
 * \file log.cpp
 * \brief Set up logging.
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
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */
#define BOOST_LOG_DYN_LINK 1
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions/attr.hpp>

namespace genesis {

using namespace boost::log;

void init_logging () {
    boost::shared_ptr<sinks::synchronous_sink<sinks::text_ostream_backend> >
       sink = add_console_log();
#ifndef GENESIS_DEBUG
    sink->set_filter(boost::log::expressions::attr<int>("Severity") >= 4);
#endif
    sink->locked_backend ()->auto_flush (true);
    add_file_log ("genesis.log");
    add_common_attributes ();
}

}