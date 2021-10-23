//LightShader
float2 lightPos;
float2 imageSize;
float range;

texture map;
sampler samp
{
    Texture = map;
};

float4 main(float2 uv : TEXCOORD) : SV_TARGET
{
    float4 result = tex2D(samp, uv);

    float2 pixelCoord = uv * imageSize;

    float dist = distance(pixelCoord, lightPos);

    //if(dist > range)
        //return float4(0, 0, 0, 0);
    result -= dist * (range * 0.0001f);

    return result;
}

technique tech
{
    pass p0
    {
        PixelShader = compile ps_2_0 main();
    }
}