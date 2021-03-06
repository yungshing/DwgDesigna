#ifndef CPPADAPTER_CPPADAPTER_H
#define CPPADAPTER_CPPADAPTER_H

#ifdef __cplusplus
#define EXTERN_C extern "C"
#define NAMESPACE_GLAWAY_START namespace glaway{
#define NAMESPACE_GLAWAY_END }
#else
#define EXTERN_C 
#define NAMESPACE_GLAWAY_START
#define NAMESPACE_GLAWAY_END
#endif

#ifdef CPPADAPTER_EXPORTS
#define CPPADAPTER_API EXTERN_C __declspec(dllexport)
#else
#define CPPADAPTER_API EXTERN_C __declspec(dllimport)
#endif

#endif

NAMESPACE_GLAWAY_START
/**
 * \brief 电缆批量匹配
 * \param[in] exist_cables 已完成图形生成的电缆信息
 * \param[out] cable_excel 电缆信息文件（excel)的位置
 * \return NO_ERROR 成功完成电缆批量物料匹配
 *
 */
CPPADAPTER_API DWORD BatchCableDesign(HWND parent, const wchar_t *exist_cables, wchar_t cable_excel[MAX_PATH]);
/**
 * \brief 电缆批量匹配
 * \param[in] cable_dir 批量适配后输出excel文档存放目录
 * \return NO_ERROR 成功完成电缆设计
 *
 */
//CPPADAPTER_API DWORD BatchCableDesign(HWND parent, const wchar_t *excel_dir);
/**
 * \brief 单根射频电缆设计
 * \param[out] cable_excel 电缆信息文件（excel)的位置
 * \return NO_ERROR 成功完成电缆设计，电缆信息文件存放在cable_excel指定的路径中
 *         
 */
CPPADAPTER_API DWORD SingleCableDesign(HWND parent, wchar_t cable_excel[MAX_PATH]);

/**
 * \brief 集束射频电缆设计
 * \param[out] cable_excel 电缆信息文件（excel)的位置
 * \return NO_ERROR 成功完成电缆设计，电缆信息文件存放在cable_excel指定的路径中
 *
 */
CPPADAPTER_API DWORD MultipleCableDesign(HWND parent, wchar_t cable_excel[MAX_PATH]);

/**
 * \brief 分叉低频电缆设计
 * \param[out] cable_excel 信息文件（excel)的位置
 * \return NO_ERROR 成功完成电缆设计，电缆信息文件存放在cable_excel指定的路径中
 *
 */
CPPADAPTER_API DWORD LowFrequencyBranchCableDesign(HWND parent, wchar_t cable_excel[MAX_PATH]);

/**
 * \brief 不分叉低频电缆设计
 * \param[out] cable_excel 电缆信息文件（excel)的位置
 * \return NO_ERROR 成功完成电缆设计，电缆信息文件存放在cable_excel指定的路径中
 *
 */
CPPADAPTER_API DWORD LowFrequencyCableDesign(HWND parent, wchar_t cable_excel[MAX_PATH]);

NAMESPACE_GLAWAY_END


