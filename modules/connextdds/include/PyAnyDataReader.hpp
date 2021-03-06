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

#pragma once

#include "PyConnext.hpp"
#include <dds/sub/AnyDataReader.hpp>
#include "PyEntity.hpp"

namespace pyrti {

class PyIAnyDataReader {
public:
    virtual dds::sub::AnyDataReader get_any_datareader() const = 0;

    virtual dds::sub::qos::DataReaderQos py_qos() const = 0;

    virtual void py_qos(const dds::sub::qos::DataReaderQos&) = 0;

    virtual const std::string& py_topic_name() const = 0;

    virtual const std::string& py_type_name() const = 0;

    virtual const PySubscriber py_subscriber() const = 0;

    virtual void py_close() = 0;

    virtual void py_retain() = 0;

    virtual ~PyIAnyDataReader()
    {
    }
};

class PyAnyDataReader : public dds::sub::AnyDataReader,
                        public PyIAnyDataReader {
public:
    using dds::sub::AnyDataReader::AnyDataReader;

    PyAnyDataReader(const dds::sub::AnyDataReader& adr)
            : dds::sub::AnyDataReader(adr)
    {
    }

    PyAnyDataReader(const PyIAnyDataReader& adr)
            : dds::sub::AnyDataReader(adr.get_any_datareader())
    {
    }

    dds::sub::AnyDataReader get_any_datareader() const override
    {
        return (*this);
    }

    dds::sub::qos::DataReaderQos py_qos() const override
    {
        return this->qos();
    }

    void py_qos(const dds::sub::qos::DataReaderQos& q) override
    {
        this->qos(q);
    }

    const std::string& py_topic_name() const override
    {
        return this->topic_name();
    }

    const std::string& py_type_name() const override
    {
        return this->type_name();
    }

    const PySubscriber py_subscriber() const override
    {
        auto s = this->subscriber();
        return PySubscriber(s);
    }

    void py_close() override
    {
        this->close();
    }

    void py_retain() override
    {
        this->retain();
    }
};

}  // namespace pyrti
