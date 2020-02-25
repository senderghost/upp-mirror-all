/*** Autogenerated by WIDL 4.12.1 from include/dxva2api.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __dxva2api_h__
#define __dxva2api_h__

/* Forward declarations */

#ifndef __IDirect3DDeviceManager9_FWD_DEFINED__
#define __IDirect3DDeviceManager9_FWD_DEFINED__
typedef interface IDirect3DDeviceManager9 IDirect3DDeviceManager9;
#ifdef __cplusplus
interface IDirect3DDeviceManager9;
#endif /* __cplusplus */
#endif

#ifndef __IDirectXVideoDecoder_FWD_DEFINED__
#define __IDirectXVideoDecoder_FWD_DEFINED__
typedef interface IDirectXVideoDecoder IDirectXVideoDecoder;
#ifdef __cplusplus
interface IDirectXVideoDecoder;
#endif /* __cplusplus */
#endif

#ifndef __IDirectXVideoAccelerationService_FWD_DEFINED__
#define __IDirectXVideoAccelerationService_FWD_DEFINED__
typedef interface IDirectXVideoAccelerationService IDirectXVideoAccelerationService;
#ifdef __cplusplus
interface IDirectXVideoAccelerationService;
#endif /* __cplusplus */
#endif

#ifndef __IDirectXVideoDecoderService_FWD_DEFINED__
#define __IDirectXVideoDecoderService_FWD_DEFINED__
typedef interface IDirectXVideoDecoderService IDirectXVideoDecoderService;
#ifdef __cplusplus
interface IDirectXVideoDecoderService;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <unknwn.h>

