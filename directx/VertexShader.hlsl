cbuffer myCBuffer : register(b0)
{
     float4x4 mat;
};

struct VS_INPUT
{
    float3 inPos : POSITION;
    float2 inTEXCOORD  : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 outPos :SV_POSITION;
    float2 outTEXCOORD : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.outPos = mul(float4(input.inPos, 1.0f),mat);
    output.outTEXCOORD = input.inTEXCOORD;
    return output;

}