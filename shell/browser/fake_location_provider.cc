// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/fake_location_provider.h"

#include "base/functional/callback.h"
#include "base/time/time.h"
#include "services/device/public/mojom/geoposition.mojom-shared.h"
#include "services/device/public/mojom/geoposition.mojom.h"

namespace electron {

FakeLocationProvider::FakeLocationProvider() {
  result_ = device::mojom::GeopositionResult::NewError(
      device::mojom::GeopositionError::New(
          device::mojom::GeopositionErrorCode::kPositionUnavailable,
          "Position unavailable.", ""));
}

FakeLocationProvider::~FakeLocationProvider() = default;

void FakeLocationProvider::SetUpdateCallback(
    const LocationProviderUpdateCallback& callback) {
  callback_ = callback;
}

void FakeLocationProvider::StartProvider(bool high_accuracy) {}

void FakeLocationProvider::StopProvider() {}

const device::mojom::GeopositionResult* FakeLocationProvider::GetPosition() {
  return result_.get();
}

void FakeLocationProvider::OnPermissionGranted() {
  if (!callback_.is_null()) {
    callback_.Run(this, result_.Clone());
  }
}

}  // namespace electron