#ifdef __cplusplus
extern "C" {
#endif

#if 0
typedef DWORD IDirect3DDevice9;
typedef DWORD IDirect3DSurface9;
typedef DWORD D3DFORMAT;
typedef DWORD D3DPOOL;
#endif
#ifndef __IDirectXVideoDecoderService_FWD_DEFINED__
#define __IDirectXVideoDecoderService_FWD_DEFINED__
typedef interface IDirectXVideoDecoderService IDirectXVideoDecoderService;
#ifdef __cplusplus
interface IDirectXVideoDecoderService;
#endif /* __cplusplus */
#endif

#ifndef __REFERENCE_TIME_DEFINED
#define __REFERENCE_TIME_DEFINED
typedef LONGLONG REFERENCE_TIME;
#endif /*__REFERENCE_TIME_DEFINED*/
#define DXVA2_ProcAmp_None 0x0000
#define DXVA2_ProcAmp_Brightness 0x0001
#define DXVA2_ProcAmp_Contrast 0x0002
#define DXVA2_ProcAmp_Hue 0x0004
#define DXVA2_ProcAmp_Saturation 0x0008

#define DXVA2_E_NOT_INITIALIZED     MAKE_HRESULT(1, 4, 4096)
#define DXVA2_E_NEW_VIDEO_DEVICE    MAKE_HRESULT(1, 4, 4097)
#define DXVA2_E_VIDEO_DEVICE_LOCKED MAKE_HRESULT(1, 4, 4098)
#define DXVA2_E_NOT_AVAILABLE       MAKE_HRESULT(1, 4, 4099)

DEFINE_GUID(DXVA2_ModeMPEG2_MoComp, 0xe6a9f44b, 0x61b0,0x4563, 0x9e,0xa4,0x63,0xd2,0xa3,0xc6,0xfe,0x66);
DEFINE_GUID(DXVA2_ModeMPEG2_IDCT, 0xbf22ad00, 0x03ea,0x4690, 0x80,0x77,0x47,0x33,0x46,0x20,0x9b,0x7e);
DEFINE_GUID(DXVA2_ModeMPEG2_VLD, 0xee27417f, 0x5e28,0x4e65, 0xbe,0xea,0x1d,0x26,0xb5,0x08,0xad,0xc9);
DEFINE_GUID(DXVA2_ModeH264_A, 0x1b81be64, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_B, 0x1b81be65, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_C, 0x1b81be66, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_D, 0x1b81be67, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_E, 0x1b81be68, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_F, 0x1b81be69, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeWMV8_A, 0x1b81be80, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeWMV8_B, 0x1b81be81, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeWMV9_A, 0x1b81be90, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeWMV9_B, 0x1b81be91, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeWMV9_C, 0x1b81be94, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_A, 0x1b81beA0, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_B, 0x1b81beA1, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_C, 0x1b81beA2, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_D, 0x1b81beA3, 0xa0c7,0x11d3, 0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);

typedef enum _DXVA2_SampleFormat {
  DXVA2_SampleFormatMask                  = 0x00FF,
  DXVA2_SampleUnknown                     = 0,
  DXVA2_SampleProgressiveFrame            = 2,
  DXVA2_SampleFieldInterleavedEvenFirst   = 3,
  DXVA2_SampleFieldInterleavedOddFirst    = 4,
  DXVA2_SampleFieldSingleEven             = 5,
  DXVA2_SampleFieldSingleOdd              = 6,
  DXVA2_SampleSubStream                   = 7 
} DXVA2_SampleFormat;

typedef enum _DXVA2_VideoChromaSubSampling {
  DXVA2_VideoChromaSubsamplingMask                              = 0x0F,
  DXVA2_VideoChromaSubsampling_Unknown                          = 0,
  DXVA2_VideoChromaSubsampling_ProgressiveChroma                = 0x8,
  DXVA2_VideoChromaSubsampling_Horizontally_Cosited             = 0x4,
  DXVA2_VideoChromaSubsampling_Vertically_Cosited               = 0x2,
  DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes   = 0x1,
  DXVA2_VideoChromaSubsampling_MPEG2                            = 
              DXVA2_VideoChromaSubsampling_Horizontally_Cosited |
              DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  DXVA2_VideoChromaSubsampling_MPEG1                            = 
              DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  DXVA2_VideoChromaSubsampling_DV_PAL                           = 
              DXVA2_VideoChromaSubsampling_Horizontally_Cosited | 
              DXVA2_VideoChromaSubsampling_Vertically_Cosited,
  DXVA2_VideoChromaSubsampling_Cosited                          = 
              DXVA2_VideoChromaSubsampling_Horizontally_Cosited | 
              DXVA2_VideoChromaSubsampling_Vertically_Cosited | 
              DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes 
} DXVA2_VideoChromaSubSampling;

typedef enum _DXVA2_NominalRange {
  DXVA2_NominalRangeMask       = 0x07,
  DXVA2_NominalRange_Unknown   = 0,
  DXVA2_NominalRange_Normal    = 1,
  DXVA2_NominalRange_Wide      = 2,
  DXVA2_NominalRange_0_255     = 1,
  DXVA2_NominalRange_16_235    = 2,
  DXVA2_NominalRange_48_208    = 3 
} DXVA2_NominalRange;

typedef enum _DXVA2_VideoLighting {
  DXVA2_VideoLightingMask       = 0x0F,
  DXVA2_VideoLighting_Unknown   = 0,
  DXVA2_VideoLighting_bright    = 1,
  DXVA2_VideoLighting_office    = 2,
  DXVA2_VideoLighting_dim       = 3,
  DXVA2_VideoLighting_dark      = 4 
} DXVA2_VideoLighting;

typedef enum _DXVA2_VideoPrimaries {
  DXVA2_VideoPrimariesMask             = 0x001f,
  DXVA2_VideoPrimaries_Unknown         = 0,
  DXVA2_VideoPrimaries_reserved        = 1,
  DXVA2_VideoPrimaries_BT709           = 2,
  DXVA2_VideoPrimaries_BT470_2_SysM    = 3,
  DXVA2_VideoPrimaries_BT470_2_SysBG   = 4,
  DXVA2_VideoPrimaries_SMPTE170M       = 5,
  DXVA2_VideoPrimaries_SMPTE240M       = 6,
  DXVA2_VideoPrimaries_EBU3213         = 7,
  DXVA2_VideoPrimaries_SMPTE_C         = 8 
} DXVA2_VideoPrimaries;

typedef enum _DXVA2_VideoTransferFunction {
  DXVA2_VideoTransFuncMask       = 0x001f,
  DXVA2_VideoTransFunc_Unknown   = 0,
  DXVA2_VideoTransFunc_10        = 1,
  DXVA2_VideoTransFunc_18        = 2,
  DXVA2_VideoTransFunc_20        = 3,
  DXVA2_VideoTransFunc_22        = 4,
  DXVA2_VideoTransFunc_709       = 5,
  DXVA2_VideoTransFunc_240M      = 6,
  DXVA2_VideoTransFunc_sRGB      = 7,
  DXVA2_VideoTransFunc_28        = 8 
} DXVA2_VideoTransferFunction;

typedef enum  {
  DXVA2_SurfaceType_DecoderRenderTarget      = 0,
  DXVA2_SurfaceType_ProcessorRenderTarget    = 1,
  DXVA2_SurfaceType_D3DRenderTargetTexture   = 2 
} DXVA2_SurfaceType;

typedef enum _DXVA2_VideoTransferMatrix {
  DXVA2_VideoTransferMatrixMask         = 0x07,
  DXVA2_VideoTransferMatrix_Unknown     = 0,
  DXVA2_VideoTransferMatrix_BT709       = 1,
  DXVA2_VideoTransferMatrix_BT601       = 2,
  DXVA2_VideoTransferMatrix_SMPTE240M   = 3 
} DXVA2_VideoTransferMatrix;

typedef struct _DXVA2_AYUVSample16 {
  USHORT Cr;
  USHORT Cb;
  USHORT Y;
  USHORT Alpha;
} DXVA2_AYUVSample16;

typedef struct _DXVA2_AYUVSample8 {
  UCHAR Cr;
  UCHAR Cb;
  UCHAR Y;
  UCHAR Alpha;
} DXVA2_AYUVSample8;
typedef struct _DXVA2_ConfigPictureDecode {
    GUID guidConfigBitstreamEncryption;
    GUID guidConfigMBcontrolEncryption;
    GUID guidConfigResidDiffEncryption;
    UINT ConfigBitstreamRaw;
    UINT ConfigMBcontrolRasterOrder;
    UINT ConfigResidDiffHost;
    UINT ConfigSpatialResid8;
    UINT ConfigResid8Subtraction;
    UINT ConfigSpatialHost8or9Clipping;
    UINT ConfigSpatialResidInterleaved;
    UINT ConfigIntraResidUnsigned;
    UINT ConfigResidDiffAccelerator;
    UINT ConfigHostInverseScan;
    UINT ConfigSpecificIDCT;
    UINT Config4GroupedCoefs;
    USHORT ConfigMinRenderTargetBuffCount;
    USHORT ConfigDecoderSpecific;
} DXVA2_ConfigPictureDecode;
typedef struct _DXVA2_DecodeBufferDesc {
    DWORD CompressedBufferType;
    UINT BufferIndex;
    UINT DataOffset;
    UINT DataSize;
    UINT FirstMBaddress;
    UINT NumMBsInBuffer;
    UINT Width;
    UINT Height;
    UINT Stride;
    UINT ReservedBits;
    PVOID pvPVPState;
} DXVA2_DecodeBufferDesc;
typedef struct _DXVA2_DecodeExtensionData {
    UINT Function;
    PVOID pPrivateInputData;
    UINT PrivateInputDataSize;
    PVOID pPrivateOutputData;
    UINT PrivateOutputDataSize;
} DXVA2_DecodeExtensionData;
typedef struct _DXVA2_DecodeExecuteParams {
    UINT NumCompBuffers;
    DXVA2_DecodeBufferDesc *pCompressedBuffers;
    DXVA2_DecodeExtensionData *pExtensionData;
} DXVA2_DecodeExecuteParams;
typedef struct _DXVA2_ExtendedFormat {
    __C89_NAMELESS union {
        __C89_NAMELESS struct {
            UINT SampleFormat : 8;
            UINT VideoChromaSubsampling : 4;
            UINT NominalRange : 3;
            UINT VideoTransferMatrix : 3;
            UINT VideoLighting : 4;
            UINT VideoPrimaries : 5;
            UINT VideoTransferFunction : 5;
        } __C89_NAMELESSSTRUCTNAME;
        UINT value;
    } __C89_NAMELESSUNIONNAME;
} DXVA2_ExtendedFormat;
typedef struct _DXVA2_Fixed32 {
  __C89_NAMELESS union {
    __C89_NAMELESS struct {
      USHORT Fraction;
      SHORT  Value;
    } DUMMYSTRUCTNAME;
    LONG   ll;
  } DUMMYUNIONNAME;
} DXVA2_Fixed32;

typedef struct _DXVA2_FilterValues {
  DXVA2_Fixed32 Level;
  DXVA2_Fixed32 Threshold;
  DXVA2_Fixed32 Radius;
} DXVA2_FilterValues;
typedef struct _DXVA2_Frequency {
    UINT Numerator;
    UINT Denominator;
} DXVA2_Frequency;
typedef struct _DXVA2_ProcAmpValues {
  DXVA2_Fixed32 Brightness;
  DXVA2_Fixed32 Contrast;
  DXVA2_Fixed32 Hue;
  DXVA2_Fixed32 Saturation;
} DXVA2_ProcAmpValues;

typedef struct _DXVA2_ValueRange {
  DXVA2_Fixed32 MinValue;
  DXVA2_Fixed32 MaxValue;
  DXVA2_Fixed32 DefaultValue;
  DXVA2_Fixed32 StepSize;
} DXVA2_ValueRange;
typedef struct _DXVA2_VideoDesc {
    UINT SampleWidth;
    UINT SampleHeight;
    DXVA2_ExtendedFormat SampleFormat;
    D3DFORMAT Format;
    DXVA2_Frequency InputSampleFreq;
    DXVA2_Frequency OutputFrameFreq;
    UINT UABProtectionLevel;
    UINT Reserved;
} DXVA2_VideoDesc;
/* DeviceCaps
DXVA2_VPDev_EmulatedDXVA1
DXVA2_VPDev_HardwareDevice
DXVA2_VPDev_SoftwareDevice
*/
/* DeinterlaceTechnology
DXVA2_DeinterlaceTech_Unknown
DXVA2_DeinterlaceTech_BOBLineReplicate
DXVA2_DeinterlaceTech_BOBVerticalStretch
DXVA2_DeinterlaceTech_BOBVerticalStretch4Tap
DXVA2_DeinterlaceTech_MedianFiltering
DXVA2_DeinterlaceTech_EdgeFiltering
DXVA2_DeinterlaceTech_FieldAdaptive
DXVA2_DeinterlaceTech_PixelAdaptive
DXVA2_DeinterlaceTech_MotionVectorSteered
DXVA2_DeinterlaceTech_InverseTelecine
*/

/* VideoProcessorOperations
DXVA2_VideoProcess_YUV2RGB
DXVA2_VideoProcess_StretchX
DXVA2_VideoProcess_StretchY
DXVA2_VideoProcess_AlphaBlend
DXVA2_VideoProcess_SubRects
DXVA2_VideoProcess_SubStreams
DXVA2_VideoProcess_SubStreamsExtended
DXVA2_VideoProcess_YUV2RGBExtended
DXVA2_VideoProcess_AlphaBlendExtended
DXVA2_VideoProcess_Constriction
DXVA2_VideoProcess_NoiseFilter
DXVA2_VideoProcess_DetailFilter
DXVA2_VideoProcess_PlanarAlpha
DXVA2_VideoProcess_LinearScaling
DXVA2_VideoProcess_GammaCompensated
DXVA2_VideoProcess_MaintainsOriginalFieldData
*/

/*NoiseFilterTechnology
DXVA2_NoiseFilterTech_Unsupported
DXVA2_NoiseFilterTech_Unknown
DXVA2_NoiseFilterTech_Median
DXVA2_NoiseFilterTech_Temporal
DXVA2_NoiseFilterTech_BlockNoise
DXVA2_NoiseFilterTech_MosquitoNoise
*/

/* DetailFilterTechnology
DXVA2_DetailFilterTech_Unsupported
DXVA2_DetailFilterTech_Unknown
DXVA2_DetailFilterTech_Edge
DXVA2_DetailFilterTech_Sharpening
*/
typedef struct _DXVA2_VideoProcessBltParams {
  REFERENCE_TIME       TargetFrame;
  RECT                 TargetRect;
  SIZE                 ConstrictionSize;
  UINT                 StreamingFlags;
  DXVA2_AYUVSample16   BackgroundColor;
  DXVA2_ExtendedFormat DestFormat;
  DXVA2_ProcAmpValues  ProcAmpValues;
  DXVA2_Fixed32        Alpha;
  DXVA2_FilterValues   NoiseFilterLuma;
  DXVA2_FilterValues   NoiseFilterChroma;
  DXVA2_FilterValues   DetailFilterLuma;
  DXVA2_FilterValues   DetailFilterChroma;
  DWORD                DestData;
} DXVA2_VideoProcessBltParams;

#ifdef _D3D9_H_
typedef struct _DXVA2_VideoProcessorCaps {
  UINT    DeviceCaps;
  D3DPOOL InputPool;
  UINT    NumForwardRefSamples;
  UINT    NumBackwardRefSamples;
  UINT    Reserved;
  UINT    DeinterlaceTechnology;
  UINT    ProcAmpControlCaps;
  UINT    VideoProcessorOperations;
  UINT    NoiseFilterTechnology;
  UINT    DetailFilterTechnology;
} DXVA2_VideoProcessorCaps;
#endif

/* SampleData
DXVA2_SampleData_RFF
DXVA2_SampleData_TFF
DXVA2_SampleData_RFF_TFF_Present
*/

#ifdef _D3D9_H_
typedef struct _DXVA2_VideoSample {
  REFERENCE_TIME       Start;
  REFERENCE_TIME       End;
  DXVA2_ExtendedFormat SampleFormat;
  IDirect3DSurface9*   SrcSurface;
  RECT                 SrcRect;
  RECT                 DstRect;
  DXVA2_AYUVSample8    Pal[16];
  DXVA2_Fixed32        PlanarAlpha;
  DWORD                SampleData;
} DXVA2_VideoSample;
#endif

/* Constants */

#define DXVA2_VideoDecoderRenderTarget 0
#define DXVA2_VideoProcessorRenderTarget 1
#define DXVA2_VideoSoftwareRenderTarget 2

/* CompressedBufferType */
#define DXVA2_PictureParametersBufferType 0
#define DXVA2_MacroBlockControlBufferType 1
#define DXVA2_ResidualDifferenceBufferType 2
#define DXVA2_DeblockingControlBufferType 3
#define DXVA2_InverseQuantizationMatrixBufferType 4
#define DXVA2_SliceControlBufferType 5
#define DXVA2_BitStreamDateBufferType 6
#define DXVA2_MotionVectorBuffer 7
#define DXVA2_FilmGrainBuffer 8

__forceinline const DXVA2_Fixed32 DXVA2_Fixed32OpaqueAlpha (void) {
  DXVA2_Fixed32 f32;
  f32.ll = 0 + (1 << 16);
  return f32;
}

__forceinline const DXVA2_Fixed32 DXVA2_Fixed32TransparentAlpha (void) {
  DXVA2_Fixed32 f32;
  f32.ll = 0;
  return f32;
}

__forceinline float DXVA2FixedToFloat (const DXVA2_Fixed32 f32) {
  return (float)f32.Value + (float)f32.Fraction / (1 << 16);
}

__forceinline DXVA2_Fixed32 DXVA2FloatToFixed (const float f) {
  DXVA2_Fixed32 f32;
  f32.Value    = ((ULONG) (f * (1 << 16))) >> 16;
  f32.Fraction = ((ULONG) (f * (1 << 16))) & 0xFFFF;
  return f32;
}
#ifdef _D3D9_H_
HRESULT WINAPI DXVA2CreateDirect3DDeviceManager9(UINT *pResetToken,IDirect3DDeviceManager9 **ppDXVAManager);
HRESULT WINAPI DXVA2CreateVideoService(IDirect3DDevice9 *pDD,REFIID riid,void **ppService);
/*****************************************************************************
 * IDirect3DDeviceManager9 interface
 */
#ifndef __IDirect3DDeviceManager9_INTERFACE_DEFINED__
#define __IDirect3DDeviceManager9_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDirect3DDeviceManager9, 0xa0cade0f, 0x06d5, 0x4cf4, 0xa1,0xc7, 0xf3,0xcd,0xd7,0x25,0xaa,0x75);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("a0cade0f-06d5-4cf4-a1c7-f3cdd725aa75")
IDirect3DDeviceManager9 : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE ResetDevice(
        IDirect3DDevice9 *pDevice,
        UINT resetToken) = 0;

    virtual HRESULT STDMETHODCALLTYPE OpenDeviceHandle(
        HANDLE *phDevice) = 0;

    virtual HRESULT STDMETHODCALLTYPE CloseDeviceHandle(
        HANDLE hDevice) = 0;

    virtual HRESULT STDMETHODCALLTYPE TestDevice(
        HANDLE hDevice) = 0;

    virtual HRESULT STDMETHODCALLTYPE LockDevice(
        HANDLE hDevice,
        IDirect3DDevice9 **ppDevice,
        WINBOOL fBlock) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnlockDevice(
        HANDLE hDevice,
        WINBOOL fSaveState) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetVideoService(
        HANDLE hDevice,
        REFIID riid,
        void **ppService) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDirect3DDeviceManager9, 0xa0cade0f, 0x06d5, 0x4cf4, 0xa1,0xc7, 0xf3,0xcd,0xd7,0x25,0xaa,0x75)
