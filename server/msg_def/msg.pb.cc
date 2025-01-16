// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#include "msg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR LWT::LWT(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.device_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct LWTDefaultTypeInternal {
  PROTOBUF_CONSTEXPR LWTDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~LWTDefaultTypeInternal() {}
  union {
    LWT _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 LWTDefaultTypeInternal _LWT_default_instance_;
PROTOBUF_CONSTEXPR Data::Data(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.device_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.temp_)*/0
  , /*decltype(_impl_.rh_)*/0
  , /*decltype(_impl_.epoch_)*/int64_t{0}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct DataDefaultTypeInternal {
  PROTOBUF_CONSTEXPR DataDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~DataDefaultTypeInternal() {}
  union {
    Data _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 DataDefaultTypeInternal _Data_default_instance_;
static ::_pb::Metadata file_level_metadata_msg_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_msg_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_msg_2eproto = nullptr;

const uint32_t TableStruct_msg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::LWT, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::LWT, _impl_.device_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Data, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Data, _impl_.device_),
  PROTOBUF_FIELD_OFFSET(::Data, _impl_.temp_),
  PROTOBUF_FIELD_OFFSET(::Data, _impl_.rh_),
  PROTOBUF_FIELD_OFFSET(::Data, _impl_.epoch_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::LWT)},
  { 7, -1, -1, sizeof(::Data)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_LWT_default_instance_._instance,
  &::_Data_default_instance_._instance,
};

const char descriptor_table_protodef_msg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\tmsg.proto\"\025\n\003LWT\022\016\n\006device\030\001 \001(\t\"\?\n\004Da"
  "ta\022\016\n\006device\030\001 \001(\t\022\014\n\004temp\030\002 \001(\005\022\n\n\002rh\030\003"
  " \001(\002\022\r\n\005epoch\030\004 \001(\003b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_msg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_msg_2eproto = {
    false, false, 107, descriptor_table_protodef_msg_2eproto,
    "msg.proto",
    &descriptor_table_msg_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_msg_2eproto::offsets,
    file_level_metadata_msg_2eproto, file_level_enum_descriptors_msg_2eproto,
    file_level_service_descriptors_msg_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_msg_2eproto_getter() {
  return &descriptor_table_msg_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_msg_2eproto(&descriptor_table_msg_2eproto);

// ===================================================================

class LWT::_Internal {
 public:
};

LWT::LWT(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:LWT)
}
LWT::LWT(const LWT& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  LWT* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.device_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.device_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.device_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_device().empty()) {
    _this->_impl_.device_.Set(from._internal_device(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:LWT)
}

inline void LWT::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.device_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.device_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.device_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

LWT::~LWT() {
  // @@protoc_insertion_point(destructor:LWT)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void LWT::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.device_.Destroy();
}

void LWT::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void LWT::Clear() {
// @@protoc_insertion_point(message_clear_start:LWT)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.device_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* LWT::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string device = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_device();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "LWT.device"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* LWT::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:LWT)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string device = 1;
  if (!this->_internal_device().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_device().data(), static_cast<int>(this->_internal_device().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "LWT.device");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_device(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:LWT)
  return target;
}

size_t LWT::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:LWT)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string device = 1;
  if (!this->_internal_device().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_device());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData LWT::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    LWT::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*LWT::GetClassData() const { return &_class_data_; }


void LWT::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<LWT*>(&to_msg);
  auto& from = static_cast<const LWT&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:LWT)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_device().empty()) {
    _this->_internal_set_device(from._internal_device());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void LWT::CopyFrom(const LWT& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:LWT)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LWT::IsInitialized() const {
  return true;
}

void LWT::InternalSwap(LWT* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.device_, lhs_arena,
      &other->_impl_.device_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata LWT::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_msg_2eproto_getter, &descriptor_table_msg_2eproto_once,
      file_level_metadata_msg_2eproto[0]);
}

// ===================================================================

class Data::_Internal {
 public:
};

