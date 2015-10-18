/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#ifndef __USBSPEC_H__
#define __USBSPEC_H__

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION (WINAPI_PARTITION_DESKTOP)
#include <pshpack1.h>

typedef enum _USB_DEVICE_SPEED {
  UsbLowSpeed = 0,
  UsbFullSpeed,
  UsbHighSpeed,
  UsbSuperSpeed
} USB_DEVICE_SPEED;

typedef enum _USB_DEVICE_TYPE {
  Usb11Device = 0,
  Usb20Device
} USB_DEVICE_TYPE;

typedef union _BM_REQUEST_TYPE {
  __C89_NAMELESS struct _BM {
    UCHAR Recipient:2;
    UCHAR Reserved:3;
    UCHAR Type:2;
    UCHAR Dir:1;
  };
  UCHAR B;
} BM_REQUEST_TYPE,*PBM_REQUEST_TYPE;

typedef struct _USB_DEFAULT_PIPE_SETUP_PACKET {
  BM_REQUEST_TYPE bmRequestType;
  UCHAR bRequest;
  union _wValue {
    __C89_NAMELESS struct {
      UCHAR LowByte;
      UCHAR HiByte;
    };
    USHORT W;
  } wValue;
  union _wIndex {
    struct {
      UCHAR LowByte;
      UCHAR HiByte;
    };
    USHORT W;
  } wIndex;
  USHORT wLength;
} USB_DEFAULT_PIPE_SETUP_PACKET,*PUSB_DEFAULT_PIPE_SETUP_PACKET;

#define BMREQUEST_HOST_TO_DEVICE 0
#define BMREQUEST_DEVICE_TO_HOST 1

#define BMREQUEST_STANDARD 0
#define BMREQUEST_CLASS 1
#define BMREQUEST_VENDOR 2

#define BMREQUEST_TO_DEVICE 0
#define BMREQUEST_TO_INTERFACE 1
#define BMREQUEST_TO_ENDPOINT 2
#define BMREQUEST_TO_OTHER 3

#define USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX(d, i) ((USHORT) (((USHORT) d) << 8 | i))

#define USB_REQUEST_GET_STATUS 0x00
#define USB_REQUEST_CLEAR_FEATURE 0x01
#define USB_REQUEST_SET_FEATURE 0x03
#define USB_REQUEST_SET_ADDRESS 0x05
#define USB_REQUEST_GET_DESCRIPTOR 0x06
#define USB_REQUEST_SET_DESCRIPTOR 0x07
#define USB_REQUEST_GET_CONFIGURATION 0x08
#define USB_REQUEST_SET_CONFIGURATION 0x09
#define USB_REQUEST_GET_INTERFACE 0x0a
#define USB_REQUEST_SET_INTERFACE 0x0b
#define USB_REQUEST_SYNC_FRAME 0x0c

#define USB_REQUEST_SET_SEL 0x30
#define USB_REQUEST_ISOCH_DELAY 0x31

#define USB_DEVICE_DESCRIPTOR_TYPE 0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE 0x02
#define USB_STRING_DESCRIPTOR_TYPE 0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE 0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE 0x05
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE 0x06
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE 0x07
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE 0x08
#define USB_OTG_DESCRIPTOR_TYPE 0x09
#define USB_DEBUG_DESCRIPTOR_TYPE 0x0a
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE 0x0b
#define USB_BOS_DESCRIPTOR_TYPE 0x0f
#define USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE 0x10
#define USB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR_TYPE 0x30

#define USB_RESERVED_DESCRIPTOR_TYPE 0x06
#define USB_CONFIG_POWER_DESCRIPTOR_TYPE 0x07

#define USB_FEATURE_ENDPOINT_STALL 0x00
#define USB_FEATURE_REMOTE_WAKEUP 0x01
#define USB_FEATURE_TEST_MODE 0x02