#endif
#else
typedef struct IDirect3DDeviceManager9Vtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDirect3DDeviceManager9 *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDirect3DDeviceManager9 *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDirect3DDeviceManager9 *This);

    /*** IDirect3DDeviceManager9 methods ***/
    HRESULT (STDMETHODCALLTYPE *ResetDevice)(
        IDirect3DDeviceManager9 *This,
        IDirect3DDevice9 *pDevice,
        UINT resetToken);

    HRESULT (STDMETHODCALLTYPE *OpenDeviceHandle)(
        IDirect3DDeviceManager9 *This,
        HANDLE *phDevice);

    HRESULT (STDMETHODCALLTYPE *CloseDeviceHandle)(
        IDirect3DDeviceManager9 *This,
        HANDLE hDevice);

    HRESULT (STDMETHODCALLTYPE *TestDevice)(
        IDirect3DDeviceManager9 *This,
        HANDLE hDevice);

    HRESULT (STDMETHODCALLTYPE *LockDevice)(
        IDirect3DDeviceManager9 *This,
        HANDLE hDevice,
        IDirect3DDevice9 **ppDevice,
        WINBOOL fBlock);

    HRESULT (STDMETHODCALLTYPE *UnlockDevice)(
        IDirect3DDeviceManager9 *This,
        HANDLE hDevice,
        WINBOOL fSaveState);

    HRESULT (STDMETHODCALLTYPE *GetVideoService)(
        IDirect3DDeviceManager9 *This,
        HANDLE hDevice,
        REFIID riid,
        void **ppService);

    END_INTERFACE
} IDirect3DDeviceManager9Vtbl;

