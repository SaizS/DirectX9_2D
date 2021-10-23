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

float4 Grayscale(float2 uv : TEXCOORD) : SV_TARGET
{
    float4 result = tex2D(samp, uv);
    float scale = dot(result.rgb, float3(0.3f, 0.59f, 0.11f));
        
    return float4(scale.xxx, result.a) * color;
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

    pass p1
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        SrcBlend = SrcAlpha;
        DestBlend = One;

        PixelShader = compile ps_2_0 main();
    }

    pass p2
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;

        PixelShader = compile ps_2_0 Grayscale();
    }
}