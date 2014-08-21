// Copyright 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MINI_CHROMIUM_BASE_SYNCHRONIZATION_LOCK_IMPL_H_
#define MINI_CHROMIUM_BASE_SYNCHRONIZATION_LOCK_IMPL_H_

#include <pthread.h>

#include "base/basictypes.h"

namespace base {
namespace internal {

// This class implements the underlying platform-specific spin-lock mechanism
// used for the Lock class.  Most users should not use LockImpl directly, but
// should instead use Lock.
class LockImpl {
 public:
  LockImpl();
  ~LockImpl();

  // If the lock is not held, take it and return true.  If the lock is already
  // held by something else, immediately return false.
  bool Try();

  // Take the lock, blocking until it is available if necessary.
  void Lock();

  // Release the lock.  This must only be called by the lock's holder: after
  // a successful call to Try, or a call to Lock.
  void Unlock();

  // Return the native underlying lock.
  // TODO(awalker): refactor lock and condition variables so that this is
  // unnecessary.
  pthread_mutex_t* native_handle() { return &lock_; }

 private:
  pthread_mutex_t lock_;

  DISALLOW_COPY_AND_ASSIGN(LockImpl);
};

}  // namespace internal
}  // namespace base

#endif  // MINI_CHROMIUM_BASE_SYNCHRONIZATION_LOCK_IMPL_H_