interface IDirect3DDeviceManager9 {
    CONST_VTBL IDirect3DDeviceManager9Vtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDirect3DDeviceManager9_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IDirect3DDeviceManager9_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDirect3DDeviceManager9_Release(This) (This)->lpVtbl->Release(This)
/*** IDirect3DDeviceManager9 methods ***/
#define IDirect3DDeviceManager9_ResetDevice(This,pDevice,resetToken) (This)->lpVtbl->ResetDevice(This,pDevice,resetToken)
#define IDirect3DDeviceManager9_OpenDeviceHandle(This,phDevice) (This)->lpVtbl->OpenDeviceHandle(This,phDevice)
#define IDirect3DDeviceManager9_CloseDeviceHandle(This,hDevice) (This)->lpVtbl->CloseDeviceHandle(This,hDevice)
#define IDirect3DDeviceManager9_TestDevice(This,hDevice) (This)->lpVtbl->TestDevice(This,hDevice)
#define IDirect3DDeviceManager9_LockDevice(This,hDevice,ppDevice,fBlock) (This)->lpVtbl->LockDevice(This,hDevice,ppDevice,fBlock)
#define IDirect3DDeviceManager9_UnlockDevice(This,hDevice,fSaveState) (This)->lpVtbl->UnlockDevice(This,hDevice,fSaveState)
#define IDirect3DDeviceManager9_GetVideoService(This,hDevice,riid,ppService) (This)->lpVtbl->GetVideoService(This,hDevice,riid,ppService)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IDirect3DDeviceManager9_QueryInterface(IDirect3DDeviceManager9* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IDirect3DDeviceManager9_AddRef(IDirect3DDeviceManager9* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IDirect3DDeviceManager9_Release(IDirect3DDeviceManager9* This) {
    return This->lpVtbl->Release(This);
}
/*** IDirect3DDeviceManager9 methods ***/
static FORCEINLINE HRESULT IDirect3DDeviceManager9_ResetDevice(IDirect3DDeviceManager9* This,IDirect3DDevice9 *pDevice,UINT resetToken) {
    return This->lpVtbl->ResetDevice(This,pDevice,resetToken);
}
static FORCEINLINE HRESULT IDirect3DDeviceManager9_OpenDeviceHandle(IDirect3DDeviceManager9* This,HANDLE *phDevice) {
    return This->lpVtbl->OpenDeviceHandle(This,phDevice);
}
static FORCEINLINE HRESULT IDirect3DDeviceManager9_CloseDeviceHandle(IDirect3DDeviceManager9* This,HANDLE hDevice) {
    return This->lpVtbl->CloseDeviceHandle(This,hDevice);
}
static FORCEINLINE HRESULT IDirect3DDeviceManager9_TestDevice(IDirect3DDeviceManager9* This,HANDLE hDevice) {
    return This->lpVtbl->TestDevice(This,hDevice);
}
static FORCEINLINE HRESULT IDirect3DDeviceManager9_LockDevice(IDirect3DDeviceManager9* This,HANDLE hDevice,IDirect3DDevice9 **ppDevice,WINBOOL fBlock) {
    return This->lpVtbl->LockDevice(This,hDevice,ppDevice,fBlock);
}
static FORCEINLINE HRESULT IDirect3DDeviceManager9_UnlockDevice(IDirect3DDeviceManager9* This,HANDLE hDevice,WINBOOL fSaveState) {
    return This->lpVtbl->UnlockDevice(This,hDevice,fSaveState);
}
static FORCEINLINE HRESULT IDirect3DDeviceManager9_GetVideoService(IDirect3DDeviceManager9* This,HANDLE hDevice,REFIID riid,void **ppService) {
    return This->lpVtbl->GetVideoService(This,hDevice,riid,ppService);
}
#endif
#endif

