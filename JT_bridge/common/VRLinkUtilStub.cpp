/*********************************************************************
** VR-Link Utility Stub Implementation
** This file provides implementations for DtWarn and DtInfo
** if they are not available in the linked libraries.
*********************************************************************/
#if DtHLA

#include <vlutil/vlprint.h>
#include <vlutil/vlPrintUtil.h>

// DtOutputStream 构造函数签名：
// DtOutputStream(DtOutputStreamBuffer *b, int &globalThresholdRef, 
//                int threshold = 1, DtPrinter *dflt_printer = 0)

// 创建全局阈值变量（用于控制输出级别）
// 注意：构造函数需要引用，所以必须是全局变量
int g_warnThresholdRef = 1;
int g_infoThresholdRef = 1;

// 创建 DtOutputStreamBuffer 对象（DtOutputStream 需要这些）
// 这些必须在 DtOutputStream 之前创建
DtOutputStreamBuffer g_warnBuffer;
DtOutputStreamBuffer g_infoBuffer;

// 创建默认打印机
DtStderrPrinter g_warnPrinter;
DtStdoutPrinter g_infoPrinter;

// 定义全局对象
// 注意：如果库中已有定义，链接器会报重复定义错误
// 这种情况下，需要注释掉这些定义，并确保正确链接库
DtOutputStream DtWarn(&g_warnBuffer, g_warnThresholdRef, 1, &g_warnPrinter);
DtOutputStream DtInfo(&g_infoBuffer, g_infoThresholdRef, 1, &g_infoPrinter);

#endif // DtHLA

