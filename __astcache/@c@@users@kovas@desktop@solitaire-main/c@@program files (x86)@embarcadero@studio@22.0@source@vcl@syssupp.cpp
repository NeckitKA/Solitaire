// -----------------------------------------------------------------------------------
// syssupp.cpp: System namespace support functions
//
// $Rev: 112483 $
//
// Copyright(c) 1995-2023 Embarcadero Technologies, Inc.
//              All rights reserved
// -----------------------------------------------------------------------------------

#if defined(_WIN32) && !defined(_WIN64) && defined(__clang__)
 #define CLANG_WIN32
#endif

#include <System.hpp>
#include <System.SyncObjs.hpp>
#include <System_thunks.h>
#include <assert.h>
#if defined(_WIN32) && !defined(_DELPHI_NEXTGEN)
 #include <System.Win.ComObj.hpp>
#endif

#ifdef __clang__
#include <mutex>
#include <unordered_map>
#include <string.h>
#include <System.Typinfo.hpp>
#endif

namespace System
{
  String __fastcall LoadResourceString(ResourceString const * const rsrc)
  {
    return System::LoadResString(const_cast<TResStringRec*>(rsrc));
  }

#ifdef _WIN32
 #ifdef _WIN64
  extern long __fastcall _CheckAutoResult(long);
 #endif

  void __fastcall CheckSafecallResult(HRESULT hr)
  {
 #if defined(_WIN32) && !defined(_DELPHI_NEXTGEN)
    static int *volatile __init_comobj = &System::Win::Comobj::CoInitFlags;
 #endif
 #if defined(_WIN64)
    System::_CheckAutoResult(hr);
 #else
    typedef void (__fastcall *_System__CheckAutoResult_Proc)(long);
    (reinterpret_cast<_System__CheckAutoResult_Proc>(_System__CheckAutoResult))(hr);
 #endif
  }
#endif

  void* InterLockedExchg(void** p1, void* p2)
  {
    return System::Syncobjs::TInterlocked::Exchange(*p1, p2);
  }

#ifdef __clang__
  extern const bool _init_inst = false;
#endif

  _di_IInterface __fastcall TAggregatedObject::GetController()
  {
    _di_IInterface result;
    IInterface **ppIntf = static_cast<IInterface**>(&result);
    *ppIntf = static_cast<IInterface*>(FController);
    return result;
  }
}

#ifdef __clang__

// The following RTTI type declarations are copied from libcxxabi to faciliate
// the creation of a data structure that's binary compatible with std::type_info in two ways
// For more details see __delphi_type_info in this file.

namespace {
  // This declaration serves the purpose of writing to the type name field *and* making it
  // possible to instantiate the __class_type_info type.
  class fake_type_info {
  public:
    virtual ~fake_type_info() {}
    const char *__type_name;
  };
}


namespace __cxxabiv1
{
class __shim_type_info
    : public ::fake_type_info
{
public:
    virtual ~__shim_type_info();
    inline __shim_type_info() {}

    virtual void noop1() const;
    virtual void noop2() const;
    virtual bool can_catch(const __shim_type_info* thrown_type, void*& adjustedPtr) const = 0;
    virtual bool equals(__shim_type_info const &rhs) const;
    bool is_equal(__shim_type_info const *prhs) const;
};

struct __dynamic_cast_info;

class __class_type_info : public __shim_type_info
{
public:
    // Make sure the vtable is imported from the run-time dll.
#if defined(_WIN32)
    __declspec(dllimport)
#endif
    virtual ~__class_type_info();
    inline __class_type_info() {}

    void process_static_type_above_dst(__dynamic_cast_info*, const void*, const void*, int) const;
    void process_static_type_below_dst(__dynamic_cast_info*, const void*, int) const;
    void process_found_base_class(__dynamic_cast_info*, void*, int) const;
    virtual void search_above_dst(__dynamic_cast_info*, const void*, const void*, int) const;
    virtual void search_below_dst(__dynamic_cast_info*, const void*, int) const;
    virtual bool can_catch(const __shim_type_info*, void*&) const;
    virtual void has_unambiguous_public_base(__dynamic_cast_info*, void*, int) const;
};

}

#endif // defined(__clang__)

