#pragma once

#include "CoreMinimal.h"


// Helpers for Iris serialization

namespace UE::Net
{
	// -----------------------------------------------------------------------------
	// Fixed-compression helpers for 0–MaxValue floats with BitCount precision
	// Epic doesn't have per float compression helpers yet for Iris serializers
	// -----------------------------------------------------------------------------

	// Based on Epics FixedCompressionFloat functions for std archives

	template<int32 MaxValue, uint32 NumBits>
	uint32 GetCompressedFloat(const float Value)
	{
		using Details = TFixedCompressedFloatDetails<MaxValue, NumBits>;

		bool clamp = false;
		int64 ScaledValue;
		if (MaxValue > Details::MaxBitValue)
		{
			// We have to scale this down
			const float Scale = float(Details::MaxBitValue) / MaxValue;
			ScaledValue = FMath::TruncToInt(Scale * Value);
		}
		else
		{
			// We will scale up to get extra precision. But keep is a whole number preserve whole values
			constexpr int32 Scale = Details::MaxBitValue / MaxValue;
			ScaledValue = FMath::RoundToInt(Scale * Value);
		}

		uint32 Delta = static_cast<uint32>(ScaledValue + Details::Bias);

		if (Delta > Details::MaxDelta)
		{
			clamp = true;
			Delta = static_cast<int32>(Delta) > 0 ? Details::MaxDelta : 0;
		}

		return Delta;
	}

	template<int32 MaxValue, uint32 NumBits>
	float GetDecompressedFloat(uint32 Delta)
	{
		using Details = TFixedCompressedFloatDetails<MaxValue, NumBits>;

		float Value = 0.0f;

		float UnscaledValue = static_cast<float>(static_cast<int32>(Delta) - Details::Bias);

		if constexpr (MaxValue > Details::MaxBitValue)
		{
			// We have to scale down, scale needs to be a float:
			constexpr float InvScale = MaxValue / (float)Details::MaxBitValue;
			Value = UnscaledValue * InvScale;
		}
		else
		{
			constexpr int32 Scale = Details::MaxBitValue / MaxValue;
			constexpr float InvScale = float(1) / (float)Scale;

			Value = UnscaledValue * InvScale;
		}

		return Value;
	}
}