

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState PointSampler : register(s0);


cbuffer PostProcessingCB: register(b0)
{
    float4  Color;
    //----------
    int UseHDR;
    int UseBloom;
    int UseDepthOfF;
    int UseColour;
    //------------
    int UseBlur;
    float fadeAmount;
    float FarPlane;
    float focalwidth;
    //--------------
    float focalDistance;
    float blerAttenuation;
    int pad1;
    int pad2;
};

struct QuadVS_Input 
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

struct QuadVS_Output 
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float2 texCoord1 : TEXCOORD1;
    float2 texCoord2 : TEXCOORD2;
    float2 texCoord3 : TEXCOORD3;
    float2 texCoord4 : TEXCOORD4;
    float2 texCoord5 : TEXCOORD5;
    float2 texCoord6 : TEXCOORD6;
    float2 texCoord7 : TEXCOORD7;
    float2 texCoord8 : TEXCOORD8;
    float2 texCoord9 : TEXCOORD9;
};

QuadVS_Output QuadVS(QuadVS_Input Input)
{
    // no mvp transform - model coordinates already in projection space (-1 to 1)
    QuadVS_Output Output;
    Output.Pos = Input.Pos;
    Output.Tex = Input.Tex;

    // Determine the floating point size of a texel for a screen with this specific width.
   float texelSize = 1.0f / 1280;

    // Create UV coordinates for the pixel and its four horizontal neighbors on either side.
   Output.texCoord1 = Input.Tex + float2(0.0f, texelSize * -4.0f);
   Output.texCoord2 = Input.Tex + float2(0.0f, texelSize * -3.0f);
   Output.texCoord3 = Input.Tex + float2(0.0f, texelSize * -2.0f);
   Output.texCoord4 = Input.Tex + float2(0.0f, texelSize * -1.0f);
   Output.texCoord5 = Input.Tex + float2(0.0f, texelSize * 0.0f);
   Output.texCoord6 = Input.Tex + float2(0.0f, texelSize * 1.0f);
   Output.texCoord7 = Input.Tex + float2(0.0f, texelSize * 2.0f);
   Output.texCoord8 = Input.Tex + float2(0.0f, texelSize * 3.0f);
   Output.texCoord9 = Input.Tex + float2(0.0f, texelSize * 4.0f);


    return Output;
}

//Pixel shader
float4 QuadPS(QuadVS_Output Input) : SV_TARGET
{
    float4 vColor = tex.Sample(PointSampler, Input.Tex);
    
    if (UseBloom == 1) {

       float4 vColor2 = tex2.Sample(PointSampler, Input.Tex);
       vColor = vColor+ (0.3*vColor2);
       

    }
    if (UseColour == 1) {
        vColor = vColor * Color;

    }
  
    
    return vColor;
}