#endif


#endif  /* __IDirect3DDeviceManager9_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IDirectXVideoDecoder interface
 */
#ifndef __IDirectXVideoDecoder_INTERFACE_DEFINED__
#define __IDirectXVideoDecoder_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDirectXVideoDecoder, 0xf2b0810a, 0xfd00, 0x43c9, 0x91,0x8c, 0xdf,0x94,0xe2,0xd8,0xef,0x7d);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("f2b0810a-fd00-43c9-918c-df94e2d8ef7d")
IDirectXVideoDecoder : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetVideoDecoderService(
        IDirectXVideoDecoderService **ppService) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCreationParameters(
        GUID *pDeviceGuid,
        DXVA2_VideoDesc *pVideoDesc,
        DXVA2_ConfigPictureDecode *pConfig,
        IDirect3DSurface9 ***pDecoderRenderTargets,
        UINT *pNumSurfaces) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetBuffer(
        UINT BufferType,
        void **ppBuffer,
        UINT *pBufferSize) = 0;

    virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer(
        UINT BufferType) = 0;

    virtual HRESULT STDMETHODCALLTYPE BeginFrame(
        IDirect3DSurface9 *pRenderTarget,
        void *pvPVPData) = 0;

    virtual HRESULT STDMETHODCALLTYPE EndFrame(
        HANDLE *pHandleComplete) = 0;

    virtual HRESULT STDMETHODCALLTYPE Execute(
        const DXVA2_DecodeExecuteParams *pExecuteParams) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDirectXVideoDecoder, 0xf2b0810a, 0xfd00, 0x43c9, 0x91,0x8c, 0xdf,0x94,0xe2,0xd8,0xef,0x7d)
