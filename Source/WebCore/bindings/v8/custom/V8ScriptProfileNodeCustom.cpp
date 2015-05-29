/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#if ENABLE(JAVASCRIPT_DEBUGGER)
#include "V8ScriptProfileNode.h"

#include "ScriptProfileNode.h"
#include "V8Binding.h"
#include "V8Proxy.h"

#include <v8-profiler.h>

namespace WebCore {

v8::Handle<v8::Value> V8ScriptProfileNode::childrenAccessorGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.ScriptProfileNode.childrenAccessorGetter");
    ScriptProfileNode* imp = V8ScriptProfileNode::toNative(info.Holder());
    const ProfileNodesList& children = imp->children();
    v8::Handle<v8::Array> result = v8::Array::New(children.size());
    int index = 0;
    ProfileNodesList::const_iterator end = children.end();
    for (ProfileNodesList::const_iterator iter = children.begin(); iter != end; ++iter)
        result->Set(v8::Integer::New(index++), toV8(iter->get()));
    return result;
}

v8::Handle<v8::Value> V8ScriptProfileNode::callUIDAccessorGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.ScriptProfileNode.callUIDAccessorGetter");
    ScriptProfileNode* imp = V8ScriptProfileNode::toNative(info.Holder());
    return v8::Number::New(imp->callUID());
}

v8::Handle<v8::Value> toV8(ScriptProfileNode* impl)
{
    if (!impl)
        return v8::Null();
    v8::Local<v8::Function> function = V8ScriptProfileNode::GetTemplate()->GetFunction();
    if (function.IsEmpty()) {
        // Return if allocation failed.
        return v8::Local<v8::Object>();
    }
    v8::Local<v8::Object> instance = SafeAllocation::newInstance(function);
    if (instance.IsEmpty()) {
        // Avoid setting the wrapper if allocation failed.
        return v8::Local<v8::Object>();
    }
    impl->ref();
    V8DOMWrapper::setDOMWrapper(instance, &V8ScriptProfileNode::info, impl);
    return instance;
}

} // namespace WebCore

#endif // ENABLE(JAVASCRIPT_DEBUGGER)
