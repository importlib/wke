/*
 * Copyright (C) 2008, 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "config.h"
#include "JSNotAnObject.h"

#include <wtf/UnusedParam.h>

namespace JSC {

ASSERT_CLASS_FITS_IN_CELL(JSNotAnObject);

const ClassInfo JSNotAnObject::s_info = { "Object", &Base::s_info, 0, 0, CREATE_METHOD_TABLE(JSNotAnObject) };

// JSValue methods
JSValue JSNotAnObject::defaultValue(ExecState* exec, PreferredPrimitiveType) const
{
    ASSERT_UNUSED(exec, exec->hadException());
    return jsNumber(0);
}

bool JSNotAnObject::getOwnPropertySlotVirtual(ExecState* exec, const Identifier& identifier, PropertySlot& slot)
{
    return getOwnPropertySlot(this, exec, identifier, slot);
}

// JSObject methods
bool JSNotAnObject::getOwnPropertySlot(JSCell*, ExecState* exec, const Identifier&, PropertySlot&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::getOwnPropertySlotVirtual(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    return getOwnPropertySlot(this, exec, propertyName, slot);
}

bool JSNotAnObject::getOwnPropertySlot(JSCell*, ExecState* exec, unsigned, PropertySlot&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::getOwnPropertyDescriptor(ExecState* exec, const Identifier&, PropertyDescriptor&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

void JSNotAnObject::putVirtual(ExecState* exec, const Identifier& identifier, JSValue value, PutPropertySlot& slot)
{
    put(this, exec, identifier, value, slot);
}

void JSNotAnObject::put(JSCell*, ExecState* exec, const Identifier& , JSValue, PutPropertySlot&)
{
    ASSERT_UNUSED(exec, exec->hadException());
}

void JSNotAnObject::putVirtual(ExecState* exec, unsigned i, JSValue value)
{
    putByIndex(this, exec, i, value);
}

void JSNotAnObject::putByIndex(JSCell*, ExecState* exec, unsigned, JSValue)
{
    ASSERT_UNUSED(exec, exec->hadException());
}

bool JSNotAnObject::deletePropertyVirtual(ExecState* exec, const Identifier& propertyName)
{
    return deleteProperty(this, exec, propertyName);
}

bool JSNotAnObject::deleteProperty(JSCell*, ExecState* exec, const Identifier&)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

bool JSNotAnObject::deletePropertyVirtual(ExecState* exec, unsigned propertyName)
{
    return deletePropertyByIndex(this, exec, propertyName);
}

bool JSNotAnObject::deletePropertyByIndex(JSCell*, ExecState* exec, unsigned)
{
    ASSERT_UNUSED(exec, exec->hadException());
    return false;
}

void JSNotAnObject::getOwnPropertyNames(ExecState* exec, PropertyNameArray&, EnumerationMode)
{
    ASSERT_UNUSED(exec, exec->hadException());
}

} // namespace JSC
