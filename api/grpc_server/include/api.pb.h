// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: api.proto
// Protobuf C++ Version: 5.27.0

#ifndef GOOGLE_PROTOBUF_INCLUDED_api_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_api_2eproto_2epb_2eh

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
#include "google/protobuf/empty.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_api_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_api_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_api_2eproto;
namespace api {
class SensorRows;
struct SensorRowsDefaultTypeInternal;
extern SensorRowsDefaultTypeInternal _SensorRows_default_instance_;
}  // namespace api
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace api {

// ===================================================================


// -------------------------------------------------------------------

class SensorRows final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:api.SensorRows) */ {
 public:
  inline SensorRows() : SensorRows(nullptr) {}
  ~SensorRows() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR SensorRows(
      ::google::protobuf::internal::ConstantInitialized);

  inline SensorRows(const SensorRows& from) : SensorRows(nullptr, from) {}
  inline SensorRows(SensorRows&& from) noexcept
      : SensorRows(nullptr, std::move(from)) {}
  inline SensorRows& operator=(const SensorRows& from) {
    CopyFrom(from);
    return *this;
  }
  inline SensorRows& operator=(SensorRows&& from) noexcept {
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
  static const SensorRows& default_instance() {
    return *internal_default_instance();
  }
  static inline const SensorRows* internal_default_instance() {
    return reinterpret_cast<const SensorRows*>(
        &_SensorRows_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(SensorRows& a, SensorRows& b) { a.Swap(&b); }
  inline void Swap(SensorRows* other) {
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
  void UnsafeArenaSwap(SensorRows* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SensorRows* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<SensorRows>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const SensorRows& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const SensorRows& from) { SensorRows::MergeImpl(*this, from); }

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
  void InternalSwap(SensorRows* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "api.SensorRows"; }

 protected:
  explicit SensorRows(::google::protobuf::Arena* arena);
  SensorRows(::google::protobuf::Arena* arena, const SensorRows& from);
  SensorRows(::google::protobuf::Arena* arena, SensorRows&& from) noexcept
      : SensorRows(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kDeviceFieldNumber = 3,
    kEntryIdFieldNumber = 1,
    kFacilityIdFieldNumber = 2,
    kTempFieldNumber = 4,
    kRhFieldNumber = 5,
    kEpochFieldNumber = 6,
  };
  // string device = 3;
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
  // int32 entry_id = 1;
  void clear_entry_id() ;
  ::int32_t entry_id() const;
  void set_entry_id(::int32_t value);

  private:
  ::int32_t _internal_entry_id() const;
  void _internal_set_entry_id(::int32_t value);

  public:
  // int32 facility_id = 2;
  void clear_facility_id() ;
  ::int32_t facility_id() const;
  void set_facility_id(::int32_t value);

  private:
  ::int32_t _internal_facility_id() const;
  void _internal_set_facility_id(::int32_t value);

  public:
  // int32 temp = 4;
  void clear_temp() ;
  ::int32_t temp() const;
  void set_temp(::int32_t value);

  private:
  ::int32_t _internal_temp() const;
  void _internal_set_temp(::int32_t value);

  public:
  // float rh = 5;
  void clear_rh() ;
  float rh() const;
  void set_rh(float value);

  private:
  float _internal_rh() const;
  void _internal_set_rh(float value);

  public:
  // int64 epoch = 6;
  void clear_epoch() ;
  ::int64_t epoch() const;
  void set_epoch(::int64_t value);

  private:
  ::int64_t _internal_epoch() const;
  void _internal_set_epoch(::int64_t value);

  public:
  // @@protoc_insertion_point(class_scope:api.SensorRows)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      3, 6, 0,
      29, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_SensorRows_default_instance_;

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
                          const SensorRows& from_msg);
    ::google::protobuf::internal::ArenaStringPtr device_;
    ::int32_t entry_id_;
    ::int32_t facility_id_;
    ::int32_t temp_;
    float rh_;
    ::int64_t epoch_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_api_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// SensorRows

// int32 entry_id = 1;
inline void SensorRows::clear_entry_id() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.entry_id_ = 0;
}
inline ::int32_t SensorRows::entry_id() const {
  // @@protoc_insertion_point(field_get:api.SensorRows.entry_id)
  return _internal_entry_id();
}
inline void SensorRows::set_entry_id(::int32_t value) {
  _internal_set_entry_id(value);
  // @@protoc_insertion_point(field_set:api.SensorRows.entry_id)
}
inline ::int32_t SensorRows::_internal_entry_id() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.entry_id_;
}
inline void SensorRows::_internal_set_entry_id(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.entry_id_ = value;
}

// int32 facility_id = 2;
inline void SensorRows::clear_facility_id() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.facility_id_ = 0;
}
inline ::int32_t SensorRows::facility_id() const {
  // @@protoc_insertion_point(field_get:api.SensorRows.facility_id)
  return _internal_facility_id();
}
inline void SensorRows::set_facility_id(::int32_t value) {
  _internal_set_facility_id(value);
  // @@protoc_insertion_point(field_set:api.SensorRows.facility_id)
}
inline ::int32_t SensorRows::_internal_facility_id() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.facility_id_;
}
inline void SensorRows::_internal_set_facility_id(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.facility_id_ = value;
}