#endif
#else
typedef struct IDirectXVideoDecoderVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDirectXVideoDecoder *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDirectXVideoDecoder *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDirectXVideoDecoder *This);

    /*** IDirectXVideoDecoder methods ***/
    HRESULT (STDMETHODCALLTYPE *GetVideoDecoderService)(
        IDirectXVideoDecoder *This,
        IDirectXVideoDecoderService **ppService);

    HRESULT (STDMETHODCALLTYPE *GetCreationParameters)(
        IDirectXVideoDecoder *This,
        GUID *pDeviceGuid,
        DXVA2_VideoDesc *pVideoDesc,
        DXVA2_ConfigPictureDecode *pConfig,
        IDirect3DSurface9 ***pDecoderRenderTargets,
        UINT *pNumSurfaces);

    HRESULT (STDMETHODCALLTYPE *GetBuffer)(
        IDirectXVideoDecoder *This,
        UINT BufferType,
        void **ppBuffer,
        UINT *pBufferSize);

    HRESULT (STDMETHODCALLTYPE *ReleaseBuffer)(
        IDirectXVideoDecoder *This,
        UINT BufferType);

    HRESULT (STDMETHODCALLTYPE *BeginFrame)(
        IDirectXVideoDecoder *This,
        IDirect3DSurface9 *pRenderTarget,
        void *pvPVPData);

    HRESULT (STDMETHODCALLTYPE *EndFrame)(
        IDirectXVideoDecoder *This,
        HANDLE *pHandleComplete);

    HRESULT (STDMETHODCALLTYPE *Execute)(
        IDirectXVideoDecoder *This,
        const DXVA2_DecodeExecuteParams *pExecuteParams);

    END_INTERFACE
} IDirectXVideoDecoderVtbl;

interface IDirectXVideoDecoder {
    CONST_VTBL IDirectXVideoDecoderVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDirectXVideoDecoder_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IDirectXVideoDecoder_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDirectXVideoDecoder_Release(This) (This)->lpVtbl->Release(This)
/*** IDirectXVideoDecoder methods ***/
#define IDirectXVideoDecoder_GetVideoDecoderService(This,ppService) (This)->lpVtbl->GetVideoDecoderService(This,ppService)
#define IDirectXVideoDecoder_GetCreationParameters(This,pDeviceGuid,pVideoDesc,pConfig,pDecoderRenderTargets,pNumSurfaces) (This)->lpVtbl->GetCreationParameters(This,pDeviceGuid,pVideoDesc,pConfig,pDecoderRenderTargets,pNumSurfaces)
#define IDirectXVideoDecoder_GetBuffer(This,BufferType,ppBuffer,pBufferSize) (This)->lpVtbl->GetBuffer(This,BufferType,ppBuffer,pBufferSize)
#define IDirectXVideoDecoder_ReleaseBuffer(This,BufferType) (This)->lpVtbl->ReleaseBuffer(This,BufferType)
#define IDirectXVideoDecoder_BeginFrame(This,pRenderTarget,pvPVPData) (This)->lpVtbl->BeginFrame(This,pRenderTarget,pvPVPData)
#define IDirectXVideoDecoder_EndFrame(This,pHandleComplete) (This)->lpVtbl->EndFrame(This,pHandleComplete)
#define IDirectXVideoDecoder_Execute(This,pExecuteParams) (This)->lpVtbl->Execute(This,pExecuteParams)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IDirectXVideoDecoder_QueryInterface(IDirectXVideoDecoder* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IDirectXVideoDecoder_AddRef(IDirectXVideoDecoder* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IDirectXVideoDecoder_Release(IDirectXVideoDecoder* This) {
    return This->lpVtbl->Release(This);
}
/*** IDirectXVideoDecoder methods ***/
static FORCEINLINE HRESULT IDirectXVideoDecoder_GetVideoDecoderService(IDirectXVideoDecoder* This,IDirectXVideoDecoderService **ppService) {
    return This->lpVtbl->GetVideoDecoderService(This,ppService);
}
static FORCEINLINE HRESULT IDirectXVideoDecoder_GetCreationParameters(IDirectXVideoDecoder* This,GUID *pDeviceGuid,DXVA2_VideoDesc *pVideoDesc,DXVA2_ConfigPictureDecode *pConfig,IDirect3DSurface9 ***pDecoderRenderTargets,UINT *pNumSurfaces) {
    return This->lpVtbl->GetCreationParameters(This,pDeviceGuid,pVideoDesc,pConfig,pDecoderRenderTargets,pNumSurfaces);
}
static FORCEINLINE HRESULT IDirectXVideoDecoder_GetBuffer(IDirectXVideoDecoder* This,UINT BufferType,void **ppBuffer,UINT *pBufferSize) {
    return This->lpVtbl->GetBuffer(This,BufferType,ppBuffer,pBufferSize);
}
static FORCEINLINE HRESULT IDirectXVideoDecoder_ReleaseBuffer(IDirectXVideoDecoder* This,UINT BufferType) {
    return This->lpVtbl->ReleaseBuffer(This,BufferType);
}
static FORCEINLINE HRESULT IDirectXVideoDecoder_BeginFrame(IDirectXVideoDecoder* This,IDirect3DSurface9 *pRenderTarget,void *pvPVPData) {
    return This->lpVtbl->BeginFrame(This,pRenderTarget,pvPVPData);
}
static FORCEINLINE HRESULT IDirectXVideoDecoder_EndFrame(IDirectXVideoDecoder* This,HANDLE *pHandleComplete) {
    return This->lpVtbl->EndFrame(This,pHandleComplete);
}
static FORCEINLINE HRESULT IDirectXVideoDecoder_Execute(IDirectXVideoDecoder* This,const DXVA2_DecodeExecuteParams *pExecuteParams) {
    return This->lpVtbl->Execute(This,pExecuteParams);
}
#endif
#endif

