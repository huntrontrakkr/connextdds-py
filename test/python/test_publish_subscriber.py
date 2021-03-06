 #
 # (c) 2020 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 #
 # RTI grants Licensee a license to use, modify, compile, and create derivative
 # works of the Software solely for use with RTI products.  The Software is
 # provided "as is", with no warranty of any type, including any warranty for
 # fitness for any purpose. RTI is under no obligation to maintain or support
 # the Software.  RTI shall not be liable for any incidental or consequential
 # damages arising out of the use or inability to use the software.
 #

import rti.connextdds as dds
import utils

DOMAIN_ID = 0


def test_write_timestamp():
    system = utils.TestSystem(DOMAIN_ID, "StringTopicType")
    test_timestamp = dds.Time(123)
    system.writer.write("hi", test_timestamp)
    utils.wait(system.reader)
    samples = system.reader.take()
    assert samples[0].info.source_timestamp == test_timestamp


def test_write_handle():
    system = utils.TestSystem(DOMAIN_ID, "KeyedStringTopicType")
    sample = dds.KeyedStringTopicType()
    handle = system.writer.register_instance(sample)
    system.writer.write(sample, handle)
    utils.wait(system.reader)
    samples = system.reader.take()
    assert samples[0].info.instance_handle == handle


def test_write_handle_and_timestamp():
    system = utils.TestSystem(DOMAIN_ID, "KeyedStringTopicType")
    sample = dds.KeyedStringTopicType()
    test_timestamp = dds.Time(123)
    handle = system.writer.register_instance(sample)
    system.writer.write(sample, handle, test_timestamp)
    utils.wait(system.reader)
    samples = system.reader.take()
    assert samples[0].info.instance_handle == handle
    assert samples[0].info.source_timestamp == test_timestamp


def test_write_timestamp_w_operator():
    system = utils.TestSystem(DOMAIN_ID, "StringTopicType")
    test_timestamp = dds.Time(123)
    system.writer << ("hi", test_timestamp)
    utils.wait(system.reader)
    samples = system.reader.take()
    assert samples[0].info.source_timestamp == test_timestamp


def test_write_handle_w_operator():
    system = utils.TestSystem(DOMAIN_ID, "KeyedStringTopicType")
    sample = dds.KeyedStringTopicType()
    handle = system.writer.register_instance(sample)
    system.writer << (sample, handle)
    utils.wait(system.reader)
    samples = system.reader.take()
    assert samples[0].info.instance_handle == handle


def test_write_w_operator_mix():
    system = utils.TestSystem(DOMAIN_ID, "KeyedStringTopicType")
    sample = dds.KeyedStringTopicType()
    handle = system.writer.register_instance(sample)
    system.writer << (sample, handle) << dds.KeyedStringTopicType("Hi", "Hi") << (
        dds.KeyedStringTopicType("hello", "hello"),
        dds.Time(123),
    )
