#pragma once

namespace xlink2 {
enum class ValueReferenceType {
    Direct,                           
    String,                           
    Curve,                            
    Random,                           
    Unknown1,                      
    Unknown2,
    Random2Pow,
    Random3Pow,
    Random4Pow,
    Random1Point5Pow,
    RandomWeightMin2Pow,
    RandomWeightMin3Pow,
    RandomWeightMin4Pow,
    RandomWeightMin1Point5Pow,
    RandomWeightMax2Pow,
    RandomWeightMax3Pow,
    RandomWeightMax4Pow,
    RandomWeightMax1Point5Pow,

};
}  // namespace xlink2