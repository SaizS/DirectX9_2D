texture map;
sampler samp
{
    Texture = map;
};

float4 color;

float value;

float4 main(float2 uv : TEXCOORD) : SV_TARGET
{
    float4 result = tex2D(samp, uv);

    if(uv.x > value)
        result.a = 0;

    return result;
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