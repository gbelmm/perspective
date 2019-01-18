/******************************************************************************
 *
 * Copyright (c) 2019, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */

#define BOOST_NO_EXCEPTIONS
#define BOOST_EXCEPTION_DISABLE

#include <sstream>
#include <perspective/first.h>
#include <perspective/date_parser.h>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace pt = boost::posix_time;

namespace boost {
void
throw_exception(std::exception const& e) {
    std::cout << e.what() << std::endl;
}
}

namespace perspective {

const std::string t_date_parser::VALID_FORMATS[12] = {
    "%Y%m%dT%H%M%S%F%q", // ISO
    "%Y-%m-%dT%H:%M:%S:%f",
    "%Y-%m-%dT%H:%M:%S:%fZ",
    "%Y-%m-%d %H:%M:%S%F%Q", // ISO extended
    "%A, %d %b %Y %k:%M:%S %q", // RFC 0822
    "%Y-%m-%d\\%H:%M:%S%F"
    "%m-%d-%Y",
    "%m/%d/%Y",
    "%m-%d-%Y",
    "%m %d %Y",
    "%m/%d/%Y",
    "%m/%d/%y",
    "%d %m %Y"
};

t_date_parser::t_date_parser() {
    for (const std::string &fmt : VALID_FORMATS) {
        std::locale new_locale = std::locale(std::locale::classic(), new pt::time_input_facet(fmt));
        locales.push_back(new_locale);
    }
}

bool 
t_date_parser::is_valid(std::string const& datestring) {
    for (const auto &locale : locales) {
        pt::ptime time_obj;
        std::stringstream ss(datestring);
        ss.imbue(locale);
        bool is_date_time = static_cast<bool>(ss >> time_obj);
        if (is_date_time) {
            std::cout << "true" << std::endl;
            return true;
        } else {
            std::cout << "false" << std::endl;
            continue;
        }
    }
    return false;
}
} // end namespace perspective