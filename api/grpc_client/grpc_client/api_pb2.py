# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: api.proto
# Protobuf Python Version: 5.29.0
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import runtime_version as _runtime_version
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
_runtime_version.ValidateProtobufRuntimeVersion(
    _runtime_version.Domain.PUBLIC,
    5,
    29,
    0,
    '',
    'api.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\tapi.proto\x12\x03\x61pi\x1a\x1bgoogle/protobuf/empty.proto\"l\n\nSensorRows\x12\x10\n\x08\x65ntry_id\x18\x01 \x01(\x05\x12\x13\n\x0b\x66\x61\x63ility_id\x18\x02 \x01(\x05\x12\x0e\n\x06\x64\x65vice\x18\x03 \x01(\t\x12\x0c\n\x04temp\x18\x04 \x01(\x05\x12\n\n\x02rh\x18\x05 \x01(\x02\x12\r\n\x05\x65poch\x18\x06 \x01(\x03\x32\x45\n\x05Query\x12<\n\rGetSensorRows\x12\x16.google.protobuf.Empty\x1a\x0f.api.SensorRows\"\x00\x30\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'api_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_SENSORROWS']._serialized_start=47
  _globals['_SENSORROWS']._serialized_end=155
  _globals['_QUERY']._serialized_start=157
  _globals['_QUERY']._serialized_end=226
# @@protoc_insertion_point(module_scope)
