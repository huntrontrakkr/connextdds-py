/*
 * (c) 2020 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software solely for use with RTI products.  The Software is
 * provided "as is", with no warranty of any type, including any warranty for
 * fitness for any purpose. RTI is under no obligation to maintain or support
 * the Software.  RTI shall not be liable for any incidental or consequential
 * damages arising out of the use or inability to use the software.
 */

#include "PyConnext.hpp"
#include <rti/core/status/Status.hpp>

using namespace rti::core::status;

namespace pyrti {

template<>
void init_class_defs(py::class_<EventCount32>& cls)
{
    cls.def_property_readonly("total", &EventCount32::total, "The total count.")
            .def_property_readonly(
                    "change",
                    &EventCount32::change,
                    "The incremental count.");
}

template<>
void process_inits<EventCount32>(py::module& m, ClassInitList& l)
{
    l.push_back([m]() mutable {
        return init_class<EventCount32>(m, "EventCount32");
    });
}

}  // namespace pyrti
