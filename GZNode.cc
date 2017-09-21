/*
 * Copyright 2013 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <node.h>
#include "GZNode.hh"

#include "OgreMaterialParser.hh"

using namespace v8;
using namespace gzweb;

/////////////////////////////////////////////////
void GZNode::Init(Handle<Object> exports)
{
  Isolate* isolate = exports->GetIsolate();
  
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "GZNode"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "loadMaterialScripts", LoadMaterialScripts);

  exports->Set(String::NewFromUtf8(isolate, "GZNode"),
               tpl->GetFunction());
}

/////////////////////////////////////////////////
void GZNode::New(const FunctionCallbackInfo<Value>& args)
{
  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    GZNode* obj = new GZNode();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  }
}

/////////////////////////////////////////////////
void GZNode::LoadMaterialScripts(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1)
  {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsString())
  {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong argument type. String expected.")));
    return;
  }

  GZNode* obj = ObjectWrap::Unwrap<GZNode>(args.This());

  String::Utf8Value path(args[0]->ToString());

  OgreMaterialParser materialParser;
  materialParser.Load(std::string(*path));
  std::string materialJson = materialParser.GetMaterialAsJson();

  args.GetReturnValue().Set(String::NewFromUtf8(isolate ,materialJson.c_str()));

  return;
}

/////////////////////////////////////////////////
void InitAll(Handle<Object> exports)
{
  GZNode::Init(exports);
}

/////////////////////////////////////////////////
NODE_MODULE(gzbridge, InitAll)