#define USB_FEATURE_FUNCTION_SUSPEND 0x00
#define USB_FEATURE_U1_ENABLE 0x30
#define USB_FEATURE_U2_ENABLE 0x31
#define USB_FEATURE_LTM_ENABLE 0x32

#define USB_GETSTATUS_SELF_POWERED 0x01
#define USB_GETSTATUS_REMOTE_WAKEUP_ENABLED 0x02

#define USB_GETSTATUS_U1_ENABLE 0x04
#define USB_GETSTATUS_U2_ENABLE 0x08
#define USB_GETSTATUS_LTM_ENABLE 0x10

typedef union _USB_DEVICE_STATUS {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT SelfPowered : 1;
    USHORT RemoteWakeup : 1;
    USHORT U1Enable : 1;
    USHORT U2Enable : 1;
    USHORT LtmEnable : 1;
    USHORT Reserved : 11;
  };
} USB_DEVICE_STATUS,*PUSB_DEVICE_STATUS;

typedef union _USB_INTERFACE_STATUS {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT RemoteWakeupCapable : 1;
    USHORT RemoteWakeupEnabled : 1;
    USHORT Reserved : 14;
  };
} USB_INTERFACE_STATUS,*PUSB_INTERFACE_STATUS;
;

typedef union _USB_ENDPOINT_STATUS {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT Halt : 1;
    USHORT Reserved : 15;
  };
} USB_ENDPOINT_STATUS,*PUSB_ENDPOINT_STATUS;

typedef struct _USB_COMMON_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
} USB_COMMON_DESCRIPTOR,*PUSB_COMMON_DESCRIPTOR;

typedef struct _USB_DEVICE_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  USHORT bcdUSB;
  UCHAR bDeviceClass;
  UCHAR bDeviceSubClass;
  UCHAR bDeviceProtocol;
  UCHAR bMaxPacketSize0;
  USHORT idVendor;
  USHORT idProduct;
  USHORT bcdDevice;
  UCHAR iManufacturer;
  UCHAR iProduct;
  UCHAR iSerialNumber;
  UCHAR bNumConfigurations;
} USB_DEVICE_DESCRIPTOR,*PUSB_DEVICE_DESCRIPTOR;

#define USB_DEVICE_CLASS_RESERVED 0x00
#define USB_DEVICE_CLASS_AUDIO 0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS 0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE 0x03
#define USB_DEVICE_CLASS_MONITOR 0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE 0x05
#define USB_DEVICE_CLASS_POWER 0x06
#define USB_DEVICE_CLASS_IMAGE 0x06
#define USB_DEVICE_CLASS_PRINTER 0x07
#define USB_DEVICE_CLASS_STORAGE 0x08
#define USB_DEVICE_CLASS_HUB 0x09
#define USB_DEVICE_CLASS_CDC_DATA 0x0a
#define USB_DEVICE_CLASS_SMART_CARD 0x0b
#define USB_DEVICE_CLASS_CONTENT_SECURITY 0x0d
#define USB_DEVICE_CLASS_VIDEO 0x0e
#define USB_DEVICE_CLASS_PERSONAL_HEALTHCARE 0x0f
#define USB_DEVICE_CLASS_DIAGNOSTIC_DEVICE 0xdc
#define USB_DEVICE_CLASS_WIRELESS_CONTROLLER 0xe0
#define USB_DEVICE_CLASS_MISCELLANEOUS 0xef
#define USB_DEVICE_CLASS_APPLICATION_SPECIFIC 0xfe
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC 0xff

typedef struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  USHORT bcdUSB;
  UCHAR bDeviceClass;
  UCHAR bDeviceSubClass;
  UCHAR bDeviceProtocol;
  UCHAR bMaxPacketSize0;
  UCHAR bNumConfigurations;
  UCHAR bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR,*PUSB_DEVICE_QUALIFIER_DESCRIPTOR;

