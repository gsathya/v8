// Copyright 2019 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_COMPILER_FEEDBACK_SOURCE_H_
#define V8_COMPILER_FEEDBACK_SOURCE_H_

#include "src/compiler/heap-refs.h"
#include "src/objects/feedback-vector.h"

namespace v8 {
namespace internal {
namespace compiler {

struct FeedbackSource {
  enum ICState { kMonomorphic, kPolymorphic };

  FeedbackSource() { DCHECK(!IsValid()); }
  V8_EXPORT_PRIVATE FeedbackSource(Handle<FeedbackVector> vector_,
                                   FeedbackSlot slot_);
  FeedbackSource(FeedbackVectorRef vector_, FeedbackSlot slot_);
  explicit FeedbackSource(FeedbackNexus const& nexus);

  bool IsValid() const { return !vector.is_null() && !slot.IsInvalid(); }
  int index() const;

  Handle<FeedbackVector> vector;
  FeedbackSlot slot;
  ICState state;

  struct Hash {
    size_t operator()(FeedbackSource const& source) const {
      return base::hash_combine(source.vector.address(), source.slot);
    }
  };

  struct Equal {
    bool operator()(FeedbackSource const& lhs,
                    FeedbackSource const& rhs) const {
      return lhs.vector.equals(rhs.vector) && lhs.slot == rhs.slot;
    }
  };
};

bool operator==(FeedbackSource const&, FeedbackSource const&);
bool operator!=(FeedbackSource const&, FeedbackSource const&);

V8_EXPORT_PRIVATE std::ostream& operator<<(std::ostream& os,
                                           FeedbackSource const&);

}  // namespace compiler
}  // namespace internal
}  // namespace v8

#endif  // V8_COMPILER_FEEDBACK_SOURCE_H_