extern "C" {

#ifdef __clang__

// NOTE: Temporary until RTL implements better
// Similar to __cxxabiv1::__dynamic_cast but for Delphi-style classes
void* __dynamic_delphi_cast(const void *src_ptr,  // object started from
                            const void *src_type, // type of the starting object
                            const void *dst_type) // desired target type
{
  if (!src_ptr)
    return 0;

  assert(src_type  && "Must specify valid src_type VMT to __dynamic_delphi_cast");
  assert(dst_type  && "Must specify valid dst_type VMT to __dynamic_delphi_cast");
  System::TClass* src_cls = (System::TClass*)(src_type);
  System::TClass* dst_cls = (System::TClass*)(dst_type);

  System::TObject* obj = reinterpret_cast<System::TObject*>(const_cast<void*>(src_ptr));
  return obj->InheritsFrom(*dst_cls) ? obj : 0;
}

#if defined(__clang__)
void *__delphi_type_info(System::Typinfo::PTypeInfo *delphi_type_info_ptr) {
    System::Typinfo::TTypeInfo *delphi_type_info = *delphi_type_info_ptr;
    assert(delphi_type_info);
    static std::mutex type_info_mutex;
    std::lock_guard<std::mutex> guard(type_info_mutex);
    static std::unordered_map<System::Typinfo::TTypeInfo *, std::type_info*> type_info_map;
    std::type_info*& ti = type_info_map[delphi_type_info];
    if (!ti) {
        UTF8String utf8_name(System::Typinfo::GetTypeName(delphi_type_info));
        if (auto *type_data = System::Typinfo::GetTypeData(delphi_type_info)) {
            UTF8String unit_name(type_data->UnitNameFld().ToString());
            utf8_name = unit_name + "." + utf8_name;
        }
        // This hack serves the purpose of creating an object in memory that's binary
        // compatible with the std::type_info derivate that the compiler would generate
        // for a class without base, with the difference that the type name is not
        // known at compile time.
        // The memory layout is, roughly, two pointers:
        //    (1) the pointer to the vtable of ::__cxxabiv1::__class_type_info
        //    (2) the __type_name string pointer
        //
        // The __type_name pointer is needed for the inline std::type_info::name() function
        // to work (returns that pointer). The vtable pointer is needed for the
        // implementation of std::type_info::operator==() to work, which performs a dynamic_cast
        // to __shim_type_info in order to call the virtual equals() method on it. Eventually
        // that will just compare strings, but the dynamic_cast must work to avoid crashing.
        auto class_type_info = new ::__cxxabiv1::__class_type_info();
        class_type_info->__type_name = strdup(utf8_name.c_str());
        ti = reinterpret_cast<std::type_info *>(class_type_info);
    }
    return ti;
}

void *__dynamic_delphi_type_info(System::TObject *obj) {
    assert(obj);
    auto ti = reinterpret_cast<System::Typinfo::TTypeInfo *>(obj->ClassInfo());
    return __delphi_type_info(&ti);
}
#endif // defined(__clang__)

#if defined(_DELPHI_AUTOREFCOUNT)

void System_InstCopy(void**, void*);
void System_InstAddRef(void*);
void System_InstClear(void**);

void System_InstWeakClear(void**);
void System_InstWeakCopy(void**, void*);

void System_AsgClosureObj(void*, void*, void*);
void System_ClosureAddWeakRef(void*);
void System_ClosureRemoveWeakRef(void*);
void System_CopyClosure(void*, void*);

#else

static void System_InstCopy(void** dst, void* src)
{
  *dst = src;
}

static void System_InstAddRef(void*)
{
}

static void System_InstClear(void**)
{
}

void System_InstWeakClear(void**)
{
}

void System_InstWeakCopy(void**, void*)
{
}

void System_AsgClosureObj(void*, void*, void*)
{
}

void System_ClosureAddWeakRef(void*)
{
}

void System_ClosureRemoveWeakRef(void*)
{
}

void System_CopyClosure(void*, void*)
{
}

#endif

#include <stdio.h>

void (*ARC_LOG_PROC)(const char*);

void bcp_storeStrong(void** dst, void* src)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    if (dst)
      sprintf(msg, "%s([%p->%p], [%p])", __func__, dst, *dst, src);
    else
      sprintf(msg, "%s([%p], [%p])", __func__, dst, src);
    ARC_LOG_PROC(msg);
  }
  System_InstCopy(dst, src);
}

void bcp_initStrong(void** dst, void* src)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    if (dst)
      sprintf(msg, "%s([%p->%p], [%p])", __func__, dst, *dst, src);
    else
      sprintf(msg, "%s([%p], [%p])", __func__, dst, src);
    ARC_LOG_PROC(msg);
  }
  *dst = 0;
  System_InstCopy(dst, src);
}

void bcp_addref(void* p)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    sprintf(msg, "%s([%p])", __func__, p);
    ARC_LOG_PROC(msg);
  }
  System_InstAddRef(p);
}

