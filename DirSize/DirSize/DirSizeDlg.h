/*  OpenWQSG - DirSize
*  Copyright (C) WQSG <wqsg@qq.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/

// DirSizeDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <vector>

struct SItemInfo
{
	TCHAR m_szName[MAX_PATH];
	bool m_bDir;

	LONGLONG m_nSize;

	size_t m_Index;

	friend bool operator<( _In_ const SItemInfo& str1, _In_ const SItemInfo& str2 )
	{
		return str1.m_nSize < str2.m_nSize;
	}
	friend bool operator>( _In_ const SItemInfo& str1, _In_ const SItemInfo& str2 )
	{
		return str1.m_nSize > str2.m_nSize;
	}
};

typedef std::vector<SItemInfo> TItemInfos;
struct SDirNode
{
	TItemInfos m_Infos;
	LONGLONG m_AllSize;

	SDirNode()
		: m_AllSize(0)
	{
	}
};

struct SPathNode
{
	size_t m_Index;
	CString m_strName;
};

typedef std::vector<SDirNode> TDirs;
// CDirSizeDlg 对话框
class CDirSizeDlg : public CDialog
{
	TDirs m_Dirs;
	std::vector<SPathNode> m_Path;
	CString m_strBasePath;
	CString m_strFullPath;
// 构造
public:
	CDirSizeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIRSIZE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();
private:
	CImageList m_imageList;
	//CListCtrl m_cList;
	CString m_LastSelDir;

	CWQSGList m_WList;

	BOOL Find( CString a_strPath , const size_t a_DirIndex );
	BOOL Open( CString a_strPath );
	void Clear();

	void UpdateUI();
public:
	afx_msg void OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDirUp();
	afx_msg void OnFileOpenDir();
};
