texture map;
sampler samp
{
    Texture = map;
};

float4 color;

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
        DestBlend = InvSrcAlpha;

        PixelShader = compile ps_2_0 Grayscale();
    }

    pass p2 //Negative
    {
        AlphaBlendEnable = true;
        BlendOp = RevSubtract;
        SrcBlend = SrcAlpha;
        DestBlend = One;

        PixelShader = compile ps_2_0 main();
    }

    pass p3 //Negative
    {
        AlphaBlendEnable = true;
        BlendOp = Subtract;
        SrcBlend = One;
        DestBlend = One;

        PixelShader = compile ps_2_0 main();
    }
}