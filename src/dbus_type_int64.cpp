#include <iomanip>
#include <sstream>

#include <boost/thread/recursive_mutex.hpp>

#include "dbus_type.h"
#include "dbus_type_base.h"
#include "dbus_type_int64.h"

#include "dbus_message.h"
#include "dbus_messageprotocol.h"
#include "dbus_messagestream.h"
#include "dbus_type_struct.h"

const std::string DBus::Type::Int64::s_StaticTypeCode("x");

DBus::Type::Int64::Int64()
    : m_Value(0)
{
    setSignature(s_StaticTypeCode);
}

DBus::Type::Int64::Int64(int64_t v)
    : m_Value(v)
{
    setSignature(s_StaticTypeCode);
}

void DBus::Type::Int64::marshall(MessageStream& stream) const { stream.writeInt64(m_Value); }

bool DBus::Type::Int64::unmarshall(const UnmarshallingData& data)
{
    if (m_Unmarshalling.areWeSkippingPadding && !Utils::isAlignedTo(getAlignment(), data.offset)) {
        return false;
    }
    m_Unmarshalling.areWeSkippingPadding = false;

    m_Value <<= 8;
    m_Value += data.c;

    if (++m_Unmarshalling.count == 8) {
        m_Value = doSwap64(m_Value);
        return true;
    }
    return false;
}

std::string DBus::Type::Int64::toString(const std::string& prefix) const
{
    std::stringstream ss;

    ss << prefix << "Int64 ";
    ss << m_Value << " (0x" << std::hex << std::setfill('0') << std::setw(8) << m_Value << ")\n";

    return ss.str();
}

std::string DBus::Type::Int64::asString() const
{
    std::stringstream ss;
    ss << m_Value;
    return ss.str();
}