Data::Data(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Data)
}
Data::Data(const Data& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Data* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.device_){}
    , decltype(_impl_.temp_){}
    , decltype(_impl_.rh_){}
    , decltype(_impl_.epoch_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.device_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.device_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_device().empty()) {
    _this->_impl_.device_.Set(from._internal_device(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.temp_, &from._impl_.temp_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.epoch_) -
    reinterpret_cast<char*>(&_impl_.temp_)) + sizeof(_impl_.epoch_));
  // @@protoc_insertion_point(copy_constructor:Data)
}

inline void Data::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.device_){}
    , decltype(_impl_.temp_){0}
    , decltype(_impl_.rh_){0}
    , decltype(_impl_.epoch_){int64_t{0}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.device_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.device_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Data::~Data() {
  // @@protoc_insertion_point(destructor:Data)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Data::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.device_.Destroy();
}

void Data::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Data::Clear() {
// @@protoc_insertion_point(message_clear_start:Data)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.device_.ClearToEmpty();
  ::memset(&_impl_.temp_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.epoch_) -
      reinterpret_cast<char*>(&_impl_.temp_)) + sizeof(_impl_.epoch_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Data::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string device = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_device();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Data.device"));
        } else
          goto handle_unusual;
        continue;
      // int32 temp = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.temp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // float rh = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          _impl_.rh_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // int64 epoch = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.epoch_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Data::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Data)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string device = 1;
  if (!this->_internal_device().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_device().data(), static_cast<int>(this->_internal_device().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Data.device");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_device(), target);
  }

  // int32 temp = 2;
  if (this->_internal_temp() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_temp(), target);
  }

  // float rh = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_rh = this->_internal_rh();
  uint32_t raw_rh;
  memcpy(&raw_rh, &tmp_rh, sizeof(tmp_rh));
  if (raw_rh != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_rh(), target);
  }

  // int64 epoch = 4;
  if (this->_internal_epoch() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(4, this->_internal_epoch(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Data)
  return target;
}

size_t Data::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Data)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string device = 1;
  if (!this->_internal_device().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_device());
  }

  // int32 temp = 2;
  if (this->_internal_temp() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_temp());
  }

  // float rh = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_rh = this->_internal_rh();
  uint32_t raw_rh;
  memcpy(&raw_rh, &tmp_rh, sizeof(tmp_rh));
  if (raw_rh != 0) {
    total_size += 1 + 4;
  }

  // int64 epoch = 4;
  if (this->_internal_epoch() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_epoch());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Data::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Data::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Data::GetClassData() const { return &_class_data_; }


void Data::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Data*>(&to_msg);
  auto& from = static_cast<const Data&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Data)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_device().empty()) {
    _this->_internal_set_device(from._internal_device());
  }
  if (from._internal_temp() != 0) {
    _this->_internal_set_temp(from._internal_temp());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_rh = from._internal_rh();
  uint32_t raw_rh;
  memcpy(&raw_rh, &tmp_rh, sizeof(tmp_rh));
  if (raw_rh != 0) {
    _this->_internal_set_rh(from._internal_rh());
  }
  if (from._internal_epoch() != 0) {
    _this->_internal_set_epoch(from._internal_epoch());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Data::CopyFrom(const Data& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Data::IsInitialized() const {
  return true;
}

void Data::InternalSwap(Data* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.device_, lhs_arena,
      &other->_impl_.device_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Data, _impl_.epoch_)
      + sizeof(Data::_impl_.epoch_)
      - PROTOBUF_FIELD_OFFSET(Data, _impl_.temp_)>(
          reinterpret_cast<char*>(&_impl_.temp_),
          reinterpret_cast<char*>(&other->_impl_.temp_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Data::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_msg_2eproto_getter, &descriptor_table_msg_2eproto_once,
      file_level_metadata_msg_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::LWT*
Arena::CreateMaybeMessage< ::LWT >(Arena* arena) {
  return Arena::CreateMessageInternal< ::LWT >(arena);
}
template<> PROTOBUF_NOINLINE ::Data*
Arena::CreateMaybeMessage< ::Data >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Data >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
