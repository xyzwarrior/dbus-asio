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

#include <boost/thread/recursive_mutex.hpp>

#include "dbus_type.h"
#include "dbus_type_base.h"
#include "dbus_type_helpers.h"
#include "dbus_type_objectpath.h"
#include "dbus_type_string.h"
#include "dbus_type_struct.h"

#include "dbus_message.h"
#include "dbus_messageprotocol.h"
#include "dbus_messagestream.h"
#include "dbus_validation.h"

const std::string DBus::Type::ObjectPath::s_StaticTypeCode("o");

DBus::Type::ObjectPath::ObjectPath() { setSignature(s_StaticTypeCode); }

DBus::Type::ObjectPath::ObjectPath(const std::string& v)
    : String(v)
{
    setSignature(s_StaticTypeCode);
}

void DBus::Type::ObjectPath::marshall(MessageStream& stream) const
{
    Validation::throwOnInvalidObjectPath(m_Value);

    // Exactly the same as STRING except the content must be a valid object path (see above).
    Type::String::marshall(stream);
}
