// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: msg.proto
// Protobuf C++ Version: 5.27.0

#ifndef GOOGLE_PROTOBUF_INCLUDED_msg_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_msg_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5027000
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_msg_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_msg_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_msg_2eproto;
namespace msg {
class LWT;
struct LWTDefaultTypeInternal;
extern LWTDefaultTypeInternal _LWT_default_instance_;
class Sensor;
struct SensorDefaultTypeInternal;
extern SensorDefaultTypeInternal _Sensor_default_instance_;
}  // namespace msg
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace msg {

// ===================================================================


// -------------------------------------------------------------------

class Sensor final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:msg.Sensor) */ {
 public:
  inline Sensor() : Sensor(nullptr) {}
  ~Sensor() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR Sensor(
      ::google::protobuf::internal::ConstantInitialized);

  inline Sensor(const Sensor& from) : Sensor(nullptr, from) {}
  inline Sensor(Sensor&& from) noexcept
      : Sensor(nullptr, std::move(from)) {}
  inline Sensor& operator=(const Sensor& from) {
    CopyFrom(from);
    return *this;
  }
  inline Sensor& operator=(Sensor&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Sensor& default_instance() {
    return *internal_default_instance();
  }
  static inline const Sensor* internal_default_instance() {
    return reinterpret_cast<const Sensor*>(
        &_Sensor_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(Sensor& a, Sensor& b) { a.Swap(&b); }
  inline void Swap(Sensor* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Sensor* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Sensor* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<Sensor>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Sensor& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const Sensor& from) { Sensor::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(Sensor* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "msg.Sensor"; }

 protected:
  explicit Sensor(::google::protobuf::Arena* arena);
  Sensor(::google::protobuf::Arena* arena, const Sensor& from);
  Sensor(::google::protobuf::Arena* arena, Sensor&& from) noexcept
      : Sensor(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kDeviceFieldNumber = 1,
    kTempFieldNumber = 2,
    kRhFieldNumber = 3,
    kEpochFieldNumber = 4,
  };
  // string device = 1;
  void clear_device() ;
  const std::string& device() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_device(Arg_&& arg, Args_... args);
  std::string* mutable_device();
  PROTOBUF_NODISCARD std::string* release_device();
  void set_allocated_device(std::string* value);

  private:
  const std::string& _internal_device() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_device(
      const std::string& value);
  std::string* _internal_mutable_device();

  public:
  // int32 temp = 2;
  void clear_temp() ;
  ::int32_t temp() const;
  void set_temp(::int32_t value);

  private:
  ::int32_t _internal_temp() const;
  void _internal_set_temp(::int32_t value);

  public:
  // float rh = 3;
  void clear_rh() ;
  float rh() const;
  void set_rh(float value);

  private:
  float _internal_rh() const;
  void _internal_set_rh(float value);

  public:
  // int64 epoch = 4;
  void clear_epoch() ;
  ::int64_t epoch() const;
  void set_epoch(::int64_t value);

  private:
  ::int64_t _internal_epoch() const;
  void _internal_set_epoch(::int64_t value);

  public:
  // @@protoc_insertion_point(class_scope:msg.Sensor)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 4, 0,
      25, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_Sensor_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const Sensor& from_msg);
    ::google::protobuf::internal::ArenaStringPtr device_;
    ::int32_t temp_;
    float rh_;
    ::int64_t epoch_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_msg_2eproto;
};
// -------------------------------------------------------------------

class LWT final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:msg.LWT) */ {
 public:
  inline LWT() : LWT(nullptr) {}
  ~LWT() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR LWT(
      ::google::protobuf::internal::ConstantInitialized);

  inline LWT(const LWT& from) : LWT(nullptr, from) {}
  inline LWT(LWT&& from) noexcept
      : LWT(nullptr, std::move(from)) {}
  inline LWT& operator=(const LWT& from) {
    CopyFrom(from);
    return *this;
  }
  inline LWT& operator=(LWT&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const LWT& default_instance() {
    return *internal_default_instance();
  }
  static inline const LWT* internal_default_instance() {
    return reinterpret_cast<const LWT*>(
        &_LWT_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(LWT& a, LWT& b) { a.Swap(&b); }
  inline void Swap(LWT* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(LWT* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  LWT* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<LWT>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const LWT& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const LWT& from) { LWT::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(LWT* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "msg.LWT"; }

 protected:
  explicit LWT(::google::protobuf::Arena* arena);
  LWT(::google::protobuf::Arena* arena, const LWT& from);
  LWT(::google::protobuf::Arena* arena, LWT&& from) noexcept
      : LWT(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kDeviceFieldNumber = 1,
  };
  // string device = 1;
  void clear_device() ;
  const std::string& device() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_device(Arg_&& arg, Args_... args);
  std::string* mutable_device();
  PROTOBUF_NODISCARD std::string* release_device();
  void set_allocated_device(std::string* value);

  private:
  const std::string& _internal_device() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_device(
      const std::string& value);
  std::string* _internal_mutable_device();

  public:
  // @@protoc_insertion_point(class_scope:msg.LWT)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      22, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_LWT_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const LWT& from_msg);
    ::google::protobuf::internal::ArenaStringPtr device_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_msg_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// LWT

// string device = 1;
inline void LWT::clear_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.ClearToEmpty();
}
inline const std::string& LWT::device() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:msg.LWT.device)
  return _internal_device();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void LWT::set_device(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:msg.LWT.device)
}
inline std::string* LWT::mutable_device() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_device();
  // @@protoc_insertion_point(field_mutable:msg.LWT.device)
  return _s;
}
inline const std::string& LWT::_internal_device() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.device_.Get();
}
inline void LWT::_internal_set_device(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.Set(value, GetArena());
}
inline std::string* LWT::_internal_mutable_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.device_.Mutable( GetArena());
}
inline std::string* LWT::release_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:msg.LWT.device)
  return _impl_.device_.Release();
}
inline void LWT::set_allocated_device(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.device_.IsDefault()) {
          _impl_.device_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg.LWT.device)
}