#endif


#endif  /* __IDirectXVideoDecoder_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IDirectXVideoAccelerationService interface
 */
#ifndef __IDirectXVideoAccelerationService_INTERFACE_DEFINED__
#define __IDirectXVideoAccelerationService_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDirectXVideoAccelerationService, 0xfc51a550, 0xd5e7, 0x11d9, 0xaf,0x55, 0x00,0x05,0x4e,0x43,0xff,0x02);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("fc51a550-d5e7-11d9-af55-00054e43ff02")
IDirectXVideoAccelerationService : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE CreateSurface(
        UINT Width,
        UINT Height,
        UINT BackBuffers,
        D3DFORMAT Format,
        D3DPOOL Pool,
        DWORD Usage,
        DWORD DxvaType,
        IDirect3DSurface9 **ppSurface,
        HANDLE *pSharedHandle) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDirectXVideoAccelerationService, 0xfc51a550, 0xd5e7, 0x11d9, 0xaf,0x55, 0x00,0x05,0x4e,0x43,0xff,0x02)
#endif
#else
typedef struct IDirectXVideoAccelerationServiceVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDirectXVideoAccelerationService *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDirectXVideoAccelerationService *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDirectXVideoAccelerationService *This);

    /*** IDirectXVideoAccelerationService methods ***/
    HRESULT (STDMETHODCALLTYPE *CreateSurface)(
        IDirectXVideoAccelerationService *This,
        UINT Width,
        UINT Height,
        UINT BackBuffers,
        D3DFORMAT Format,
        D3DPOOL Pool,
        DWORD Usage,
        DWORD DxvaType,
        IDirect3DSurface9 **ppSurface,
        HANDLE *pSharedHandle);

    END_INTERFACE
} IDirectXVideoAccelerationServiceVtbl;

interface IDirectXVideoAccelerationService {
    CONST_VTBL IDirectXVideoAccelerationServiceVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDirectXVideoAccelerationService_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IDirectXVideoAccelerationService_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDirectXVideoAccelerationService_Release(This) (This)->lpVtbl->Release(This)
/*** IDirectXVideoAccelerationService methods ***/
#define IDirectXVideoAccelerationService_CreateSurface(This,Width,Height,BackBuffers,Format,Pool,Usage,DxvaType,ppSurface,pSharedHandle) (This)->lpVtbl->CreateSurface(This,Width,Height,BackBuffers,Format,Pool,Usage,DxvaType,ppSurface,pSharedHandle)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IDirectXVideoAccelerationService_QueryInterface(IDirectXVideoAccelerationService* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IDirectXVideoAccelerationService_AddRef(IDirectXVideoAccelerationService* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IDirectXVideoAccelerationService_Release(IDirectXVideoAccelerationService* This) {
    return This->lpVtbl->Release(This);
}
/*** IDirectXVideoAccelerationService methods ***/
static FORCEINLINE HRESULT IDirectXVideoAccelerationService_CreateSurface(IDirectXVideoAccelerationService* This,UINT Width,UINT Height,UINT BackBuffers,D3DFORMAT Format,D3DPOOL Pool,DWORD Usage,DWORD DxvaType,IDirect3DSurface9 **ppSurface,HANDLE *pSharedHandle) {
    return This->lpVtbl->CreateSurface(This,Width,Height,BackBuffers,Format,Pool,Usage,DxvaType,ppSurface,pSharedHandle);
}
#endif
#endif

#endif


#endif  /* __IDirectXVideoAccelerationService_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IDirectXVideoDecoderService interface
 */
#ifndef __IDirectXVideoDecoderService_INTERFACE_DEFINED__
#define __IDirectXVideoDecoderService_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDirectXVideoDecoderService, 0xfc51a551, 0xd5e7, 0x11d9, 0xaf,0x55, 0x00,0x05,0x4e,0x43,0xff,0x02);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("fc51a551-d5e7-11d9-af55-00054e43ff02")
IDirectXVideoDecoderService : public IDirectXVideoAccelerationService
{
    virtual HRESULT STDMETHODCALLTYPE GetDecoderDeviceGuids(
        UINT *pCount,
        GUID **pGuids) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDecoderRenderTargets(
        REFGUID Guid,
        UINT *pCount,
        D3DFORMAT **pFormats) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDecoderConfigurations(
        REFGUID Guid,
        const DXVA2_VideoDesc *pVideoDesc,
        void *pReserved,
        UINT *pCount,
        DXVA2_ConfigPictureDecode **ppConfigs) = 0;

    virtual HRESULT STDMETHODCALLTYPE CreateVideoDecoder(
        REFGUID Guid,
        const DXVA2_VideoDesc *pVideoDesc,
        const DXVA2_ConfigPictureDecode *pConfig,
        IDirect3DSurface9 **ppDecoderRenderTargets,
        UINT NumRenderTargets,
        IDirectXVideoDecoder **ppDecode) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDirectXVideoDecoderService, 0xfc51a551, 0xd5e7, 0x11d9, 0xaf,0x55, 0x00,0x05,0x4e,0x43,0xff,0x02)
