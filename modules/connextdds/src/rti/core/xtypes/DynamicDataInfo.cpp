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
#include <rti/core/xtypes/DynamicDataInfo.hpp>
#include "PySafeEnum.hpp"

using namespace rti::core::xtypes;

namespace pyrti {

template<>
void init_class_defs(py::class_<DynamicDataInfo>& cls)
{
    cls.def_property_readonly(
               "member_count",
               &DynamicDataInfo::member_count,
               "The number of members of this sample.")
            .def_property_readonly(
                    "stored_size",
                    &DynamicDataInfo::stored_size,
                    "The number of bytes currently used to store the data of "
                    "this "
                    "sample.")
            .def_property_readonly(
                    "encapsulation_kind",
                    &DynamicDataInfo::encapsulation_kind,
                    "The encapsulation kind.")
            .def_property_readonly(
                    "is_optimized_storage",
                    &DynamicDataInfo::is_optimized_storage,
                    "Flag indicating whether storage is optimized.")
            .def(py::self == py::self, "Test for equality.")
            .def(py::self != py::self, "Test for inequality.");
}

template<>
void process_inits<DynamicDataInfo>(py::module& m, ClassInitList& l)
{
    init_dds_safe_enum<DynamicDataEncapsulationKind_def>(
            m,
            "DynamicDataEncapsulationKind",
            [](py::object& o) {
                py::enum_<DynamicDataEncapsulationKind::type>(o, "DynamicDataEncapsulationKind")
                        .value("CDR_BIG_ENDIAN",
                               DynamicDataEncapsulationKind::type::
                                       CDR_BIG_ENDIAN,
                               "CDR big endian encapsulation.")
                        .value("CDR_LITTLE_ENDIAN",
                               DynamicDataEncapsulationKind::type::
                                       CDR_LITTLE_ENDIAN,
                               "CDR little endian encapsulation.")
                        .value("PL_CDR_BIG_ENDIAN",
                               DynamicDataEncapsulationKind::type::
                                       PL_CDR_BIG_ENDIAN,
                               "PL CDR big endian encapsulation.")
                        .value("PL_CDR_LITTLE_ENDIAN",
                               DynamicDataEncapsulationKind::type::
                                       PL_CDR_LITTLE_ENDIAN,
                               "PL CDR little endian encapsulation.")
                        .value("DEFAULT",
                               DynamicDataEncapsulationKind::type::DEFAULT,
                               "Default encapsulation.")
                        .export_values();
            });

    l.push_back([m]() mutable {
        return init_class<DynamicDataInfo>(m, "DynamicDataInfo");
    });
}

}  // namespace pyrti
