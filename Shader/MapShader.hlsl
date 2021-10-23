texture map;
sampler samp
{
    Texture = map;
};

float4 color;

//0 �⺻
//1 ���� ȥ��
//2 �׷��̽�����

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