typedef struct _USB_BOS_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  USHORT wTotalLength;
  UCHAR bNumDeviceCaps;
} USB_BOS_DESCRIPTOR,*PUSB_BOS_DESCRIPTOR;

#define USB_DEVICE_CAPABILITY_WIRELESS_USB 0x01
#define USB_DEVICE_CAPABILITY_USB20_EXTENSION 0x02
#define USB_DEVICE_CAPABILITY_SUPERSPEED_USB 0x03
#define USB_DEVICE_CAPABILITY_CONTAINER_ID 0x04

typedef struct _USB_DEVICE_CAPABILITY_USB20_EXTENSION_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bDevCapabilityType;
  union {
    ULONG AsUlong;
    __C89_NAMELESS struct {
      ULONG Reserved:1;
      ULONG LPMCapable:1;
      ULONG BESLAndAlternateHIRDSupported:1;
      ULONG BaselineBESLValid:1;
      ULONG DeepBESLValid:1;
      ULONG Reserved1:3;
      ULONG BaselineBESL:4;
      ULONG DeepBESL:4;
      ULONG Reserved2:16;
    };
  } bmAttributes;
} USB_DEVICE_CAPABILITY_USB20_EXTENSION_DESCRIPTOR,*PUSB_DEVICE_CAPABILITY_USB20_EXTENSION_DESCRIPTOR;

#define USB_DEVICE_CAPABILITY_USB20_EXTENSION_BMATTRIBUTES_RESERVED_MASK 0xffff00e1

typedef struct _USB_DEVICE_CAPABILITY_SUPERSPEED_USB_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bDevCapabilityType;
  UCHAR bmAttributes;
  USHORT wSpeedsSupported;
  UCHAR bFunctionalitySupport;
  UCHAR bU1DevExitLat;
  USHORT wU2DevExitLat;
} USB_DEVICE_CAPABILITY_SUPERSPEED_USB_DESCRIPTOR,*PUSB_DEVICE_CAPABILITY_SUPERSPEED_USB_DESCRIPTOR;

#define USB_DEVICE_CAPABILITY_SUPERSPEED_BMATTRIBUTES_RESERVED_MASK 0xfd
#define USB_DEVICE_CAPABILITY_SUPERSPEED_BMATTRIBUTES_LTM_CAPABLE 0x02

#define USB_DEVICE_CAPABILITY_SUPERSPEED_SPEEDS_SUPPORTED_RESERVED_MASK 0xfff0

#define USB_DEVICE_CAPABILITY_SUPERSPEED_SPEEDS_SUPPORTED_LOW 0x0001
#define USB_DEVICE_CAPABILITY_SUPERSPEED_SPEEDS_SUPPORTED_FULL 0x0002
#define USB_DEVICE_CAPABILITY_SUPERSPEED_SPEEDS_SUPPORTED_HIGH 0x0004
#define USB_DEVICE_CAPABILITY_SUPERSPEED_SPEEDS_SUPPORTED_SUPER 0x0008

#define USB_DEVICE_CAPABILITY_SUPERSPEED_U1_DEVICE_EXIT_MAX_VALUE 0x0a
#define USB_DEVICE_CAPABILITY_SUPERSPEED_U2_DEVICE_EXIT_MAX_VALUE 0x07ff

#define USB_DEVICE_CAPABILITY_MAX_U1_LATENCY 0x0a
#define USB_DEVICE_CAPABILITY_MAX_U2_LATENCY 0x07ff

typedef struct _USB_DEVICE_CAPABILITY_CONTAINER_ID_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bDevCapabilityType;
  UCHAR bReserved;
  UCHAR ContainerID[16];
} USB_DEVICE_CAPABILITY_CONTAINER_ID_DESCRIPTOR,*PUSB_DEVICE_CAPABILITY_CONTAINER_ID_DESCRIPTOR;