// string device = 3;
inline void SensorRows::clear_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.ClearToEmpty();
}
inline const std::string& SensorRows::device() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:api.SensorRows.device)
  return _internal_device();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void SensorRows::set_device(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:api.SensorRows.device)
}
inline std::string* SensorRows::mutable_device() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_device();
  // @@protoc_insertion_point(field_mutable:api.SensorRows.device)
  return _s;
}
inline const std::string& SensorRows::_internal_device() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.device_.Get();
}
inline void SensorRows::_internal_set_device(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.Set(value, GetArena());
}
inline std::string* SensorRows::_internal_mutable_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.device_.Mutable( GetArena());
}
inline std::string* SensorRows::release_device() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:api.SensorRows.device)
  return _impl_.device_.Release();
}
inline void SensorRows::set_allocated_device(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.device_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.device_.IsDefault()) {
          _impl_.device_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:api.SensorRows.device)
}

// int32 temp = 4;
inline void SensorRows::clear_temp() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.temp_ = 0;
}
inline ::int32_t SensorRows::temp() const {
  // @@protoc_insertion_point(field_get:api.SensorRows.temp)
  return _internal_temp();
}
inline void SensorRows::set_temp(::int32_t value) {
  _internal_set_temp(value);
  // @@protoc_insertion_point(field_set:api.SensorRows.temp)
}
inline ::int32_t SensorRows::_internal_temp() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.temp_;
}
inline void SensorRows::_internal_set_temp(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.temp_ = value;
}

// float rh = 5;
inline void SensorRows::clear_rh() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.rh_ = 0;
}
inline float SensorRows::rh() const {
  // @@protoc_insertion_point(field_get:api.SensorRows.rh)
  return _internal_rh();
}
inline void SensorRows::set_rh(float value) {
  _internal_set_rh(value);
  // @@protoc_insertion_point(field_set:api.SensorRows.rh)
}
inline float SensorRows::_internal_rh() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.rh_;
}
inline void SensorRows::_internal_set_rh(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.rh_ = value;
}

// int64 epoch = 6;
inline void SensorRows::clear_epoch() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.epoch_ = ::int64_t{0};
}
inline ::int64_t SensorRows::epoch() const {
  // @@protoc_insertion_point(field_get:api.SensorRows.epoch)
  return _internal_epoch();
}
inline void SensorRows::set_epoch(::int64_t value) {
  _internal_set_epoch(value);
  // @@protoc_insertion_point(field_set:api.SensorRows.epoch)
}
inline ::int64_t SensorRows::_internal_epoch() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.epoch_;
}
inline void SensorRows::_internal_set_epoch(::int64_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.epoch_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace api


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_api_2eproto_2epb_2eh
