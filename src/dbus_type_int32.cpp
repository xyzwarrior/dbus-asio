// This file is part of dbus-asio
// Copyright 2018 Brightsign LLC
//
// This library is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, version 3, or at your
// option any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// The GNU Lesser General Public License version 3 is included in the
// file named COPYING. If you do not have this file see
// <http://www.gnu.org/licenses/>.

#include <iomanip>
#include <sstream>

#include <boost/thread/recursive_mutex.hpp>

#include "dbus_type.h"
#include "dbus_type_base.h"
#include "dbus_type_int32.h"

#include "dbus_message.h"
#include "dbus_messageprotocol.h"
#include "dbus_messagestream.h"
#include "dbus_type_struct.h"

const std::string DBus::Type::Int32::s_StaticTypeCode("i");

DBus::Type::Int32::Int32()
    : m_Value(0)
{
    setSignature(s_StaticTypeCode);
}

DBus::Type::Int32::Int32(int32_t v)
    : m_Value(v)
{
    setSignature(s_StaticTypeCode);
}

void DBus::Type::Int32::marshall(MessageStream& stream) const { stream.writeInt32(m_Value); }

bool DBus::Type::Int32::unmarshall(const UnmarshallingData& data)
{
    if (m_Unmarshalling.areWeSkippingPadding && !Utils::isAlignedTo(getAlignment(), data.offset)) {
        return false;
    }
    m_Unmarshalling.areWeSkippingPadding = false;

    m_Value <<= 8;
    m_Value += data.c;

    if (++m_Unmarshalling.count == 4) {
        m_Value = doSwap32(m_Value);
        return true;
    }
    return false;
}

std::string DBus::Type::Int32::toString(const std::string& prefix) const
{
    std::stringstream ss;

    ss << prefix << "Int32 ";
    ss << m_Value << " (0x" << std::hex << std::setfill('0') << std::setw(4) << m_Value << ")\n";

    return ss.str();
}

std::string DBus::Type::Int32::asString() const
{
    std::stringstream ss;
    ss << m_Value;
    return ss.str();
}