typedef struct _USB_DEVICE_CAPABILITY_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bDevCapabilityType;
} USB_DEVICE_CAPABILITY_DESCRIPTOR,*PUSB_DEVICE_CAPABILITY_DESCRIPTOR;

typedef struct _USB_CONFIGURATION_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  USHORT wTotalLength;
  UCHAR bNumInterfaces;
  UCHAR bConfigurationValue;
  UCHAR iConfiguration;
  UCHAR bmAttributes;
  UCHAR MaxPower;
} USB_CONFIGURATION_DESCRIPTOR,*PUSB_CONFIGURATION_DESCRIPTOR;

#define USB_CONFIG_POWERED_MASK 0xc0
#define USB_CONFIG_BUS_POWERED 0x80
#define USB_CONFIG_SELF_POWERED 0x40
#define USB_CONFIG_REMOTE_WAKEUP 0x20
#define USB_CONFIG_RESERVED 0x1f

typedef struct _USB_INTERFACE_ASSOCIATION_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bFirstInterface;
  UCHAR bInterfaceCount;
  UCHAR bFunctionClass;
  UCHAR bFunctionSubClass;
  UCHAR bFunctionProtocol;
  UCHAR iFunction;
} USB_INTERFACE_ASSOCIATION_DESCRIPTOR,*PUSB_INTERFACE_ASSOCIATION_DESCRIPTOR;

typedef struct _USB_INTERFACE_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bInterfaceNumber;
  UCHAR bAlternateSetting;
  UCHAR bNumEndpoints;
  UCHAR bInterfaceClass;
  UCHAR bInterfaceSubClass;
  UCHAR bInterfaceProtocol;
  UCHAR iInterface;
} USB_INTERFACE_DESCRIPTOR,*PUSB_INTERFACE_DESCRIPTOR;

typedef struct _USB_ENDPOINT_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bEndpointAddress;
  UCHAR bmAttributes;
  USHORT wMaxPacketSize;
  UCHAR bInterval;
} USB_ENDPOINT_DESCRIPTOR,*PUSB_ENDPOINT_DESCRIPTOR;

#define USB_ENDPOINT_DIRECTION_MASK 0x80
#define USB_ENDPOINT_DIRECTION_OUT(addr) (! ((addr) & USB_ENDPOINT_DIRECTION_MASK))
#define USB_ENDPOINT_DIRECTION_IN(addr) ((addr) & USB_ENDPOINT_DIRECTION_MASK)

#define USB_ENDPOINT_ADDRESS_MASK 0x0f

#define USB_ENDPOINT_TYPE_MASK 0x03
#define USB_ENDPOINT_TYPE_CONTROL 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS 0x01
#define USB_ENDPOINT_TYPE_BULK 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT 0x03

#define USB_ENDPOINT_TYPE_BULK_RESERVED_MASK 0xfc
#define USB_ENDPOINT_TYPE_CONTROL_RESERVED_MASK 0xfc
#define USB_20_ENDPOINT_TYPE_INTERRUPT_RESERVED_MASK 0xfc
#define USB_30_ENDPOINT_TYPE_INTERRUPT_RESERVED_MASK 0xcc
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_RESERVED_MASK 0xc0

#define USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE_MASK 0x30
#define USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE_PERIODIC 0x00
#define USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE_NOTIFICATION 0x10
#define USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE_RESERVED10 0x20
#define USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE_RESERVED11 0x30
#define USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE(bmAttr) (bmAttr &USB_30_ENDPOINT_TYPE_INTERRUPT_USAGE_MASK)

#define USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION_MASK 0x0c
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION_NO_SYNCHRONIZATION 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION_ASYNCHRONOUS 0x04
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION_ADAPTIVE 0x08
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION_SYNCHRONOUS 0x0c
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION(bmAttr) (bmAttr &USB_ENDPOINT_TYPE_ISOCHRONOUS_SYNCHRONIZATION_MASK)

