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
#include "PySeq.hpp"
#include <rti/core/policy/CorePolicy.hpp>
#include "PyVector.hpp"

using namespace rti::core;

namespace pyrti {

template<>
void init_class_defs(py::class_<EndpointGroup>& cls)
{
    cls.def(py::init<const std::string&, int32_t>(),
            py::arg("role_name"),
            py::arg("quorum_count"),
            "Create an EndpointGroup with the provided parameters.")
            .def_property(
                    "role_name",
                    (std::string(EndpointGroup::*)() const)
                            & EndpointGroup::role_name,
                    (EndpointGroup & (EndpointGroup::*) (const std::string&) )
                            & EndpointGroup::role_name,
                    "Get/set the EndpointGroup's role name.")
            .def_property(
                    "quorum_count",
                    (int32_t(EndpointGroup::*)() const)
                            & EndpointGroup::quorum_count,
                    (EndpointGroup & (EndpointGroup::*) (const int32_t))
                            & EndpointGroup::quorum_count,
                    "Get/set the EndpointGroup's quorum count.");

    py::implicitly_convertible<
            std::vector<EndpointGroup>,
            dds::core::vector<EndpointGroup>>();
}

template<>
void process_inits<EndpointGroup>(py::module& m, ClassInitList& l)
{
    l.push_back([m, &l]() mutable {
        auto func = init_class_with_seq<EndpointGroup>(m, "EndpointGroup");
        init_dds_vector_nonbuffer_class<EndpointGroup>(
                m,
                "EndpointGroupVector",
                l);
        return func;
    });
}

}  // namespace pyrti
