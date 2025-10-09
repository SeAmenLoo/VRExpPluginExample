#pragma once

#include "Iris/Serialization/NetSerializer.h"
#include "VRBPDatatypes.h"

#include "FTransformNetQuantizeNetSerializer.generated.h"

USTRUCT()
struct FTransformNetQuantizeNetSerializerConfig : public FNetSerializerConfig
{
    GENERATED_BODY()
};

namespace UE::Net
{
    UE_NET_DECLARE_SERIALIZER(FTransformNetQuantizeNetSerializer, VREXPANSIONPLUGIN_API);
}