#define USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE_MASK 0x30
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE_DATA_ENDOINT 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE_FEEDBACK_ENDPOINT 0x10
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE_IMPLICIT_FEEDBACK_DATA_ENDPOINT 0x20
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE_RESERVED 0x30
#define USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE(bmAttr) (bmAttr &USB_ENDPOINT_TYPE_ISOCHRONOUS_USAGE_MASK)

typedef union _USB_HIGH_SPEED_MAXPACKET {
  __C89_NAMELESS struct _MP {
    USHORT MaxPacket : 11;
    USHORT HSmux : 2;
    USHORT Reserved : 3;
  };
  USHORT us;
} USB_HIGH_SPEED_MAXPACKET,*PUSB_HIGH_SPEED_MAXPACKET;

#define USB_ENDPOINT_SUPERSPEED_BULK_MAX_PACKET_SIZE 1024
#define USB_ENDPOINT_SUPERSPEED_CONTROL_MAX_PACKET_SIZE 512
#define USB_ENDPOINT_SUPERSPEED_ISO_MAX_PACKET_SIZE 1024
#define USB_ENDPOINT_SUPERSPEED_INTERRUPT_MAX_PACKET_SIZE 1024

typedef struct _USB_STRING_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  WCHAR bString[1];
} USB_STRING_DESCRIPTOR,*PUSB_STRING_DESCRIPTOR;

#define MAXIMUM_USB_STRING_LENGTH 255

typedef struct _USB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bMaxBurst;
  union {
    UCHAR AsUchar;
    struct {
      UCHAR MaxStreams:5;
      UCHAR Reserved1:3;
    } Bulk;
    struct {
      UCHAR Mult:2;
      UCHAR Reserved2:6;
    } Isochronous;
  } bmAttributes;
  USHORT wBytesPerInterval;
} USB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR,*PUSB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR;

#define USB_SUPERSPEED_ISOCHRONOUS_MAX_MULTIPLIER 2

typedef struct _USB_HUB_DESCRIPTOR {
  UCHAR bDescriptorLength;
  UCHAR bDescriptorType;
  UCHAR bNumberOfPorts;
  USHORT wHubCharacteristics;
  UCHAR bPowerOnToPowerGood;
  UCHAR bHubControlCurrent;
  UCHAR bRemoveAndPowerMask[64];
} USB_HUB_DESCRIPTOR,*PUSB_HUB_DESCRIPTOR;

#define USB_20_HUB_DESCRIPTOR_TYPE 0x29

typedef struct _USB_30_HUB_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bNumberOfPorts;
  USHORT wHubCharacteristics;
  UCHAR bPowerOnToPowerGood;
  UCHAR bHubControlCurrent;
  UCHAR bHubHdrDecLat;
  USHORT wHubDelay;
  USHORT DeviceRemovable;
} USB_30_HUB_DESCRIPTOR,*PUSB_30_HUB_DESCRIPTOR;

#define USB_30_HUB_DESCRIPTOR_TYPE 0x2a

#define USB_REQUEST_GET_STATE 0x02

#define USB_REQUEST_CLEAR_TT_BUFFER 0x08
#define USB_REQUEST_RESET_TT 0x09
#define USB_REQUEST_GET_TT_STATE 0x0a
#define USB_REQUEST_STOP_TT 0x0b

#define USB_REQUEST_SET_HUB_DEPTH 0x0c
#define USB_REQUEST_GET_PORT_ERR_COUNT 0x0d

typedef union _USB_HUB_STATUS {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT LocalPowerLost:1;
    USHORT OverCurrent:1;
    USHORT Reserved:14;
  };
} USB_HUB_STATUS,*PUSB_HUB_STATUS;

typedef union _USB_HUB_CHANGE {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT LocalPowerChange:1;
    USHORT OverCurrentChange:1;
    USHORT Reserved:14;
  };
} USB_HUB_CHANGE,*PUSB_HUB_CHANGE;