#endif
#else
typedef struct IDirectXVideoDecoderServiceVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDirectXVideoDecoderService *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDirectXVideoDecoderService *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDirectXVideoDecoderService *This);

    /*** IDirectXVideoAccelerationService methods ***/
    HRESULT (STDMETHODCALLTYPE *CreateSurface)(
        IDirectXVideoDecoderService *This,
        UINT Width,
        UINT Height,
        UINT BackBuffers,
        D3DFORMAT Format,
        D3DPOOL Pool,
        DWORD Usage,
        DWORD DxvaType,
        IDirect3DSurface9 **ppSurface,
        HANDLE *pSharedHandle);

    /*** IDirectXVideoDecoderService methods ***/
    HRESULT (STDMETHODCALLTYPE *GetDecoderDeviceGuids)(
        IDirectXVideoDecoderService *This,
        UINT *pCount,
        GUID **pGuids);

    HRESULT (STDMETHODCALLTYPE *GetDecoderRenderTargets)(
        IDirectXVideoDecoderService *This,
        REFGUID Guid,
        UINT *pCount,
        D3DFORMAT **pFormats);

    HRESULT (STDMETHODCALLTYPE *GetDecoderConfigurations)(
        IDirectXVideoDecoderService *This,
        REFGUID Guid,
        const DXVA2_VideoDesc *pVideoDesc,
        void *pReserved,
        UINT *pCount,
        DXVA2_ConfigPictureDecode **ppConfigs);

    HRESULT (STDMETHODCALLTYPE *CreateVideoDecoder)(
        IDirectXVideoDecoderService *This,
        REFGUID Guid,
        const DXVA2_VideoDesc *pVideoDesc,
        const DXVA2_ConfigPictureDecode *pConfig,
        IDirect3DSurface9 **ppDecoderRenderTargets,
        UINT NumRenderTargets,
        IDirectXVideoDecoder **ppDecode);

    END_INTERFACE
} IDirectXVideoDecoderServiceVtbl;

interface IDirectXVideoDecoderService {
    CONST_VTBL IDirectXVideoDecoderServiceVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDirectXVideoDecoderService_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IDirectXVideoDecoderService_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDirectXVideoDecoderService_Release(This) (This)->lpVtbl->Release(This)
/*** IDirectXVideoAccelerationService methods ***/
#define IDirectXVideoDecoderService_CreateSurface(This,Width,Height,BackBuffers,Format,Pool,Usage,DxvaType,ppSurface,pSharedHandle) (This)->lpVtbl->CreateSurface(This,Width,Height,BackBuffers,Format,Pool,Usage,DxvaType,ppSurface,pSharedHandle)
/*** IDirectXVideoDecoderService methods ***/
#define IDirectXVideoDecoderService_GetDecoderDeviceGuids(This,pCount,pGuids) (This)->lpVtbl->GetDecoderDeviceGuids(This,pCount,pGuids)
#define IDirectXVideoDecoderService_GetDecoderRenderTargets(This,Guid,pCount,pFormats) (This)->lpVtbl->GetDecoderRenderTargets(This,Guid,pCount,pFormats)
#define IDirectXVideoDecoderService_GetDecoderConfigurations(This,Guid,pVideoDesc,pReserved,pCount,ppConfigs) (This)->lpVtbl->GetDecoderConfigurations(This,Guid,pVideoDesc,pReserved,pCount,ppConfigs)
#define IDirectXVideoDecoderService_CreateVideoDecoder(This,Guid,pVideoDesc,pConfig,ppDecoderRenderTargets,NumRenderTargets,ppDecode) (This)->lpVtbl->CreateVideoDecoder(This,Guid,pVideoDesc,pConfig,ppDecoderRenderTargets,NumRenderTargets,ppDecode)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IDirectXVideoDecoderService_QueryInterface(IDirectXVideoDecoderService* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IDirectXVideoDecoderService_AddRef(IDirectXVideoDecoderService* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IDirectXVideoDecoderService_Release(IDirectXVideoDecoderService* This) {
    return This->lpVtbl->Release(This);
}
/*** IDirectXVideoAccelerationService methods ***/
static FORCEINLINE HRESULT IDirectXVideoDecoderService_CreateSurface(IDirectXVideoDecoderService* This,UINT Width,UINT Height,UINT BackBuffers,D3DFORMAT Format,D3DPOOL Pool,DWORD Usage,DWORD DxvaType,IDirect3DSurface9 **ppSurface,HANDLE *pSharedHandle) {
    return This->lpVtbl->CreateSurface(This,Width,Height,BackBuffers,Format,Pool,Usage,DxvaType,ppSurface,pSharedHandle);
}
/*** IDirectXVideoDecoderService methods ***/
static FORCEINLINE HRESULT IDirectXVideoDecoderService_GetDecoderDeviceGuids(IDirectXVideoDecoderService* This,UINT *pCount,GUID **pGuids) {
    return This->lpVtbl->GetDecoderDeviceGuids(This,pCount,pGuids);
}
static FORCEINLINE HRESULT IDirectXVideoDecoderService_GetDecoderRenderTargets(IDirectXVideoDecoderService* This,REFGUID Guid,UINT *pCount,D3DFORMAT **pFormats) {
    return This->lpVtbl->GetDecoderRenderTargets(This,Guid,pCount,pFormats);
}
static FORCEINLINE HRESULT IDirectXVideoDecoderService_GetDecoderConfigurations(IDirectXVideoDecoderService* This,REFGUID Guid,const DXVA2_VideoDesc *pVideoDesc,void *pReserved,UINT *pCount,DXVA2_ConfigPictureDecode **ppConfigs) {
    return This->lpVtbl->GetDecoderConfigurations(This,Guid,pVideoDesc,pReserved,pCount,ppConfigs);
}
static FORCEINLINE HRESULT IDirectXVideoDecoderService_CreateVideoDecoder(IDirectXVideoDecoderService* This,REFGUID Guid,const DXVA2_VideoDesc *pVideoDesc,const DXVA2_ConfigPictureDecode *pConfig,IDirect3DSurface9 **ppDecoderRenderTargets,UINT NumRenderTargets,IDirectXVideoDecoder **ppDecode) {
    return This->lpVtbl->CreateVideoDecoder(This,Guid,pVideoDesc,pConfig,ppDecoderRenderTargets,NumRenderTargets,ppDecode);
}
#endif
#endif

#endif


#endif  /* __IDirectXVideoDecoderService_INTERFACE_DEFINED__ */

#endif /* _D3D9_H_ */
/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __dxva2api_h__ */