// -------------------------------------------------------------------

// Sensor

// string device = 1;
inline void Sensor::clear_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.ClearToEmpty();
}
inline const std::string& Sensor::device() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:msg.Sensor.device)
  return _internal_device();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Sensor::set_device(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:msg.Sensor.device)
}
inline std::string* Sensor::mutable_device() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_device();
  // @@protoc_insertion_point(field_mutable:msg.Sensor.device)
  return _s;
}
inline const std::string& Sensor::_internal_device() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.device_.Get();
}
inline void Sensor::_internal_set_device(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.Set(value, GetArena());
}
inline std::string* Sensor::_internal_mutable_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.device_.Mutable( GetArena());
}
inline std::string* Sensor::release_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:msg.Sensor.device)
  return _impl_.device_.Release();
}
inline void Sensor::set_allocated_device(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.device_.IsDefault()) {
          _impl_.device_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg.Sensor.device)
}

// int32 temp = 2;
inline void Sensor::clear_temp() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.temp_ = 0;
}
inline ::int32_t Sensor::temp() const {
  // @@protoc_insertion_point(field_get:msg.Sensor.temp)
  return _internal_temp();
}
inline void Sensor::set_temp(::int32_t value) {
  _internal_set_temp(value);
  // @@protoc_insertion_point(field_set:msg.Sensor.temp)
}
inline ::int32_t Sensor::_internal_temp() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.temp_;
}
inline void Sensor::_internal_set_temp(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.temp_ = value;
}

// float rh = 3;
inline void Sensor::clear_rh() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.rh_ = 0;
}
inline float Sensor::rh() const {
  // @@protoc_insertion_point(field_get:msg.Sensor.rh)
  return _internal_rh();
}
inline void Sensor::set_rh(float value) {
  _internal_set_rh(value);
  // @@protoc_insertion_point(field_set:msg.Sensor.rh)
}
inline float Sensor::_internal_rh() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.rh_;
}
inline void Sensor::_internal_set_rh(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.rh_ = value;
}

// int64 epoch = 4;
inline void Sensor::clear_epoch() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.epoch_ = ::int64_t{0};
}
inline ::int64_t Sensor::epoch() const {
  // @@protoc_insertion_point(field_get:msg.Sensor.epoch)
  return _internal_epoch();
}
inline void Sensor::set_epoch(::int64_t value) {
  _internal_set_epoch(value);
  // @@protoc_insertion_point(field_set:msg.Sensor.epoch)
}
inline ::int64_t Sensor::_internal_epoch() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.epoch_;
}
inline void Sensor::_internal_set_epoch(::int64_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.epoch_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace msg


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_msg_2eproto_2epb_2eh