void bcp_release(void** dst)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    if (dst)
      sprintf(msg, "%s([%p->%p])", __func__, dst, *dst);
    else
      sprintf(msg, "%s([%p])", __func__, dst);
    ARC_LOG_PROC(msg);
  }
  if (dst)
    System_InstClear(dst);
}

void bcp_initWeak(void** dst, void* src)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    if (dst)
      sprintf(msg, "%s([%p->%p], [%p])", __func__, dst, *dst, src);
    else
      sprintf(msg, "%s([%p], [%p])", __func__, dst, src);
    ARC_LOG_PROC(msg);
  }
  *dst = 0;
  System_InstWeakCopy(dst, src);
}

void bcp_releaseWeak(void** dst)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    if (dst)
      sprintf(msg, "%s([%p->%p])", __func__, dst, *dst);
    else
      sprintf(msg, "%s([%p])", __func__, dst);
    ARC_LOG_PROC(msg);
  }
  if (dst)
    System_InstWeakClear(dst);
}

void bcp_storeWeak(void** dst, void* src)
{
  if (ARC_LOG_PROC)
  {
    char msg[100];
    if (dst)
      sprintf(msg, "%s([%p->%p], [%p])", __func__, dst, *dst, src);
    else
      sprintf(msg, "%s([%p], [%p])", __func__, dst, src);
    ARC_LOG_PROC(msg);
  }
  System_InstWeakCopy(dst, src);
}

void bcp_closureAddref(void *p)
{
  System_ClosureAddWeakRef(p);
}

void bcp_closureRelease(void *p)
{
  System_ClosureRemoveWeakRef(p);
}

void bcp_closureCopy(void *dst, void *src)
{
  System_CopyClosure(dst, src);
}

void bcp_closureAsg(void *p, void *data, void *code)
{
  System_AsgClosureObj(p, data, code);
}

#endif // __clang__
} // extern "C"

#if defined(_WIN32)

#include <utilcls.h>

// Specialization of DebugHlpr_HRCHECK to handle safecall exceptions
// and generate an EOleException with rich error info.
template <>
HRESULT DebugHlpr_HRCHECK(HRESULT hr, const char* /*expr*/,
                          const char* /*file*/, int /*line*/)
{
  System::CheckSafecallResult(hr);
  return hr;
}
#endif

// NOTE: There's no need to expose DebugLog for Android as librtlhelper.a (delphi_support.cpp)
//       made a copy of DebugLog and the Andoid linker is unhappy about duplicates symbols
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)

// Simple DebugLog(const char *fmt, ...) routine for debugging purposes on Mobile

#ifdef __APPLE__
#include <asl.h>
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define LOGI(...) ((void)__android_log_vprint(ANDROID_LOG_INFO, "CppApp", __VA_ARGS__))
#endif

#include <stdarg.h>

#ifdef __APPLE__
#include <asl.h>
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define LOGI(...) ((void)__android_log_vprint(ANDROID_LOG_INFO, "CppApp", __VA_ARGS__))
#endif

#include <stdarg.h>

extern "C" void DebugLog(const char* fmt, ...) {
#ifdef __APPLE__
  static aslclient debugClient = 0;
  if (!debugClient) {
    debugClient = asl_open("CppApp", "com.apple.console", ASL_OPT_STDERR|ASL_OPT_NO_DELAY);
    assert(debugClient);
  }
#endif

  va_list vl;
  va_start(vl, fmt);

#ifdef __APPLE__
  aslmsg msg = asl_new(ASL_TYPE_MSG);
  asl_set(msg, ASL_KEY_FACILITY, "com.apple.console");
  asl_vlog(debugClient, msg, ASL_LEVEL_WARNING, fmt, vl);
#endif

#ifdef __ANDROID__
  LOGI(fmt, vl);
#endif

  va_end(vl);
}

#endif


#if defined(__APPLE__)
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysctl.h>

// http://developer.apple.com/library/mac/#qa/qa1361/_index.html
// Returns true if the current process is being debugged (either
// running under the debugger or has a debugger attached post facto).
bool IsDebuggerPresent(void)
{
  int                 junk;
  int                 mib[4];
  struct kinfo_proc   info;
  size_t              size;

  // Initialize the flags so that, if sysctl fails for some bizarre
  // reason, we get a predictable result.

  info.kp_proc.p_flag = 0;

  // Initialize mib, which tells sysctl the info we want, in this case
  // we're looking for information about a specific process ID.

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PID;
  mib[3] = getpid();

  // Call sysctl.

  size = sizeof(info);
  junk = sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, NULL, 0);
  assert(junk == 0);

  // We're being debugged if the P_TRACED flag is set.

  return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
}
#endif