typedef union _USB_HUB_STATUS_AND_CHANGE {
  ULONG AsUlong32;
  __C89_NAMELESS struct {
    USB_HUB_STATUS HubStatus;
    USB_HUB_CHANGE HubChange;
  };
} USB_HUB_STATUS_AND_CHANGE,*PUSB_HUB_STATUS_AND_CHANGE;

typedef union _USB_20_PORT_STATUS {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT CurrentConnectStatus:1;
    USHORT PortEnabledDisabled:1;
    USHORT Suspend:1;
    USHORT OverCurrent:1;
    USHORT Reset:1;
    USHORT Reserved0:3;
    USHORT PortPower:1;
    USHORT LowSpeedDeviceAttached:1;
    USHORT HighSpeedDeviceAttached:1;
    USHORT PortTestMode:1;
    USHORT PortIndicatorControl:1;
    USHORT Reserved1:3;
  };
} USB_20_PORT_STATUS,*PUSB_20_PORT_STATUS;

#define USB_PORT_STATUS_CONNECT 0x0001
#define USB_PORT_STATUS_ENABLE 0x0002
#define USB_PORT_STATUS_SUSPEND 0x0004
#define USB_PORT_STATUS_OVER_CURRENT 0x0008
#define USB_PORT_STATUS_RESET 0x0010
#define USB_PORT_STATUS_POWER 0x0100
#define USB_PORT_STATUS_LOW_SPEED 0x0200
#define USB_PORT_STATUS_HIGH_SPEED 0x0400

typedef union _USB_20_PORT_CHANGE {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT ConnectStatusChange:1;
    USHORT PortEnableDisableChange:1;
    USHORT SuspendChange:1;
    USHORT OverCurrentIndicatorChange:1;
    USHORT ResetChange:1;
    USHORT Reserved2:11;
  };
} USB_20_PORT_CHANGE,*PUSB_20_PORT_CHANGE;

typedef union _USB_30_PORT_STATUS {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT CurrentConnectStatus:1;
    USHORT PortEnabledDisabled:1;
    USHORT Reserved0:1;
    USHORT OverCurrent:1;
    USHORT Reset:1;
    USHORT PortLinkState:4;
    USHORT PortPower:1;
    USHORT NegotiatedDeviceSpeed:3;
    USHORT Reserved1:3;
  };
} USB_30_PORT_STATUS,*PUSB_30_PORT_STATUS;

#define PORT_LINK_STATE_U0 0
#define PORT_LINK_STATE_U1 1
#define PORT_LINK_STATE_U2 2
#define PORT_LINK_STATE_U3 3
#define PORT_LINK_STATE_DISABLED 4
#define PORT_LINK_STATE_RX_DETECT 5
#define PORT_LINK_STATE_INACTIVE 6
#define PORT_LINK_STATE_POLLING 7
#define PORT_LINK_STATE_RECOVERY 8
#define PORT_LINK_STATE_HOT_RESET 9
#define PORT_LINK_STATE_COMPLIANCE_MODE 10
#define PORT_LINK_STATE_LOOPBACK 11
#define PORT_LINK_STATE_TEST_MODE 11

typedef union _USB_30_PORT_CHANGE {
  USHORT AsUshort16;
  __C89_NAMELESS struct {
    USHORT ConnectStatusChange:1;
    USHORT Reserved2:2;
    USHORT OverCurrentIndicatorChange:1;
    USHORT ResetChange:1;
    USHORT BHResetChange:1;
    USHORT PortLinkStateChange:1;
    USHORT PortConfigErrorChange:1;
    USHORT Reserved3:8;
  };
} USB_30_PORT_CHANGE,*PUSB_30_PORT_CHANGE;

typedef union _USB_PORT_STATUS {
  USHORT AsUshort16;
  USB_20_PORT_STATUS Usb20PortStatus;
  USB_30_PORT_STATUS Usb30PortStatus;
} USB_PORT_STATUS,*PUSB_PORT_STATUS;

