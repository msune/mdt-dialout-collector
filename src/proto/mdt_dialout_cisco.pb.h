// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mdt_dialout_cisco.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_mdt_5fdialout_5fcisco_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_mdt_5fdialout_5fcisco_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_mdt_5fdialout_5fcisco_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_mdt_5fdialout_5fcisco_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mdt_5fdialout_5fcisco_2eproto;
namespace mdt_dialout {
class MdtDialoutArgs;
struct MdtDialoutArgsDefaultTypeInternal;
extern MdtDialoutArgsDefaultTypeInternal _MdtDialoutArgs_default_instance_;
}  // namespace mdt_dialout
PROTOBUF_NAMESPACE_OPEN
template<> ::mdt_dialout::MdtDialoutArgs* Arena::CreateMaybeMessage<::mdt_dialout::MdtDialoutArgs>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mdt_dialout {

// ===================================================================

class MdtDialoutArgs final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mdt_dialout.MdtDialoutArgs) */ {
 public:
  inline MdtDialoutArgs() : MdtDialoutArgs(nullptr) {}
  ~MdtDialoutArgs() override;
  explicit constexpr MdtDialoutArgs(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MdtDialoutArgs(const MdtDialoutArgs& from);
  MdtDialoutArgs(MdtDialoutArgs&& from) noexcept
    : MdtDialoutArgs() {
    *this = ::std::move(from);
  }

  inline MdtDialoutArgs& operator=(const MdtDialoutArgs& from) {
    CopyFrom(from);
    return *this;
  }
  inline MdtDialoutArgs& operator=(MdtDialoutArgs&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MdtDialoutArgs& default_instance() {
    return *internal_default_instance();
  }
  static inline const MdtDialoutArgs* internal_default_instance() {
    return reinterpret_cast<const MdtDialoutArgs*>(
               &_MdtDialoutArgs_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MdtDialoutArgs& a, MdtDialoutArgs& b) {
    a.Swap(&b);
  }
  inline void Swap(MdtDialoutArgs* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MdtDialoutArgs* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MdtDialoutArgs* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MdtDialoutArgs>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MdtDialoutArgs& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const MdtDialoutArgs& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MdtDialoutArgs* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mdt_dialout.MdtDialoutArgs";
  }
  protected:
  explicit MdtDialoutArgs(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDataFieldNumber = 2,
    kErrorsFieldNumber = 3,
    kReqIdFieldNumber = 1,
    kTotalSizeFieldNumber = 4,
  };
  // bytes data = 2;
  void clear_data();
  const std::string& data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_data();
  PROTOBUF_NODISCARD std::string* release_data();
  void set_allocated_data(std::string* data);
  private:
  const std::string& _internal_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_data(const std::string& value);
  std::string* _internal_mutable_data();
  public:

  // string errors = 3;
  void clear_errors();
  const std::string& errors() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_errors(ArgT0&& arg0, ArgT... args);
  std::string* mutable_errors();
  PROTOBUF_NODISCARD std::string* release_errors();
  void set_allocated_errors(std::string* errors);
  private:
  const std::string& _internal_errors() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_errors(const std::string& value);
  std::string* _internal_mutable_errors();
  public:

  // int64 ReqId = 1;
  void clear_reqid();
  int64_t reqid() const;
  void set_reqid(int64_t value);
  private:
  int64_t _internal_reqid() const;
  void _internal_set_reqid(int64_t value);
  public:

  // int32 totalSize = 4;
  void clear_totalsize();
  int32_t totalsize() const;
  void set_totalsize(int32_t value);
  private:
  int32_t _internal_totalsize() const;
  void _internal_set_totalsize(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:mdt_dialout.MdtDialoutArgs)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr data_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr errors_;
  int64_t reqid_;
  int32_t totalsize_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_mdt_5fdialout_5fcisco_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MdtDialoutArgs

// int64 ReqId = 1;
inline void MdtDialoutArgs::clear_reqid() {
  reqid_ = int64_t{0};
}
inline int64_t MdtDialoutArgs::_internal_reqid() const {
  return reqid_;
}
inline int64_t MdtDialoutArgs::reqid() const {
  // @@protoc_insertion_point(field_get:mdt_dialout.MdtDialoutArgs.ReqId)
  return _internal_reqid();
}
inline void MdtDialoutArgs::_internal_set_reqid(int64_t value) {
  
  reqid_ = value;
}
inline void MdtDialoutArgs::set_reqid(int64_t value) {
  _internal_set_reqid(value);
  // @@protoc_insertion_point(field_set:mdt_dialout.MdtDialoutArgs.ReqId)
}

// bytes data = 2;
inline void MdtDialoutArgs::clear_data() {
  data_.ClearToEmpty();
}
inline const std::string& MdtDialoutArgs::data() const {
  // @@protoc_insertion_point(field_get:mdt_dialout.MdtDialoutArgs.data)
  return _internal_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MdtDialoutArgs::set_data(ArgT0&& arg0, ArgT... args) {
 
 data_.SetBytes(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mdt_dialout.MdtDialoutArgs.data)
}
inline std::string* MdtDialoutArgs::mutable_data() {
  std::string* _s = _internal_mutable_data();
  // @@protoc_insertion_point(field_mutable:mdt_dialout.MdtDialoutArgs.data)
  return _s;
}
inline const std::string& MdtDialoutArgs::_internal_data() const {
  return data_.Get();
}
inline void MdtDialoutArgs::_internal_set_data(const std::string& value) {
  
  data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* MdtDialoutArgs::_internal_mutable_data() {
  
  return data_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* MdtDialoutArgs::release_data() {
  // @@protoc_insertion_point(field_release:mdt_dialout.MdtDialoutArgs.data)
  return data_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void MdtDialoutArgs::set_allocated_data(std::string* data) {
  if (data != nullptr) {
    
  } else {
    
  }
  data_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), data,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (data_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mdt_dialout.MdtDialoutArgs.data)
}

// string errors = 3;
inline void MdtDialoutArgs::clear_errors() {
  errors_.ClearToEmpty();
}
inline const std::string& MdtDialoutArgs::errors() const {
  // @@protoc_insertion_point(field_get:mdt_dialout.MdtDialoutArgs.errors)
  return _internal_errors();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MdtDialoutArgs::set_errors(ArgT0&& arg0, ArgT... args) {
 
 errors_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mdt_dialout.MdtDialoutArgs.errors)
}
inline std::string* MdtDialoutArgs::mutable_errors() {
  std::string* _s = _internal_mutable_errors();
  // @@protoc_insertion_point(field_mutable:mdt_dialout.MdtDialoutArgs.errors)
  return _s;
}
inline const std::string& MdtDialoutArgs::_internal_errors() const {
  return errors_.Get();
}
inline void MdtDialoutArgs::_internal_set_errors(const std::string& value) {
  
  errors_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* MdtDialoutArgs::_internal_mutable_errors() {
  
  return errors_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* MdtDialoutArgs::release_errors() {
  // @@protoc_insertion_point(field_release:mdt_dialout.MdtDialoutArgs.errors)
  return errors_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void MdtDialoutArgs::set_allocated_errors(std::string* errors) {
  if (errors != nullptr) {
    
  } else {
    
  }
  errors_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), errors,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (errors_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    errors_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mdt_dialout.MdtDialoutArgs.errors)
}

// int32 totalSize = 4;
inline void MdtDialoutArgs::clear_totalsize() {
  totalsize_ = 0;
}
inline int32_t MdtDialoutArgs::_internal_totalsize() const {
  return totalsize_;
}
inline int32_t MdtDialoutArgs::totalsize() const {
  // @@protoc_insertion_point(field_get:mdt_dialout.MdtDialoutArgs.totalSize)
  return _internal_totalsize();
}
inline void MdtDialoutArgs::_internal_set_totalsize(int32_t value) {
  
  totalsize_ = value;
}
inline void MdtDialoutArgs::set_totalsize(int32_t value) {
  _internal_set_totalsize(value);
  // @@protoc_insertion_point(field_set:mdt_dialout.MdtDialoutArgs.totalSize)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace mdt_dialout

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_mdt_5fdialout_5fcisco_2eproto
