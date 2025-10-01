#pragma once

#include "Iris/Serialization/NetSerializer.h"
#include "Iris/Serialization/NetSerializers.h"
#include "Iris/Serialization/NetSerializerDelegates.h"
#include "VRBPDatatypes.h"

#include "FBPAdvGripPhysicsSettingsNetSerializer.generated.h"

USTRUCT()
struct FBPAdvGripPhysicsSettingsNetSerializerConfig : public FNetSerializerConfig
{
    GENERATED_BODY()
};

namespace UE::Net
{
    UE_NET_DECLARE_SERIALIZER(FBPAdvGripPhysicsSettingsNetSerializer, VREXPANSIONPLUGIN_API);


}