typedef union _USB_PORT_CHANGE {
  USHORT AsUshort16;
  USB_20_PORT_CHANGE Usb20PortChange;
  USB_30_PORT_CHANGE Usb30PortChange;
} USB_PORT_CHANGE,*PUSB_PORT_CHANGE;

typedef union _USB_PORT_STATUS_AND_CHANGE {
  ULONG AsUlong32;
  __C89_NAMELESS struct {
    USB_PORT_STATUS PortStatus;
    USB_PORT_CHANGE PortChange;
  };
} USB_PORT_STATUS_AND_CHANGE,*PUSB_PORT_STATUS_AND_CHANGE;

typedef union _USB_HUB_30_PORT_REMOTE_WAKE_MASK {
  UCHAR AsUchar8;
  __C89_NAMELESS struct {
    UCHAR ConnectRemoteWakeEnable:1;
    UCHAR DisconnectRemoteWakeEnable:1;
    UCHAR OverCurrentRemoteWakeEnable:1;
    UCHAR Reserved0:5;
  };
} USB_HUB_30_PORT_REMOTE_WAKE_MASK,*PUSB_HUB_30_PORT_REMOTE_WAKE_MASK;

typedef union _USB_FUNCTION_SUSPEND_OPTIONS {
  UCHAR AsUchar;
  __C89_NAMELESS struct {
    UCHAR PowerState:1;
    UCHAR RemoteWakeEnabled:1;
    UCHAR Reserved:6;
  };
} USB_FUNCTION_SUSPEND_OPTIONS,*PUSB_FUNCTION_SUSPEND_OPTIONS;

#define USB_FEATURE_INTERFACE_POWER_D0 0x0002
#define USB_FEATURE_INTERFACE_POWER_D1 0x0003
#define USB_FEATURE_INTERFACE_POWER_D2 0x0004
#define USB_FEATURE_INTERFACE_POWER_D3 0x0005

#define USB_SUPPORT_D0_COMMAND 0x01
#define USB_SUPPORT_D1_COMMAND 0x02
#define USB_SUPPORT_D2_COMMAND 0x04
#define USB_SUPPORT_D3_COMMAND 0x08
#define USB_SUPPORT_D1_WAKEUP 0x10
#define USB_SUPPORT_D2_WAKEUP 0x20

typedef struct _USB_CONFIGURATION_POWER_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR SelfPowerConsumedD0[3];
  UCHAR bPowerSummaryId;
  UCHAR bBusPowerSavingD1;
  UCHAR bSelfPowerSavingD1;
  UCHAR bBusPowerSavingD2;
  UCHAR bSelfPowerSavingD2;
  UCHAR bBusPowerSavingD3;
  UCHAR bSelfPowerSavingD3;
  USHORT TransitionTimeFromD1;
  USHORT TransitionTimeFromD2;
  USHORT TransitionTimeFromD3;
} USB_CONFIGURATION_POWER_DESCRIPTOR,*PUSB_CONFIGURATION_POWER_DESCRIPTOR;

typedef struct _USB_INTERFACE_POWER_DESCRIPTOR {
  UCHAR bLength;
  UCHAR bDescriptorType;
  UCHAR bmCapabilitiesFlags;
  UCHAR bBusPowerSavingD1;
  UCHAR bSelfPowerSavingD1;
  UCHAR bBusPowerSavingD2;
  UCHAR bSelfPowerSavingD2;
  UCHAR bBusPowerSavingD3;
  UCHAR bSelfPowerSavingD3;
  USHORT TransitionTimeFromD1;
  USHORT TransitionTimeFromD2;
  USHORT TransitionTimeFromD3;
} USB_INTERFACE_POWER_DESCRIPTOR,*PUSB_INTERFACE_POWER_DESCRIPTOR;

#include <poppack.h>

#endif
#endif
