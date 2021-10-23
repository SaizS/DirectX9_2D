texture map;
sampler samp
{
    Texture = map;
};

float4 color;

//0 기본
//1 가산 혼합
//2 그레이스케일

float4 main(float2 uv : TEXCOORD) : SV_TARGET
{
    float4 result = tex2D(samp, uv);
    return result * color;
}

technique tech
{
    pass p0
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;

        PixelShader = compile ps_2_0 main();
    }
}